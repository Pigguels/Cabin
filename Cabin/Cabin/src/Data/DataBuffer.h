#pragma once
#include "Core/Debug.h"
#include "Data/BitFunctions.h"
#include <malloc.h>

/*
Summary:
The DataBuffer class, allows easy reading and writing of a memory buffer.
Setting the growth to less than zero will make the buffer double in size,
above zero will grow by that amount, and zero with disable the growth all together.
*/
class DataBuffer
{
public:
	enum SeekMode
	{
		Front,
		Current,
		End,
	};

	DataBuffer()
	{
		Init(0, -1);
	}
	DataBuffer(int _size, int _growth = -1)
	{
		Init(_size, _growth);
	}
	DataBuffer(const DataBuffer& that) = delete;
	~DataBuffer()
	{
		_ClearData();
	}
	void operator=(const DataBuffer& that) = delete;

	void Clear()
	{
		_ClearData();
		size = 0;
		growth = 0;
		current = 0;
	}

	void Init(int _size, int _growth)
	{
		_ClearData();
		size = _size;
		growth = _growth;
		current = 0;
		_Resize(size);
	}

	/*
	Summary:
	Transfers the contents of this DataBuffer into the given DataBuffer.
	Any contents of the given DataBuffer are cleaned up.
	*/
	void GiveOwnership(DataBuffer& that)
	{
		ASSERT_MSG(data != that.data, "Trying to transfer a DataBuffer to itself.");

		that._ClearData();
		that.size = size;
		that.growth = growth;
		that.current = current;
		that.data = data;

		data = nullptr;
		Clear();
	}
	/*
	Summary:
	Transfers the contents of the given DataBuffer into this DataBuffer.
	Any contents of this DataBuffer are cleaned up.
	*/
	void TakeOwnership(DataBuffer& that) { that.GiveOwnership(*this); }

	/*
	Summary:
	Swaps all the values in this DataBuffer with the given DataBuffer.
	*/
	void Swap(DataBuffer& that)
	{
		ASSERT_MSG(data != that.data, "Trying to swap a DataBuffer to itself.");

		SWAP(size, that.size);
		SWAP(growth, that.growth);
		SWAP(current, that.current);

		void* tmp = data;
		data = that.data;
		that.data = tmp;
	}

	DataBuffer& Seek(int offset, SeekMode seekMode)
	{
		if (seekMode == SeekMode::Front) current = offset;
		else if (seekMode == SeekMode::Current) current += offset;
		else if (seekMode == SeekMode::End) current = size - offset - 1;
		return *this;
	}

	DataBuffer& Read(void* dst, int amount)
	{
		ASSERT_MSG(current + amount < size, "Trying to read over the edge of a DataBuffer.");
		memcpy(dst, _GetAt(current), amount);
		current += amount;
		return *this;
	}
	template <typename T> DataBuffer& Read(T& dst)
	{
		return Read((void*)*dst, sizeof(T));
	}
	template <typename T> DataBuffer& operator>>(T& dst)
	{
		return Read((void*)&dst, sizeof(T));
	}

	DataBuffer& Write(void* src, int amount)
	{
		if (current + amount >= size)
		{
			ASSERT_MSG(growth != 0, "Trying to write to a full databuffer.");
			_Resize(size == 0 ? amount : _GetNextSize(amount));
		}
		memcpy(_GetAt(current), src, amount);
		current += amount;
		return *this;
	}
	template <typename T> DataBuffer& Write(const T& src)
	{
		return Write((void*)*src, sizeof(T));
	}
	template <typename T> DataBuffer& operator<<(const T& src)
	{
		return Write((void*)&src, sizeof(T));
	}

	int GetSize() const { return size; }
	int GetCurrent() const { return current; }
	void* GetData() const { return data; }

private:
	char* _GetAt(int index) const { return (char*)data + index; }

	int _GetNextSize(int amount) const
	{
		int targetSize = size + amount;
		int nextSize = size;
		if (growth < 0) while ((nextSize *= 2) < targetSize);
		else while ((nextSize += growth) < targetSize);
		return nextSize;
	}

	void _ClearData()
	{
		if (data)
		{
			free(data);
			data = nullptr;
		}
	}

	void _Resize(int newSize)
	{
		void* newData = nullptr;
		if (newSize > 0)
		{
			newData = malloc(newSize);

			if (current > 0)
				memcpy(newData, data, current < newSize ? current : newSize);
		}

		if (data) free(data);
		data = newData;
		size = newSize;
	}

	int size = 0;
	int growth = 0;
	int current = 0;
	void* data = nullptr;
};
