#pragma once
#include "CollisionSphere.h"
#include "CollisionData.h"
#include "CollisionPlane.h"
class CollisionDetector
{
public:
	CollisionDetector();
	~CollisionDetector();

	unsigned int SphereandSphere(const CollisionSphere &sphereOne,const CollisionSphere &sphereTwo, CollisionData* data);
	unsigned int SphereandHalfSpace(const CollisionSphere &sphereOne, const CollisionPlane &planeOne, CollisionData* data);
	unsigned int SphereandTruePlane(const CollisionSphere &sphereOne, const CollisionPlane &planeOne, CollisionData* data);
private:

};

