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
	contact->restitution = 1;
	contact->contactNormal = normal;
	contact->penetration = sphereOne.getRadius() + sphereTwo.getRadius() - mag;

	data->AddContacts(1);

	return 1;
}