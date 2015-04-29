//=============================================================================
//                              Lens Flare
//
// Written by Jake Ellenberg And Robert Bethune
// 
// 
//
// Draws three lens flare images that go towards the sun, when the sun is on screen
//=============================================================================
#include "LensFlare.h"
#include <string>
#include <sstream>
#include "DirectInput.h"
#include "d3dUtil.h"
#include <math.h>
//=============================================================================

LensFlare::LensFlare(D3DXVECTOR2 mapSize)
{
	m_MapSize = mapSize;
	m_AspectRatio = 315/243;
	m_pFX = NULL;

	m_NumFlares = 3;

	loadFlares();
	buildEffect();
	buildFlares();
}

LensFlare::~LensFlare()
{
	ReleaseCOM(m_FlareTextures[0]);
	ReleaseCOM(m_FlareTextures[1]);
	ReleaseCOM(m_FlareTextures[2]);
	ReleaseCOM(m_Mesh);
	ReleaseCOM(m_pFX);
	delete m_Colors[0];
	delete m_Colors[1];
}

void LensFlare::Draw(Camera* camera)
{
	D3DXVECTOR3 sunPos = D3DXVECTOR3(-1.0f, .658943415f, 0.434479266f); //sets the sun position to where it is in our world
	sunPos *= 1000000000; //multiplies it to make it very far away

	D3DVIEWPORT9 viewPort;
	gd3dDevice->GetViewport(&viewPort);

	UINT numPasses = 0;
	D3DXVECTOR3 cameraPos = camera->pos();
	D3DXMATRIX cameraViewProj = camera->viewProj();

	D3DXVECTOR2 sunScreenPos;
	D3DXVECTOR2 centerPos = D3DXVECTOR2((float)viewPort.Width / 2, (float)viewPort.Height / 2);
	D3DXVECTOR3  tempPos = sunPos;

	D3DXVec3TransformCoord(&tempPos, &tempPos, &cameraViewProj);
	
	sunScreenPos.x = ((tempPos.x + 1.0f) * viewPort.Width) / 2;
	sunScreenPos.y = ((tempPos.y + 1.0f) * viewPort.Height) / 2;

	D3DXVECTOR3 sunWorldPos;

	D3DXVECTOR2 maxDistanceVector = D3DXVECTOR2(viewPort.Width * 1.5f, viewPort.Height * 1.5f);

	if(sunScreenPos.x >  -maxDistanceVector.x && sunScreenPos.x < maxDistanceVector.x && sunScreenPos.y >  -maxDistanceVector.y && sunScreenPos.y < maxDistanceVector.y 
		&& camera->look().x < 0) //Hard coded look at check so that the lens flare does not show up when the sun is behind the camera
	{
		D3DXVECTOR2 directionToSun;
		directionToSun.x = centerPos.x - sunScreenPos.x;
		directionToSun.y = centerPos.y - sunScreenPos.y;

		float distance = sqrt((directionToSun.x * directionToSun.x) + (directionToSun.y * directionToSun.y));

		D3DXVec2Normalize(&directionToSun, &directionToSun);

		D3DXMATRIX matWorld;
		D3DXMatrixIdentity(&matWorld);

		HR(m_pFX->SetTechnique(m_hTech));

		HR(m_pFX->SetValue(m_hEyePos, &cameraPos, sizeof(D3DXVECTOR3)));
		HR(m_pFX->SetMatrix(m_hViewProj, &cameraViewProj));
		HR(m_pFX->SetTexture(m_hFlareTexture, m_FlareTextures[0]));
		HR(m_pFX->SetValue(m_hGridSize, &m_MapSize, sizeof(D3DXVECTOR2)));

		for(int i = 0; i < m_NumFlares; i++)
		{
			D3DXVECTOR2 flareScreenPos;

			D3DXVECTOR2 zRange = D3DXVECTOR2(.997f, .999f);

			float fraction = (float)i / (float)m_NumFlares;
			float flareZ = fraction * zRange.x + (1-fraction) * zRange.y;

			float fadeFraction = distance / (maxDistanceVector.x / 2);
			float fade = fadeFraction * 0.5f + (1-fadeFraction) * 0.01f;

			flareScreenPos.x = centerPos.x + (directionToSun.x * distance * fraction);
			flareScreenPos.y = centerPos.y + (directionToSun.y * distance * fraction * -1);

			D3DXVECTOR3 flareWorldPos;
			D3DXVec3Unproject(&flareWorldPos, &D3DXVECTOR3((float)((int)flareScreenPos.x), (float)((int)flareScreenPos.y), flareZ), &viewPort, &camera->proj(), &camera->view(), &matWorld);

			HR(m_pFX->SetValue(m_hQuadPos, &flareWorldPos, sizeof(D3DXVECTOR3)));
			HR(m_pFX->SetFloat(m_hFade, fade));
			HR(m_pFX->SetValue(m_hColor, m_Colors[i], sizeof(D3DXVECTOR3)));
			HR(m_pFX->SetTexture(m_hFlareTexture, m_FlareTextures[i]));
			HR(m_pFX->Begin(&numPasses, 0));
			HR(m_pFX->BeginPass(0));

			HR(m_Mesh->DrawSubset(i));

			HR(m_pFX->EndPass());
			HR(m_pFX->End());
		}
	}
}

void LensFlare::OnResetDevice()
{
	m_pFX->OnResetDevice();
}

void LensFlare::OnLostDevice()
{
	m_pFX->OnLostDevice();
}

void LensFlare::loadFlares()
{
	HR( D3DXCreateTextureFromFile(gd3dDevice, "Textures/FlareTextures/flare6.jpg", &m_FlareTextures[0]));
	HR( D3DXCreateTextureFromFile(gd3dDevice, "Textures/FlareTextures/flare3.jpg", &m_FlareTextures[1]));
	HR( D3DXCreateTextureFromFile(gd3dDevice, "Textures/FlareTextures/flare5.jpg", &m_FlareTextures[2]));

	m_Colors[0] = new D3DXVECTOR3(205.0f/255.0f, 192.0f/255.0f, 192.0f/255.0f);
	m_Colors[1] = new D3DXVECTOR3(193.0f/255.0f, 151.0f, 177.0f/255.0f);
	m_Colors[2] = new D3DXVECTOR3(200.0f/255.0f, 200.0f/255.0f, 255.0f/255.0f);
}

void LensFlare::buildFlares()
{
	D3DVERTEXELEMENT9 elems[MAX_FVF_DECL_SIZE];

	UINT numElems = 0;
	HR(VertexPosQuadTex::Decl->GetDeclaration(elems, &numElems));

	HR(D3DXCreateMesh(m_NumFlares*2, m_NumFlares*4, D3DXMESH_MANAGED, 
		elems, gd3dDevice, &m_Mesh));

	VertexPosQuadTex* v = 0;
	WORD* k = 0;
	HR(m_Mesh->LockVertexBuffer(0, (void**)&v));
	HR(m_Mesh->LockIndexBuffer(0, (void**)&k));
	
	int indexOffset = 0;

	for(int i = 0; i < m_NumFlares; i++)
	{
		float scaleAmount = 50;

		D3DXVECTOR3 scale(scaleAmount,scaleAmount * 2,scaleAmount);

		CreateBillBoard(v, k, indexOffset, D3DXVECTOR3(0,0,0), scale);

		v += 4;
		k += 6;
	}

	HR(m_Mesh->UnlockVertexBuffer());
	HR(m_Mesh->UnlockIndexBuffer());

	// Fill in the attribute buffer
	DWORD* attributeBufferPtr = 0;
	HR(m_Mesh->LockAttributeBuffer(0, &attributeBufferPtr));
	for(UINT i = 0; i < m_Mesh->GetNumFaces(); ++i)
	{
		attributeBufferPtr[i] = (int)(i / 2);
	}
	HR(m_Mesh->UnlockAttributeBuffer());

	DWORD* adj = new DWORD[m_Mesh->GetNumFaces() * 3];
	HR(m_Mesh->GenerateAdjacency(EPSILON, adj));
	HR(m_Mesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT|D3DXMESHOPT_VERTEXCACHE,
		adj, 0, 0, 0));

	delete [] adj;
}

void LensFlare::buildEffect()
{
	ID3DXBuffer* errors = 0;
	HR(D3DXCreateEffectFromFile(gd3dDevice, "LensFlare.fx", 0, 0, 0, 0, &m_pFX, &errors));

	if( errors )
	{
		MessageBox(0, (char*)errors->GetBufferPointer(), 0, 0);
	}

	m_hTech            = m_pFX->GetTechniqueByName("BillBoardTech");

	m_hEyePos          = m_pFX->GetParameterByName(0, "gEyePosW");
	m_hViewProj        = m_pFX->GetParameterByName(0, "gViewProj");
	m_hFlareTexture    = m_pFX->GetParameterByName(0, "gTex");
	m_hGridSize		   = m_pFX->GetParameterByName(0, "gGridSize");
	m_hOffset		   = m_pFX->GetParameterByName(0, "gOffset");
	m_hQuadPos		   = m_pFX->GetParameterByName(0, "gQuadPos");
	m_hFade			   = m_pFX->GetParameterByName(0, "gFade");
	m_hColor		   = m_pFX->GetParameterByName(0, "gColor");
	HR(m_pFX->SetTexture(m_hFlareTexture, m_FlareTextures[0]));
}
//=============================================================================