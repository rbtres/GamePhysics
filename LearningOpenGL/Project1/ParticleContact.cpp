#include "ParticleContact.h"

ParticleContact::ParticleContact()
{
	particle[0] = NULL;
	particle[1] = NULL;
}

ParticleContact::~ParticleContact()
{

}

void ParticleContact::resolve(float duration)
{
	resolveVelocity(duration);
	resolveInterpenetration(duration);
}

float ParticleContact::calculateSeparatingVelocity()
{
	Vector3D relativeVelocity = particle[0]->getVel();
	if (particle[1] != NULL)
	{
		relativeVelocity -= particle[1]->getVel();
	}

	return relativeVelocity.Dot(contactNormal);
}

void ParticleContact::resolveVelocity(float duration)
{
	float separatingVelocity = calculateSeparatingVelocity();

	if (separatingVelocity > 0)
	{
		return;
	}

	float newSeparatingVelocity = -separatingVelocity * restitution;

	Vector3D accCausedVelocity = particle[0]->getAcc();

	if (particle[1])
	{
		accCausedVelocity -= particle[1]->getAcc();
	}

	float realAccCausedSepVel =  accCausedVelocity.Dot(contactNormal) * (duration / 1000);

	if (realAccCausedSepVel < 0)
	{
		separatingVelocity -= realAccCausedSepVel;
		
	}

	float deltaVelocity = (newSeparatingVelocity - separatingVelocity) ;

	float invertMass = getInverseMass();

	if (invertMass <= 0) return;

	float impulse = deltaVelocity / invertMass;

	Vector3D impulsePerMass = contactNormal * impulse;

	particle[0]->setVel( particle[0]->getVel() + impulsePerMass * (1 / particle[0]->getMass()));

	if (particle[1])
	{
		particle[1]->setVel(particle[1]->getVel() + impulsePerMass * -(1 / particle[1]->getMass()));
	}
}
float ParticleContact::getInverseMass()
{
	float invertMass =  1 / particle[0]->getMass();
	if (particle[1])
	{
		invertMass += 1 / particle[1]->getMass();
	}
	return invertMass;
}
void ParticleContact::resolveInterpenetration(float duration)
{
	if (penetration >= 0) return;

	float invertMass = getInverseMass();

	if (invertMass <= 0) return;

	Vector3D movePerIMass = contactNormal * (penetration / invertMass);

	Vector3D particleZeroMove = movePerIMass *  (1 / particle[0]->getMass()) * (duration / 1000);
	Vector3D particleOneMove;

	if (particle[1])
	{
		particleOneMove = movePerIMass* -(1 / particle[1]->getMass()) * (duration / 1000);
	}
	else
	{
		particleOneMove = Vector3D::Zero;
	}

	particle[0]->setPos(particle[0]->getPos() - particleZeroMove);
	if (particle[1])
	{
		particle[1]->setPos(particle[1]->getPos() - particleOneMove);
	}
}