#include "ParticleCable.h"

ParticleCable::ParticleCable()
{
}


ParticleCable::~ParticleCable()
{
}

float ParticleCable::currentLength()
{
	return particle_a->getPos().Distance(particle_b->getPos());
}

void ParticleCable::AddContact(PhysicsManager* manager)
{
	float length = currentLength();

	if (length < max_length) return;

	ParticleContact contact;
	contact.particle[0] = particle_a;
	contact.particle[1] = particle_b;
	Vector3D normal = particle_b->getPos() - particle_a->getPos();
	normal.Normalize();
	contact.contactNormal = normal;
	contact.penetration = length - max_length;
	contact.restitution = restitution;
	manager->AddContact(contact);
	
}