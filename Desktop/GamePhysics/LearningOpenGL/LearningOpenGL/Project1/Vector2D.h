//============================================================================================
//Create by Robert Bethune
//Vector2D.h
//Base Vector Class has addition(+), multiplication(*), dot(dot), and cross(cross)
//Creation Date 1/17/2015
//============================================================================================
#pragma once
class Vector2D
{
public:
	Vector2D();
	Vector2D(float x, float y);
	~Vector2D();

	Vector2D operator*(const float) const;
	Vector2D operator/(const float) const;
	Vector2D operator*(const Vector2D) const;
	Vector2D operator+(const Vector2D) const;
	Vector2D operator-(const Vector2D) const;

	float X;
	float Y;
};

