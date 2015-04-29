#pragma once
#include <vector>
#include "CollisionDataParticle.h"
class ParticleColDetector
{
public:
	ParticleColDetector();
	~ParticleColDetector();
	unsigned int SphereandSphere( PhysicsObject &sphereOne,  PhysicsObject &sphereTwo, CollisionDataParticle* data);
};

