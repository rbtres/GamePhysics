#include "GravityGenerator.h"
#include <iostream>
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
const long double GravityGenerator::GRAVITY = (6.67384 * pow(10, -11));
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
	//do some cool shit
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void GravityGenerator::UpdateForce(PhysicsObject* addedBody, PhysicsObject* otherBody)
{
	float distanceSQ = addedBody->getPos().DistanceSq(otherBody->getPos());
	Vector3D direction = otherBody->getPos() - addedBody->getPos();
	direction.Normalize();
	float force = ((-GRAVITY * addedBody->getMass() * otherBody->getMass()) / distanceSQ);
	Vector3D gravityOnObject1 = direction * force * 10000;
	otherBody->addForce(gravityOnObject1);

	//->AddForce(gravityOnObject2);
	/*
	Vector3D forceBetweenObjects;
	Vector3D distanceBetweenSq;
	Vector3D normalDir;

	float M1 = addedBody->getMass();
	float M2 = otherBody->getMass();
	
	distanceBetweenSq = Vector3D::DistanceSqVec(addedBody->getPos(), otherBody->getPos());

	normalDir = distanceBetweenSq.Normalized();

	float magSq = distanceBetweenSq.MagnitudeSq();

	
	forceBetweenObjects = normalDir * (-GRAVITY * ((M1 * M2) / (magSq)));

	/*
	if (addedBody->getPos().X < otherBody->getPos().X)
	{
		forceBetweenObjects.X = forceBetweenObjects.X * -1;
	}
	
	if (addedBody->getPos().Y < otherBody->getPos().Y)
	{
		forceBetweenObjects.Y = forceBetweenObjects.Y * -1;
	}
	
	addedBody->addForce(forceBetweenObjects);
	*/
}
//--------------------------------------------------------------------------------------------
