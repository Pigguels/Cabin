#include "Maths/Random.h"

RandomDevice::RandomDevice() { SetSeed(0); }
RandomDevice::RandomDevice(int _seed) { SetSeed(_seed); }
void RandomDevice::SetSeed(int _seed) { seed = _seed; }
int RandomDevice::Next()
{
	seed = ((hash * seed + hash)) & max;
	return seed;
}
float RandomDevice::Float01() { return (float)(Next() / (double)max); }
int RandomDevice::Range(int _min, int _max) { return Next() % (_max - _min) + _min; }
float RandomDevice::Range(float _min, float _max) { return (float)(Next() / (double)max) * (_max - _min) + _min; }
