#include "ParticleColDetector.h"


ParticleColDetector::ParticleColDetector()
{
}


ParticleColDetector::~ParticleColDetector()
{
}


unsigned int ParticleColDetector::SphereandSphere( PhysicsObject &sphereOne, PhysicsObject &sphereTwo, CollisionDataParticle* data)
{
	Vector3D posOne = sphereOne.getPos();
	Vector3D posTwo = sphereTwo.getPos();

	Vector3D dif = posOne - posTwo;

	float mag = dif.Magnitude();

	if (mag <= 0 || mag >= sphereOne.getRadius() + sphereTwo.getRadius())
	{
		return 0;
	}
	Vector3D normal = dif * (1.0f / mag);
	ParticleContact* contact = data->GetContact();

	contact->particle[0] = &sphereOne;
	contact->particle[1] = &sphereTwo;
	contact->restitution = 1.0;
	contact->contactNormal = normal;
	contact->penetration = sphereOne.getRadius() + sphereTwo.getRadius() - mag;

	data->AddContacts(1);

	return 1;
}

unsigned int ParticleColDetector::BoxandSphere(CubeGround &box, PhysicsObject  &sphere, CollisionDataParticle* data)
{
	Vector3D center = sphere.getPos();
	Vector3D inverse = box.getPos();

	inverse.Y = inverse.Y + (float)(box.Scale.Y / 2.0f) ;
	Vector3D relCenter = center - inverse;
	//relCenter = Vector3D(abs(relCenter.X), abs(relCenter.Y), abs(relCenter.Z));
	Vector3D closestPt = Vector3D(0, 0, 0);
	if ((relCenter.X - sphere.getRadius()) > box.Scale.X / 2 || (relCenter.Y - sphere.getRadius()) > box.Scale.Y / 2
		|| (relCenter.Z - sphere.getRadius()) > box.Scale.Z / 2)
		return 0;

	float dist;

	dist = relCenter.X;

	if (dist > box.Scale.X / 2) 
		dist = box.Scale.X / 2;

	if (dist < -box.Scale.X / 2) 
		dist = -box.Scale.X / 2;

	closestPt.X = dist;

	dist = relCenter.Y;

	if (dist > box.Scale.Y / 2 )
		dist = box.Scale.Y / 2;

	if (dist < -box.Scale.Y / 2) 
		dist = -box.Scale.Y/ 2;

	closestPt.Y = dist;
	

	dist = relCenter.Z;

	if (dist > box.Scale.Z/ 2) 
		dist = box.Scale.Z/ 2;

	if (dist < -box.Scale.Z / 2)
	{
		dist = -box.Scale.Z / 2;
	}

	closestPt.Z = dist;

	dist = (closestPt - relCenter).Magnitude();
	if (dist > sphere.getRadius())
	{
		return 0;
	}

	Vector3D closestPtWorld = inverse + closestPt;

	ParticleContact* contact = data->GetContact();

	Vector3D contactNormal = (center - closestPtWorld);
	contactNormal.Normalize();
	Vector3D contactPoint = closestPtWorld;
	float pen = dist;
	contact->particle[0] = &sphere;
	//contact->particle[1] = &box;
	contact->restitution = 1.0;
	contact->contactNormal = contactNormal;
	contact->penetration = pen;
	//contact->Initialize(contactPoint, contactNormal, pen, data->Restitution, data->Friction, box.Body, sphere.Body);

	data->AddContacts(1);

	return 1;
}