//=============================================================================
// Originally adapted from Terrain.cpp by Frank Luna (C) 2004.
//=============================================================================
// Changed to enhance and support a demo that demonstrates the generation and 
/// rendering of adaptive grid via GPU by Adi Bar-Lev, 2011.
//=============================================================================
//=============================================================================
#define D3D_DEBUG_INFO
//=============================================================================
#include "d3dApp.h"
#include "DirectInput.h"
#include <crtdbg.h>
#include "GfxStats.h"
#include <list>
#include "Vertex.h"
#include "GridManager.h"
#include "SkyBox.h"
#include "Clouds.h"
#include "LensFlare.h"
//=============================================================================

class TriGridDemo : public D3DApp
{
public:
	TriGridDemo(HINSTANCE hInstance, std::string winCaption, D3DDEVTYPE devType, DWORD requestedVP);
	~TriGridDemo();

	bool checkDeviceCaps();
	void onLostDevice();
	void onResetDevice();
	void updateScene(float dt);
	void drawScene();

	void drawGridLOD();
	void buildProjMtx();

private:
	GfxStats*		mGfxStats;
	DWORD			mNumVertices;
	DWORD			mNumTriangles;

	SkyBox*			m_SkyBox;
	GridManager*	m_pGridManager;
	Clouds*			m_pClouds;
	LensFlare*		m_LensFlare;

	bool			m_TPressed;
	bool			m_NPressed;
	D3DXMATRIX		mProj;
	
};
//=============================================================================

//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif

	TriGridDemo app(hInstance, "Grid Demo", D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING);
	gd3dApp = &app;

	DirectInput di(DISCL_NONEXCLUSIVE|DISCL_FOREGROUND, DISCL_NONEXCLUSIVE|DISCL_FOREGROUND);
	gDInput = &di;

    if(!gd3dApp->checkDeviceCaps())
		return 0;
	else
		return gd3dApp->run();
}

//-----------------------------------------------------------------------------
TriGridDemo::TriGridDemo(HINSTANCE hInstance, std::string winCaption, D3DDEVTYPE devType, DWORD requestedVP)
: D3DApp(hInstance, winCaption, devType, requestedVP)
{
	if(!checkDeviceCaps())
	{
		MessageBox(0, "checkDeviceCaps() Failed", 0, 0);
		PostQuitMessage(0);
	}

	mGfxStats = new GfxStats();

    int     resPerLevel = 128;//128;
    float   minQuadSize = 0.1f;     // the size of the smallest quad.
    float   maxHeight = 100.0f;      // moon.  use 150.0f for mountains
    float   maxDist = 5000.0f;      // size of the grid
	m_pGridManager = new GridManager( resPerLevel, minQuadSize, maxDist, maxHeight );

	m_SkyBox = new SkyBox();

	InitAllVertexDeclarations();

	m_pClouds = new Clouds(D3DXVECTOR2(m_pGridManager->getGridSize() * 5, m_pGridManager->getGridSize() * 5), 1000.0f, 2000.0f, 200.0f, 1000.0f, 1000);

	m_LensFlare = new LensFlare(D3DXVECTOR2(m_pGridManager->getGridSize(), m_pGridManager->getGridSize()));

	onResetDevice();
}

//-----------------------------------------------------------------------------
TriGridDemo::~TriGridDemo()
{
	delete mGfxStats;
    delete m_pGridManager;
	delete m_pClouds;

	DestroyAllVertexDeclarations();
}

//-----------------------------------------------------------------------------
bool TriGridDemo::checkDeviceCaps()
{
	D3DCAPS9 caps;
	HR(gd3dDevice->GetDeviceCaps(&caps));

	// Check for vertex shader version 2.0 support.
	if( caps.VertexShaderVersion < D3DVS_VERSION(3, 0) )
		return false;

	// Check for pixel shader version 2.0 support.
	if( caps.PixelShaderVersion < D3DPS_VERSION(2, 0) )
		return false;

	return true;
}

//-----------------------------------------------------------------------------
void TriGridDemo::onLostDevice()
{
	mGfxStats->onLostDevice();
	m_pGridManager->onLostDevice();
	m_SkyBox->OnLostDevice();
	m_pClouds->OnLostDevice();
	m_LensFlare->OnLostDevice();
}

//-----------------------------------------------------------------------------
void TriGridDemo::onResetDevice()
{
	mGfxStats->onResetDevice();
	m_pGridManager->onResetDevice();
	m_SkyBox->OnResetDevice();
	m_pClouds->OnResetDevice();
	m_LensFlare->OnResetDevice();

	// The aspect ratio depends on the backbuffer dimensions, which can 
	// possibly change after a reset.  So rebuild the projection matrix.
	buildProjMtx();
}

//-----------------------------------------------------------------------------
void TriGridDemo::updateScene(float dt)
{
	mGfxStats->setVertexCount(mNumVertices);
	mGfxStats->setTriCount(mNumTriangles);
	mGfxStats->update(dt);

	// Get snapshot of input devices.
	gDInput->poll();

	// Check input.

	if( gDInput->keyDown(DIK_T) && !m_TPressed )
	{
		m_TPressed = true;
		m_pGridManager->toggleTexture();
	}
	if( !gDInput->keyDown(DIK_T))
	{
		m_TPressed = false;
	}

	if( gDInput->keyDown(DIK_N) && !m_NPressed )
	{
		m_NPressed = true;
		m_pGridManager->toggleNormal();
	}
	if( !gDInput->keyDown(DIK_N))
	{
		m_NPressed = false;
	}

	m_pGridManager->updateCamera(dt);
}

//------------------------------------------------------------------------------
void TriGridDemo::drawScene()
{
    if (m_SolidFillStyle)
        gd3dDevice->SetRenderState( D3DRS_FILLMODE , D3DFILL_SOLID );
    else
        gd3dDevice->SetRenderState( D3DRS_FILLMODE , D3DFILL_WIREFRAME );

	//Allows for alpha blend
	gd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	gd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	gd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	gd3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	gd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	gd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	drawGridLOD();
}

//------------------------------------------------------------------------------
void TriGridDemo::drawGridLOD()
{
	// Clear the backbuffer and depth buffer.
	HR(gd3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0));

    HR( gd3dDevice->BeginScene());

	m_SkyBox->Draw(m_pGridManager->getCamera()->pos(), m_pGridManager->getCamera()->viewProj());
	m_pClouds->Draw(m_pGridManager->getCamera()->pos(), m_pGridManager->getCamera()->viewProj(), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	

	int     vtxNum = m_pGridManager->drawGrid(mProj );

	
	m_LensFlare->Draw(m_pGridManager->getCamera());

    mGfxStats->setTriCount( 2 * vtxNum );   // rough estimate    
    mGfxStats->setVertexCount( vtxNum );  
    mGfxStats->display();

    HR( gd3dDevice->EndScene());

	// Present the backbuffer.
	HR(gd3dDevice->Present(0, 0, 0, 0));
} 

//-----------------------------------------------------------------------------
void TriGridDemo::buildProjMtx()
{
	float w = (float)md3dPP.BackBufferWidth;
	float h = (float)md3dPP.BackBufferHeight;
	m_pGridManager->setLens(D3DX_PI * 0.25f, w/h, 1.0f, 5000.0f);
	D3DXMatrixPerspectiveFovLH(&mProj, D3DX_PI * 0.25f, w/h, 1.0f, 5000.0f);
}
//=============================================================================