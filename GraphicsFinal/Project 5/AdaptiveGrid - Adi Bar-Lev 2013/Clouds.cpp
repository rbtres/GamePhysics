//=============================================================================
//                              Clouds
//
// Authors Jake Ellenberg And Robert Bethune
// Based on code by Frank Luna, http://www.d3dcoder.net/d3d9c.htm
//
// Draws billboards with clouds textures 
// given a hight range, a scale range, and a mapsize
//=============================================================================
#include "Clouds.h"
#include <string>
#include "DirectInput.h"
#include "d3dUtil.h"

//------------------------------------------------------------------------------
Clouds::Clouds(D3DXVECTOR2 mapSize, float minHeight, float maxHeight, float minScale, float maxScale, int numClouds)
{
	m_MapSize = mapSize;
	m_MinHeight = minHeight;
	m_MaxHeight = maxHeight;
	m_MinScale = minScale;
	m_MaxScale = maxScale;
	m_NumClouds = numClouds;
	HR( D3DXCreateTextureFromFile(gd3dDevice, "Textures/CloudTextures/Texture_Cloud.jpg", &m_CloudTexture));
	m_AspectRatio = 839/437;
	m_CloudIB = NULL;
	m_CloudVB = NULL;
	m_pFX = NULL;
	buildEffect();
	buildClouds();
}

//------------------------------------------------------------------------------
Clouds::~Clouds(void)
{
	ReleaseCOM(m_CloudTexture);
	ReleaseCOM(m_pFX);
	ReleaseCOM(m_Mesh);
}

//------------------------------------------------------------------------------
void Clouds::OnResetDevice()
{
	m_pFX->OnResetDevice();
}

//------------------------------------------------------------------------------
void Clouds::OnLostDevice()
{
	m_pFX->OnLostDevice();
}

//------------------------------------------------------------------------------
void Clouds::buildEffect()
{
	ID3DXBuffer* errors = 0;
	HR(D3DXCreateEffectFromFile(gd3dDevice, "Billboard.fx", 
		0, 0, 0, 0, &m_pFX, &errors));
	if( errors )
	{
		MessageBox(0, (char*)errors->GetBufferPointer(), 0, 0);
	}
		

	m_hTech            = m_pFX->GetTechniqueByName("BillBoardTech");

	m_hEyePos          = m_pFX->GetParameterByName(0, "gEyePosW");
	m_hViewProj        = m_pFX->GetParameterByName(0, "gViewProj");
	m_hCloudTexture    = m_pFX->GetParameterByName(0, "gTex");
	m_hGridSize		   = m_pFX->GetParameterByName(0, "gGridSize");
	m_hOffset		   = m_pFX->GetParameterByName(0, "gOffset");

	HR(m_pFX->SetTexture(m_hCloudTexture, m_CloudTexture));
}

//------------------------------------------------------------------------------
void Clouds::Draw(D3DXVECTOR3 cameraPos, D3DXMATRIX cameraViewProj, D3DXVECTOR3 offSet)
{
	UINT numPasses = 0;

	HR(m_pFX->SetTechnique(m_hTech));

	HR(m_pFX->SetValue(m_hEyePos, &cameraPos, sizeof(D3DXVECTOR3)));
	HR(m_pFX->SetMatrix(m_hViewProj, &cameraViewProj));
	HR(m_pFX->SetTexture(m_hCloudTexture, m_CloudTexture));
	HR(m_pFX->SetValue(m_hOffset, &offSet, sizeof(D3DXVECTOR3)));
	HR(m_pFX->SetValue(m_hGridSize, &m_MapSize, sizeof(D3DXVECTOR2)));

	HR(m_pFX->Begin(&numPasses, 0));
	HR(m_pFX->BeginPass(0));

	// Draw to depth buffer only.
	HR(m_Mesh->DrawSubset(0));

	HR(m_pFX->EndPass());
	HR(m_pFX->End());
}

//Used Frank Lunas grass example as a reference for this function
//------------------------------------------------------------------------------
void Clouds::buildClouds()
{
	D3DVERTEXELEMENT9 elems[MAX_FVF_DECL_SIZE];

	UINT numElems = 0;
	HR(VertexPosQuadTex::Decl->GetDeclaration(elems, &numElems));

	HR(D3DXCreateMesh(m_NumClouds*2, m_NumClouds*4, D3DXMESH_MANAGED, 
		elems, gd3dDevice, &m_Mesh));

	VertexPosQuadTex* v = 0;
	WORD* k = 0;
	HR(m_Mesh->LockVertexBuffer(0, (void**)&v));
	HR(m_Mesh->LockIndexBuffer(0, (void**)&k));
	
	int indexOffset = 0;

	for(int i = 0; i < m_NumClouds; i++)
	{
		// Generate random position in region.  Note that we also shift
		// this region to place it in the world.
		float x = (float)((rand() % (int)m_MapSize.x) - (m_MapSize.x*0.5f));
		float z = (float)((rand() % (int)m_MapSize.y) - (m_MapSize.y*0.5f));
		float y = GetRandomFloat(m_MinHeight, m_MaxHeight);

		float sx = GetRandomFloat(m_MinScale, m_MaxScale); 
		float sy = m_AspectRatio * sx;
		float sz = 1.0f;

		D3DXVECTOR3 pos(x, y, z);
		D3DXVECTOR3 scale(sx, sy, sz);

		CreateBillBoard(v, k, indexOffset, pos, scale);

		v += 4;
		k += 6;
	}

	HR(m_Mesh->UnlockVertexBuffer());
	HR(m_Mesh->UnlockIndexBuffer());

	// Fill in the attribute buffer (everything in subset 0)
	DWORD* attributeBufferPtr = 0;
	HR(m_Mesh->LockAttributeBuffer(0, &attributeBufferPtr));
	for(UINT i = 0; i < m_Mesh->GetNumFaces(); ++i)
		attributeBufferPtr[i] = 0;
	HR(m_Mesh->UnlockAttributeBuffer());

	DWORD* adj = new DWORD[m_Mesh->GetNumFaces() * 3];
	HR(m_Mesh->GenerateAdjacency(EPSILON, adj));
	HR(m_Mesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT|D3DXMESHOPT_VERTEXCACHE,
		adj, 0, 0, 0));

	delete [] adj;
}
//=============================================================================