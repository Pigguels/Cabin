#pragma once

/*
Summary
A Random device that will generate random numbers based off a given seed.
*/
class RandomDevice
{
public:

	RandomDevice();
	RandomDevice(int _seed);

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

	const int min = 0;
	const int max = 0x7fffffff;

private:
	// 0x27534865 - goldilox
	// 0x37534765 - improved
	// 0x37a34765 - further
	const int hash = 0x37a35765; // more

	int seed;
};
