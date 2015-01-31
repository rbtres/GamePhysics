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
	Vector3D forceBetweenObjects;
	Vector3D distanceBetweenSq;
	Vector3D normalDir;

	float M1 = addedBody->getMass();
	float M2 = otherBody->getMass();
	
	distanceBetweenSq = Vector3D::DistanceSqVec(addedBody->getPos(), otherBody->getPos());

	normalDir = distanceBetweenSq.Normalized();

	float magSq = distanceBetweenSq.MagnitudeSq();

	
	forceBetweenObjects =  normalDir * (-GRAVITY * ((M1 * M2) / (magSq))) * 11000;

	addedBody->addForce(forceBetweenObjects);
	
}
//--------------------------------------------------------------------------------------------
