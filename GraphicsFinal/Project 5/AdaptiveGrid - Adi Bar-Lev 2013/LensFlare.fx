//Effect parameter
uniform extern float4x4 gViewProj;
uniform extern float3 gEyePosW;

uniform extern float3 gOffset;

uniform extern float2 gGridSize;

uniform extern float3 gQuadPos;

uniform extern float3 gColor;


uniform extern float gFade;

uniform extern texture  gTex;
//=============================================================================

//-----------------------------------------------------------------------------
sampler TexS = sampler_state
{
	Texture = <gTex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU  = WRAP;
    AddressV  = WRAP;
};
 
//-----------------------------------------------------------------------------
struct OutputVS
{
    float4 posH    : POSITION0;
    float2 tex0    : TEXCOORD0;
};

//-----------------------------------------------------------------------------
OutputVS BillBoardVS(float3 posL :		 POSITION0,
					 float3 quadPosW :	 TEXCOORD0,
					 float2 tex0 :		 TEXCOORD1)
{
	 // Zero out our output.
	OutputVS outVS = (OutputVS)0;

	quadPosW = gQuadPos;

	//Locks the z axis rotation
	float3 look = normalize(gEyePosW - quadPosW);
	float3 right = normalize(cross(float3(0.0f, 1.0f, 0.0f), look));
	float3 up    = cross(look, right);
	
	// Build look-at rotation matrix which makes the billboard face the camera.
	float4x4 lookAtMtx;
	lookAtMtx[0] = float4(right, 0.0f);
	lookAtMtx[1] = float4(up, 0.0f);
	lookAtMtx[2] = float4(look, 0.0f);
	lookAtMtx[3] = float4(quadPosW, 1.0f);
	
	// Transform to world space.
	float4 posW = mul(float4(posL, 1.0f), lookAtMtx);

	outVS.posH = mul(posW, gViewProj);
	outVS.tex0 = tex0;

	return outVS;
}

//-----------------------------------------------------------------------------
float4 BillBoardPS(float2 tex0 : TEXCOORD0) : COLOR
{
	float4 texColor = tex2D(TexS, tex0);

	//Colors that are too dark get alpha'ed out
	if(texColor.r < 0.25 && texColor.g < 0.25 && texColor.b < 0.25)
	{
		texColor.a = 0;
	}

	//fades by the fade value plus a default constant of half
	texColor.a -= gFade + .5f;

	return float4(gColor, texColor.a);
}

//-----------------------------------------------------------------------------
technique BillBoardTech
{
	pass P0
    {
        // Specify the vertex and pixel shader associated with this pass.
        vertexShader = compile vs_3_0 BillBoardVS();
        pixelShader  = compile ps_3_0 BillBoardPS();
        
		
        AlphaRef = 200;
        AlphaFunc = GreaterEqual;
        AlphaTestEnable = false;
        
        CullMode = None;
	}
}
//=============================================================================