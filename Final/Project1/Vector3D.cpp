#include "Vector3D.h"
#include <cmath>


Vector3D const Vector3D::Zero = Vector3D(0, 0, 0);
//--------------------------------------------------------------------------------------------
Vector3D::Vector3D()
{
	X = 0;
	Y = 0;
	Z = 0;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Vector3D::Vector3D(const Vector3D& rhs)
{
	X = rhs.X;
	Y = rhs.Y;
	Z = rhs.Z;
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
void Vector3D::operator+=(const Vector3D& rhs)
{
	X += rhs.X;
	Y += rhs.Y;
	Z += rhs.Z;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void Vector3D::operator-=(const Vector3D& rhs)
{
	X -= rhs.X;
	Y -= rhs.Y;
	Z -= rhs.Z;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Vector3D Vector3D::operator*(const float& rhs) 
{
	return Vector3D(X * rhs, Y * rhs, Z * rhs);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Vector3D Vector3D::operator/(const float& rhs)
{
	return Vector3D(X / rhs, Y / rhs, Z / rhs);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Vector3D Vector3D::operator+(const Vector3D& rhs)
{
	return Vector3D(X + rhs.X, Y + rhs.Y, Z + rhs.Z);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Vector3D Vector3D::operator-(const Vector3D& rhs)
{
	return Vector3D(X - rhs.X, Y - rhs.Y, Z - rhs.Z);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
bool Vector3D::operator==(const Vector3D& rhs) 
{
	return (X == rhs.X && Y == rhs.Y && Z == rhs.Z);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
bool Vector3D::operator!=(const Vector3D& rhs)
{
	return (X != rhs.X || Y != rhs.Y || Z != rhs.Z);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Vector3D Vector3D::Cross(const Vector3D& rhs)
{
	return Vector3D((Y * rhs.Z - Z * rhs.Y), (Z * rhs.X - X * rhs.Z), (X * rhs.Y - Y * rhs.X));
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
float Vector3D::Dot(const Vector3D& rhs)
{
	return Y * rhs.Y + X * rhs.X + Z * rhs.Z;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
float Vector3D::Magnitude()
{
	return sqrt(Dot(*this));
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
float Vector3D::MagnitudeSq()
{
	return Dot(*this);
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

//--------------------------------------------------------------------------------------------
float Vector3D::Distance(const Vector3D& rhs)
{
	float distance;
	
	distance = sqrtf(DistanceSq(rhs));

	return distance;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
float Vector3D::DistanceSq(const Vector3D& rhs)
{
	float distanceSquared;
	distanceSquared = (X - rhs.X) * (X - rhs.X) + (Y - rhs.Y) * (Y - rhs.Y)
		+ (Z - rhs.Z) * (Z - rhs.Z);

	return distanceSquared;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
float Vector3D::Distance(const Vector3D& lhs, const Vector3D& rhs)
{
	float distance;

	distance = sqrtf(DistanceSq(lhs, rhs));

	return distance;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
float Vector3D::DistanceSq(const Vector3D& lhs, const Vector3D& rhs)
{
	float distanceSquared;
	distanceSquared = (lhs.X - rhs.X) * (lhs.X - rhs.X) + (lhs.Y - rhs.Y) * (lhs.Y - rhs.Y)
		+ (lhs.Z - rhs.Z) * (lhs.Z - rhs.Z);

	return distanceSquared;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Vector3D Vector3D::DistanceSqVec(const Vector3D& lhs, const Vector3D& rhs)
{
	Vector3D distanceSqrVec;
	distanceSqrVec = Vector3D(lhs.X - rhs.X * lhs.X - rhs.X, lhs.Y - rhs.Y * lhs.Y - rhs.Y,
		lhs.Z - rhs.Z * lhs.Z - rhs.Z);

	return distanceSqrVec;
}
//--------------------------------------------------------------------------------------------