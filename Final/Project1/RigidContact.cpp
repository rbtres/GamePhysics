#include "RigidContact.h"


RigidContact::RigidContact()
{
}

RigidContact::~RigidContact()
{
}

void RigidContact::Initialize(Vector3D contactPoint, Vector3D contactNormal, float pen, float rest, float fric, RigidBody* one, RigidBody* two)
{
	m_contactPoint = contactPoint;
	m_contactNormal = contactNormal;
	
	m_penetration = pen;
	m_restitution = rest;
	m_friction = fric;

	m_bodyOne = one;
	m_bodyTwo = two;
}

void RigidContact::Resolve(float msTime)
{

}