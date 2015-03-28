#pragma once
#include "ParticleContactGenerator.h"
class ParticleCable :
	public ParticleContactGenerator
{
public:
	ParticleCable();
	~ParticleCable();
	PhysicsObject* particle_a, *particle_b;
	float max_length;
	void AddContact(PhysicsManager* manager);
	float restitution;

private:
	float currentLength();
};

