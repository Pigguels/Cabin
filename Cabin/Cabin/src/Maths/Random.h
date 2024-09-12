#pragma once

/*
Summary
A Random device that will generate random numbers based off a given seed.
*/
class Random
{
public:
	Random();
	Random(int _seed);

	/*
	Summary:
	Sets the seed of this Random device.
	*/
	void SetSeed(int _seed);

	/*
	Summary:
	Returns the next random number from this Random device.
	*/
	int Next();

	/*
	Summary:
	Returns a random float between the range of 0.0f - 1.0f.
	*/
	float Float01();

	/*
	Summary:
	Returns a random int between the given min (inclusive) and max (exclusive) range.
	*/
	int Range(int _min, int _max);
	/*
	Summary:
	Returns a random float between the given min (inclusive) and max (exclusive) range.
	*/
	float Range(float _min, float _max);

	static const unsigned int max = 0x7fffffff;

private:
	static const unsigned int hash = 0xBadDecaf;
	int seed;
};
