#include "Bungie.h"
#include <cmath>

Bungie::Bungie()
{
	m_k = 5;
}


Bungie::~Bungie()
{
}
void Bungie::UpdateForce(PhysicsObject* object)
{
	Vector3D force;
	force = object->getPos();
	force -= m_AnchorObject->getPos();

	float magnitude = force.Magnitude();
	magnitude = fabs(magnitude - m_restLength);
	if (magnitude <= m_restLength)
	{
		return;
	}

	magnitude *= m_k;

	force.Normalize();
	force = force * -magnitude;
	object->addForce(force);

}
void Bungie::UpdateForce(PhysicsObject* addedBody, PhysicsObject* otherBody)
{
	m_AnchorObject = otherBody;

	UpdateForce(addedBody);
}