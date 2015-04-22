#pragma once
#include "CollisionPrimitive.h"
class CollisionBox :
	public CollisionPrimitive
{
public:
	CollisionBox();
	~CollisionBox();

	Vector3D Halfsize;
};

