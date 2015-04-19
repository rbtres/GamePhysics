#pragma once
#include "PhysicsObject.h"
#include "RigidBody.h"
class ForceGenerator
{
public:
	virtual void UpdateForce(PhysicsObject* object) = 0;
	virtual void UpdateForce(PhysicsObject* addedBody, PhysicsObject* otherBody) = 0;
	virtual void UpdateForce(RigidBody* bodyOne, RigidBody* bodyTwo = NULL) = 0;
};

