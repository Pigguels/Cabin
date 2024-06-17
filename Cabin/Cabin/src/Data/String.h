#pragma once
#include "Data/HashFunctions.h"

namespace Internal { class InternalString; }

/*
Summary:
A base string class for handling char arrays.
This class adds handy wrappers for string 'modification'.

With modification in quotes as when modifying a string we actually
create a new InternalString to serve for our need,
and then decrement the ref count of the previous string.

This would be good to comeback to at somepoint to create more dynamic strings,
as to avoid allocating and freeing memory as much,
especially with strings that only have a ref count of one.
*/
class String
{
public:
	String();
	String(const char* _str);
	String(const String& _str);
	~String();


	bool operator=(const String& that);
	String operator+(const String& that);
	String& operator+=(const String& that);

	bool operator==(const String& that) const;
	bool operator!=(const String& that) const;
	bool operator>(const String& that) const;
	bool operator>=(const String& that) const;
	bool operator<(const String& that) const;
	bool operator<=(const String& that) const;

	bool operator=(const char* _str);
	String operator+(const char* _str);
	String& operator+=(const char* _str);

	bool operator==(const char* _str) const;
	bool operator!=(const char* _str) const;
	bool operator>(const char* _str) const;
	bool operator<(const char* _str) const;
	bool operator>=(const char* _str) const;
	bool operator<=(const char* _str) const;

	const char* c_str() const;
	const unsigned int Hash() const;
	const int Length() const;

	/*
	Summary:
	Returns a version of this string converted to uppercase
	*/
	String ToUpper() const;
	/*
	Summary:
	Returns a version of this string converted to lowercase
	*/
	String ToLower() const;
	/*
	Summary:
	Returns this string converted to an integer
	[Note: Undefinded results can occur if the string contains any glyphs that arent between 0-9]
	[Note: The sign of the number can be definded using a '-' at the beginning of the number]
	*/
	int ToInt() const;
	/*
	Summary:
	Returns the gylph at the given index of the string
	*/
	const char GetAt(int index) const;
	/*
	Summary:
	Compares this string to the given string
	Returns -1 if this string precedes the one given, or 1 if the given string precedes this string, or 0 if both strings are equal
	*/
	int Compare(const String that) const;

	static const String EMPTY;

private:
	Internal::InternalString* str = nullptr;

	/*
	Summary:
	Releases and resets this strings internal string,
	Returns true if the internal string is deleted
	*/
	void ReleaseInternalString();
};

namespace HashFunctions
{
	template<>
	class HashKey<String>
	{
	public:
		static unsigned int GetHash(String t) { return t.Hash(); }
		static bool CompareKey(String a, String b) { return a == b; }
		static String GetNullKey() { return String::EMPTY; };
	};
}
