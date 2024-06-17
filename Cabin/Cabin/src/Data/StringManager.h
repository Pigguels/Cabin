#pragma once
#include "Data/InbuiltList.h"
#include "Data/InternalString.h"

namespace Internal
{
	/*
	Summary:
	The string manager, this class holds all internal strings that
	the user side string class uses to be able to share multiple strings.
	*/
	class StringManager
	{
		friend class InternalString;
	public:
		static StringManager& Instance();

		/*
		Summary:
		Creates an InternalString that is managed by this StringManager.
		*/
		InternalString* GetOrCreateInternalString(const char* str);
		/*
		Summary:
		Adds a ref to a given InternalString.
		Returns the new ref count of the InternalString.
		*/
		int AddRef(InternalString* str);
		/*
		Summary:
		Decrements a ref from a given InternalString, destroying it if there are no refs left.
		Returns the new ref count of the InternalString.
		*/
		int DecRef(InternalString* str);

		/*
		Summary:
		Returns the given InternalString if it is being held by the StringManager.
		*/
		InternalString* Contains(InternalString* str) const;
		/*
		Summary:
		Returns the given InternalString if it is being held by the StringManager.
		*/
		InternalString* Contains(const char* str) const;

		/*
		Summary:
		Returns the sentinal empty InternalString.
		*/
		InternalString* GetEmptyString() const;

	private:
		StringManager();
		~StringManager();
		
		/*
		Summary:
		Creates a new InternalString and adds it to the manager.
		Returns the created InternalString.
		*/
		InternalString* CreateInternalString(const char* str);

		/*
		Summary:
		Adds an InternalString to be managed by this StringManager
		[Note: Added internal strings are 'observable' by user Strings]
		*/
		void Add(InternalString* str);
		/*
		Summary:
		Removes an InternalString from being managed by this StringManager
		[Note: InternalStrings that are removed are no longer 'observable' by user Strings]
		*/
		void Remove(InternalString* str);

		unsigned int GetStringBucketIndex(const InternalString& str) const;
		unsigned int GetStringBucketIndex(const char* str) const;

		INBUILTLIST_IMPLEMENT(Bucket, InternalString);

		const int bucketCount = 1024;
		Bucket* buckets = nullptr;

		InternalString* emptyString = nullptr;
	};
}
