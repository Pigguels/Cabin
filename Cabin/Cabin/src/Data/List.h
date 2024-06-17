#pragma once
#include "Core/Debug.h"

namespace Internal
{
	template<typename T = int>
	struct ListNode
	{
		ListNode() : item(), prev(nullptr), next(nullptr) {}
		ListNode(const T& _item, ListNode* _prev, ListNode* _next)
		{
			item = _item;
			next = _next;
			prev = _prev;
		}
		T item;
		ListNode* next;
		ListNode* prev;
	};

	template<typename T = int>
	class ListIterator
	{
		typedef ListNode<T> NodeType;
	public:
		ListIterator() : node(nullptr) {}
		ListIterator(NodeType* _node) { node = _node; }

		T& operator*() const { return node->item; }
		T* operator->() const { return *(node->item); }
		ListIterator& operator++()
		{
			node = node->next;
			return *this;
		}
		ListIterator operator++(int)
		{
			ListIterator temp = *this;
			++(*this);
			return temp;
		}
		ListIterator operator+(int offset) const
		{
			ListIterator temp = *this;
			for (int i = 0; i < offset; i++)
				temp++;

			return temp;
		}
		ListIterator& operator+=(int offset)
		{
			for (int i = 0; i < offset; i++)
				(*this)++;

			return *this;
		}
		ListIterator& operator--()
		{
			node = node->prev;
			return *this;
		}
		ListIterator operator--(int)
		{
			ListIterator temp = *this;
			--(*this);
			return temp;
		}
		ListIterator operator-(int offset) const
		{
			ListIterator temp = *this;
			for (int i = 0; i < offset; i++)
				temp--;

			return temp;
		}
		ListIterator& operator-=(int offset)
		{
			for (int i = 0; i < offset; i++)
				(*this)--;

			return *this;
		}
		ListIterator& operator[](int offset)
		{
			return *(*this + offset);
		}
		bool operator==(const ListIterator& that) { return this->node == that.node; }
		bool operator!=(const ListIterator& that) { return !(*this == that); }

	private:
		NodeType* node;
	};
}

/*
Summary:
A fully dynamic list object that can push, pop, insert and remove items.
*/
template<typename T = int>
class List
{
	typedef Internal::ListNode<T> NodeType;
public:

	using Iterator = Internal::ListIterator<T>;

	List()
	{
		_InitEnds();
	}
	List(const List& that) = delete;
	~List()
	{
		Clear();
	}

	void operator=(const List& that) = delete;

	T& operator[](int index)
	{
		ASSERT_MSG(index >= 0, "List index out of range");
		NodeType* currentNode = first.next;
		for (int i = 0; i < index; i++)
		{
			currentNode = currentNode->next;
			ASSERT_MSG(currentNode != &last, "List index out of range");
		}
		return (currentNode->item);
	}

	/*
	Summary:
	Clears all items in the list
	*/
	void Clear()
	{
		/* Iterate through and delete every node */
		NodeType* toDestroy = first.next;
		NodeType* next = toDestroy->next;
		while (toDestroy != &last)
		{
			delete toDestroy;
			toDestroy = next;
			next = next->next;
		}

		_InitEnds();
	}

	/*
	Summary:
	Copies the contents of this List into the given List.
	*/
	void CopyInto(List& that)
	{
		that.Clear();
		that._InitEnds();
		for (const T& item : *this)
			that.Add(item);
	}
	/*
	Summary:
	Copies the contents from the given List into this List.
	*/
	void CopyFrom(const List& that)
	{
		that.CopyInto(*this);
	}

	/*
	Summary:
	Adds an item to the end of the list.
	*/
	void Add(const T& item)
	{
		NodeType* nodeToAdd = new NodeType(item, last.prev, &last);
		last.prev->next = nodeToAdd;
		last.prev = nodeToAdd;
	}

	/*
	Summary:
	Adds an item into the list at the given index.
	*/
	void AddAt(const T& item, int index)
	{
		ASSERT_MSG(index >= 0, "List insert index out of range");

		/* Find insertion point */
		NodeType* currentNode = first.next;
		for (int i = 0; i < index; i++)
		{
			ASSERT_MSG(currentNode != &last, "List insert index out of range");
			currentNode = currentNode->next;
		}

		/* Create and insert the node */
		NodeType* nodeToAdd = new NodeType(item, currentNode->prev, currentNode);
		nodeToAdd->prev->next = nodeToAdd;
		currentNode->prev = nodeToAdd;
	}

	/*
	Summary:
	Pops (removes) an item from the end of the list
	Returns true if an item was popped
	*/
	bool Pop()
	{
		/* List is empty, cant pop */
		if (first.next == &last)
			return false;

		NodeType* nodeToRemove = last.prev;
		nodeToRemove->prev->next = &last;
		last.prev = nodeToRemove->prev;

		delete nodeToRemove;

		return true;
	}

	/*
	Summary:
	Removes an item at the given index
	*/
	bool Remove(int index)
	{
		ASSERT_MSG(first.next != &last, "List calling remove on an empty list");

		/* Early out as list is empty */
		if (first.next == &last)
			return false;

		/* find the node to remove */
		NodeType* nodeToRemove = first.next;
		for (int i = 0; i < index; i++)
		{
			nodeToRemove = nodeToRemove->next;
			ASSERT_MSG(nodeToRemove != &last, "List remove index out of range");
		}

		nodeToRemove->prev->next = nodeToRemove->next;
		nodeToRemove->next->prev = nodeToRemove->prev;

		delete nodeToRemove;

		return true;
	}

	/*
	Summary:
	Returns the total count of items in the list
	[Note: This action is expensive, caching is advised]
	*/
	int Count() const
	{
		int totalCount = 0;

		/* Iterate through the list and calculate the total node count */
		NodeType* currentNode = first.next;
		while (currentNode != &last)
		{
			totalCount++;
			currentNode = currentNode->next;
		}

		return totalCount;
	}

	Iterator begin() { return Iterator(first.next); }
	Iterator end() { return Iterator(&last); }

private:
	/*
	Summary:
	Initialises the ends of the list
	*/
	void _InitEnds()
	{
		first = NodeType();
		last = NodeType();
		first.next = &last;
		last.prev = &first;
	}

	NodeType first;
	NodeType last;
};
