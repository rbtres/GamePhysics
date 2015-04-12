#pragma once
#include "ParticleContactGenerator.h"
class WallContact :public ParticleContactGenerator
{
public:
	WallContact();
	~WallContact();
	void AddContact(PhysicsManager* manager);
	float WallSize = 50;
};

