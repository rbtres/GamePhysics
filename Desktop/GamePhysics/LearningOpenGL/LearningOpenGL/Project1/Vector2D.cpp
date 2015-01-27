#include "Vector2D.h"
#include <cmath>

//--------------------------------------------------------------------------------------------
Vector2D::Vector2D()
{
	X = 0;
	Y = 0;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Vector2D::Vector2D(float x, float y)
{
	X = x;
	Y = y;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Vector2D::~Vector2D()
{
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Vector2D Vector2D::operator*(const float& rhs)
{
	return Vector2D(X * rhs, Y * rhs);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Vector2D Vector2D::operator/(const float& rhs)
{
	return Vector2D(X / rhs, Y / rhs);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Vector2D Vector2D::operator+(const Vector2D& rhs)
{
	return Vector2D(X + rhs.X, Y + rhs.Y);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Vector2D Vector2D::operator-(const Vector2D& rhs)
{
	return Vector2D(X - rhs.X, Y - rhs.Y);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
bool Vector2D::operator==(const Vector2D& rhs)
{
	return X == rhs.X && Y == rhs.Y;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
bool Vector2D::operator!=(const Vector2D& rhs)
{
	return X != rhs.X || Y != rhs.Y;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
float Vector2D::Dot(const Vector2D& rhs)
{
	return X * rhs.X + Y * rhs.Y;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
float Vector2D::Magnitude()
{
	return sqrt(Dot(*this));
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
float Vector2D::MagnitudeSqr()
{
	return Dot(*this);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void Vector2D::Normalize()
{
	Vector2D norm = Normalized();
	X = norm.X;
	Y = norm.Y;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Vector2D Vector2D::Normalized()
{
	return (*this / Magnitude());
}
//--------------------------------------------------------------------------------------------