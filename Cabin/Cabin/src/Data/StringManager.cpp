#include "Data/StringManager.h"
#include "Data/HashFunctions.h"
#include "Data/StringFunctions.h"

namespace Internal
{
	StringManager& StringManager::Instance()
	{
		static StringManager sm = StringManager();
		return sm;
	}

	StringManager::StringManager()
	{
		buckets = new Bucket[bucketCount];

		emptyString = CreateInternalString("");
		AddRef(emptyString);
	}
	StringManager::~StringManager()
	{
		DecRef(emptyString);
		delete[](buckets);
	}

	InternalString* StringManager::GetOrCreateInternalString(const char* str)
	{
		InternalString* newStr = Contains(str);
		if (!newStr)
		{
			newStr = CreateInternalString(str);
		}
		return newStr;
	}

	int StringManager::AddRef(InternalString* str)
	{
		return ++str->refs;
	}
	int StringManager::DecRef(InternalString* str)
	{
		int refs = --str->refs;
		if (refs <= 0)
		{
			Remove(str);
			free(str);
		}
		return refs;
	}

	InternalString* StringManager::Contains(InternalString* str) const
	{
		int bucketIndex = GetStringBucketIndex(*str);
		if (buckets[bucketIndex].Contains(*str))
			return str;

		return nullptr;
	}
	InternalString* StringManager::Contains(const char* str) const
	{
		int bucketIndex = GetStringBucketIndex(str);
		for (Bucket::Iterator iter = buckets[bucketIndex].begin(); iter.ptr; iter++)
		{
			if (StringFunctions::Compare(iter->c_str, str) == 0)
				return iter.ptr;
		}
		return nullptr;
	}

	InternalString* StringManager::CreateInternalString(const char* str)
	{
		int strLength = StringFunctions::Length(str);
		InternalString* strMem = (InternalString*)malloc(sizeof(InternalString) + strLength);
		InternalString* newStr = new((InternalString*)strMem) InternalString(HashFunctions::Hash(str), strLength);
		StringFunctions::Copy((char*)(strMem + 1), str);
		Add(newStr);
		return newStr;
	}

	void StringManager::Add(InternalString* str)
	{
		int bucketIndex = GetStringBucketIndex(*str);
		buckets[bucketIndex].PushFront(str);
	}
	void StringManager::Remove(InternalString* str)
	{
		int bucketIndex = GetStringBucketIndex(*str);
		buckets[bucketIndex].Remove(str);
	}

	unsigned int StringManager::GetStringBucketIndex(const InternalString& str) const { return (str.hash % bucketCount); }
	unsigned int StringManager::GetStringBucketIndex(const char* str) const { return (HashFunctions::Hash(str) % bucketCount); }

	InternalString* StringManager::GetEmptyString() const { return emptyString; }
}
