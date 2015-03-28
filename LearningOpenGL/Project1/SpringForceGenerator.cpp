#include "SpringForceGenerator.h"
#include <cmath>

SpringForceGenerator::SpringForceGenerator()
{
	m_k = 5;
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
