#pragma once
#include "CollisionSphere.h"
#include "CollisionData.h"
#include "CollisionPlane.h"
#include "CollisionBox.h"
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
	unsigned int BoxandBox(const CollisionBox &boxOne, const CollisionBox &boxTwo, CollisionData* data);

	Vector3D GetContactPoint( Vector3D& pointOne,  const Vector3D& directionOne, float oneSize,
		Vector3D& pointTwo, const  Vector3D& directionTwo, float twoSize, bool useOne);

	void FillPointFaceBoxBox(const CollisionBox& boxOne, const CollisionBox& boxTwo, const Vector3D center, CollisionData* data, int best, float pen);
private:


};

