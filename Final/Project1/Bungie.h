#pragma once
#include "ForceGenerator.h"
class Bungie :
	public ForceGenerator
{
public:
	Bungie();
	~Bungie();
	virtual void UpdateForce(PhysicsObject* object);
	virtual void UpdateForce(PhysicsObject* addedBody, PhysicsObject* otherBody);

	//Player
	PhysicsObject* m_AnchorObject;
protected:
	float m_k;
	float m_restLength;
};

