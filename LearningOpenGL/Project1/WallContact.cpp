#include "WallContact.h"


WallContact::WallContact()
{
}


WallContact::~WallContact()
{
}

void WallContact::AddContact(PhysicsManager* manager)
{
	for (auto physicsObject : manager->GetPhysicsVector())
	{
		float phycicsObjectX = physicsObject->getPos().X;
		if (phycicsObjectX - physicsObject->getRadius() < -WallSize)
		{
			ParticleContact contact;
			contact.penetration = phycicsObjectX - physicsObject->getRadius() + WallSize;
			contact.particle[0] = physicsObject;
			contact.restitution = .5;
			contact.contactNormal = Vector3D(1,0 , 0);
			manager->AddContact(contact);
		}
		else if (phycicsObjectX + physicsObject->getRadius() > WallSize)
		{
			ParticleContact contact;
			contact.penetration = phycicsObjectX + physicsObject->getRadius() - WallSize;
			contact.particle[0] = physicsObject;
			contact.restitution = .5;
			contact.contactNormal = Vector3D(-1, 0, 0);
			manager->AddContact(contact);
		}

		float phycicsObjectZ = physicsObject->getPos().Z;
		if (phycicsObjectZ - physicsObject->getRadius() < -WallSize)
		{
			ParticleContact contact;
			contact.penetration = phycicsObjectZ - physicsObject->getRadius() + WallSize;
			contact.particle[0] = physicsObject;
			contact.restitution = .5;
			contact.contactNormal = Vector3D(0, 0, 1);
			manager->AddContact(contact);
		}
		else if (phycicsObjectZ + physicsObject->getRadius() > WallSize)
		{
			ParticleContact contact;
			contact.penetration = phycicsObjectZ + physicsObject->getRadius() - WallSize;
			contact.particle[0] = physicsObject;
			contact.restitution = .5;
			contact.contactNormal = Vector3D(0, 0, -1);
			manager->AddContact(contact);
		}
	}
}