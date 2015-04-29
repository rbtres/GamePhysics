//=============================================================================
//                              Lens Flare
//
// Written by Jake Ellenberg And Robert Bethune
// 
// 
//
// Draws three lens flare images that go towards the sun, when the sun is on screen
//=============================================================================
#ifndef LENSFLARE_H
#define LENSFLARE_H
//=============================================================================
#include <d3dx9.h>
#include "Vertex.h"
#include "Camera.h"
#include <d3d9.h>
#include "d3dUtil.h"
//=============================================================================
class LensFlare
{
public:
	LensFlare(D3DXVECTOR2 mapSize);
	~LensFlare();

	void Draw(Camera* camera);

	void OnResetDevice();
	void OnLostDevice();
protected:
	void loadFlares();
	void buildFlares();
	void buildEffect();
private:
	int						m_NumFlares;

	LPD3DXMESH				m_Mesh;

	D3DXVECTOR2             m_MapSize;

	D3DXVECTOR3				m_PosOnScreen;
	D3DXVECTOR3             m_SunPos;
	D3DXVECTOR3*			m_Colors[3];

	ID3DXEffect*			m_pFX;
	IDirect3DTexture9*		m_FlareTextures[3];

	D3DXHANDLE				m_hTech;
	D3DXHANDLE				m_hEyePos;
	D3DXHANDLE				m_hViewProj;
	D3DXHANDLE				m_hGridSize;
	D3DXHANDLE				m_hOffset;
	D3DXHANDLE				m_hFlareTexture;
	D3DXHANDLE				m_hQuadPos;
	D3DXHANDLE				m_hFade;
	D3DXHANDLE				m_hColor;

	float					m_AspectRatio;
};
//=============================================================================
#endif LENSFLARE_H