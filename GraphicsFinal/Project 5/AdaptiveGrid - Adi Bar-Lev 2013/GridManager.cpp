//=============================================================================
// GridManager.cpp by Adi Bar-Lev 2011.
//
// This class is creating a patch that will be addptively moved to tile 
// an infinite grid and change the height and the texture according to the 
// absolute location in space, while moving and doing grid seemless translation
// on the fly in order to keep the center as the highest LOD resolution.
// All major calculations including grid height, normals and translations are 
// done on the fly by the GPU vertex and pixel shader (version 3.0)
//
// You may use this code or modify it as long as you keep this paragraph.
//=============================================================================
#define _USE_MATH_DEFINES

#include <math.h>
#include "DirectInput.h"
#include "GridManager.h"

//------------------------------------------------------------------------------
GridManager::GridManager( int segRes, float minSize, float maxDist, float maxHeight )
{
	m_SegmentsNum = segRes;
	m_FirstLevelCellSize = minSize;
	m_FirstLevelOffset = 0.5f * m_FirstLevelCellSize * m_SegmentsNum;
	m_LevelsNum = (int) (log( maxDist ) + 0.5f);

	m_gridOffset = D3DXVECTOR3(0.0f,0.0f,0.0f);

	m_MaxHeight = maxHeight;

	m_MaxPower = powf( 2.0f, (float) m_LevelsNum );
	m_GridSize = m_SegmentsNum * m_FirstLevelCellSize * m_MaxPower;

	m_Color = D3DXVECTOR4(1.0,0,1.0,1.0);

    m_CenterPatchVB = NULL;
    m_CenterPatchIB = NULL;
    
    m_SkirtVB = NULL;
    m_SkirtIB = NULL;
    
    m_LPatchVB = NULL;
    m_LPatchIB = NULL;

	m_Camera = new Camera();

	//---------- Light Direction ---------
	m_Light = D3DXVECTOR3(-1, 1, 0.5);

	//---------- Lights ---------
	m_DiffuseLightColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_SpecularLightColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_AmbientLightColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//---------- Mtrl ---------
	m_DiffuseColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_SpecularColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_AmbientColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	m_TextureOn = true;
	m_NormalOn = true;
	
	//---------- Shine ---------
	m_Shininess = 1;

	//---------- Light Coefficents ---------
	m_AmbientCoefficent = .35f;
	m_DiffuseCoefficent = .6f;
	m_SpecCoefficent = 0.05f;

	connectEffect();
	createGridBuffers();
}

//------------------------------------------------------------------------------
GridManager::~GridManager()
{
	ReleaseCOM(m_CenterPatchVB);
	ReleaseCOM(m_CenterPatchIB);
	
	ReleaseCOM(m_SkirtVB);
	ReleaseCOM(m_SkirtIB);
	
	ReleaseCOM(m_LPatchVB);
	ReleaseCOM(m_LPatchIB);

	ReleaseCOM( m_HeightTexture );
    ReleaseCOM( m_NormalTexture );
    ReleaseCOM( m_Ground1Texture );
    ReleaseCOM( m_Ground2Texture );
    ReleaseCOM( m_Ground3Texture );
    ReleaseCOM( m_BlendTexture );

	delete m_Camera;

	ReleaseCOM(m_pFX);
}

//------------------------------------------------------------------------------
void GridManager::connectEffect()
{
	// Create the FX from a .fx file.
	ID3DXBuffer*	errors = 0;
	HR( D3DXCreateEffectFromFile(gd3dDevice, "GridLOD.fx", 
		0, 0, D3DXSHADER_DEBUG, 0, &m_pFX, &errors));
	if( errors ) 
		MessageBox(0, (char*)errors->GetBufferPointer(), 0, 0);	

	HR( D3DXCreateTextureFromFile(gd3dDevice, "Textures/TerrainTextures/Texture_Height_2.jpg", &m_HeightTexture ));
	HR( D3DXCreateTextureFromFile(gd3dDevice, "Textures/TerrainTextures/Texture_Normal_2.jpg", &m_NormalTexture ));
	HR( D3DXCreateTextureFromFile(gd3dDevice, "Textures/TerrainTextures/noiseTexture.jpg", &m_NoiseTexture ));

	HR( D3DXCreateTextureFromFile(gd3dDevice, "Textures/TerrainTextures/Texture_Blend_2.jpg", &m_BlendTexture ));

	HR( D3DXCreateTextureFromFile(gd3dDevice, "Textures/GroundTextures/Texture_2_Rock.jpg", &m_Ground1Texture ));
	HR( D3DXCreateTextureFromFile(gd3dDevice, "Textures/GroundTextures/Texture_2_Grass.jpg", &m_Ground2Texture ));
	HR( D3DXCreateTextureFromFile(gd3dDevice, "Textures/GroundTextures/Texture_2_Dirt.jpg", &m_Ground3Texture ));

	HR( D3DXCreateTextureFromFile(gd3dDevice, "Textures/GroundTextures/Texture_2_Rock_Normal.jpg", &m_Ground1Normal ));
	HR( D3DXCreateTextureFromFile(gd3dDevice, "Textures/GroundTextures/Texture_2_Grass_Normal.jpg", &m_Ground2Normal ));
	HR( D3DXCreateTextureFromFile(gd3dDevice, "Textures/GroundTextures/Texture_2_Dirt_Normal.jpg", &m_Ground3Normal ));

	// Obtain handles.
	m_hTech			= m_pFX->GetTechniqueByName("TransformTech");

	m_hLightVec = m_pFX->GetParameterByName(0, "gLightVecW");

	m_hWorldInverseTranspose = m_pFX->GetParameterByName(0, "gWorldInverseTranspose");

	m_hAmbientMtrl = m_pFX->GetParameterByName(0, "gAmbientMtrl");
	m_hDiffuseMtrl = m_pFX->GetParameterByName(0, "gDiffuseMtrl");
	m_hSpecularMtrl = m_pFX->GetParameterByName(0, "gSpecularMtrl");
	m_hSpecularPower = m_pFX->GetParameterByName(0, "gSpecularPower");

	m_hAmbientLight = m_pFX->GetParameterByName(0, "gAmbientLight");
	m_hDiffuseLight = m_pFX->GetParameterByName(0, "gDiffuseLight");
	m_hSpecularLight = m_pFX->GetParameterByName(0, "gSpecularLight");

	m_hSpecularCoefficient = m_pFX->GetParameterByName(0, "gSpecularCoefficient");
	m_hDiffuseCoefficient = m_pFX->GetParameterByName(0, "gDiffuseCoefficient");
	m_hAmbientCoefficient = m_pFX->GetParameterByName(0, "gAmbientCoefficient");

	m_hFogCenter = m_pFX->GetParameterByName(0, "gFogCenter");

	m_hTextureOn = m_pFX->GetParameterByName(0, "gTextureOn");
	m_hNormalOn  = m_pFX->GetParameterByName(0, "gNormalOn");

	m_hInvSceneSize = m_pFX->GetParameterByName(0, "gInvSceneSize");
	m_hVP			= m_pFX->GetParameterByName(0, "gVP");
	m_hWorld		= m_pFX->GetParameterByName(0, "gWorld");
	m_hCellOffset	= m_pFX->GetParameterByName(0, "gCellsOffset");
	m_hColor		= m_pFX->GetParameterByName(0, "gColor");
	m_hMaxCellSize	= m_pFX->GetParameterByName(0, "gMaxCellSize");
	m_hHeightMultiplier	= m_pFX->GetParameterByName(0, "gHeightMultiplier");
	m_hHeightTexture = m_pFX->GetParameterByName(0, "gHeightTexture");
	m_hNormalTexture = m_pFX->GetParameterByName(0, "gNormalTexture");
	m_hGround1Texture = m_pFX->GetParameterByName(0, "gGroundTexture1");
	m_hGround2Texture = m_pFX->GetParameterByName(0, "gGroundTexture2");
	m_hGround3Texture = m_pFX->GetParameterByName(0, "gGroundTexture3");
	m_hGround1Normal = m_pFX->GetParameterByName(0, "gGroundNormal1");
	m_hGround2Normal = m_pFX->GetParameterByName(0, "gGroundNormal2");
	m_hGround3Normal = m_pFX->GetParameterByName(0, "gGroundNormal3");
	m_hBlendTexture = m_pFX->GetParameterByName(0, "gBlendTexture");
	m_hNoiseTexture = m_pFX->GetParameterByName(0, "gNoiseTexture");
    m_hViewerPos = m_pFX->GetParameterByName(0, "gViewerPos");
}

//------------------------------------------------------------------------------
void GridManager::createGridBuffers()
{
	createCenterBuffers();
	createLPatchBuffers();
}

//------------------------------------------------------------------------------
void GridManager::createCenterBuffers()
{
	std::vector<VertexPosTex>	Vtx;
	std::vector<WORD>			Idx;
	int							vtxPerSide = m_SegmentsNum - 1;	// off with the side skirts

	CreateGrid( vtxPerSide, m_FirstLevelCellSize, Vtx, Idx );

	// Save vertex count and triangle count for DrawIndexedPrimitive arguments.
	m_CenterVtxNum  = vtxPerSide * vtxPerSide;
	m_CenterTriNum = 2 * (vtxPerSide - 1) * (vtxPerSide - 1);

	int		halfSize = vtxPerSide >> 1;
	int		numCellPerSide = vtxPerSide-1;
	m_LPatchVtxNum = vtxPerSide * vtxPerSide - halfSize * halfSize;
	m_LPatchTriNum = 2 * (numCellPerSide * numCellPerSide - halfSize * halfSize);

	// Obtain a pointer to a new vertex buffer.
	HR(gd3dDevice->CreateVertexBuffer( m_CenterVtxNum * sizeof(VertexPosTex), 
		D3DUSAGE_WRITEONLY,	0, D3DPOOL_MANAGED, &m_CenterPatchVB, 0));

	// Now lock it to obtain a pointer to its internal data, and write the
	// grid's vertex data.
	VertexPosTex*		pVtx = 0;
	HR( m_CenterPatchVB->Lock(0, 0, (void**)&pVtx, 0));
	memcpy( pVtx, (void *) &Vtx[0], m_CenterVtxNum * sizeof(VertexPosTex) );
	HR( m_CenterPatchVB->Unlock());


	// Obtain a pointer to a new index buffer.
	HR(gd3dDevice->CreateIndexBuffer( m_CenterTriNum*3*sizeof(WORD), D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_CenterPatchIB, 0));

	// Now lock it to obtain a pointer to its internal data, and write the
	// grid's index data.
	WORD*	pIdx = 0;
	HR( m_CenterPatchIB->Lock(0, 0, (void**)&pIdx, 0));
	memcpy( pIdx, (void *) &Idx[0], 3 * m_CenterTriNum * sizeof(WORD) );
	HR( m_CenterPatchIB->Unlock());
}

//------------------------------------------------------------------------------
void GridManager::createLPatchBuffers()
{
	std::vector<VertexPosTex>	Vtx;
	std::vector<WORD>			Idx;

	CreateLPatchWithSkirt( m_SegmentsNum, m_FirstLevelCellSize, Vtx, Idx, m_LPatchVtxNum, m_LPatchTriNum  );

	// Obtain a pointer to a new vertex buffer.
	HR(gd3dDevice->CreateVertexBuffer( m_LPatchVtxNum * sizeof(VertexPosTex), 
		D3DUSAGE_WRITEONLY,	0, D3DPOOL_MANAGED, &m_LPatchVB, 0));

	// Now lock it to obtain a pointer to its internal data, and write the
	// grid's vertex data.
	VertexPosTex*		pVtx = 0;
	HR( m_LPatchVB->Lock(0, 0, (void**)&pVtx, 0));
	memcpy( pVtx, (void *) &Vtx[0], m_LPatchVtxNum * sizeof(VertexPosTex) );
	HR( m_LPatchVB->Unlock());


	// Obtain a pointer to a new index buffer.
	HR(gd3dDevice->CreateIndexBuffer( m_LPatchTriNum*3*sizeof(WORD), D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_LPatchIB, 0));

	// Now lock it to obtain a pointer to its internal data, and write the
	// grid's index data.
	WORD*	pIdx = 0;
	HR( m_LPatchIB->Lock(0, 0, (void**)&pIdx, 0));
	memcpy( pIdx, (void *) &Idx[0], 3 * m_LPatchTriNum * sizeof(WORD) );
	HR( m_LPatchIB->Unlock());
}

//------------------------------------------------------------------------------
// m_posOnGrid + m_gridOffset = pos
//
// m_gridOffset - the shift of the textures coordinates on the grid, hence 
// the shift of the height map.
//
// m_posOnGrid - the remaining shift to be done in the view matrix.
//------------------------------------------------------------------------------
void GridManager::buildViewMatrix(float& maxCellSize )
{
	static D3DXVECTOR3		pos = D3DXVECTOR3(0,0,0);

    // Setting the cell size to be the maximal size - big jumps
	float			    maxPower = powf( 2.0f, (float) m_LevelsNum );
	maxCellSize = m_FirstLevelCellSize * maxPower;

	D3DXVECTOR3		    posCellOffset = pos / maxCellSize;
	D3DXVECTOR3		    lookAtDir =  m_Camera->look();

	m_Pos = pos;
	m_gridOffset = D3DXVECTOR3( (float)((int) posCellOffset.x), 0, (float)((int) posCellOffset.z) ) * maxCellSize;
	m_posOnGrid = pos - m_gridOffset;
	pos += m_Camera->lastMoveVector();
	m_Camera->lastMoveVector() =  D3DXVECTOR3(0.0f,0.0f,0.0f);

	D3DXVECTOR3		lookAt = m_posOnGrid + lookAtDir;

	D3DXMatrixLookAtLH( &m_ViewMatrix, &m_posOnGrid, &lookAt, &m_Camera->up());
}

//------------------------------------------------------------------------------
void GridManager::updateCamera(float dt) 
{ 
	m_Camera->update(dt);
}


//------------------------------------------------------------------------------
// Parameters specific for the landscape shader - water surface will use others.
void GridManager::setLandscapeShaderParameters( void )
{
	// Setup the rendering FX
	HR( m_pFX->SetTechnique( m_hTech ));

	HR( m_pFX->SetTexture( m_hHeightTexture, m_HeightTexture ));
	HR( m_pFX->SetTexture( m_hNormalTexture, m_NormalTexture ));
	HR( m_pFX->SetTexture( m_hGround1Texture, m_Ground1Texture ));
	HR( m_pFX->SetTexture( m_hGround2Texture, m_Ground2Texture ));
	HR( m_pFX->SetTexture( m_hGround3Texture, m_Ground3Texture ));
	HR( m_pFX->SetTexture( m_hGround1Normal, m_Ground1Normal ));
	HR( m_pFX->SetTexture( m_hGround2Normal, m_Ground2Normal ));
	HR( m_pFX->SetTexture( m_hGround3Normal, m_Ground3Normal ));
	HR( m_pFX->SetTexture( m_hBlendTexture, m_BlendTexture ));
	HR( m_pFX->SetTexture( m_hNoiseTexture, m_NoiseTexture ));
	HR( m_pFX->SetFloat( m_hHeightMultiplier, m_MaxHeight ) );
	HR( m_pFX->SetFloat( m_hInvSceneSize, 1.0f / m_GridSize ) );
}

//------------------------------------------------------------------------------
int GridManager::drawGrid(D3DXMATRIX& Proj )
{	
	float			maxCellSize;
	D3DXMATRIX		world;
	D3DXMATRIX		worldInverseTranspose;
    int             vtxNum = 0;

	buildViewMatrix(maxCellSize );
	
	D3DXMATRIX		matViewProj   = m_ViewMatrix * Proj;

	// Let Direct3D know the vertex buffer, index buffer and vertex declaration we are using.
	//HR( d3dDevice->SetStreamSource(0, m_CenterPatchVB , 0, sizeof(VertexPosTex)));
	//HR( d3dDevice->SetIndices( m_CenterPatchIB ));

	HR( gd3dDevice->SetStreamSource(0, m_LPatchVB , 0, sizeof(VertexPosTex)));
	HR( gd3dDevice->SetIndices( m_LPatchIB ));

	HR( gd3dDevice->SetVertexDeclaration(VertexPosTex::Decl));

	setLandscapeShaderParameters();

	HR( m_pFX->SetMatrix( m_hVP, &(matViewProj)));
	HR( m_pFX->SetVector( m_hColor, &m_Color ) );
	HR( m_pFX->SetFloat( m_hMaxCellSize, maxCellSize ) );
	HR( m_pFX->SetVector( m_hCellOffset, (D3DXVECTOR4 *) &m_gridOffset ) );
	HR( m_pFX->SetVector( m_hViewerPos, (D3DXVECTOR4 *) &m_Pos ) );
	HR( m_pFX->SetVector( m_hFogCenter, (D3DXVECTOR4 *) &m_Camera->proj() ) );

	//------------------------------------------------------------------------------
	HR(m_pFX->SetValue(m_hLightVec, &m_Light, sizeof(D3DXVECTOR3)));

	//HR(m_Effect->SetValue(m_DiffuseMtrlHandle, &m_DiffuseColor, sizeof(D3DXCOLOR)));
	
	HR( m_pFX->SetValue( m_hAmbientMtrl, &m_AmbientColor, sizeof(D3DXCOLOR) ) );
	HR( m_pFX->SetValue( m_hDiffuseMtrl, &m_DiffuseColor, sizeof(D3DXCOLOR) ) );
	HR( m_pFX->SetValue( m_hSpecularMtrl, &m_SpecularColor, sizeof(D3DXCOLOR) ) );
	HR( m_pFX->SetFloat( m_hSpecularPower, m_Shininess ) );

	HR( m_pFX->SetValue( m_hAmbientLight, &m_AmbientLightColor, sizeof(D3DXCOLOR) ) );
	HR( m_pFX->SetValue( m_hDiffuseLight, &m_DiffuseLightColor, sizeof(D3DXCOLOR) ) );
	HR( m_pFX->SetValue( m_hSpecularLight, &m_SpecularLightColor, sizeof(D3DXCOLOR) ) );

	HR( m_pFX->SetBool( m_hTextureOn, m_TextureOn ) );
	HR( m_pFX->SetBool( m_hNormalOn, m_NormalOn) );

	HR( m_pFX->SetFloat( m_hSpecularCoefficient, m_SpecCoefficent ) );
	HR( m_pFX->SetFloat( m_hDiffuseCoefficient, m_DiffuseCoefficent ) );
	HR( m_pFX->SetFloat( m_hAmbientCoefficient, m_AmbientCoefficent ) );

	

	for ( int level=0 ; level<m_LevelsNum ; level++ )
	{
		float		scaleFactor = powf( 2.0f, (float) level);

		for ( int quadrant=0 ; quadrant<4 ; quadrant++ )
		{
			buildWorldMatrix( world, level, quadrant );
			buildWorldMatrix( worldInverseTranspose, level, quadrant );
			D3DXMatrixInverse(&worldInverseTranspose, 0, &worldInverseTranspose);
			D3DXMatrixTranspose(&worldInverseTranspose, &worldInverseTranspose);
			HR( m_pFX->SetMatrix( m_hWorld, &world ) );
			HR( m_pFX->SetMatrix( m_hWorldInverseTranspose, &worldInverseTranspose ) );

			// Begin passes.
			UINT numPasses = 0;
			HR( m_pFX->Begin(&numPasses, 0));
			for(UINT i = 0; i < numPasses; ++i)
			{
				HR(m_pFX->BeginPass(i));
				HR(gd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_LPatchVtxNum, 0, m_LPatchTriNum ));
                vtxNum += m_LPatchVtxNum;
				HR(m_pFX->EndPass());
			}
			HR( m_pFX->End() );
		}
	}
    return vtxNum;
}
//------------------------------------------------------------------------------
void GridManager::buildWorldMatrix( D3DXMATRIX& worldMatrix, int level, int quadrant )
{
	float			scaleFactor = powf( 2.0f, (float) level);
	float			scaledSize = m_FirstLevelOffset * scaleFactor;
	int				xOffset = quadrant % 2, zOffset = quadrant / 2;
	D3DXVECTOR3		center = D3DXVECTOR3( 0,0,0 );
	D3DXVECTOR3		offset = D3DXVECTOR3( -scaledSize + xOffset * scaledSize, 0, -scaledSize + zOffset * scaledSize );
	D3DXVECTOR3		scale = D3DXVECTOR3( scaleFactor, scaleFactor, scaleFactor );

	D3DXMatrixRotationY( &worldMatrix, (float) (quadrant * M_PI_2) );
	worldMatrix *= scaleFactor;
	worldMatrix._44 = 1.0f;
}
//------------------------------------------------------------------------------
