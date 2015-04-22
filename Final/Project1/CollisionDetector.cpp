#include "CollisionDetector.h"
#include "RigidContact.h"

CollisionDetector::CollisionDetector()
{
}


CollisionDetector::~CollisionDetector()
{
}
unsigned int CollisionDetector::SphereandSphere(const CollisionSphere &sphereOne,const CollisionSphere &sphereTwo, CollisionData* data)
{
	if (data->GetContactsLeft() <= 0)
	{
		return 0;
	}
	
	Vector3D posOne = sphereOne.GetAxis(3);
	Vector3D posTwo = sphereTwo.GetAxis(3);

	Vector3D dif = posOne - posTwo;

	float mag = dif.Magnitude();

	if (mag <= 0 || mag >= sphereOne.Radius + sphereTwo.Radius)
	{
		return 0;
	}
	Vector3D normal = dif * (1.0f / mag);
	RigidContact* contact = data->GetContact();
	contact->Initialize(posOne + dif * .5f, normal, sphereOne.Radius + sphereTwo.Radius - mag, data->Restitution, data->Friction, sphereOne.Body, sphereTwo.Body);

	data->AddContacts(1);
	return 1;
}

unsigned int CollisionDetector::SphereandHalfSpace(const CollisionSphere &sphereOne, const CollisionPlane &planeOne, CollisionData* data)
{
	if (data->GetContactsLeft() <= 0)
	{
		return 0;
	}

	Vector3D posOne = sphereOne.GetAxis(3);

	float sphereDistance = planeOne.Direction.Dot(posOne);
	
	if (sphereDistance >= 0)
		return 0;
	
	RigidContact* contact = data->GetContact();
	contact->Initialize(posOne-planeOne.Direction * (sphereDistance + sphereOne.Radius), planeOne.Direction, -sphereDistance, data->Restitution, data->Friction, sphereOne.Body, nullptr);

	data->AddContacts(1);
	return 1;
}

unsigned int CollisionDetector::SphereandTruePlane(const CollisionSphere &sphereOne, const CollisionPlane &planeOne, CollisionData* data)
{
	if (data->GetContactsLeft() <= 0)
	{
		return 0;
	}

	Vector3D posOne = sphereOne.GetAxis(3);

	float sphereDistance = planeOne.Direction.Dot(posOne) - planeOne.Offset;

	if (sphereDistance * sphereDistance >= sphereOne.Radius * sphereOne.Radius)
		return 0;

	RigidContact* contact = data->GetContact();
	contact->Initialize(posOne - planeOne.Direction * (sphereDistance + sphereOne.Radius), planeOne.Direction, -sphereDistance, data->Restitution, data->Friction, sphereOne.Body, nullptr);

	data->AddContacts(1);
	return 1;

}