#pragma once
#include "ForceGenerator.h"
class SpringForceGenerator :
	public ForceGenerator
{
public:
	SpringForceGenerator();
	~SpringForceGenerator();

	virtual void UpdateForce(PhysicsObject* object);
	virtual void UpdateForce(PhysicsObject* addedBody, PhysicsObject* otherBody);

	//Player
	PhysicsObject* m_AnchorObject;
protected:
	float m_k;
	float m_restLength;
};

