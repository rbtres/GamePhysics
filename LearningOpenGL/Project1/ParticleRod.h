#pragma once
#include "ParticleContactGenerator.h"
class ParticleRod :
	public ParticleContactGenerator
{
public:
	ParticleRod();
	~ParticleRod();
	PhysicsObject* particle_a, *particle_b;
	void AddContact(PhysicsManager* manager);
	float max_length;
private:
	float currentLength();
};

