#pragma once
#include "Core/Debug.h"
#include "Data/StringFunctions.h"
#include "Data/String.h"

class StringBuilder
{
public:
	StringBuilder()
	{
		Init(4, -1);
	}
	StringBuilder(int _capacity, int _growth = -1)
	{
		Init(_capacity, _growth);
	}
	~StringBuilder()
	{
		_ClearData();
	}

	void Empty()
	{
		top = 0;
		_AppendNullTerminator();
	}

	void Init(int _capacity, int _growth = -1)
	{
		_ClearData();
		capacity = _capacity > 0 ? _capacity : 4;
		growth = _growth;
		top = 0;
		_Resize(capacity);
		_AppendNullTerminator();
	}

	// ========================================================================================================================

	StringBuilder& Insert(const char* str, int index, int length)
	{
		ASSERT_MSG(index >= 0 && index <= top, "StringBuilder Insert index out of range.");

		if (top + length >= capacity)
		{
			ASSERT_MSG(growth != 0, "Trying to Insert into a full StringBuilder.");
			_Resize(_GetNextSize(top + length));
		}

		memcpy(_GetAt(index + length), _GetAt(index), sizeof(char) * (top - index) + 1);
		memcpy(_GetAt(index), str, sizeof(char) * length);

		top += length;
		_AppendNullTerminator();
		return *this;
	}
	StringBuilder& Insert(const char* str, int index) { return Insert(str, index, StringFunctions::Length(str) - 1); }
	StringBuilder& Insert(const char c, int index) { return Insert(&c, index, 1); }
	StringBuilder& Insert(StringBuilder& sb, int index) { return Insert(sb.c_str(), index, sb.Length() - 1); }
	StringBuilder& Insert(String& str, int index) { return Insert(str.c_str(), index, str.Length() - 1); }

	StringBuilder& Prepend(const char* str, int length) { return Insert(str, 0, length); }
	StringBuilder& Prepend(const char* str) { return Insert(str, 0); }
	StringBuilder& Prepend(const char c) { return Insert(&c, 0, 1); }
	StringBuilder& Prepend(StringBuilder& sb) { return Insert(sb.c_str(), 0, sb.Length() - 1); }
	StringBuilder& Prepend(String& str) { return Insert(str.c_str(), 0, str.Length() - 1); }

	StringBuilder& Append(const char* str, int length)
	{
		if (top + length >= capacity)
		{
			ASSERT_MSG(growth != 0, "Trying to Append onto a full StringBuilder.");
			_Resize(capacity == 0 ? length + 1 : _GetNextSize(top + length));
		}
		memcpy(_GetAt(top), str, length);
		top += length;
		_AppendNullTerminator();
		return *this;
	}
	StringBuilder& Append(const char* str) { return Append(str, StringFunctions::Length(str) - 1); }
	StringBuilder& Append(const char c) { return Append(&c, 1); }
	StringBuilder& Append(StringBuilder& sb) { return Append(sb.c_str(), sb.Length() - 1); }
	StringBuilder& Append(String& str) { return Append(str.c_str(), str.Length() - 1); }

	StringBuilder& operator<<(const char* str) { return Append(str); }
	StringBuilder& operator<<(const char c) { return Append(c); }
	StringBuilder& operator<<(StringBuilder& sb) { return Append(sb.c_str()); }
	StringBuilder& operator<<(String& str) { return Append(str.c_str()); }

	int Length() const { return top + 1; }
	int Capacity() const { return capacity; }
	const char* c_str() const { return (const char*)data; }
	String ToString() const { return c_str(); }

private:
	inline char* _GetAt(int index) const { return (char*)data + index; }

	inline int _GetNextSize() const { return growth < 0 ? capacity * 2 : capacity + growth; }
	int _GetNextSize(int amountToAdd) const
	{
		int target = top + amountToAdd;
		int newCapacity = capacity > 0 ? capacity : 4;
		if (growth < 0) while ((newCapacity *= 2) < target);
		else while ((newCapacity += growth) < target);
		return newCapacity;
	}

	void _AppendChar(char c)
	{
		if (top >= capacity)
		{
			ASSERT_MSG(growth != 0, "Trying to add to a StringBuilder that is full.");
			_Resize(capacity == 0 ? 4 : _GetNextSize());
		}
		*_GetAt(top++) = c;
	}
	inline void _AppendNullTerminator() { *_GetAt(top) = '\0'; }

	void _ClearData()
	{
		if (data)
		{
			free(data);
			data = nullptr;
		}
	}

	void _Resize(int newCapacity)
	{
		void* newData = nullptr;
		if (newCapacity > 0)
		{
			newData = malloc(sizeof(char) * newCapacity);
			if (top > 0)
				memcpy(newData, data, (top < newCapacity ? top : newCapacity));
		}

		if (data) free(data);
		data = newData;
		capacity = newCapacity;
	}

	int capacity = 0;
	int growth = 0;
	int top = 0;
	void* data = nullptr;
};
