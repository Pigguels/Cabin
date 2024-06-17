#pragma once
#include "Maths/Maths.h"

struct Vec3
{
	Vec3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	Vec3(const float& d)
	{
		x = d;
		y = d;
		z = d;
	}
	Vec3(const float& _x, const float& _y, const float& _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	Vec3(const Vec3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	Vec3 operator+(const Vec3& that) const
	{
		return Vec3(x + that.x, y + that.y, z + that.z);
	}
	Vec3 operator-(const Vec3& that) const
	{
		return Vec3(x - that.x, y - that.y, z - that.z);
	}
	Vec3 operator*(const float& v) const
	{
		return Vec3(x * v, y * v, z* v);
	}
	Vec3 operator/(const float& v) const
	{
		return Vec3(x / v, y / v, z / v);
	}
	void operator+=(const Vec3& that)
	{
		x += that.x;
		y += that.y;
		z += that.z;
	}
	void operator-=(const Vec3& that)
	{
		x -= that.x;
		y -= that.y;
		z -= that.z;
	}
	void operator*=(const float& v)
	{
		x *= v;
		y *= v;
		z *= v;
	}
	void operator/=(const float& v)
	{
		x /= v;
		y /= v;
		z /= v;
	}
	bool operator==(const Vec3& v)
	{
		return x == v.x && y == v.y && z == v.z;
	}

	float SqrMag() const
	{
		return (x * x + y * y + z * z);
	}
	float Mag() const
	{
		return Maths::Sqrt(x * x + y * y + z * z);
	}
	void Normalise()
	{
		float mag = Mag();
		x /= mag;
		y /= mag;
		z /= mag;
	}
	Vec3 GetNormalised() const
	{
		Vec3 v = *this;
		v.Normalise();
		return v;
	}

	static Vec3 ClampMag(const Vec3& v, const float& mag)
	{
		return v.GetNormalised() * mag;
	}
	static Vec3 Cross(const Vec3& a, const Vec3& b)
	{
		return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}
	static float Dot(const Vec3& a, const Vec3& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}
	static float Distance(const Vec3& a, const Vec3& b)
	{
		return (a - b).Mag();
	}
	static Vec3 MoveTowards(const Vec3& a, const Vec3& b, const float& step)
	{
		float mag = (b - a).Mag();
		return (mag <= step) ? b : (a + ((b - a) / mag) * step);
	}
	static Vec3 LerpUnclamped(const Vec3& a, const Vec3& b, const float& t)
	{
		return a * (1.0f - t) + b * t;
	}
	static Vec3 Lerp(const Vec3& a, const Vec3& b, const float& t)
	{
		return LerpUnclamped(a, b, Maths::Clamp01(t));
	}
};
