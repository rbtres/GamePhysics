#pragma once
#include "CollisionPrimitive.h"

class CollisionSphere : public CollisionPrimitive
{
public:
	CollisionSphere();
	~CollisionSphere();

	float Radius;
};

