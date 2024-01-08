#include <iostream>
#include "Vector2.h"

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2(const Vector2& v)
{
	x = v.x;
	y = v.y;
}

Vector2 Vector2::operator+(const Vector2& v)
{
	return Vector2(this->x + v.x, this->y + v.y);
}

Vector2 Vector2::operator=(const Vector2& v)
{
	this->x = v.x;
	this->y = v.y;
	return *this;
}

Vector2 Vector2::operator*(float number){
	return Vector2(x * number, y * number);
}

void Vector2::Normalise()
{
	x = x / LenZero();
	y = y / LenZero();
}
float Vector2::LenZero()
{
	return std::sqrt(x * x + y * y);
}

float Vector2::Len(Vector2 v)
{
	float a, b;
	a = abs(x - v.x);
	b = abs(y - v.y);
	return std::sqrt(a*a + b*b);
}

std::ostream &operator<<(std::ostream& os, const Vector2 &v)
{
	os << v.x << " " << v.y;
	return os;
}
