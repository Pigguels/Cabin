#pragma once
#include "Maths/Maths.h"
#include "Maths/Mat4.h"

struct Vec4
{
	Vec4()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}
	Vec4(const float& d)
	{
		x = d;
		y = d;
		z = d;
		w = d;
	}
	Vec4(const float& _x, const float& _y, const float& _z, const float& _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
	Vec4(const Vec4& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 0.0f;

	Vec4 operator+(const Vec4& that) const
	{
		return Vec4(x + that.x, y + that.y, z + that.z, w + that.w);
	}
	Vec4 operator-(const Vec4& that) const
	{
		return Vec4(x - that.x, y - that.y, z - that.z, w - that.w);
	}
	Vec4 operator*(const float& v) const
	{
		return Vec4(x * v, y * v, z * v, w * v);
	}
	Vec4 operator*(const Mat4& m) const
	{
		return Vec4(
			x * m.m[0] + y * m.m[4] + z * m.m[8] + w * m.m[12],
			x * m.m[1] + y * m.m[5] + z * m.m[9] + w * m.m[13],
			x * m.m[2] + y * m.m[6] + z * m.m[10] + w * m.m[14],
			x * m.m[3] + y * m.m[7] + z * m.m[11] + w * m.m[15]
		);
	}
	Vec4 operator/(const float& v) const
	{
		return Vec4(x / v, y / v, z / v, w / v);
	}
	void operator+=(const Vec4& that)
	{
		x += that.x;
		y += that.y;
		z += that.z;
		w += that.w;
	}
	void operator-=(const Vec4& that)
	{
		x -= that.x;
		y -= that.y;
		z -= that.z;
		w -= that.w;
	}
	void operator*=(const float& v)
	{
		x *= v;
		y *= v;
		z *= v;
		w *= v;
	}
	void operator/=(const float& v)
	{
		x /= v;
		y /= v;
		z /= v;
		w /= v;
	}
	bool operator==(const Vec4& v)
	{
		return x == v.x && y == v.y && z == v.z && w == v.w;
	}

	float SqrMag() const
	{
		return (x * x + y * y + z * z + w * w);
	}
	float Mag() const
	{
		return Maths::Sqrt(x * x + y * y + z * z + w * w);
	}
	void Normalise()
	{
		float mag = Mag();
		x /= mag;
		y /= mag;
		z /= mag;
		w /= mag;
	}
	Vec4 GetNormalised() const
	{
		Vec4 v = *this;
		v.Normalise();
		return v;
	}

	static Vec4 ClampMag(const Vec4& v, const float& mag)
	{
		return v.GetNormalised() * mag;
	}
	static float Dot(const Vec4& a, const Vec4& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}
	static float Distance(const Vec4& a, const Vec4& b)
	{
		return (a - b).Mag();
	}
	static Vec4 MoveTowards(const Vec4& a, const Vec4& b, const float& step)
	{
		float mag = (b - a).Mag();
		return (mag <= step) ? b : (a + ((b - a) / mag) * step);
	}
	static Vec4 LerpUnclamped(const Vec4& a, const Vec4& b, const float& t)
	{
		return a * (1.0f - t) + b * t;
	}
	static Vec4 Lerp(const Vec4& a, const Vec4& b, const float& t)
	{
		return LerpUnclamped(a, b, Maths::Clamp01(t));
	}
};
