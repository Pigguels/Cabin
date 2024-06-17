#pragma once
#include "Data/Dict.h"

namespace Internal
{
	/*
	Summary:
	A managed reference object.
	Interfaces with a given ReferenceManager object.
	*/
	template <class T, class Manager>
	class ManagedRef
	{
	public:
		ManagedRef() {}
		ManagedRef(Manager* _manager, T* _ref, const String& _handle)
		{
			manager = _manager;
			ref = _ref;
			handle = _handle;
			refs = new int(0);
		}
		ManagedRef(const ManagedRef& that)
		{
			refs = that.refs;
			ref = that.ref;
			handle = that.handle;
			manager = that.manager;
			AddRef();
		}
		~ManagedRef()
		{
			DecRef();
			refs = nullptr;
		}

		T* operator->() const { return Ref(); }
		T& operator*() const { return *Ref(); }

		bool operator==(const ManagedRef& that) const { return refs == that.refs; }
		bool operator!=(const ManagedRef& that) const { return !(*this == that); }
		void operator=(const ManagedRef& that)
		{
			if (*this == that) return;

			DecRef();

			refs = that.refs;
			ref = that.ref;
			handle = that.handle;
			manager = that.manager;

			AddRef();
		}

		int AddRef() { return refs ? ++(*refs) : 0; }
		int DecRef()
		{
			if (!refs) return 0;

			int refCount = --(*refs);
			if (refCount <= 0) manager->_DestroyRef(this);

			return refCount;
		}

		int RefCount() const { return refs ? *refs : 0; }
		T* Ref() const { return refs ? ref : nullptr; }
		String Handle() const { return handle; }

		bool Valid() const { return Ref(); }

	private:
		int* refs = nullptr;
		T* ref = nullptr;
		String handle = String::EMPTY;
		Manager* manager = nullptr;
	};

	/*
	Summary:
	A base manager object for managing ManagedRef objects that maps references to handles, tracks their reference counts,
	and cleans them up when nothing is referencing them anymore.
	*/
	template <class T>
	class RefManager
	{
	public:
		using Ref = ManagedRef<T, RefManager<T>>;
		friend class Ref;

		/*
		Summary:
		Returns the Ref with the corresponding handle.
		In the case of there being no Ref with a matching handle, returns an invalid Ref.
		*/
		virtual Ref Get(const String& handle) const
		{
			Ref* ref = refs.TryGet(handle);
			return ref ? *ref : Ref();
		}

		bool Contains(const String& handle) const { return refs.Contains(handle); }
		bool Count() const { return refs.Count(); }

	protected:
		RefManager() {}
		/*
		Summary:
		Creates a new Ref stored with the given handle.
		Returns the created Ref.
		*/
		Ref _CreateRef(const String& handle)
		{
			Ref* existing = refs.TryGet(handle);
			if (existing) return *existing;

			T* refObj = new T();
			Ref ref = Ref(this, refObj, handle);
			refs.Add(handle, ref);
			//ref.DecRef(); // make sure the reference is only held externally
			return ref;
		}
		virtual void _DestroyRef(Ref* ref)
		{
			T* refObj = ref->Ref();
			refObj->~T();
			delete refObj;
		}
		Dict<String, Ref> refs;
	};
}
