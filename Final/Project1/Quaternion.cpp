#include "Quaternion.h"
#include <math.h>

Quaternion::Quaternion(const Quaternion& rhs)
{
	R = rhs.R;
	I = rhs.I;
	J = rhs.J;
	K = rhs.K;
}

Quaternion::Quaternion()
{
	R = 0;
	I = 0;
	J = 0;
	K = 0;
}

Quaternion::Quaternion(float r, float i, float j, float k)
{
	R = r;
	I = i;
	J = j;
	K = k;
}

Quaternion::Quaternion(Vector3D v)
{
	R = 0;
	I = v.X;
	J = v.Y;
	K = v.Z;
}

Quaternion::~Quaternion()
{
}

void Quaternion::Normalize()
{
	float magnitude = R*R + I * I + J * J + K * K;

	if (magnitude == 0)
	{
		R = 1;
		return;
	}

	float length = 1.0f / sqrtf(magnitude);

	R *= magnitude;
	I *= magnitude;
	J *= magnitude;
	K *= magnitude;
}

void Quaternion::operator*=(const Quaternion& rhs)
{
	Quaternion q = *this;

	R = q.R * rhs.R - q.I * rhs.I - q.J * rhs.J - q.K * rhs.K;
	I = q.R * rhs.I + q.I *rhs.R + q.J * rhs.K - q.K * rhs.J;
	J = q.R * rhs.J + q.J * rhs.R + q.K * rhs.I - q.I * rhs.K;
	K = q.R * rhs.K + q.K * rhs.R + q.I * rhs.J - q.J * rhs.I;
}
Quaternion Quaternion::operator*(const Quaternion& rhs)
{
	Quaternion q = Quaternion(*this);
	q *= rhs;
	return q;
}

void Quaternion::RotateByVector(const Vector3D& rhs)
{
	Quaternion q = Quaternion(rhs);

	(*this) *= q;
}

void Quaternion::AddScaleVector(const Vector3D& rhs, float scale)
{
	Vector3D scaledVector = Vector3D(rhs);
	scaledVector = scaledVector * scale;
	Quaternion q = Quaternion(rhs);

	q *= (*this);
	R += q.R * .5f;
	I += q.I * .5f;
	J += q.J * .5f;
	K += q.K * .5f;
}