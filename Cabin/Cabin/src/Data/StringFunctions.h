#pragma once
#include "Maths/Maths.h"
#include "Data/BitFunctions.h"

namespace StringFunctions
{
	/*
	Summary:
	Returns true if the given char is a lowercase character.
	*/
	static bool IsLower(const char c) { return (c >= 'a' && c <= 'z'); }
	/*
	Summary:
	Returns true if the given char is an uppercase character.
	*/
	static bool IsUpper(const char c) { return (c >= 'A' && c <= 'Z'); }
	/*
	Summary:
	Returns true if a given char is a letter character.
	*/
	static bool IsLetter(const char c) { return IsUpper(c) || IsLower(c); }
	/*
	Summary:
	Returns true if a given char is a digit character.
	*/
	static bool IsDigit(const char c) { return c >= '0' && c <= '9'; }
	/*
	Summary:
	Returns true if a given char is a hex character.
	*/
	static bool IsHex(const char c) { return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'); }
	/*
	Summary:
	Returns true if a given char is a whitespace character.
	*/
	static bool IsWhiteSpace(const char c) { return c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' '; }
	/*
	Summary:
	Returns true if a given char is a control character.
	*/
	static bool IsControl(const char c) { return c <= '\10'; }
	/*
	Summary:
	Returns true if a given char is a punctuation character.
	*/
	static bool IsPunc(const char c)
	{
		return
		c == '!' || c == '"' || c == '#' || c == '$' || c == '%' || c == '&' || c == '\'' || c == '(' || c == ')' || c == '*' || c == '+' || c == ',' || c == '-' || c == '.' || c == '/' ||
		c == ':' || c == ';' || c == '<' || c == '=' || c == '>' || c == '?' || c == '@' ||
		c == '[' || c == '\\' || c == ']' || c == '^' || c == '_' || c == '`' ||
		c == '{' || c == '|' || c == '}' || c == '~';
	}
	/*
	Summary:
	Returns the length of the given string.
	[Note: This includes the null terminator]
	*/
	static int Length(const char* str)
	{
		int length = 1;
		while (*(str++) != '\0') ++length;
		return length;
	}

	/*
	Summary:
	Compares two chars.
	Returns -1 if a precedes b, or 1 if b precedes a, or 0 if both chars are equal
	*/
	static int Compare(const char a, const char b) { return a == b ? 0 : (a < b ? -1 : 1); }
	/*
	Summary:
	Compares two strings.
	Returns -1 if a precedes b, or 1 if b precedes a, or 0 if both strings are equal
	*/
	static int Compare(const char* a, const char* b)
	{
		int lr = 0;
		while (lr == 0 && !(*a == '\0' && *b == '\0'))
			lr = Compare(*(a++), *(b++));
		return lr;
	}
	/*
	Summary:
	Compares two strings upto a given length.
	Returns -1 if a precedes b, or 1 if b precedes a, or 0 if both strings are equal.
	*/
	static int Compare(const char* a, const char* b, int length)
	{
		int lr = 0;
		while (--length >= 0 && lr == 0 && !(*a == '\0' && *b == '\0')) lr = Compare(*(a++), *(b++));
		return lr;
	}

	/*
	Summary:
	Copies one string onto another, upto a given length.
	*/
	static void Copy(char* dst, const char* src, int length)
	{
		while (--length >= 0) *(dst++) = *(src++);
	}
	/*
	Summary:
	Copies one string onto another.
	[Note: The user needs to ensure that the buffer they are copying to has enough space to hold the source]
	*/
	static void Copy(char* dst, const char* src)
	{
		if (*src != '\0')
		{
			while (*src != '\0') *(dst++) = *(src++);
		}
		*dst = '\0';
	}

	/*
	Summary:
	Reverses the given string.
	*/
	static void Reverse(char* str)
	{
		for (int i = 0, j = Length(str) - 2; i < j; i++, j--)
			SWAP(str[i], str[j]);
	}

	/*
	Summary:
	Searches a string for the given substring, returns the index of its first occurance, or -1 if there are no occurances.
	*/
	static int Find(const char* src, const char* substring)
	{
		int index = 0;
		int compLen = Length(substring) - 1;
		while (*src != '\0')
		{
			if (Compare(src++, substring, compLen) == 0) return index;
			++index;
		}
		return -1;
	}
	/*
	Summary:
	Searches a string upto the given length for the given substring, returns the index of its first occurance, or -1 if there are no occurances.
	*/
	static int Find(const char* src, const char* substring, int length)
	{
		int index = 0;
		int compLen = Length(substring) - 1;
		while (--length >= 0 && *src != '\0')
		{
			if (Compare(src++, substring, compLen) == 0) return index;
			++index;
		}
		return -1;
	}
	/*
	Summary:
	Searches a string for the first whitespace character, returns the index of the whitespace, or -1 if there is no whitespace.
	*/
	static int FindNextWhiteSpace(const char* src)
	{
		int index = 0;
		while (*src != '\0')
		{
			if (IsWhiteSpace(*(src++))) return index;
			++index;
		}
		return -1;
	}
	/*
	Summary:
	Searches a string upto a given length for whitespace, returns the index of the first whitespace character, or -1 if there is no whitespace.
	*/
	static int FindNextWhiteSpace(const char* src, int length)
	{
		int index = 0;
		while (--length >= 0 && *src != '\0')
		{
			if (IsWhiteSpace(*(src++))) return index;
			++index;
		}
		return -1;
	}
	/*
	Summary:
	Searches a string for non-whitespace, returns the index of the first non-whitespace character, or -1 if there is no non-whitespace.
	*/
	static int FindNextNonWhiteSpace(const char* src)
	{
		int index = 0;
		while (*src != '\0')
		{
			if (!IsWhiteSpace(*(src++))) return index;
			++index;
		}
		return -1;
	}/*
	Summary:
	Searches a string upto a given length for non-whitespace, returns the index of the first non-whitespace character, or -1 if there is no non-whitespace.
	*/
	static int FindNextNonWhiteSpace(const char* src, int length)
	{
		int index = 0;
		while (--length >= 0 && *src != '\0')
		{
			if (!IsWhiteSpace(*(src++))) return index;
			++index;
		}
		return -1;
	}

	/*
	Summary:
	Returns the given char converted to uppercase.
	*/
	static char ToUpper(const char c) { return IsLower(c) ? (c - 'a' + 'A') : c; }
	/*
	Summary:
	Converts the given string to uppercase.
	*/
	static void ToUpper(char* str)
	{
		while (*str != '\0') *str = ToUpper(*(str++));
	}
	/*
	Summary:
	Returns the given char converted to lowercase.
	*/
	static char ToLower(const char c) { return IsUpper(c) ? (c - 'A' + 'a') : c; }
	/*
	Summary:
	Converts the given string to lowercase.
	*/
	static void ToLower(char* str)
	{
		while (*str != '\0') *str = ToLower(*(str++));
	}
	/*
	Summary:
	Returns the given char with its case swapped.
	*/
	static char SwapCase(const char c) { return IsUpper(c) ? (c - 'A' + 'a') : IsLower(c) ? (c - 'a' + 'A') : c; }
	/*
	Summary:
	Swaps the given strings case.
	*/
	static void SwapCase(char* str)
	{
		while (*str != '\0') *str = SwapCase(*(str++));
	}

	/*
	Summary:
	Returns the given char number to an int.
	*/
	static int ToInt(const char c)
	{
		if (IsDigit(c)) return c - '0';
		if (IsLower(c)) return c - 'a';
		if (IsUpper(c)) return c - 'A';
		return 0;
	}
	/*
	Summary:
	Returns the given string to an integer.
	[Note: Undefinded results can occur if the string contains any glyphs that arent between 0-9]
	[Note: The sign of the number can be definded using a '-' at the beginning of the number]
	*/
	static int ToInt(const char* str, int base = 10)
	{
		int total = 0;
		bool neg = *str == '-';
		if (neg) --str;
		while (*str != '\0')
		{
			total *= base;
			total += ToInt(*(str++));
		}
		return neg ? total * -1 : total;
	}

	/*
	Summary:
	Returns the given number converted into a string format.
	Optional base value to handle octal, hexadecimal and whatever else may need it.
	[Note: the returned strings characters will become undefined afer base 36, as it goes from 0-9 then a-z]
	[Note: The user needs to ensure that the buffer they are constructing to has enough space to hold the converted string]
	*/
	static char* IntToStr(char* outStr, int n, const int base = 10)
	{
		bool neg = false;
		char* curr = outStr;

		if (n != 0)
		{
			if (n < 0)
			{
				neg = true;
				n *= -1;
			}

			while (n > 0)
			{
				*curr = n % base;
				*curr += (*curr > '9' ? ('a' - 10) : '0'); // convert the number range to 0-9 or a-z, any base after 36 is undefined
				n /= base;
				++curr;
			}
		}
		else
			*(curr++) = '0';
		
		if (neg) *(curr++) = '-';

		*curr = '\0';

		Reverse(outStr);
		return outStr;
	}

	/*
	Summary:
	Converts a string to a float.
	[Note: Undefinded results can occur if the string contains any glyphs that arent between 0-9]
	[Note: The sign of the number can be definded using a '-' at the beginning of the number]
	*/
	static float ToFloat(const char* str)
	{
		float total = 0;
		bool neg = *str == '-';
		if (neg) ++str;
		
		while (*str != '.' && *str != '\0') // whole
		{
			total *= 10;
			total += ToInt(*(str++));
		}

		if (*str == '.') // fractional
		{
			++str;
			float fract = 0;
			int digits = 0;
			while (*str != '\0')
			{
				fract *= 10;
				fract += ToInt(*(str++));
				++digits;
			}
			while (digits--) fract *= 0.1f;
			total += fract;
		}

		return neg ? total * -1 : total;
	}

	static char* FloatToStr(char* outStr, float n)
	{
		bool neg = false;
		char* curr = outStr;

		if (n != 0.0f)
		{
			if (n < 0)
			{
				neg = true;
				n *= -1;
			}

			int wholeN = n;
			int decimalPos = 0;
			while ((wholeN = n) != n)
			{
				n *= 10;
				++decimalPos;
			}

			while (wholeN > 0)
			{
				if (decimalPos-- == 0) *(curr++) = '.'; // Add the middle decimal point

				*curr = wholeN % 10;
				*curr += (*curr > '9' ? ('a' - 10) : '0'); // convert the number range to 0-9 or a-z, any base after 36 is undefined
				wholeN *= 0.1f;
				++curr;
			}

			if (decimalPos >= 0)
			{
				// solve for the preceding decimal point and zeros
				while (decimalPos-- > 0) *(curr++) = '0';
				*(curr++) = '.';
				*(curr++) = '0';
			}

		}
		else
			*(curr++) = '0';

		if (neg) *(curr++) = '-';

		*curr = '\0';

		Reverse(outStr);
		return outStr;
	}
}
