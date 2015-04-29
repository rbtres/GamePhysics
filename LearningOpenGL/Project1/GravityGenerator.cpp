#include "GravityGenerator.h"
#include <iostream>
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
//Au^3 / solar mass * sec ^2
const long double GravityGenerator::GRAVITY = (3.965 * pow(10, -14));
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
GravityGenerator::GravityGenerator()
{

}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
GravityGenerator::~GravityGenerator()
{

}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void GravityGenerator::UpdateForce(PhysicsObject* object)
{
	Vector3D force;
	force.Y = -9.8f * object->getMass();
	object->addForce(force);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void GravityGenerator::UpdateForce(PhysicsObject* addedBody, PhysicsObject* otherBody)
{
	Vector3D forceBetweenObjects;
	Vector3D distanceBetweenSq;
	Vector3D normalDir;

	float M1 = addedBody->getMass();
	float M2 = otherBody->getMass();
	
	distanceBetweenSq = Vector3D::DistanceSqVec(addedBody->getPos(), otherBody->getPos());

	normalDir = distanceBetweenSq.Normalized();

	float magSq = distanceBetweenSq.MagnitudeSq();

	
	forceBetweenObjects = normalDir * (float)(-GRAVITY * ((M1 * M2) / (magSq)));

	addedBody->addForce(forceBetweenObjects);
	
}
//--------------------------------------------------------------------------------------------
