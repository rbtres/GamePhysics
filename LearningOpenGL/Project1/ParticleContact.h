#pragma once
#include "Particle.h"
class ParticleContact
{
public:
	ParticleContact();
	~ParticleContact();

	PhysicsObject* particle[2];

	float restitution;
	float penetration;

	Vector3D contactNormal;
	float calculateSeparatingVelocity();
	void resolve(float duration);

private:
	void resolveVelocity(float duration);
	void resolveInterpenetration(float duration);

	float getInverseMass();
};

