//============================================================================================
//Create by Robert Bethune
//PhysicsObject
//Base PhysicsObject class will be purely virtual just hold some required information
//Creation Date 1/18/2015
//Last Updated 2/7/2015
//============================================================================================
#pragma once
#include "Vector3D.h"
#include "GL/glut.h"
//============================================================================================
class PhysicsObject
{
public:
//--------------------------------------------------------------------------------------------
	PhysicsObject();
	~PhysicsObject();
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
	virtual void Init(float radius = 0, Vector3D pos = Vector3D::Zero, Vector3D startVel = Vector3D::Zero, Vector3D startAcc = Vector3D::Zero, Vector3D startRot = Vector3D::Zero);
	virtual void Update(int msTime);
	virtual void Draw();
	virtual void Reset();
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
	inline void setPos(Vector3D pos) { m_Pos = pos; }
	inline Vector3D getPos() { return m_Pos; }

	inline void setVel(Vector3D vel) { m_Vel = vel; }
	inline Vector3D getVel() { return m_Vel; }

	inline void setAcc(Vector3D acc) { m_Acc = acc; }
	inline Vector3D getAcc() { return m_Acc; }

	inline void setDamping(float damping) { m_Damping = damping; }
	inline float getDamping() { return m_Damping; }

	inline void addForce(Vector3D force) { m_Force += force; }
	inline void setForce(Vector3D force) { m_Force = force; }
	inline Vector3D getForce() { return m_Force; }
	inline Vector3D getOldForce() { return m_OldForce; }

	inline void setMass(float mass) { m_Mass = mass; }
	inline float getMass(){ return m_Mass; }
//--------------------------------------------------------------------------------------------
//============================================================================================
protected:
//--------------------------------------------------------------------------------------------
	Vector3D m_Pos;
	Vector3D m_Vel;
	Vector3D m_Acc;
	Vector3D m_Rot;

	Vector3D m_InitPos;
	Vector3D m_InitVel;
	Vector3D m_InitAcc;
	Vector3D m_InitRot;

	float m_Damping;
	float m_Mass;
	float m_Radius;
	Vector3D m_Force;
	Vector3D m_OldForce;
//--------------------------------------------------------------------------------------------
};
//============================================================================================
