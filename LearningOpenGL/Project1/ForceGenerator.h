#pragma once
#include "PhysicsObject.h"
class ForceGenerator
{
public:
	virtual void UpdateForce(PhysicsObject* object) = 0;
	virtual void UpdateForce(PhysicsObject* addedBody, PhysicsObject* otherBody) = 0;
};

