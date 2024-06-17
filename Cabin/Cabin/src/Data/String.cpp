#include "Data/String.h"
#include "Data/StringManager.h"
#include "Data/StringFunctions.h"

const String String::EMPTY = String();

String::String()
{
	Internal::StringManager& strManager = Internal::StringManager::Instance();
	str = strManager.GetEmptyString();
	strManager.AddRef(str);
}
String::String(const char* _str)
{
	Internal::StringManager& strManager = Internal::StringManager::Instance();
	str = strManager.GetOrCreateInternalString(_str);
	strManager.AddRef(str);
}
String::String(const String& _str)
{
	Internal::StringManager& strManager = Internal::StringManager::Instance();
	if (str)
		strManager.DecRef(str);

	str = _str.str;
	strManager.AddRef(str);
}

String::~String()
{
	ReleaseInternalString();
}

bool String::operator=(const String& that)
{
	if (str != that.str)
	{
		ReleaseInternalString();
		str = that.str;
		Internal::StringManager::Instance().AddRef(str);
		return true;
	}
	return false;
}
String String::operator+(const String& that)
{
	int currLength = Length() - 1;
	char* newStr = new char[currLength + that.Length()];
	StringFunctions::Copy(newStr, c_str(), currLength);
	StringFunctions::Copy(&newStr[currLength], that.c_str(), that.Length());
	String appended = String(newStr);
	delete[](newStr);
	return appended;
}
String& String::operator+=(const String& that)
{
	*this = *this + that;
	return *this;
}

bool String::operator==(const String& that) const
{
	return str == that.str;
}
bool String::operator!=(const String& that) const
{
	return !(*this == that);
}
bool String::operator>(const String& that) const
{
	return (StringFunctions::Compare(c_str(), that.c_str()) > 0);
}
bool String::operator>=(const String& that) const
{
	return (StringFunctions::Compare(c_str(), that.c_str()) >= 0);
}
bool String::operator<(const String& that) const
{
	return (StringFunctions::Compare(c_str(), that.c_str()) < 0);
}
bool String::operator<=(const String& that) const
{
	return (StringFunctions::Compare(c_str(), that.c_str()) <= 0);
}

bool String::operator=(const char* _str)
{
	if (StringFunctions::Compare(c_str(), _str) != 0)
	{
		ReleaseInternalString();

		Internal::StringManager& strManager = Internal::StringManager::Instance();
		str = strManager.GetOrCreateInternalString(_str);
		strManager.AddRef(str);
		return true;
	}
	return false;
}
String String::operator+(const char* _str)
{
	int currLength = Length() - 1;
	int strLength = StringFunctions::Length(_str);
	char* newStr = new char[currLength + strLength];
	StringFunctions::Copy(newStr, c_str(), currLength);
	StringFunctions::Copy(&newStr[currLength], _str, strLength);
	String appended = String(newStr);
	delete[](newStr);
	return appended;
}
String& String::operator+=(const char* _str)
{
	*this = *this + _str;
	return *this;
}

bool String::operator==(const char* _str) const
{
	return (StringFunctions::Compare(c_str(), _str) == 0);
}
bool String::operator!=(const char* _str) const
{
	return !(*this == _str);
}
bool String::operator>(const char* _str) const
{
	return (StringFunctions::Compare(c_str(), _str) > 0);
}
bool String::operator>=(const char* _str) const
{
	return (StringFunctions::Compare(c_str(), _str) >= 0);
}
bool String::operator<(const char* _str) const
{
	return (StringFunctions::Compare(c_str(), _str) < 0);
}
bool String::operator<=(const char* _str) const
{
	return (StringFunctions::Compare(c_str(), _str) <= 0);
}

const char* String::c_str() const { return str->c_str; }
const unsigned int String::Hash() const { return str->hash; }
const int String::Length() const { return str->length; }

//String String::ToUpper() const
//{
//	char* upper = new char[str->length];
//	StringFunctions::Copy(upper, str->c_str);
//	String upperStr = String(StringFunctions::ToUpper(upper));
//	delete[](upper);
//	return upperStr;
//}
//String String::ToLower() const
//{
//	char* lower = new char[str->length];
//	StringFunctions::Copy(lower, str->c_str);
//	String lowerStr = String(StringFunctions::ToLower(lower));
//	delete[](lower);
//	return lowerStr;
//}
//int String::ToInt() const
//{
//	return StringFunctions::ToInt(str->c_str);
//}
const char String::GetAt(int index) const
{
	ASSERT_MSG(index < (int)str->length, "String GetAt index out of range");
	return str->c_str[index];
}
int String::Compare(const String that) const
{
	return StringFunctions::Compare(str->c_str, that.c_str());
}

void String::ReleaseInternalString()
{
	if (str)
		Internal::StringManager::Instance().DecRef(str);
	str = nullptr;
}
