#pragma once
#include "Vector3D.h"
#include "Quaternion.h"
#include "Matrix.h"
class RigidBody
{
public:
	RigidBody();
	~RigidBody();

	inline void SetInertiaTensor(const Matrix &intertia) { m_intertiaTensor = intertia; m_intertiaTensor = m_intertiaTensor.InvMatrix(); }
	inline void AddForce(const Vector3D &force){ m_ForceAcc += force; m_isAwake = true; }
	inline void ClearAcc(){ m_ForceAcc = Vector3D::Zero;  m_TorqueAcc = Vector3D::Zero; }

	void Initialize(Vector3D pos = Vector3D::Zero, Vector3D startVel = Vector3D::Zero, Vector3D startAcc = Vector3D::Zero, Vector3D startRot = Vector3D::Zero, float linDam = 1, float angDam = 1);
	void Intergrate(float duration);
	void AddForceAtPoint(const Vector3D &force, const Vector3D &point);
	void AddForceAtBody(const Vector3D &force, const Vector3D &point);

	void Reset();
	
	bool IsMassInf(){ return m_inverseMass == 1; }
	
	Vector3D GetPointInWorldSpace(const Vector3D &point);
	float GetMass(){ return 1 / m_inverseMass; }
	static void TransformInvertiaTensor(Matrix &iitWorld, const Quaternion &quaternion, const Matrix &iitBody, const Matrix &rotationMatrix);
	static void CalculateTransformMatrix(Matrix &trans, const Vector3D &pos, const Quaternion &orientation);
protected:
	void calculateDerivedData();
	
	bool m_isAwake;

	float m_inverseMass;
	float m_linearDampening;
	float m_angluarDampening;

	Vector3D m_Pos;
	Vector3D m_Acc;
	Vector3D m_LastFrameAcc;
	Vector3D m_Vel;
	Vector3D m_Rot;
	Vector3D m_ForceAcc;
	Vector3D m_TorqueAcc;

	Vector3D m_InitPos;
	Vector3D m_InitAcc;
	Vector3D m_InitVel;
	Vector3D m_InitRot;

	Matrix m_trans;
	Matrix m_intertiaTensor;
	Matrix m_transWorld;
	Matrix m_inverseTensorWorld;

	Quaternion m_Orientation;

};

