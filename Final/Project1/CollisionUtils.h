#pragma once
#include "Vector3D.h"
#include "CollisionPlane.h"
#include "CollisionBox.h"
class CollisionUtils
{
public:
	CollisionUtils();
	~CollisionUtils();

	static bool CollisionBoxPlane( const CollisionBox  &box, const CollisionPlane &plane)
	{
		return true;
	}

	static bool TryAxis(const CollisionBox& boxOne, const CollisionBox& boxTwo, Vector3D normal, const Vector3D center, int index, float &smallestPenetration, int &smallestCase);
};

