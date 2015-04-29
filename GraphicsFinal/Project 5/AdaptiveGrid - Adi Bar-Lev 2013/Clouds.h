//=============================================================================
//                              Clouds
//
// Authors Jake Ellenberg And Robert Bethune
// Based on code by Frank Luna, http://www.d3dcoder.net/d3d9c.htm
//
// Draws billboards with clouds textures 
// given a hight range, a scale range, and a mapsize
//=============================================================================
#ifndef CLOUDS_H
#define CLOUDS_H
//=============================================================================
#include <d3dx9.h>
#include "Vertex.h"
#include "Camera.h"
#include <d3d9.h>
#include "d3dUtil.h"
#include "Vertex.h"
//=============================================================================
class Clouds
{
public:
	Clouds(D3DXVECTOR2 mapSize, float minHeight, float maxHeight, float minScale, float maxScale, int numClouds);
	~Clouds();

	void Draw(D3DXVECTOR3 cameraPos, D3DXMATRIX cameraViewProj, D3DXVECTOR3 offSet);

	inline int GetNumTriangles() { return m_TriNum; }
	inline int GetNumVertices()  { return m_VtxNum; }
	void OnResetDevice();
	void OnLostDevice();
protected:
	void buildClouds();
	void buildEffect();
private:

	IDirect3DVertexBuffer9* m_CloudVB;
	IDirect3DIndexBuffer9*  m_CloudIB;
	int						m_VtxNum;
	int						m_TriNum;

	int						m_NumClouds;
	LPD3DXMESH				m_Mesh;

	D3DXVECTOR2 m_MapSize;

	float m_MinHeight;
	float m_MaxHeight;
	float m_MinScale;
	float m_MaxScale;

	D3DXVECTOR3				m_Pos;

	ID3DXEffect*			m_pFX;
	IDirect3DTexture9*		m_CloudTexture;


	D3DXHANDLE				m_hTech;
	D3DXHANDLE				m_hEyePos;
	D3DXHANDLE				m_hViewProj;
	D3DXHANDLE				m_hGridSize;
	D3DXHANDLE				m_hOffset;
	D3DXHANDLE				m_hCloudTexture;

	float					m_AspectRatio;
	
};
//=============================================================================
#endif CLOUDS_H