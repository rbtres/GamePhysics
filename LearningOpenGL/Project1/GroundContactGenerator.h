#pragma once
#include "ParticleContactGenerator.h"
class GroundContactGenerator :
	public ParticleContactGenerator
{
public:
	GroundContactGenerator();
	~GroundContactGenerator();
	void AddContact(PhysicsManager* manager);
	float GroundHeight;
};

