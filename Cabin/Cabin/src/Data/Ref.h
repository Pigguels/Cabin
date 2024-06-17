#pragma once
#include <malloc.h>

/*
Summary:
A basic ref counted pointer wrapper.
tracks how many refs it has and will clean itself up upon loosing all refs.
*/
template <typename T>
class Ref
{
public:
	Ref() : ref(nullptr) {}
	Ref(const Ref& that)
	{
		ref = that.ref;
		AddRef();
	}
	~Ref()
	{
		DecRef();
		ref = nullptr;
	}

	inline T* operator->() const { return GetRef(); }

	bool operator=(const Ref& that)
	{
		if (ref == that.ref)
			return false;

		DecRef();

		ref = that.ref;

		AddRef();

		return true;
	}

	inline bool operator==(const Ref& that) const { return ref == that.ref; }
	inline bool operator!=(const Ref& that) const { return !(*this == that); }

	/*
	Summary:
	Creates a new reference for this Ref
	*/
	T* Create()
	{
		DecRef();

		ref = malloc(sizeof(int*) + sizeof(T));
		*(int*)ref = 1;

		T* tRef = new((int*)ref + 1) T();
		return tRef;
	}

	/*
	Summary:
	Adds to the reference count of this Ref.
	[Note: make sure you know what youre doing before manually altering the reference count]
	*/
	int AddRef()
	{
		return Valid() ? ++*(int*)ref : -1;
	}

	/*
	Summary:
	Decrements the reference count of this Ref, if it reaches zero the reference is cleaned up.
	[Note: make sure you know what youre doing before manually altering the reference count]
	*/
	int DecRef()
	{
		if (!Valid())
			return -1;

		if (--*(int*)ref < 1)
		{
			((T*)((int*)ref + 1))->~T();
			free(ref);
			ref = nullptr;
			return -1;
		}
		return *(int*)ref;
	}

	/*
	Summary:
	Returns if this Ref has a valid reference.
	*/
	inline bool Valid() const { return ref; }

	/*
	Summary:
	Returns this Refs current reference count or -1 if there is no current reference.
	*/
	inline int GetRefCount() const { return Valid() ? *(int*)ref : -1; }

	/*
	Summary:
	Returns this Refs current reference o nullptr if there is no current reference.
	*/
	inline T* GetRef() const { return Valid() ? (T*)((int*)ref + 1) : nullptr; }

private:
	void* ref = nullptr;
};
