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
#ifndef CAMERA_H
#define CAMERA_H
//=============================================================================
#include <d3dx9.h>

class GridManager;
//=============================================================================
class Camera
{
public:
	Camera();

	const D3DXMATRIX& view() const;
	const D3DXMATRIX& proj() const;
	const D3DXMATRIX& viewProj() const;

	const D3DXVECTOR3& right() const;
	const D3DXVECTOR3& up() const;
	const D3DXVECTOR3& look() const;

	D3DXVECTOR3& lastMoveVector();

	D3DXVECTOR3 pos() const;

	void setLens(float fov, float aspect, float nearZ, float farZ);
	void setSpeed(float speed);

	void update(float dt);

protected:
	void buildView();

protected:
	D3DXMATRIX m_View;
	D3DXMATRIX m_Proj;
	D3DXMATRIX m_ViewProj;

	// Relative to world space.
	D3DXVECTOR3 m_PosW;
	D3DXVECTOR3 m_RightW;
	D3DXVECTOR3 m_UpW;
	D3DXVECTOR3 m_LookW;
	D3DXVECTOR3 m_LastMoveVector;

	D3DXVECTOR3 m_OffsetPosition;

	float m_Speed;

};
//=============================================================================
#endif //CAMERA_H