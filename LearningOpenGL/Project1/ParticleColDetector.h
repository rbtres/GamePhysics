#pragma once
#include <vector>
#include "CollisionDataParticle.h"
#include "CubeGround.h"
class ParticleColDetector
{
public:
	ParticleColDetector();
	~ParticleColDetector();
	unsigned int SphereandSphere( PhysicsObject &sphereOne,  PhysicsObject &sphereTwo, CollisionDataParticle* data);
	unsigned int BoxandSphere(CubeGround &box, PhysicsObject  &sphere, CollisionDataParticle* data);
};

