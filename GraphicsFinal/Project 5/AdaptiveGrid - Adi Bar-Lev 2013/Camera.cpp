//=============================================================================
//                              Camera
//=============================================================================
// Camera.h by Frank Luna (C) 2004 All Rights Reserved.
//=============================================================================
// Edited by Jake Ellenberg and Robert Bethune, 2014
// EGP 300-101, Graphics Programming II
//
// First person camera
//=============================================================================
#include "Camera.h"
#include "DirectInput.h"
#include "d3dUtil.h"
#include "GridManager.h"
//=============================================================================

//-----------------------------------------------------------------------------
Camera::Camera()
{
	D3DXMatrixIdentity(&m_View);
	D3DXMatrixIdentity(&m_Proj);
	D3DXMatrixIdentity(&m_ViewProj);

	m_PosW   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RightW = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_UpW    = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_LookW  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	m_LastMoveVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Client should adjust to a value that makes sense for application's
	// unit scale, and the object the camera is attached to--e.g., car, jet,
	// human walking, etc.
	m_Speed  = 500.0f;
}

//-----------------------------------------------------------------------------
const D3DXMATRIX& Camera::view() const
{
	return m_View;
}

//-----------------------------------------------------------------------------
const D3DXMATRIX& Camera::proj() const
{
	return m_Proj;
}

//-----------------------------------------------------------------------------
const D3DXMATRIX& Camera::viewProj() const
{
	return m_ViewProj;
}

//-----------------------------------------------------------------------------
const D3DXVECTOR3& Camera::right() const
{
	return m_RightW;
}

//-----------------------------------------------------------------------------
const D3DXVECTOR3& Camera::up() const
{
	return m_UpW;
}

//-----------------------------------------------------------------------------
const D3DXVECTOR3& Camera::look() const
{
	return m_LookW;
}

//-----------------------------------------------------------------------------
D3DXVECTOR3 Camera::pos() const
{
	return m_PosW;
}

//-----------------------------------------------------------------------------
D3DXVECTOR3& Camera::lastMoveVector()
{
	return m_LastMoveVector;
}

//-----------------------------------------------------------------------------
void Camera::setLens(float fov, float aspect, float nearZ, float farZ)
{
	D3DXMatrixPerspectiveFovLH(&m_Proj, fov, aspect, nearZ, farZ);
	m_ViewProj = m_View * m_Proj;
}

//-----------------------------------------------------------------------------
void Camera::setSpeed(float speed)
{
	m_Speed = speed;
}

//-----------------------------------------------------------------------------
void Camera::update(float dt)
{
	// Find the net direction the camera is traveling in (since the
	// camera could be running and strafing).
	D3DXVECTOR3 dir(0.0f, 0.0f, 0.0f);
	if( gDInput->keyDown(DIK_W) )
		dir += m_LookW;
	if( gDInput->keyDown(DIK_S) )
		dir -= m_LookW;
	if( gDInput->keyDown(DIK_D) )
		dir += m_RightW;
	if( gDInput->keyDown(DIK_A) )
		dir -= m_RightW;

	// Move at m_Speed along net direction.
	D3DXVec3Normalize(&dir, &dir);
	D3DXVECTOR3 newPos = m_PosW + dir* m_Speed *dt;
	m_LastMoveVector += (dir* m_Speed *dt);
	
	m_PosW = newPos;

	// We rotate at a fixed speed.
	float pitch  = gDInput->mouseDY() / 150.0f;
	float yAngle = gDInput->mouseDX() / 150.0f;

	// Rotate camera's look and up vectors around the camera's right vector.
	D3DXMATRIX R;
	D3DXMatrixRotationAxis(&R, &m_RightW, pitch);
	D3DXVec3TransformCoord(&m_LookW, &m_LookW, &R);
	D3DXVec3TransformCoord(&m_UpW, &m_UpW, &R);

	// Rotate camera axes about the world's y-axis.
	D3DXMatrixRotationY(&R, yAngle);
	D3DXVec3TransformCoord(&m_RightW, &m_RightW, &R);
	D3DXVec3TransformCoord(&m_UpW, &m_UpW, &R);
	D3DXVec3TransformCoord(&m_LookW, &m_LookW, &R);

	// Rebuild the view matrix to reflect changes.
	buildView();

	m_ViewProj = m_View * m_Proj;
}

//-----------------------------------------------------------------------------
void Camera::buildView()
{
	// Keep camera's axes orthogonal to each other and of unit length.
	D3DXVec3Normalize(&m_LookW, &m_LookW);

	D3DXVec3Cross(&m_UpW, &m_LookW, &m_RightW);
	D3DXVec3Normalize(&m_UpW, &m_UpW);

	D3DXVec3Cross(&m_RightW, &m_UpW, &m_LookW);
	D3DXVec3Normalize(&m_RightW, &m_RightW);

	// Fill in the view matrix entries.

	float x = -D3DXVec3Dot(&m_PosW, &m_RightW);
	float y = -D3DXVec3Dot(&m_PosW, &m_UpW);
	float z = -D3DXVec3Dot(&m_PosW, &m_LookW);

	m_View(0,0) = m_RightW.x; 
	m_View(1,0) = m_RightW.y; 
	m_View(2,0) = m_RightW.z; 
	m_View(3,0) = x;   

	m_View(0,1) = m_UpW.x;
	m_View(1,1) = m_UpW.y;
	m_View(2,1) = m_UpW.z;
	m_View(3,1) = y;  

	m_View(0,2) = m_LookW.x; 
	m_View(1,2) = m_LookW.y; 
	m_View(2,2) = m_LookW.z; 
	m_View(3,2) = z;   

	m_View(0,3) = 0.0f;
	m_View(1,3) = 0.0f;
	m_View(2,3) = 0.0f;
	m_View(3,3) = 1.0f;
}
//=============================================================================