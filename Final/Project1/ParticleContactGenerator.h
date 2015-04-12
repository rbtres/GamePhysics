#pragma once
#include "PhysicsManager.h"
class ParticleContactGenerator
{
public:

	virtual void AddContact(PhysicsManager* manager) = 0;
};

