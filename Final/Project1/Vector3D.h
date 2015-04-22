//============================================================================================
//Create by Robert Bethune
//Vector3D.h
//Base Vector3D (x,y,z) Has basic necessary function & includes vector distance Methods
//Creation Date 1/17/2015
//Last Updated 1/31/2015
//============================================================================================
#pragma once
//============================================================================================
class Vector3D
{
public:
//--------------------------------------------------------------------------------------------
	Vector3D();
	Vector3D(const Vector3D&);
	Vector3D(float x, float y, float z);
	~Vector3D();
	static const Vector3D Zero;
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
	Vector3D operator*(const float& rhs) const;
	Vector3D operator/(const float& rhs);

	Vector3D operator+(const Vector3D& rhs);
	Vector3D operator-(const Vector3D& rhs);

	void operator+=(const Vector3D& rhs);
	void operator-=(const Vector3D& rhs);

	bool operator!=(const Vector3D& rhs);
	bool operator==(const Vector3D& rhs);

//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
	float Dot(const Vector3D& rhs) const;
	Vector3D Cross(const Vector3D& rhs);
	
	float Distance(const Vector3D& rhs);
	float DistanceSq(const Vector3D& rhs);

	static float DistanceSq(const Vector3D& lhs, const Vector3D& rhs);
	static float Distance(const Vector3D& lhs, const Vector3D& rhs);
	static Vector3D DistanceSqVec(const Vector3D& lhs, const Vector3D& rhs);

	float Magnitude();
	float MagnitudeSq();

	void Normalize();
	Vector3D Normalized();
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
	float X;
	float Y;
	float Z;
//--------------------------------------------------------------------------------------------
};
//============================================================================================
