#include "PhysicsObject.h"
#include <iostream>
//--------------------------------------------------------------------------------------------
PhysicsObject::PhysicsObject()
{
	m_Pos = Vector3D::Zero;
	m_Vel = Vector3D::Zero;
	m_Acc = Vector3D::Zero;
	m_Rot = Vector3D::Zero;

	m_InitPos = m_Pos;
	m_InitVel = m_Vel;
	m_InitAcc = m_Acc;
	m_InitRot = m_Rot;

	m_Mass = 0;
	m_Force = Vector3D::Zero;
	m_Damping = 1;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
PhysicsObject::~PhysicsObject()
{
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void PhysicsObject::Update(int msTime)
{
	//32557600 = Per Year
	//86400 = per day
	float time = (float)msTime / 1000 * 86400;
	
	if (m_Mass != 0)
	{
		m_Acc = m_Force / m_Mass;
	}

	m_Pos += m_Vel * time;

	m_Vel += m_Acc * time;

	m_Vel = m_Vel * m_Damping;

	m_Force = Vector3D::Zero;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void PhysicsObject::Init(float radius, Vector3D pos, Vector3D startVel, Vector3D startAcc, Vector3D startRot)
{
	m_Radius = radius;
	m_Pos = pos;
	m_Vel = startVel;
	m_Acc = startAcc;
	m_Rot = startRot;

	m_InitPos = m_Pos;
	m_InitVel = m_Vel;
	m_InitAcc = m_Acc;
	m_InitRot = m_Rot;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void PhysicsObject::Draw()
{

	glPushMatrix();

	glTranslatef(m_Pos.X, m_Pos.Y, m_Pos.Z);

	glutSolidSphere(m_Radius,10,10);
	
	glPopMatrix();
	
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void PhysicsObject::Reset()
{
	m_Pos = m_InitPos;
	m_Vel = m_InitVel;
	m_Acc = m_InitAcc;
	m_Rot = m_InitRot;
}
//--------------------------------------------------------------------------------------------
