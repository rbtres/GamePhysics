#include "SpringForceGenerator.h"
#include <cmath>

SpringForceGenerator::SpringForceGenerator()
{
	m_k = 5;
}
SpringForceGenerator::SpringForceGenerator(const Vector3D &localConPoint, RigidBody* anchorBody, const Vector3D &otherConPoint, float springConstant, float restLength)
{
	m_AnchoredBody = anchorBody;
	m_ConnectionPoint = localConPoint;
	m_OtherConnectionPoint = otherConPoint;
	m_k = springConstant;
	m_restLength = restLength;
}

SpringForceGenerator::~SpringForceGenerator()
{
}

void SpringForceGenerator::UpdateForce(PhysicsObject* object)
{
	Vector3D force;
	force = object->getPos();
	force -= m_AnchorObject->getPos();

	float magnitude = force.Magnitude();
	magnitude = fabs(magnitude - m_restLength);
	magnitude *= m_k;

	force.Normalize();
	force = force * -magnitude;
	object->addForce(force);

}
void SpringForceGenerator::UpdateForce(PhysicsObject* addedBody, PhysicsObject* otherBody)
{
	m_AnchorObject = otherBody;

	UpdateForce(addedBody);
}

void SpringForceGenerator::UpdateForce(RigidBody* bodyOne, RigidBody* bodyTwo)
{
	Vector3D lws = bodyOne->GetPointInWorldSpace(m_ConnectionPoint);
	Vector3D ows = m_AnchoredBody->GetPointInWorldSpace(m_OtherConnectionPoint);

	Vector3D force = lws - ows;

	float magnitude = force.Magnitude();

	magnitude = abs(magnitude - m_restLength);
	magnitude *= m_k;
	bodyOne->AddForceAtPoint(force, lws);
}