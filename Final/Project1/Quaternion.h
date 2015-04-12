#pragma once
#include "Vector2D.h"
#include "Vector3D.h"
#include "Matrix.h"

//Comments mean I could use abbreviation and when someone looked at them it
//shows the comments so they know what it did
class Quaternion
{
public:
	Quaternion();
	Quaternion(float r, float i, float j, float k);
	Quaternion(Vector3D v);
	Quaternion(const Quaternion&);
	~Quaternion();

	void Normalize();

	//Quaternion operator*(const float& rhs){};
	void operator*=(const Quaternion& rhs);
	Quaternion operator*(const Quaternion& rhs);

	//Rotate by Vector
	void RotateByVector(const Vector3D& rhs);
	//Add Scale Vector
	void AddScaleVector(const Vector3D& rhs, float scale);

	float R;
	float I;
	float J;
	float K;
private:

	 
};

