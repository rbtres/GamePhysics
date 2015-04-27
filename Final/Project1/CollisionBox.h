#pragma once
#include "CollisionPrimitive.h"
class CollisionBox :
	public CollisionPrimitive
{
public:
	CollisionBox();
	~CollisionBox();

	Vector3D Vertices[8];

	void Init(Vector3D halfsize);
	Vector3D HalfSize;
};

