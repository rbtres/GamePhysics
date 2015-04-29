//=============================================================================
//                              Sky box
//
//Eddited by Jake Ellenberg And Robert Bethune
// Based on code by Frank Luna, http://www.d3dcoder.net/d3d9c.htm
// EGP 300-101, Graphics Programming II  - SkeletonProject
//
// Draws the skybox and keeps it centered on the player
//=============================================================================
#ifndef SKYBOX_H
#define SKYBOX_H
//=============================================================================
#include <d3dx9.h>
class Camera;
//=============================================================================
class SkyBox
{
private:
	ID3DXMesh* m_Sphere;

	IDirect3DCubeTexture9* m_EnvMap;
	ID3DXEffect* m_Effect;
	
	D3DXHANDLE m_TechHandle;
	D3DXHANDLE m_EnvMapHandle;
	D3DXHANDLE m_WVPHandle;

public:
	SkyBox();
	~SkyBox();

	void OnLostDevice();
	void OnResetDevice();

	void Draw(D3DXVECTOR3 cameraPos, D3DXMATRIX cameraViewProj);

};
//=============================================================================
#endif // SKYBOX_H