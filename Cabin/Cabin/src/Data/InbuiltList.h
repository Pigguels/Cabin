#pragma once
#include "Core/Debug.h"

namespace Internal
{
	template<class T>
	class InbuiltListIterator
	{
	public:
		InbuiltListIterator() : ptr(nullptr) {}
		InbuiltListIterator(T* _ptr) : ptr(_ptr) {}

		T& operator*() { return *ptr; }
		T* operator->() { return ptr; }

		InbuiltListIterator& operator++()
		{
			ptr = ptr->next;
			return *this;
		}
		InbuiltListIterator operator++(int)
		{
			InbuiltListIterator temp = *this;
			ptr = ptr->next;
			return temp;
		}
		InbuiltListIterator& operator+=(int offset)
		{
			for (int i = 0; i < offset; i++)
				(*this)++;

			return *this;
		}

		T* ptr;
	};

	/*
	Summary:
	A oneway list object that is inbuilt into the items it stores.
	This list is designed purely for internal use of data handling objects.
	[Note: It is upto the user to dispose all items in a list]
	[Note: It is upto the user to make sure an item isnt added twice to a list, as this would cause an internal loop, breaking the list continuum]
	*/
	template <class T>
	class InbuiltList
	{
	public:
		using Iterator = InbuiltListIterator<T>;

		InbuiltList()
		{
			first = nullptr;
		}
		InbuiltList(const InbuiltList& that) = delete;
		~InbuiltList()
		{
			DestructiveClear();
		}

		void operator=(const InbuiltList& that) = delete;

		T& operator[](int index) const
		{
			ASSERT_MSG(index >= 0, "InbuiltList index out of range");
			T* current = first;
			for (int i = 0; i < index; i++)
			{
				current = current->next;
				ASSERT_MSG(current, "InbuiltList index out of range");
			}
			return *current;
		}

		/*
		Summary:
		Removes and deletes all items in the list
		*/
		void DestructiveClear()
		{
			T* toDestroy = first;
			while (toDestroy)
			{
				first = first->next;
				delete toDestroy;
				toDestroy = first;
			}
		}

		/*
		Summary:
		Pushes (adds) an item to the front of the list
		*/
		void PushFront(T* item)
		{
			item->next = first;
			first = item;
		}

		/*
		Summary:
		Pops (removes) and returns the item from the front of the list
		[Note: This function does not delete the popped item]
		*/
		T* PopFront()
		{
			if (first)
			{
				T* toDelete = first;
				first = first->next;
				return toDelete;
			}
			return nullptr;
		}

		/*
		Summary:
		Removes and returns a given item from the list
		[Note: This function does not delete the removed item]
		*/
		T* Remove(T* item)
		{
			T* previous = nullptr;
			T* current = first;
			while (current)
			{
				if (current == item)
				{
					if (previous)
						previous->next = current->next;
					else
						first = first->next;

					break;
				}

				previous = current;
				current = current->next;
			}
			return current;
		}

		/*
		Summary:
		Returns true if this list contains the given item
		*/
		bool Contains(const T& item)
		{
			T* current = first;
			while (current)
			{
				if (current == &item)
					return true;

				current = current->next;
			}
			return false;
		}

		/*
		Summary:
		Returns the total count of items in this list
		[Note: This operation is slow, avoid or cache when possible]
		*/
		int Count() const
		{
			int totalCount = 0;
			T* current = first;
			while (current)
			{
				totalCount++;
				current = current->next;
			}
			return totalCount;
		}

		Iterator begin() const { return Iterator(first); }

	private:
		T* first;
	};
}

	/*
	Summary:
	Add this to a class object to allow it to be used as an item in a inbuiltlist
	[Note: This should be added inside the private scope of a class]
	*/
#define INBUILTLIST_ITEM_IMPLEMENT(type)\
	private: friend class Internal::InbuiltList<type>;\
	friend class Internal::InbuiltList<type>::Iterator;\
	type* next = nullptr;

	/*
	Summary:
	Add this to a class object to access to the inbuilt list type
	*/
#define INBUILTLIST_IMPLEMENT(listTypeName, itemType)\
		using listTypeName = Internal::InbuiltList<itemType>;
