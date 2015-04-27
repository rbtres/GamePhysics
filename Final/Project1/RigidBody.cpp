#include "RigidBody.h"
#include <math.h>

RigidBody::RigidBody()
{
	m_isAwake = false;
}


RigidBody::~RigidBody()
{
}

void RigidBody::CalculateTransformMatrix(Matrix &trans, const Vector3D &pos, const Quaternion &orientation)
{
	float v1 = 1 - 2 * orientation.J * orientation.J - 2 * orientation.K * orientation.K;
	trans.Set(0, 0,v1);
	float v2 = 2 * orientation.I * orientation.J - 2 * orientation.R * orientation.K;
	trans.Set(0, 1, v2);
	float v3 = 2 * orientation.I * orientation.K + 2 * orientation.R * orientation.J;
	trans.Set(0, 2, v3);
	trans.Set(0, 3, pos.X);

	float v4 = 2 * orientation.I * orientation.J + 2 * orientation.R * orientation.K;
	trans.Set(1, 0, v4);
	float v5 = 1 - 2 * orientation.I * orientation.I - 2 * orientation.K * orientation.K;
	trans.Set(1, 1, v5);
	float v6 = 2 * orientation.J * orientation.K - 2 * orientation.R * orientation.I;
	trans.Set(1, 2, v6);
	trans.Set(1, 3, pos.Y);

	float v7 = 2 * orientation.I * orientation.K - 2 * orientation.R * orientation.J;
	trans.Set(2, 0, v7);
	float v8 = 2 * orientation.J * orientation.K + 2 * orientation.R * orientation.I;
	trans.Set(2, 1, v8);
	float v9 = 1 -  2 * orientation.I * orientation.I - 2 * orientation.J * orientation.J;
	trans.Set(2, 2, v9);
	trans.Set(2, 3, pos.Z);
}

void RigidBody::TransformInvertiaTensor(Matrix &iitWorld, const Quaternion &quaternion, const Matrix &iitBody, const Matrix &rotationMatrix)
{
	float t4 = rotationMatrix.Get(0) * iitBody.Get(0) + rotationMatrix.Get(1) * iitBody.Get(3) + rotationMatrix.Get(2) * iitBody.Get(6);
	float t9 = rotationMatrix.Get(0) * iitBody.Get(1) + rotationMatrix.Get(1) * iitBody.Get(4) + rotationMatrix.Get(2) * iitBody.Get(7);
	float t14 = rotationMatrix.Get(0) * iitBody.Get(2) + rotationMatrix.Get(1) * iitBody.Get(5) + rotationMatrix.Get(2) * iitBody.Get(8);
	float t28 = rotationMatrix.Get(4) * iitBody.Get(0) + rotationMatrix.Get(5) * iitBody.Get(3) + rotationMatrix.Get(6) * iitBody.Get(6);
	float t33 = rotationMatrix.Get(4) * iitBody.Get(1) + rotationMatrix.Get(5) * iitBody.Get(4) + rotationMatrix.Get(6) * iitBody.Get(7);
	float t38 = rotationMatrix.Get(4) * iitBody.Get(2) + rotationMatrix.Get(5) * iitBody.Get(5) + rotationMatrix.Get(6) * iitBody.Get(8);
	float t52 = rotationMatrix.Get(8) * iitBody.Get(0) + rotationMatrix.Get(9) * iitBody.Get(3) + rotationMatrix.Get(10) * iitBody.Get(6);
	float t57 = rotationMatrix.Get(8) * iitBody.Get(1) + rotationMatrix.Get(9) * iitBody.Get(4) + rotationMatrix.Get(10) * iitBody.Get(7);
	float t62 = rotationMatrix.Get(8) * iitBody.Get(2) + rotationMatrix.Get(9) * iitBody.Get(5) + rotationMatrix.Get(10) * iitBody.Get(8);

	float val0 = t4 * rotationMatrix.Get(0) + t9 * rotationMatrix.Get(1) + t14 * rotationMatrix.Get(2);
	iitWorld.Set(0, val0);
	float val1 = t4 * rotationMatrix.Get(4) + t9 * rotationMatrix.Get(5) + t14 * rotationMatrix.Get(6);
	iitWorld.Set(1, val1);
	float val2 = t4 * rotationMatrix.Get(8) + t9 * rotationMatrix.Get(9) + t14 * rotationMatrix.Get(10);
	iitWorld.Set(2, val2);
	float val3 = t28 * rotationMatrix.Get(0) + t33 * rotationMatrix.Get(1) + t38 * rotationMatrix.Get(2);
	iitWorld.Set(3, val3);
	float val4 = t28 * rotationMatrix.Get(4) + t33 * rotationMatrix.Get(5) + t38 * rotationMatrix.Get(6);
	iitWorld.Set(4, val4);
	float val5 = t28 * rotationMatrix.Get(8) + t33 * rotationMatrix.Get(9) + t38 * rotationMatrix.Get(10);
	iitWorld.Set(5, val5);
	float val6 = t52 * rotationMatrix.Get(0) + t57 * rotationMatrix.Get(1) + t62 * rotationMatrix.Get(2);
	iitWorld.Set(6, val6);
	float val7 = t52 * rotationMatrix.Get(4) + t57 * rotationMatrix.Get(5) + t62 * rotationMatrix.Get(6);
	iitWorld.Set(7, val7);
	float val8 = t52 * rotationMatrix.Get(8) + t57 * rotationMatrix.Get(9) + t62 * rotationMatrix.Get(10);
	iitWorld.Set(8, val8);
}

void RigidBody::calculateDerivedData()
{
	m_Orientation.Normalize();
	RigidBody::CalculateTransformMatrix(m_trans, m_Pos, m_Orientation);

	RigidBody::TransformInvertiaTensor(m_inverseTensorWorld, m_Orientation, m_intertiaTensor, m_transWorld);
}

void RigidBody::Intergrate(float duration)
{
	m_LastFrameAcc = m_Acc;
	m_LastFrameAcc += m_ForceAcc * m_inverseMass;

	Vector3D angularAcc = m_intertiaTensor.Transform(m_TorqueAcc);
	
	m_Vel += (m_LastFrameAcc * 1/duration);

	m_Rot += (angularAcc * 1/duration);

	m_Vel = m_Vel * (float)pow(m_linearDampening, 1/duration);
	m_Rot = m_Rot * (float)pow(m_angluarDampening, 1/duration);

	m_Pos += (m_Vel * 1/duration);

	m_Orientation.AddScaleVector((m_Rot * 1/duration), 1);

	calculateDerivedData();

	ClearAcc();
}

Vector3D RigidBody::GetPointInWorldSpace(const Vector3D &point)
{
	return m_trans.Transform(point);
}

void RigidBody::AddForceAtPoint(const Vector3D &force, const Vector3D &point)
{
	Vector3D worldPoint = point;
	worldPoint -= m_Pos;

	m_ForceAcc += force;
	m_TorqueAcc += worldPoint.Cross(force);

	m_isAwake = true;
}

void RigidBody::AddForceAtBody(const Vector3D &force, const Vector3D &point)
{
	AddForceAtPoint(force, point);
	m_isAwake = true;
}

void RigidBody::Initialize(Vector3D pos, Vector3D startVel, Vector3D startAcc, Vector3D startRot, float linDam, float angDam)
{
	m_isAwake = false;

	m_Pos = pos;
	m_InitPos = pos;
	
	m_Rot = startRot;
	m_InitRot = startRot;

	m_Vel = startVel;
	m_InitVel = startVel;

	m_Acc = startAcc;
	m_InitAcc = startAcc;

	m_linearDampening = linDam;
	m_angluarDampening = angDam;
}

void RigidBody::Reset()
{
	m_Pos = m_InitPos;
	m_Rot = m_InitRot;
	m_Vel = m_InitVel;
	m_Acc = m_InitAcc;
}