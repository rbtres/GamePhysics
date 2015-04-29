//=============================================================================
// d3dUtil.h by Frank Luna (C) 2005 All Rights Reserved.
//
// Contains various utility code for DirectX applications, such as, clean up
// and debugging code.
//=============================================================================

#ifndef D3DUTIL_H
#define D3DUTIL_H

// Enable extra D3D debugging in debug builds if using the debug DirectX runtime.  
// This makes D3D objects work well in the debugger watch window, but slows down 
// performance slightly.
#if defined(DEBUG) | defined(_DEBUG)
#ifndef D3D_DEBUG_INFO
#define D3D_DEBUG_INFO
#endif
#endif

#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>
#include <string>
#include <sstream>
#include <vector>
#include "Vertex.h"

//===============================================================
// Globals for convenient access.
class D3DApp;
extern D3DApp* gd3dApp;
extern IDirect3DDevice9* gd3dDevice;

//===============================================================
// Clean up

#define ReleaseCOM(x) { if(x){ x->Release();x = 0; } }

// Math Constants

const float EPSILON  = 0.001f;

//===============================================================
// Geometry generation.

void CreateLPatchWithSkirt( int cellsPerSide, float cellSize,
				std::vector<VertexPosTex>& Vtx,
				std::vector<WORD>& Idx, int& vtxNum, int& triNum );

void CreateLPatch( int vtxPerSize, float cellSize,
				std::vector<VertexPosTex>& Vtx,
				std::vector<WORD>& Idx, int& vtxNum, int& triNum );

void CreateGrid( int vtxPerSize, float cellSize,
				std::vector<VertexPosTex>& Vtx,
				std::vector<WORD>& Idx );

float GetRandomFloat(float a, float b);

float getDistance(D3DXVECTOR3 a, D3DXVECTOR3 b);

void GenTriGrid(int numVertRows, int numVertCols, 
	float dx, float dz, const D3DXVECTOR3& center, 
	std::vector<D3DXVECTOR3>& verts, std::vector<DWORD>& indices);

void CreateBillBoard(VertexPosQuadTex* v, WORD* k, int& indexOffSet, D3DXVECTOR3& worldPos, D3DXVECTOR3& scale);

//===============================================================
// Debug

#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
	#define HR(x)                                      \
	{                                                  \
		HRESULT hr = x;                                \
		if(FAILED(hr))                                 \
		{                                              \
			DXTrace(__FILE__, __LINE__, hr, #x, TRUE); \
		}                                              \
	}
	#endif

#else
	#ifndef HR
	#define HR(x) x;
	#endif
#endif 

#endif // D3DUTIL_H