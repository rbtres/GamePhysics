//============================================================================================
//Create by Robert Bethune
//Vector2D.h
//Base Vector2D (x,y) Class has basic functions will be aded
//Creation Date 1/17/2015
//============================================================================================
#pragma once
//============================================================================================
class Vector2D
{
public:
//--------------------------------------------------------------------------------------------
	Vector2D();
	Vector2D(float x, float y);
	~Vector2D();
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
	Vector2D operator*(const float& rhs);
	Vector2D operator/(const float& rhs);

	Vector2D operator+(const Vector2D& rhs);
	Vector2D operator-(const Vector2D& rhs);

	bool operator!=(const Vector2D& rhs);
	bool operator==(const Vector2D& rhs);
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
	float Dot(const Vector2D& rhs);

	float Magnitude();
	float MagnitudeSqr();

	void Normalize();
	Vector2D Normalized();
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
	float X;
	float Y;
//--------------------------------------------------------------------------------------------
};
//============================================================================================

