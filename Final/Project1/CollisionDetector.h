#pragma once
#include "CollisionSphere.h"
#include "CollisionData.h"
#include "CollisionPlane.h"
#include "Box.h"
#include <vector>

typedef std::vector<RigidContact*> Contacts;

class CollisionDetector
{
public:
	CollisionDetector();
	~CollisionDetector();

	//Contacts contact;


	unsigned int SphereandSphere(const CollisionSphere &sphereOne,const CollisionSphere &sphereTwo, CollisionData* data);
	unsigned int SphereandHalfSpace(const CollisionSphere &sphereOne, const CollisionPlane &planeOne, CollisionData* data);
	unsigned int SphereandTruePlane(const CollisionSphere &sphereOne, const CollisionPlane &planeOne, CollisionData* data);
	unsigned int BoxandPlane(const CollisionBox &box, const CollisionPlane &plane, CollisionData* data);
	unsigned int BoxandSphere(const CollisionBox &box, const CollisionSphere &sphere, CollisionData* data);
private:


};

