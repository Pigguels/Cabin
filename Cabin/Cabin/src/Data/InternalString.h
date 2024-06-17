#pragma once
#include "Data/InbuiltList.h"

namespace Internal
{
	/*
	Summary:
	Basic ref counted string object for internal use by the string and string manager.
	This object is intended to be immutable once created.
	*/
	class InternalString
	{
	public:
		InternalString(unsigned int _hash, unsigned int _length) :
			refs(0),
			hash(_hash),
			length(_length),
			c_str((char*)(this + 1))
		{}

		int refs;
		const unsigned int hash;
		const unsigned int length;
		const char* c_str;

		INBUILTLIST_ITEM_IMPLEMENT(InternalString)
	};
}
