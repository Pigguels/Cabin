#pragma once
#include "Core/Debug.h"

template <class T>
class Array
{
public:
	using Iterator = T*;

	Array()
	{
		Clear();
	}
	Array(int _size)
	{
		Init(_size);
	}
	~Array()
	{
		Clear();
	}

	T& operator[](int index) const
	{
		ASSERT_MSG(index >= 0 && index < size, "Array random lookup index out of range.");
		return *Get(index);
	}

	/* Enable enum classes to be used for an index */
	template <typename E>
	T& operator[](const E& enumeration) const
	{
		int index = static_cast<typename std::underlying_type<E>::type>(enumeration);
		ASSERT_MSG(index >= 0 && index < size, "Array enum index out of range.");
		return *Get(index);
	}

	/*
	Summary:
	Returns the item at the given index of this Array.
	*/
	T& At(int index) const
	{
		ASSERT_MSG(index >= 0 && index < size, "Array::At index out of range.");
		return *Get(index);
	}

	/*
	Summary:
	Returns the index of the given item in the Array, in cases where the Array does not contain the item -1 is returned.
	*/
	int IndexOf(const T& item) const
	{
		for (int i = 0; i < size; i++)
		{
			if (*Get(i) == item)
				return i;
		}
		return -1;
	}

	/*
	Summary:
	Returns true if this Array contains the given item.
	*/
	bool Contains(const T& item) const
	{
		return IndexOf(item) != -1;
	}

	/*
	Summary:
	Clears, cleans up and resets the Array.
	*/
	void Clear()
	{
		if (data)
		{
			for (T* curr = Get(0); curr < Get(size); curr++)
				curr->~T();

			free(data);
			data = nullptr;
		}
		size = 0;
	}

	/*
	Summary:
	Initialises the Array with the given size.
	[Note: Calling this will clean up the current Array before recreation]
	*/
	void Init(int _size)
	{
		Clear();
		size = _size;
		data = malloc(sizeof(T) * _size);

		for (T* curr = Get(0); curr < Get(size); curr++)
			new(curr) T();
	}

	/*
	Summary:
	Resizes the current Array to the given size.
	[Note: Currently stored items are retained, unless the size has shrunk in which case all items truncated are lost]
	*/
	void ResizeTo(int newSize)
	{
		if (newSize <= 0)
		{
			Clear();
		}
		else
		{
			void* newData = malloc(sizeof(T) * newSize);
			if (data)
			{
				memcpy(newData, data, sizeof(T) * Min(size, newSize));
				free(data);
			}
			data = newData;

			for (int i = size; i < newSize; i++)
				new(Get(i)) T();

			size = newSize;
		}
	}

	Iterator begin() const { return { Get(0) }; }
	Iterator end() const { return { Get(size) }; }

	int Count() const { return size; }

private:
	inline int Min(int a, int b) const { return a > b ? b : a; }

	inline T* Get(int index) const
	{
		ASSERT_MSG(data, "Array::Get cannot be called on an uninitialised Array.");
		return (T*)data + index;
	}

	int size = 0;
	void* data = nullptr;
};
