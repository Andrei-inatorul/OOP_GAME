#pragma once
#include <iostream>

class Vector2
{
public:
	float x, y;
	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2& v);
	Vector2 operator+(const Vector2& v);
	Vector2 operator=(const Vector2& v);
	Vector2 operator*(float number);
	friend Vector2 operator*(float number, const Vector2& v){
		return Vector2(v.x * number, v.y * number);
	}
	void Normalise();
	float LenZero();
	float Len(Vector2 v);
	friend std::ostream& operator<<(std::ostream& os, const Vector2& v);
};
