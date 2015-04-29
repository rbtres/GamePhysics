//=============================================================================
// GridManager.h by Adi Bar-Lev 2011.
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
#define D3D_DEBUG_INFO

#include <d3d9.h>
#include <d3dx9.h>
#include "d3dUtil.h"
#include "Vertex.h"
#include "Camera.h"

class GridManager 
{
private:
	int		m_SegmentsNum;			// resolution of the inner segment
	int		m_LevelsNum;				
	float	m_FirstLevelCellSize;	// the very minimum desired size resolution
	float	m_GridSize;				// at which to stop mesh creation (horizon)
	float	m_FirstLevelOffset;
	bool m_TextureOn;
	bool m_NormalOn;
	

	IDirect3DVertexBuffer9*		m_CenterPatchVB;
	IDirect3DIndexBuffer9*		m_CenterPatchIB;
	int							m_CenterVtxNum;
	int							m_CenterTriNum;

	IDirect3DVertexBuffer9*		m_SkirtVB;
	IDirect3DIndexBuffer9*		m_SkirtIB;
	int							m_SkirtVtxNum;
	int							m_SkirtTriNum;

	IDirect3DVertexBuffer9*		m_LPatchVB;
	IDirect3DIndexBuffer9*		m_LPatchIB;
	int							m_LPatchVtxNum;
	int							m_LPatchTriNum;

	D3DXMATRIX					m_ViewMatrix;
	D3DXVECTOR3					m_posOnGrid;
	D3DXVECTOR3					m_gridOffset;
	D3DXVECTOR3					m_Pos;
	D3DXVECTOR4					m_Color;
	float						m_MaxHeight;
	float						m_MaxPower;

	ID3DXEffect*				m_pFX;
	IDirect3DTexture9*			m_HeightTexture;
	IDirect3DTexture9*			m_NormalTexture;
	IDirect3DTexture9*			m_Ground1Texture;
	IDirect3DTexture9*			m_Ground2Texture;
	IDirect3DTexture9*			m_Ground3Texture;
	IDirect3DTexture9*			m_Ground1Normal;
	IDirect3DTexture9*			m_Ground2Normal;
	IDirect3DTexture9*			m_Ground3Normal;
	IDirect3DTexture9*			m_BlendTexture;
	IDirect3DTexture9*			m_NoiseTexture;

	D3DXHANDLE					m_hTech;
	D3DXHANDLE					m_hTextureOn;
	D3DXHANDLE					m_hMaxCellSize;
	D3DXHANDLE					m_hInvSceneSize;
	D3DXHANDLE					m_hCellOffset;
	D3DXHANDLE					m_hWorld;
	D3DXHANDLE					m_hVP;
    D3DXHANDLE                  m_hViewerPos;
	D3DXHANDLE					m_hColor;
	D3DXHANDLE					m_hHeightMultiplier;
	D3DXHANDLE					m_hHeightTexture;
	D3DXHANDLE					m_hNormalTexture;
	D3DXHANDLE					m_hGround1Texture;
	D3DXHANDLE					m_hGround2Texture;
	D3DXHANDLE					m_hGround3Texture;
	D3DXHANDLE					m_hGround1Normal;
	D3DXHANDLE					m_hGround2Normal;
	D3DXHANDLE					m_hGround3Normal;
	D3DXHANDLE					m_hBlendTexture;

	//------------------ Phong Handles ---------------

	D3DXHANDLE					m_hLightVec;
	D3DXHANDLE					m_hNormalOn;

	D3DXHANDLE					m_hWorldInverseTranspose;

	D3DXHANDLE					m_hAmbientMtrl;
	D3DXHANDLE					m_hDiffuseMtrl;
	D3DXHANDLE					m_hSpecularMtrl;
	D3DXHANDLE					m_hSpecularPower;

	D3DXHANDLE					m_hAmbientLight;
	D3DXHANDLE					m_hDiffuseLight;
	D3DXHANDLE					m_hSpecularLight;

	D3DXHANDLE					m_hSpecularCoefficient;
	D3DXHANDLE					m_hDiffuseCoefficient;
	D3DXHANDLE					m_hAmbientCoefficient;

	D3DXHANDLE					m_hFogCenter;

	D3DXHANDLE					m_hNoiseTexture;

	//------------------ ------------------------------

	//------------------ Phong Varriables ---------------

	//-------- Material Parameters -------
    D3DXMATRIX          m_WorldMat;
    D3DXMATRIX          m_ViewProjectionMat;

	D3DXVECTOR3			m_Light;

    D3DXCOLOR         m_DiffuseColor;
    D3DXCOLOR         m_SpecularColor;
	D3DXCOLOR         m_AmbientColor;

	D3DXCOLOR		m_DiffuseLightColor;
	D3DXCOLOR		m_SpecularLightColor;
	D3DXCOLOR		m_AmbientLightColor;


    float               m_Shininess;            // specular power

	//---------- Light Coefficents ---------
	float				m_AmbientCoefficent;
	float				m_DiffuseCoefficent;
	float				m_SpecCoefficent;

	//------------------ ------------------------------

	Camera*						m_Camera;

protected:
	void connectEffect();
	void createSkirtBuffers();
	void createLPatchBuffers();
	void createCenterBuffers();
	void createGridBuffers();
	void buildWorldMatrix( D3DXMATRIX& worldMatrix, int level, int quadrant );
	void buildViewMatrix(float& maxCellSize );
	void setLandscapeShaderParameters( void );
	

public:
	GridManager( int segRes, float minSize, float maxDist, float maxHeight );
	~GridManager();

    // returns the number of rendered vertices
	int drawGrid(D3DXMATRIX& Proj );
	void updateCamera(float dt);
	inline void setLens(float fov, float aspect, float nearZ, float farZ){ m_Camera->setLens(fov, aspect, nearZ, farZ); } 

	D3DXVECTOR3 getPos() { return m_Pos; }

	inline float getGridSize() { return m_GridSize; }

	inline Camera* getCamera() { return m_Camera; };

	inline D3DXVECTOR3 getLightDirection() { return m_Light; }

	inline float getMaxHeight() { return m_MaxHeight; }

	inline void toggleTexture() { m_TextureOn = !m_TextureOn; }
	inline void toggleNormal() { m_NormalOn = !m_NormalOn; }
		
	void onLostDevice()		{	HR(m_pFX->OnLostDevice());	}
	void onResetDevice()	{	HR(m_pFX->OnLostDevice());	}
};
//=============================================================================