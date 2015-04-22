#pragma once
#include "Vector3D.h"
class CollisionPlane
{
public:
	CollisionPlane();
	~CollisionPlane();

	Vector3D Direction;
	float Offset;
};

