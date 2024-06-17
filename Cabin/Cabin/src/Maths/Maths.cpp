#include "Maths/Maths.h"
#include <cmath>

namespace Maths
{
	const float Nan = NAN;
	const float Infinity = INFINITY;
	const float Epsilon = FLT_EPSILON;
	const float PI = 3.14159265359f;
	const float RadToDeg = 57.2957795131f;
	const float DegToRad = 0.01745329251f;

	float inline Sin(float v) { return sinf(v); }
	float inline Cos(float v) { return cosf(v); }
	float inline Tan(float v) { return tanf(v); }
	float inline ASin(float v) { return asinf(v); }
	float inline ACos(float v) { return acosf(v); }
	float inline ATan(float v) { return atanf(v); }
	float inline ATan2(float y, float x) { return atan2f(y, x); }
	float inline SinH(float v) { return sinhf(v); }
	float inline CosH(float v) { return coshf(v); }
	float inline TanH(float v) { return tanhf(v); }
	float inline ASinH(float v) { return asinhf(v); }
	float inline ACosH(float v) { return acoshf(v); }
	float inline ATanH(float v) { return atanhf(v); }

	float inline Exp(float v) { return expf(v); }
	float inline Log(float v) { return logf(v); }
	float inline Log10(float v) { return log10f(v); }
	float inline Fract(float v) { return v - (int)v; }
	float inline Mod(float a, float b) { return fmodf(a, b); }
	float inline Pow(float v, float p) { return powf(v, p); }
	float inline Sqr(float v) { return v * v; }
	float inline Sqrt(float v) { return sqrtf(v); }
	float inline Cbrt(float v) { return cbrtf(v); }
	float inline Hypot(float a, float b) { return Sqrt(Sqr(a) + Sqr(b)); }

	float inline Ceil(float v) { return ceilf(v); }
	float inline Floor(float v) { return floorf(v); }
	float inline Round(float v) { return roundf(v); }
	float inline Trunc(float v) { return truncf(v); }
	
	float Wrap(float v, float min, float max) { return Mod(v - min, max - min) + (Sign(v) > 0 ? min : (min + max)); }
	float Angle(float v) { return Wrap(v, 0.0f, 360.0f); }
}
