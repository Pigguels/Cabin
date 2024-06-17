#pragma once
#include "Core/Types.h"
#include "Core/Debug.h"

namespace HashFunctions
{
	static const u32 hashSeed32 = 0xBadDecaf;

	/*
	Summary:
	Returns a hash generated from the given number and seed
	*/
	static u32 Hash(u8 n, const u32 seed)
	{
		return (u32)((n >> 4) ^ n * (u8)(seed >> 2));
	}
	/*
	Summary:
	Returns a hash generated from the given number
	*/
	static u32 Hash(u8 n)
	{
		return Hash(n, hashSeed32);
	}
	/*
	Summary:
	Returns a hash generated from the given number and seed
	*/
	static u32 Hash(s8 n, const u32 seed)
	{
		return (u32)((n >> 4) ^ n * (s8)(seed >> 2));
	}
	/*
	Summary:
	Returns a hash generated from the given number
	*/
	static u32 Hash(s8 n)
	{
		return Hash(n, hashSeed32);
	}
	/*
	Summary:
	Returns a hash generated from the given number and seed
	*/
	static u32 Hash(u16 n, const u32 seed)
	{
		return (u32)((n >> 8) ^ n * (u16)(seed >> 4));
	}
	/*
	Summary:
	Returns a hash generated from the given number
	*/
	static u32 Hash(u16 n)
	{
		return Hash(n, hashSeed32);
	}
	/*
	Summary:
	Returns a hash generated from the given number and seed
	*/
	static u32 Hash(s16 n, const u32 seed)
	{
		return (u32)((n >> 8) ^ n * (s16)(seed >> 4));
	}
	/*
	Summary:
	Returns a hash generated from the given number
	*/
	static u32 Hash(s16 n)
	{
		return Hash(n, hashSeed32);
	}
	/*
	Summary:
	Returns a hash generated from the given number and seed
	*/
	static u32 Hash(u32 n, const u32 seed)
	{
		return (n >> 16) ^ n * seed;
	}
	/*
	Summary:
	Returns a hash generated from the given number
	*/
	static u32 Hash(u32 n)
	{
		// there is a known collision with [ 2521013421 ] equating to 0
		// i need to fix this
		ASSERT(n != 2521013421); // this is the one bad number for the 0xBadDecaf seed

		return Hash(n, hashSeed32);
	}
	/*
	Summary:
	Returns a hash generated from the given number and seed
	*/
	static u32 Hash(s32 n, const u32 seed)
	{
		return (n >> 16) ^ n * seed;
	}
	/*
	Summary:
	Returns a hash generated from the given number
	*/
	static u32 Hash(s32 n)
	{
		// there is a known collision with [ 2521013421 ] equating to 0
		// i need to fix this
		ASSERT(n != 2521013421); // this is the one bad number for the 0xBadDecaf seed

		return Hash(n, hashSeed32);
	}

	/*
	Summary:
	Returns a hash generated from the given c string and a seed
	*/
	static u32 Hash(const char* str, const u32 seed)
	{
		unsigned int hash = 0;

		for (int i = 0; str[i] != '\0'; i++)
		{
			hash += str[i] * seed << (hash * str[i]);
		}

		return hash;
	}

	/*
	Summary:
	Returns a hash generated from the given c string
	*/
	static u32 Hash(const char* str)
	{
		return Hash(str, hashSeed32);
	}

	/*
	Summary:
	Returns a hash generated from the given block of data, read up to the given length, using the given seed
	[Note: This function reads in 4 byte (char) steps, so the length will be in chars]
	*/
	static u32 DataHash(const void* data, const u32 length, const u32 seed)
	{
		unsigned int hash = 0;
		for (unsigned int i = 0; i < length; i++)
		{
			hash += ((char*)data)[i] * seed << (hash * ((char*)data)[i]);
		}

		return hash;
	}

	/*
	Summary:
	Returns a hash generated from the given block of data, read up to the given length
	[Note: This function reads in 4 byte (char) steps, so the length will be in chars]
	*/
	static u32 DataHash(const void* data, const u32 length)
	{
		return DataHash(data, length, hashSeed32);
	}


	/*
	Summary:
	A static wrapper class to allow ease of access to getting and comparing the hash of a type.
	*/
	template<class T>
	class HashKey
	{
	public:
		static u32 GetHash(T t) { return 0; };
		static bool CompareKey(T a, T b) { return false; };
		static T GetNullKey();
	};
	template<>
	class HashKey<u8>
	{
	public:
		static u32 GetHash(u8 t) { return HashFunctions::Hash(t); }
		static bool CompareKey(u8 a, u8 b) { return a == b; }
		static u8 GetNullKey() { return -1; };
	};
	template<>
	class HashKey<s8>
	{
	public:
		static u32 GetHash(s8 t) { return HashFunctions::Hash(t); }
		static bool CompareKey(s8 a, s8 b) { return a == b; }
		static s8 GetNullKey() { return -1; };
	};
	template<>
	class HashKey<u16>
	{
	public:
		static u32 GetHash(u16 t) { return HashFunctions::Hash(t); }
		static bool CompareKey(u16 a, u16 b) { return a == b; }
		static u16 GetNullKey() { return -1; };
	};
	template<>
	class HashKey<s16>
	{
	public:
		static u32 GetHash(s16 t) { return HashFunctions::Hash(t); }
		static bool CompareKey(s16 a, s16 b) { return a == b; }
		static s16 GetNullKey() { return -1; };
	};
	template<>
	class HashKey<u32>
	{
	public:
		static u32 GetHash(u32 t) { return HashFunctions::Hash(t); }
		static bool CompareKey(u32 a, u32 b) { return a == b; }
		static u32 GetNullKey() { return -1; };
	};
	template<>
	class HashKey<s32>
	{
	public:
		static u32 GetHash(s32 t) { return HashFunctions::Hash(t); }
		static bool CompareKey(s32 a, s32 b) { return a == b; }
		static s32 GetNullKey() { return -1; };
	};
}
