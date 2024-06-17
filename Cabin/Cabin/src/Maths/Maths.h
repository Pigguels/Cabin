#pragma once

namespace Maths
{
	extern const float Nan;
	extern const float Infinity;
	extern const float Epsilon;
	extern const float PI;
	extern const float RadToDeg;
	extern const float DegToRad;
	
	extern inline float Sin(float v);
	extern inline float Cos(float v);
	extern inline float Tan(float v);
	extern inline float ASin(float v);
	extern inline float ACos(float v);
	extern inline float ATan(float v);
	extern inline float ATan2(float y, float x);
	extern inline float SinH(float v);
	extern inline float CosH(float v);
	extern inline float TanH(float v);
	extern inline float ASinH(float v);
	extern inline float ACosH(float v);
	extern inline float ATanH(float v);
	
	extern inline float Exp(float v);
	extern inline float Log(float v);
	extern inline float Log10(float v);
	extern inline float Fract(float v);
	extern inline float Mod(float a, float b);
	extern inline float Pow(float v, float p);
	extern inline float Sqr(float v);
	extern inline float Sqrt(float v);
	extern inline float Cbrt(float v);
	extern inline float Hypot(float a, float b);
	
	extern inline float Ceil(float v);
	extern inline float Floor(float v);
	extern inline float Round(float v);
	extern inline float Trunc(float v);
	template<typename T> int Sign(T v) { return v < T(0) ? -1 : 1; }
	
	template<typename T> float Abs(T v) { return v < T(0) ? -v : v; }
	template<typename T> float Min(T a, T b) { return a > b ? b : a; }
	template<typename T> float Max(T a, T b) { return a < b ? b : a; }
	extern float Wrap(float v, float min, float max);
	extern float Angle(float v);
	template<typename T> float Clamp(T v, T min, T max) { return Min(max, Max(min, v)); }
	template<typename T> float Clamp01(T v) { return Clamp(v, T(0), T(1)); }

	template<typename T> float MoveTowards(T a, T b, T step) { return (Abs(b - a) <= step) ? b : (a + step * Sign(b - a)); }
	template<typename T> float LerpUnclamped(T a, T b, float t) { return ((b - a) * t) + a; }
	template<typename T> float Lerp(T a, T b, float t) { return LerpUnclamped(a, b, Clamp01(t)); }
}