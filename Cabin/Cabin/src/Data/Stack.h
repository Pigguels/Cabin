#pragma once
#include "Core/Debug.h"
#include "Data/BitFunctions.h"

/*
Summary:
The Stack class, allow the user to create a dynamic stack of items.
The user can specify the base size of the stack and can specify the growth of the Stack.

Growth rules:
- If growth is set to zero the Stack will be a fixed size.
- If growth is a positive number the Stack will increase in size by the amount of growth.
- If growth is a negative number the Stack will double its current size.

[Note: The Stack will not auto shrink itself]
*/
template <class T>
class Stack
{
public:
	using Iterator = T*;

	Stack()
	{
		Init(0, -1);
	}
	Stack(int _capacity, int _growth = -1)
	{
		Init(_capacity, _growth);
	}
	Stack(std::initializer_list<T> l)
	{
		Init(l);
	}
	Stack(const Stack& that) = delete;
	~Stack()
	{
		_ClearData();
	}

	void operator=(const Stack& index) = delete;

	T& operator[](unsigned int index) const { return Get(index); }

	/* Enable enum classes to be used for an index */
	template <typename E> T& operator[](const E& enumeration) const
	{
		int index = static_cast<typename std::underlying_type<E>::type>(enumeration);
		return Get(index);
	}

	/*
	Summary:
	Returns the item at the given index of this Stack.
	*/
	T& Get(unsigned int index) const
	{
		ASSERT_MSG(index >= 0 && index < top, "Stack::At index out of range.");
		return *_GetAt(index);
	}

	/*
	Summary:
	Tries to access the item at the given index.
	Returns a pointer to the item if it exists, otherwise nullptr is returned.
	*/
	T* TryGet(unsigned int index) const { return (index >= 0 && index < top) ? _GetAt(index) : nullptr; }

	/*
	Summary:
	Returns the index of the given item in the Stack, in cases where the Stack does not contain the item -1 is returned.
	*/
	int IndexOf(const T& item) const
	{
		for (int i = 0; i < top; i++)
		{
			if (*_GetAt(i) == item)
				return i;
		}
		return -1;
	}

	/*
	Summary:
	Returns true if this Stack contains the given item.
	*/
	bool Contains(const T& item) const
	{
		return IndexOf(item) != -1;
	}

	/*
	Summary:
	Clears, cleans up and resets the Stack.
	*/
	void Clear()
	{
		_ClearData();
		capacity = 0;
		growth = 0;
		top = 0;
	}

	/*
	Summary:
	Initialises the Stack with the given capacity and growth.
	[Note: Calling this will clean up the current Stack before recreation]
	*/
	void Init(int _capacity, int _growth)
	{
		_ClearData();
		capacity = _capacity;
		growth = _growth;
		top = 0;
		_Resize(capacity);
	}

	/*
	Summary:
	Initialises the Stack with an initialiser list.
	[Note: Calling this will clean up the current Stack before recreation]
	*/
	void Init(std::initializer_list<T> l)
	{
		Init(l.size(), -1);
		for (const T* it = l.begin(); it != l.end(); ++it) Add(*it);
	}

	/*
	Summary:
	Transfers the contents of this Stack into the given Stack.
	Any contents of the given Stack are cleaned up.
	*/
	void GiveOwnership(Stack& that)
	{
		that._ClearData();
		that.data = data;
		that.capacity = capacity;
		that.growth = growth;
		that.top = top;

		data = nullptr;
		Clear();
	}
	/*
	Summary:
	Transfers the contents of the given Stack into this Stack.
	Any contents of this Stack are cleaned up.
	*/
	void TakeOwnership(Stack& that) { that.GiveOwnership(*this); }

	/*
	Summary:
	Swaps the contents of this Stack with the contents of the given Stack, and viceversa.
	*/
	void Swap(Stack& that)
	{
		ASSERT_MSG(data != that.data, "Trying to swap a Stack to itself.");
		SWAP(capacity, that.capacity);
		SWAP(growth, that.growth);
		SWAP(top, that.top);

		void* tmp = data;
		data = that.data;
		that.data = tmp;
	}

	/*
	Summary:
	Copies the contents of this Stack into the given Stack.
	*/
	void CopyInto(Stack& that) const
	{
		that.Init(top, growth);
		for (const T& item : *this)
			that.Add(item);
	}
	/*
	Summary:
	Copies the contents from the given Stack into this Stack.
	*/
	void CopyFrom(const Stack& that)
	{
		that.CopyInto(*this);
	}

	/*
	Summary:
	Adds an item onto the end of the Stack.
	*/
	void Add(const T& item)
	{
		if (top == capacity)
		{
			ASSERT_MSG(growth != 0, "Stack::Add called on a stack that is full.");
			_Resize(capacity == 0 ? 4 : _GetNextSize());
		}
		new(_GetAt(top++)) T(item);
	}

	/*
	Summary:
	Adds an item into the Stack at the given index.
	*/
	void AddAt(const T& item, int index)
	{
		ASSERT_MSG(index >= 0 && index <= top, "Stack::AddAt index out of range.");

		if (top == capacity)
		{
			ASSERT_MSG(growth != 0, "Stack::AddAt called on a stack that is full.");

			_Resize(capacity == 0 ? 4 : _GetNextSize());
			// not the most efficient as it will need to memcpy the entire buffer then shift the items that are past the index,
			// rather than just copying them already shifted
			// however this is more readable as is for the moment
		}

		memmove(_GetAt(index + 1), _GetAt(index), sizeof(T) * (top++ - index));

		T* addedItem = new(_GetAt(index)) T();
		*addedItem = item;
	}
	/*
	Summary:
	Adds a new item onto the end of the Stack.
	*/
	T& AddNew()
	{
		if (top == capacity)
		{
			ASSERT_MSG(growth != 0, "Stack::AddNew called on a stack that is full.");
			_Resize(capacity == 0 ? 4 : _GetNextSize());
		}
		return *(new(_GetAt(top++)) T());
	}
	/*
	Summary:
	Adds the given amount of new items onto the end of the Stack.
	*/
	void Reserve(int reserveAmount)
	{
		if (top + reserveAmount >= capacity)
		{
			ASSERT_MSG(growth != 0, "Stack::Reserve called on a stack that is either full or cannot contain the reserve amount.");
			_Resize(_GetNextSize(top + reserveAmount));
		}
		while (reserveAmount-- > 0) new(_GetAt(top++)) T();
	}

	/*
	Summary:
	Pops (removes) an item from the top of the Stack.
	Returns true if an item was removed.
	*/
	bool Pop()
	{
		if (top == 0) return false;

		_GetAt(--top)->~T();

		return true;
	}

	/*
	Summary:
	Removes an item at the given index.
	Returns true if an item was removed.
	*/
	bool RemoveAt(int index)
	{
		ASSERT_MSG(index >= 0 && index <= top, "Stack::RemoveAt index out of range.");

		if (top == 0) return false;

		_GetAt(index)->~T();

		memmove(_GetAt(index), _GetAt(index + 1), sizeof(T) * ((top--) - index));

		return true;
	}

	/*
	Summary:
	Removes the given item from the Stack.
	Returns true if an item was removed.
	*/
	bool Remove(const T& item)
	{
		for (int i = 0; i < top; ++i)
		{
			if (*_GetAt(i) == item) return RemoveAt(i);
		}
		return false;
	}

	Iterator begin() const { return data ? _GetAt(0) : nullptr; }
	Iterator end() const { return data ? _GetAt(top) : nullptr; }

	int Capacity() const { return capacity; }
	int Count() const { return top; }
	int EmptyCount() const { return capacity - top; }
	int Growth() const { return growth; }

private:
	int _GetNextSize() const { return growth < 0 ? capacity * 2 : capacity + growth; }
	int _GetNextSize(int amountToAdd) const
	{
		int target = top + amountToAdd;
		int newCapacity = capacity > 0 ? capacity : 4;
		if (growth < 0) while ((newCapacity *= 2) < target);
		else while ((newCapacity += growth) < target);
		return newCapacity;
	}

	void _ClearData()
	{
		if (data)
		{
			for (T* curr = _GetAt(0); curr < _GetAt(top); curr++)
				curr->~T();

			free(data);
			data = nullptr;
		}
	}

	void _Resize(int newCapacity)
	{
		void* newData = nullptr;
		if (newCapacity > 0)
		{
			newData = malloc(sizeof(T) * newCapacity);
			if (capacity > 0)
			{
				memcpy(newData, data, sizeof(T) * (top < newCapacity ? top : newCapacity));
			}
		}

		if (data) free(data);
		data = newData;
		capacity = newCapacity;
	}

	inline T* _GetAt(int index) const
	{
		ASSERT_MSG(data, "Stack::Get cannot be called on an uninitialised Stack.");
		return (T*)data + index;
	}

	int growth = 0;
	int capacity = 0;
	int top = 0;
	void* data = nullptr;
};
