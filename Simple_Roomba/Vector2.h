#pragma once

struct Vector2
{
	float x = 0;
	float y = 0;

	Vector2(float x = 0, float y = 0)
		:x(x), y(y)
	{
	}

	Vector2 operator*(int scalar) const
	{
		return Vector2(x * scalar, y * scalar);
	}

	Vector2 operator+(Vector2 other) const
	{
		return Vector2(x + other.x, y + other.y);
	}

	void Normalize()
	{
		float length = this->x * this->x + this->y * this->y;
		this->x /= length;
		this->y /= length;
	}
};