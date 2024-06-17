#pragma once

namespace Algorithms
{
	template<typename T>
	void Swap(T& a, T& b)
	{
		T c = a;
		a = b;
		b = c;
	}

	template<typename T, typename Iter>
	Iter Find(Iter begin, Iter end, const T& value) // no point to use on a dictionary
	{
		while (begin != end)
		{
			if (*begin == value) return begin;
			begin++;
		}
		return nullptr;
	}
	template<typename T, typename Iter>
	int FindAt(Iter begin, Iter end, const T& value) // no point to use on a dictionary
	{
		for (int i = 0; begin + i != end; ++i)
		{
			if (*(begin + i) == value) return i;
		}
		return -1;
	}

	template<typename Iter, typename CheckFunc>
	Iter FindIf(Iter begin, Iter end, const CheckFunc& check) // no point to use on a dictionary
	{
		while (begin != end)
		{
			if (check(*begin)) return begin;
			begin++;
		}
		return nullptr;
	}
	template<typename Iter, typename CheckFunc>
	int FindIfAt(Iter begin, Iter end, const CheckFunc& check) // no point to use on a dictionary
	{
		for (int i = 0; begin + i != end; ++i)
		{
			if (check(*(begin + i))) return i;
		}
		return -1;
	}

	template<typename Iter, typename CompareFunc>
	void BubbleSort(Iter begin, Iter end, const CompareFunc& comp)
	{
		bool sorted = false;
		while (!sorted)
		{
			sorted = true;
			for (Iter it = begin + 1; it < end; it++)
			{
				if (comp(*(it - 1), *it))
				{
					Swap(*(it - 1), *it);
					sorted = false;
				}
			}
		}
	}
}
