//=============================================================================
//                              Sky box
//
// Eddited by Jake Ellenberg And Robert Bethune
// Based on code by Frank Luna, http://www.d3dcoder.net/d3d9c.htm
// EGP 300-101, Graphics Programming II  - SkeletonProject
//
// Draws the skybox and keeps it centered on the player
//=============================================================================
#include <string>
#include "d3dApp.h"
#include "d3dUtil.h"
#include "SkyBox.h"
#include "Camera.h"
//=============================================================================

//-----------------------------------------------------------------------------
SkyBox::SkyBox()
{
	HR(D3DXCreateSphere(gd3dDevice, 1000, 30, 30, &m_Sphere, 0));
	HR(D3DXCreateCubeTextureFromFile(gd3dDevice, "Textures/SkyMapTextures/JakeMap.dds", &m_EnvMap));

	ID3DXBuffer* errors = 0;
	HR(D3DXCreateEffectFromFile(gd3dDevice, "sky.fx", 0, 0, 0, 0, &m_Effect, &errors));

	if( errors )
	{
		MessageBox(0, (char*)errors->GetBufferPointer(), 0, 0);
	}

	m_TechHandle = m_Effect->GetTechniqueByName("SkyTech");
	m_WVPHandle    = m_Effect->GetParameterByName(0, "gWVP");
	m_EnvMapHandle = m_Effect->GetParameterByName(0, "gEnvMap");

	// Set effect parameters that do not vary.
	HR(m_Effect->SetTechnique(m_TechHandle));
	HR(m_Effect->SetTexture(m_EnvMapHandle, m_EnvMap));
}

//-----------------------------------------------------------------------------
SkyBox::~SkyBox()
{
	ReleaseCOM(m_Sphere);
	ReleaseCOM(m_EnvMap);
	ReleaseCOM(m_Effect);
}

//-----------------------------------------------------------------------------
void SkyBox::OnLostDevice()
{
	HR(m_Effect->OnLostDevice());
}

//-----------------------------------------------------------------------------
void SkyBox::OnResetDevice()
{
	HR(m_Effect->OnResetDevice());
}

//-----------------------------------------------------------------------------
void SkyBox::Draw(D3DXVECTOR3 cameraPos, D3DXMATRIX cameraViewProj)
{
	D3DXMATRIX world;

	D3DXMatrixTranslation(&world, cameraPos.x, cameraPos.y, cameraPos.z);
	HR(m_Effect->SetMatrix(m_WVPHandle, &(world * cameraViewProj)));

	UINT numPasses = 0;
	HR(m_Effect->Begin(&numPasses, 0));
	HR(m_Effect->BeginPass(0));
	HR(m_Sphere->DrawSubset(0));
	HR(m_Effect->EndPass());
	HR(m_Effect->End());
}
//=============================================================================