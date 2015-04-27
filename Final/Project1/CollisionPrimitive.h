#pragma once
#include "RigidBody.h"
class CollisionPrimitive
{
public:
	CollisionPrimitive();
	~CollisionPrimitive();

	RigidBody* Body;
	
	Matrix Offset;
	Matrix Transform;
	void CalculateInternals() { Transform = Body->GetTransformMatrix() * Offset; }

	inline Vector3D GetAxis(unsigned index) const { return Transform.GetAxis(index); };

protected:
	

};

