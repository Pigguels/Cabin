#pragma once

/*
Summary:
A simple pair class to hold two objects.
*/
template <class A, class B>
struct Pair
{
	Pair()
	{
		a = A();
		b = B();
	}
	Pair(const A& _a, const B& _b)
	{
		a = _a;
		b = _b;
	}

	void operator=(const Pair& that)
	{
		a = that.a;
		b = that.b;
	}
	bool operator==(const Pair& that)
	{
		return (a == that.a && b == that.b);
	}
	bool operator!=(const Pair& that)
	{
		return a != that.a || b != that.b;
	}

	A a;
	B b;
};
