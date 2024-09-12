#include "Maths/Random.h"

Random::Random() : seed(1) {}
Random::Random(int _seed) : seed(_seed) {}
void Random::SetSeed(int _seed) { seed = _seed; }
int Random::Next()
{
	seed = ((seed * hash) ^ (seed >> 1)) & max;
	return seed;
}
float Random::Float01() { return (float)(Next() / (double)max); } // must be double to accurately divide the size of a 32 bit value
int Random::Range(int _min, int _max) { return Next() % (_max - _min) + _min; }
float Random::Range(float _min, float _max) { return Float01() * (_max - _min) + _min; }
