#pragma once
#include "Vec2.h"

struct Rect
{
	Rect()
	{
		l = 0.0f;
		r = 0.0f;
		t = 0.0f;
		b = 0.0f;
	}
	Rect(float _l, float _r, float _t, float _b)
	{
		l = _l;
		r = _r;
		t = _t;
		b = _b;
	}

	float l, r, t, b;

	bool Contains(const Vec2& point) const { return (point.x >= l && point.x <= r && point.y >= b && point.y <= t); }
	bool Intersects(const Rect& rect) const { return (l < rect.r && r > rect.l && t < rect.b && b > rect.t); }
};

