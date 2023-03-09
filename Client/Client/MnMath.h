#pragma once
#include <math.h>
#define PI 3.14159265358979

struct Vector2 {
	float x;
	float y;

	static Vector2 Up;
	static Vector2 Right;

	static Vector2 One;
	static Vector2 Zero;

	Vector2()
		:	x(0.0f)
		,	y(0.0f)
	{

	}
	Vector2(int x,int y)
		: x(x)
		, y(y)
	{

	}
	Vector2(float x, float y)
		: x(x)
		, y(y)
	{

	}

	Vector2(const Vector2&) = default;
	Vector2& operator=(const Vector2&) = default;

	Vector2(Vector2&&) = default;
	Vector2& operator=(Vector2&&) = default;

	Vector2 operator+(Vector2 other)
	{
		Vector2 tmp;
		tmp.x = x + other.x;
		tmp.y = y + other.y;
		return tmp;
	}

	Vector2 operator-(Vector2 other)
	{
		Vector2 tmp;
		tmp.x = x - other.x;
		tmp.y = y - other.y;
		return tmp;
	}

	void operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
	}
	void operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
	}

	Vector2 operator*(Vector2 other)
	{
		Vector2 tmp;
		tmp.x = x * other.x;
		tmp.y = y * other.y;
		return tmp;
	}

	float Length()
	{
		return sqrtf(x * x + y * y);
	}

	Vector2& Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;

		return *this;
	}

};

namespace ya::math
{
	inline static Vector2 Rotate(Vector2 vector, float degree)
	{
		float radian = (degree / 180.0f) * PI;
		vector.Normalize();

		float x = vector.x * cosf(radian) - vector.y * sinf(radian);
		float y = vector.x * sinf(radian) + vector.y * cosf(radian);
		return Vector2(x, y);
	}
}

