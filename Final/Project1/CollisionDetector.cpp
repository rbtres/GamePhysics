#include "CollisionDetector.h"
#include "RigidContact.h"
#include "CollisionUtils.h"
CollisionDetector::CollisionDetector()
{
	contactCount = 0;
	contactUsed = 0;
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
	
	RigidContact*contact = data->GetContact();
	contact->Initialize(posOne - planeOne.Direction * (sphereDistance + sphereOne.Radius), planeOne.Direction, -sphereDistance, data->Restitution, data->Friction, sphereOne.Body, nullptr);

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

unsigned int CollisionDetector::BoxandPlane(const CollisionBox &box, const CollisionPlane &plane, CollisionData* data)
{
	if (data->GetContactsLeft <= 0)return 0;

	if (!CollisionUtils::CollisionBoxPlane(box, plane))
	{
		return 0;
	}


	static float mults[8][3] = { { 1, 1, 1 }, { -1, 1, 1 }, { 1, -1, 1 }, { -1, -1, 1 }, { 1, 1, -1 }, { -1, 1, -1 }, { 1, -1, -1 }, { -1, -1, -1 } };
	Contacts  contact = data->Contacts;
	unsigned int contactUsed = 0;

	for (int i = 0; i < 8; i++)
	{

		
		Vector3D vertextPos = Vector3D(mults[i][0],mults[i][1], mults[i][2]);
		//vertextPos.ComponentProductUpdate(Box.HalfSize);
		vertextPos = box.Offset.Transform(vertextPos);
		float vertexDistance = vertextPos.Dot(plane.Direction);

		if (vertexDistance <= plane.Offset)
		{
			Vector3D contactPoint = plane.Direction;
			contactPoint = contactPoint * (vertexDistance - plane.Offset);
			contactPoint += vertextPos;
			Vector3D contactNormal = plane.Direction;
			float pen = plane.Offset - vertexDistance;

			contact[i] = data->Contacts[i];

			contact[i]->Initialize(contactPoint, contactNormal, pen, data->Restitution, data->Friction, box.Body, nullptr);

			contactUsed++;
			if (contactUsed == data->GetContactsLeft)
				return contactUsed;
		}
	}
	data->AddContacts(contactUsed);
	return contactUsed;
}

unsigned int CollisionDetector::BoxandSphere(const CollisionBox &box, const CollisionSphere &sphere, CollisionData* data)
{
	Vector3D center = sphere.GetAxis(3);
	Matrix inverse = box.Offset.InvMatrix();
	Vector3D relCenter = inverse.Transform(center);
	Vector3D closestPt = Vector3D(0, 0, 0);
	if ((relCenter.X - sphere.Radius) > box.HalfSize.X || (relCenter.Y - sphere.Radius) > box.HalfSize.Y
		|| (relCenter.X - sphere.Radius) > box.HalfSize.Z)
		return 0;

	float dist;

	dist = relCenter.X;

	if (dist > box.HalfSize.X) dist = box.HalfSize.X;

	if (dist < -box.HalfSize.X) dist = -box.HalfSize.X;

	closestPt.X = dist;

	dist = relCenter.Y;

	if (dist > box.HalfSize.Y) dist = box.HalfSize.Y;

	if (dist < -box.HalfSize.Y) dist = -box.HalfSize.Y;

	closestPt.Y = dist;
	

	dist = relCenter.Z;

	if (dist > box.HalfSize.Z) dist = box.HalfSize.Z;

	if (dist < -box.HalfSize.Z) dist = -box.HalfSize.Z;

	closestPt.Z = dist;

	dist = (closestPt - relCenter).MagnitudeSq();
	if (dist > sphere.Radius * sphere.Radius) return 0;

	Vector3D closestPtWorld = box.Offset.Transform(closestPt);

	RigidContact* contact = data->GetContact;

	Vector3D contactNormal = (closestPtWorld - center);
	contactNormal.Normalize();
	Vector3D contactPoint = closestPtWorld;
	float pen = sphere.Radius - sqrtf(dist);

	contact->Initialize(contactPoint, contactNormal, pen, data->Restitution, data->Friction, box.Body, sphere.Body);

	data->AddContacts(1);

	return 1;


}