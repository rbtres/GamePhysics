#pragma once
#include "Vector3D.h"
#include "RigidBody.h"
class RigidContact
{
public:
	RigidContact();
	~RigidContact();

	void Initialize(Vector3D contactPoint, Vector3D contactNormal, float pen, float rest,float fric, RigidBody* one, RigidBody* two = nullptr);

private:
	Vector3D m_contactPoint;
	Vector3D m_contactNormal;

	float m_penetration;
	float m_restitution;
	float m_friction;

	RigidBody* m_bodyOne;
	RigidBody* m_bodyTwo;
};

