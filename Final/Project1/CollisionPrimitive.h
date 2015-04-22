#pragma once
#include "RigidBody.h"
class CollisionPrimitive
{
public:
	CollisionPrimitive();
	~CollisionPrimitive();

	RigidBody* Body;
	
	Matrix Offset;

	void CalculateInternals() { m_transform = Body->GetTransformMatrix() * Offset; }

	inline Vector3D GetAxis(unsigned index) const { return m_transform.GetAxis(index);};

protected:
	Matrix m_transform;

};

