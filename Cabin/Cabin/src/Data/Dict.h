#pragma once
#include "Core/Debug.h"
#include <malloc.h>
#include "Data/HashFunctions.h"
#include "Data/String.h"
#include "Data/Pair.h"

namespace Internal
{
	/*
	Summary:
	Basic inline memory iterator for a dictionary
	*/
	template <typename DictType, typename ItemType>
	class DictIterator
	{
	public:
		DictIterator(const DictType* _dict, ItemType* _item) : dict(_dict)
		{
			item = _item;

			// check that the curent iterator is valid, if not try find a valid spot
			if ((item - (ItemType*)dict->items < dict->capacity) && DictType::KeyHash::CompareKey(item->key, dict->GetNullKey()))
				++*this;
		}
		ItemType& operator*() { return *item; }
		ItemType* operator->() { return item; }
	
		DictIterator& operator++()
		{
			ASSERT_MSG(dict, "Attempting to increment a Dict::Iterator that does not have an owner Dict.");
			while ((++item - (ItemType*)dict->items < dict->capacity) && DictType::KeyHash::CompareKey(item->key, dict->GetNullKey()));
			return *this;
		}
		DictIterator operator++(int)
		{
			DictIterator temp = DictIterator(dict, item);
			++(*this);
			return temp;
		}

		bool operator==(const DictIterator& that)
		{
			return dict == that.dict && item == that.item;
		}
		bool operator!=(const DictIterator& that)
		{
			return !(*this == that);
		}
	
		const DictType* dict;
		ItemType* item;
	};
}

/*
Summary:
A dynamic and fixed dictionary class, maps values to keys for use with lookups.
Has the ability to add, remove, lookup, and check for keyvalues.
Setting the growth to less than zero will make the dictionary double in size,
above zero will grow by that amount, and zero with disable the growth all together.
*/
template <typename Key, typename Value>
class Dict
{
public:
	class KeyValue
	{
	public:
		KeyValue() : key(), value() {}
		KeyValue(const Key& _key) : key(_key), value() {}
		KeyValue(const Key& _key, const Value& _value) : key(_key), value(_value) {}
		Key key;
		Value value;
	};

	using KeyHash = HashFunctions::HashKey<Key>;
	using Iterator = Internal::DictIterator<Dict<Key, Value>, KeyValue>;
	friend Iterator;

	Dict()
	{
		Init(0, -1, KeyHash::GetNullKey());
	}
	Dict(int _capacity, int _growth = -1)
	{
		Init(_capacity, _growth, KeyHash::GetNullKey());
	}
	Dict(int _capacity, const Key& nullKey)
	{
		Init(_capacity, -1, nullKey);
	}
	Dict(int _capacity, int _growth, const Key& nullKey)
	{
		Init(_capacity, _growth, nullKey);
	}
	Dict(const Dict& that) = delete;
	~Dict()
	{
		_ClearData();
	}

	void operator=(const Dict& that) = delete;

	/*
	Summary:
	Returns the item with the given key.
	[Note: This will assert if there is no item with a matching key]
	*/
	Value& operator[](const Key& key) const
	{
		bool keyInUse;
		int keyIndex = _GetIndexForKey(items, capacity, key, keyInUse);
		
		ASSERT_MSG(keyInUse, "Dict key not in use");
		
		return _GetAt(keyIndex)->value;
	}

	/*
	Summary:
	Attempts to return a pointer to the value at the given key.
	Returns nullptr if there is no value with the given key.
	*/
	Value* TryGet(const Key& key) const
	{
		bool keyInUse;
		int keyIndex = _GetIndexForKey(items, capacity, key, keyInUse);
		return keyInUse ? &(_GetAt(keyIndex)->value) : nullptr;
	}
	bool TryGet(const Key& key, Value& out) const
	{
		bool keyInUse;
		int keyIndex = _GetIndexForKey(items, capacity, key, keyInUse);
		if (keyInUse) out = _GetAt(keyIndex)->value;
		return keyInUse;
	}

	/*
	Summary:
	Initialises the dictionary with the given count and null string.
	Setting the growth to less than zero will make the dictionary double in size,
	above zero will grow by that amount, and zero with disable the growth all together.
	*/
	void Init(const int _capacity, const int _growth, const Key& _nullKey)
	{
		_ClearData();
		growth = _growth;
		capacity = _capacity;
		nullKey = nullKey;
		_Resize(capacity);
	}

	/*
	Summary:
	Clears all items in the dictionary aswell as resets the dictionary.
	*/
	void Clear()
	{
		growth = 0;
		capacity = 0;
		nullKey = Key();
		_ClearData();
	}

	/*
	Summary:
	Copies the contents of this Stack into the given Stack.
	*/
	void CopyInto(Dict& that) const
	{
		that.Init(count, growth, nullKey);
		for (const KeyValue& kv : *this)
			that.Add(kv.key, kv.value);
	}

	/*
	Summary:
	Copies the contents from the given Stack into this Stack.
	*/
	void CopyFrom(const Dict& that)
	{
		that.CopyInto(*this);
	}

	/*
	Summary:
	Adds an item to the dictionary with the given string key.
	Returns true if the item was added, and false if not.
	Cases where adding an item would fail is: if there was an existing item already with the given string key,
	or if there is no room to add the item
	*/
	bool Add(const Key key, const Value& item)
	{
		ASSERT_MSG(!_IsNullKey(key), "Dict cannot add item with the null key.");

		if (count >= capacity)
		{
			ASSERT_MSG(growth != 0, "Dict::Add called on a full dictionary.");
			_Resize(capacity == 0 ? 4 : _GetNextSize());
		}

		if (count < capacity && _Add(items, capacity, key, item))
		{
			++count;
			return true;
		}
		return false;
	}

	/*
	Summary:
	Removes an item with the given key.
	Returns true if an item was removed.
	*/
	bool Remove(const Key key)
	{
		ASSERT_MSG(KeyHash::GetHash(key) != KeyHash::GetHash(nullKey), "Dict cannot remove item with the nullKey.");

		bool keyInUse;
		int currIndex = _GetIndexForKey(items, capacity, key, keyInUse);

		if (keyInUse)
		{
			KeyValue* current = _GetAt(currIndex);
			current->key = nullKey;
			current->value.~Value();

			for (;;)
			{
				int nextIndex = _SoftWrap(currIndex + 1, capacity);

				while (!_IsNullKey(_GetAt(nextIndex)->key))
				{
					int currProbe = _GetProbeIndex(capacity, _GetAt(nextIndex)->key);

					if ((currProbe <= currIndex && currIndex < nextIndex) ||
						(currIndex < nextIndex && nextIndex < currProbe) ||
						(currProbe <= currIndex && nextIndex < currProbe))
						break;

					nextIndex = _SoftWrap(nextIndex + 1, capacity);
				}

				/* on a free spot, patching done */
				if (_IsNullKey(_GetAt(nextIndex)->key)) break;

				/* shuffle the items back, not ideal to use a temp */
				KeyValue* toMove = (KeyValue*)items + nextIndex;
				memcpy(current, toMove, sizeof(KeyValue));
				new(toMove) KeyValue(nullKey);

				currIndex = nextIndex;
			}

			_GetAt(currIndex)->key = nullKey;

			--count;

			return true;
		}
		return false;
	}

	Iterator begin() const { return { this, _GetAt(0) }; }
	Iterator end() const { return { this, _GetAt(capacity) }; }

	/*
	Summary:
	Returns the capacity of this Dict.
	*/
	int Capacity() const { return capacity; }
	/*
	Summary:
	Returns the current count of this Dict.
	*/
	int Count() const { return count; }
	/*
	Summary:
	Returns the NullKey for of this Dict.
	*/
	const Key& GetNullKey() const { return nullKey; }

private:

	inline int _SoftWrap(int n, int max) const { return n >= max ? 0 : n; }
	inline int _GetNextSize() const { return growth < 0 ? capacity * 2 : capacity + growth; }
	inline int _GetProbeIndex(int _capacity, const Key& key) const { return KeyHash::GetHash(key) % _capacity; }
	inline KeyValue* _GetAt(int index) const { return ((KeyValue*)items + index); }
	inline bool _IsNullKey(const Key& key) const { return KeyHash::CompareKey(key, nullKey); }

	void _ClearData()
	{
		if (items)
		{
			free(items);
			items = nullptr;
		}
	}

	void _Resize(int newCapacity)
	{
		void* newItems = nullptr;

		if (newCapacity > 0)
		{
			newItems = malloc(sizeof(KeyValue) * newCapacity);

			for (int i = 0; i < newCapacity; ++i)
				new((KeyValue*)newItems + i) KeyValue(nullKey);

			if (count > 0)
			{
				for (Iterator it = begin(); it != end(); it++)
					_Add(newItems, newCapacity, it->key, it->value);
			}
		}

		if (items) free(items);
		items = newItems;

		capacity = newCapacity;
	}

	// Returns - 1 if there is no available positions
	int _GetIndexForKey(const void* _items, int _capacity, const Key& key, bool& keyInUse) const
	{
		if (_capacity != 0)
		{
			int probeIndex = _GetProbeIndex(_capacity, key);
			bool wrapped = false;
			for (int i = probeIndex; !wrapped || i < probeIndex; i++)
			{
				// soft wrap the search index
				if (i >= _capacity)
				{
					i -= _capacity;
					wrapped = true;
				}

				const Key& currentKey = ((KeyValue*)_items + i)->key;
				if (_IsNullKey(currentKey))
				{
					keyInUse = false;
					return i;
				}
				else if (KeyHash::CompareKey(currentKey, key))
				{
					keyInUse = true;
					return i;
				}
			}
		}
		keyInUse = false;
		return -1;
	}

	/*
	Summary:
	Adds a value at the given key to a given item array.
	Returns true if the item was added, and false if not.
	Cases where an item wouldnt be added is:
	- there isnt enough space
	- value with the given key is already in use.
	*/
	bool _Add(void* _items, int _capacity, const Key& key, const Value& item)
	{
		bool keyInUse = false;
		int keyIndex = _GetIndexForKey(_items, _capacity, key, keyInUse);

		if (!keyInUse && keyIndex != -1)
		{
			new((KeyValue*)_items + keyIndex) KeyValue(key, item);
			return true;
		}
		return false;
	}

	int growth = 0;
	int capacity = 0;
	int count = 0;
	Key nullKey;
	void* items = nullptr;
};
