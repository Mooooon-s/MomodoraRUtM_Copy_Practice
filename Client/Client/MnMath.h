#pragma once
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
};

