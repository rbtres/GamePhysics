#pragma once
#include "PhysicsManager.h"
class ParticleContactGenerator
{
public:

	virtual int AddContact(PhysicsManager &manager);
};

