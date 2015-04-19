#pragma once
#include "ForceGenerator.h"
class SpringForceGenerator :
	public ForceGenerator
{
public:
	SpringForceGenerator();
	SpringForceGenerator(const Vector3D &localConPoint, RigidBody* anchorBody, const Vector3D &otherConPoint, float springConstant, float restLength);
	~SpringForceGenerator();

	virtual void UpdateForce(PhysicsObject* object);
	virtual void UpdateForce(PhysicsObject* addedBody, PhysicsObject* otherBody);
	virtual void UpdateForce(RigidBody* bodyOne, RigidBody* bodyTwo = NULL);
	//Player
	PhysicsObject* m_AnchorObject;

	RigidBody* m_RigidBody;
	RigidBody* m_AnchoredBody;
protected:
	float m_k;
	float m_restLength;

	Vector3D m_ConnectionPoint;
	Vector3D m_OtherConnectionPoint;

	
};

