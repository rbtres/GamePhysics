#include "GroundContactGenerator.h"

GroundContactGenerator::GroundContactGenerator()
{
}

GroundContactGenerator::~GroundContactGenerator()
{
}

void GroundContactGenerator::AddContact(PhysicsManager* manager)
{
	for (auto physicsObject : manager->GetPhysicsVector())
	{
		float phycicsObjectY = physicsObject->getPos().Y;
		if (phycicsObjectY - physicsObject->getRadius() < GroundHeight)
		{
			ParticleContact contact;
			contact.penetration = phycicsObjectY - physicsObject->getRadius() - GroundHeight;
			contact.particle[0] = physicsObject;
			contact.restitution = .5;
			contact.contactNormal = Vector3D(0, 1, 0);
			manager->AddContact(contact);
		}
	}
}