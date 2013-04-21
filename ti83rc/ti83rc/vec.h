#ifndef _TI83RC_VEC_H
#define _TI83RC_VEC_H

#include <cmath>

struct vec2
{
	float x, y;
	
	vec2()
		: x(0.0f), y(0.0f)
	{
	}
	vec2(float x, float y)
		: x(x), y(y)
	{
	}

	vec2 operator+(const vec2& rhs) const {
		return vec2(x + rhs.x, y + rhs.y);
	}
	vec2 operator-(const vec2& rhs) const {
		return vec2(x - rhs.x, y - rhs.y);
	}
	vec2 operator*(const vec2& rhs) const {
		return vec2(x * rhs.x, y * rhs.y);
	}
	vec2 operator/(const vec2& rhs) const {
		return vec2(x / rhs.x, y / rhs.y);
	}
	vec2 operator*(float rhs) const {
		return vec2(x * rhs, y * rhs);
	}
	vec2 operator/(float rhs) const {
		return vec2(x / rhs, y / rhs);
	}
	

	vec2& operator+=(const vec2& rhs) {
		x += rhs.x; y += rhs.y; return *this;
	}
	vec2& operator-=(const vec2& rhs) {
		x -= rhs.x; y -= rhs.y; return *this;
	}
	vec2& operator*=(const vec2& rhs) {
		x *= rhs.x; y *= rhs.y; return *this;
	}
	vec2& operator/=(const vec2& rhs) {
		x /= rhs.x; y /= rhs.y; return *this;
	}
	vec2& operator*=(float rhs) {
		x *= rhs; y *= rhs; return *this;
	}
	vec2& operator/=(float rhs) {
		x /= rhs; y /= rhs; return *this;
	}

	float length_squared() const {
		return x*x + y*y;
	}

	float length() const {
		return sqrt(length_squared());
	}

	void normalize() {
		float invl = 1.0f / length();
		x *= invl;
		y *= invl;
	}
	void normalize_if_not_zero() {
		float lensq = length_squared();
		if (lensq != 0.0f) {
			float invl = 1.0f / sqrt(lensq);
			x *= invl;
			y *= invl;
		}
	}
	vec2 normalized() const {
		vec2 c = *this;
		c.normalize();
		return c;
	}

	vec2 right() const {
		return vec2(-y, x);
	}
};

inline vec2 operator*(float lhs, const vec2& rhs) {
	return vec2(lhs * rhs.x, lhs * rhs.y);
}

#endif
