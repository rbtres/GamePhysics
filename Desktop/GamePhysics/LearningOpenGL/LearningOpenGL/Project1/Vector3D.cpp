#include "Vector3D.h"
#include <cmath>

//--------------------------------------------------------------------------------------------
Vector3D::Vector3D()
{
	X = 0;
	Y = 0;
	Z = 0;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Vector3D::Vector3D(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Vector3D::~Vector3D()
{
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Vector3D Vector3D::operator*(const float& rhs) const
{
	return Vector3D(X * rhs, Y * rhs, Z * rhs);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Vector3D Vector3D::operator/(const float& rhs) const
{
	return Vector3D(X / rhs, Y / rhs, Z / rhs);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Vector3D Vector3D::operator+(const Vector3D& rhs) const
{
	return Vector3D(X + rhs.X, Y + rhs.Y, Z + rhs.Z);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Vector3D Vector3D::operator-(const Vector3D& rhs) const
{
	return Vector3D(X - rhs.X, Y - rhs.Y, Z - rhs.Z);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Vector3D Vector3D::operatorcross(const Vector3D& rhs) const
{
	return Vector3D((Y * rhs.Z - Z * rhs.Y), (Z * rhs.X - X * rhs.Z), (X * rhs.Y - Y * rhs.X));
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
float Vector3D::operatordot(const Vector3D& rhs) const
{
	return Y * rhs.Y + X * rhs.X + Z * rhs.Z;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
bool Vector3D::operator==(const Vector3D& rhs) const
{
	return (X == rhs.X && Y == rhs.Y && Z == rhs.Z);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
bool Vector3D::operator!=(const Vector3D & rhs) const
{
	return (X != rhs.X || Y != rhs.Y || Z != rhs.Z);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
float Vector3D::Magnitude()
{
	return sqrt(X * X + Y * Y + Z * Z);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
float Vector3D::MagnitudeSqr()
{
	return X * X + Y * Y + Z * Z;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void Vector3D::Normalize()
{
	Vector3D norm = Normalized();
	X = norm.X;
	Y = norm.Y;
	Z = norm.Z;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Vector3D Vector3D::Normalized()
{
	return (*this / Magnitude());
}
//--------------------------------------------------------------------------------------------