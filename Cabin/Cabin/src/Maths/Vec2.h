#pragma once
#include "Maths/Maths.h"

struct Vec2
{
	Vec2()
	{
		x = 0.0f;
		y = 0.0f;
	}
	Vec2(const float& d)
	{
		x = d;
		y = d;
	}
	Vec2(const float& _x, const float& _y)
	{
		x = _x;
		y = _y;
	}
	Vec2(const Vec2& v)
	{
		x = v.x;
		y = v.y;
	}

	float x = 0.0f;
	float y = 0.0f;

	Vec2 operator+(const Vec2& that) const
	{
		return Vec2(x + that.x, y + that.y);
	}
	Vec2 operator-(const Vec2& that) const
	{
		return Vec2(x - that.x, y - that.y);
	}
	Vec2 operator*(const float& v) const
	{
		return Vec2(x * v, y * v);
	}
	Vec2 operator/(const float& v) const
	{
		return Vec2(x / v, y / v);
	}
	void operator+=(const Vec2& that)
	{
		x += that.x;
		y += that.y;
	}
	void operator-=(const Vec2& that)
	{
		x -= that.x;
		y -= that.y;
	}
	void operator*=(const float& v)
	{
		x *= v;
		y *= v;
	}
	void operator/=(const float& v)
	{
		x /= v;
		y /= v;
	}
	bool operator==(const Vec2& v)
	{
		return x == v.x && y == v.y;
	}

	float SqrMag() const
	{
		return (x * x + y * y);
	}
	float Mag() const
	{
		return Maths::Sqrt(x * x + y * y);
	}
	void Normalise()
	{
		float mag = Mag();
		x /= mag;
		y /= mag;
	}
	Vec2 GetNormalised() const
	{
		Vec2 v = *this;
		v.Normalise();
		return v;
	}

	static Vec2 ClampMag(const Vec2& v, const float& mag)
	{
		return v.GetNormalised() * mag;
	}
	static float Dot(const Vec2& a, const Vec2& b)
	{
		return a.x * b.x + a.y * b.y;
	}
	static float Distance(const Vec2& a, const Vec2& b)
	{
		return (a - b).Mag();
	}
	static Vec2 MoveTowards(const Vec2& a, const Vec2& b, const float& step)
	{
		float mag = (b - a).Mag();
		return (mag <= step) ? b : (a + ((b - a) / mag) * step);
	}
	static Vec2 LerpUnclamped(const Vec2& a, const Vec2& b, const float& t)
	{
		return a * (1.0f - t) + b * t;
	}
	static Vec2 Lerp(const Vec2& a, const Vec2& b, const float& t)
	{
		return LerpUnclamped(a, b, Maths::Clamp01(t));
	}
};
