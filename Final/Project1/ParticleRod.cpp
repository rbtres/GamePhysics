#include "ParticleRod.h"


ParticleRod::ParticleRod()
{
}


ParticleRod::~ParticleRod()
{
}
float ParticleRod::currentLength()
{
	 return particle_a->getPos().Distance(particle_b->getPos());
}
void ParticleRod::AddContact(PhysicsManager* manager)
{
	float length = currentLength();

	if (length == max_length) return;

	ParticleContact contact;
	contact.particle[0] = particle_a;
	contact.particle[1] = particle_b;
	Vector3D normal = particle_b->getPos() - particle_a->getPos();
	normal.Normalize();
	
	if (length > max_length)
	{
		contact.contactNormal = normal;
		contact.penetration = max_length - length ;
	}
	else
	{
		contact.contactNormal = normal * -1;
		contact.penetration = length - max_length;
	}
	
	contact.restitution = 0;
	manager->AddContact(contact);
}