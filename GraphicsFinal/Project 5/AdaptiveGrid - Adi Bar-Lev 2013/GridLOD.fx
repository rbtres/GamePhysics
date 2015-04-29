//=============================================================================
// GridLOD.fx by Adi Bar-Lev 2011.
// You may use this code or modify it as long as you keep this paragraph.
//=============================================================================


uniform extern float		gInvSceneSize;
uniform extern float		gMaxCellSize;
uniform extern float		gHeightMultiplier;
uniform extern float4x4		gWorld;
uniform extern float4x4		gVP;
uniform extern float4		gColor;
uniform extern float4		gCellsOffset;
uniform extern float4		gViewerPos;		// only xz are used

uniform extern float3 gLightVecW;

uniform extern float4x4 gWorldInverseTranspose;

uniform extern float4 gAmbientMtrl;
uniform extern float4 gDiffuseMtrl;
uniform extern float4 gSpecularMtrl;
uniform extern float gSpecularPower;

uniform extern float4 gAmbientLight;
uniform extern float4 gDiffuseLight;
uniform extern float4 gSpecularLight;

uniform extern float gSpecularCoefficient;
uniform extern float gDiffuseCoefficient;
uniform extern float gAmbientCoefficient;

uniform extern float4 gFogCenter;

uniform extern bool gTextureOn;
uniform extern bool gNormalOn;

// Texures used to create the terrain
uniform extern texture		gHeightTexture;
uniform extern texture		gNormalTexture;

uniform extern texture		gNoiseTexture;

// Textures for rendering on the terrain surface
uniform extern texture		gGroundTexture1;
uniform extern texture		gGroundTexture2;
uniform extern texture		gGroundTexture3;
uniform extern texture		gGroundNormal1;
uniform extern texture		gGroundNormal2;
uniform extern texture		gGroundNormal3;
uniform extern texture		gBlendTexture;		// blending the ground textures using the RGB channels


static float3 gFogColor = {0.70f, 0.70f, 0.70f};
static float gFogStart = 2000.0f;
static float gFogRange = 1000.0f;

sampler HeightTexSampler = sampler_state
{
	Texture = <gHeightTexture>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU  = WRAP;
    AddressV  = WRAP;
};

sampler NormalTexSampler = sampler_state
{
	Texture = <gNormalTexture>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU  = WRAP;
    AddressV  = WRAP;
};

sampler NoiseTexSampler = sampler_state
{
	Texture = <gNoiseTexture>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU  = WRAP;
    AddressV  = WRAP;
};

sampler Ground1TexSampler = sampler_state
{
	Texture = <gGroundTexture1>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU  = WRAP;
    AddressV  = WRAP;
};

sampler Ground2TexSampler = sampler_state
{
	Texture = <gGroundTexture2>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU  = WRAP;
    AddressV  = WRAP;
};

sampler Ground3TexSampler = sampler_state
{
	Texture = <gGroundTexture3>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU  = WRAP;
    AddressV  = WRAP;
};



sampler GroundNormal1TexSampler = sampler_state
{
	Texture = <gGroundNormal1>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU  = WRAP;
    AddressV  = WRAP;
};

sampler GroundNormal2TexSampler = sampler_state
{
	Texture = <gGroundNormal2>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU  = WRAP;
    AddressV  = WRAP;
};

sampler GroundNormal3TexSampler = sampler_state
{
	Texture = <gGroundNormal3>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU  = WRAP;
    AddressV  = WRAP;
};

sampler BlendTexSampler = sampler_state
{
	Texture = <gBlendTexture>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU  = WRAP;
    AddressV  = WRAP;
};

//------------------------------------------------------------------------------
struct OutputVS
{
    float4 posH : POSITION0;
    float2 texH : TEXCOORD0;
	float3 posW : TEXCOORD1;
	float fogLerpParam : TEXCOORD2;
};

//------------------------------------------------------------------------------
OutputVS TransformVS(float3 posL : POSITION0, float2 texL : TEXCOORD0 )
{
    // Zero out our output.
	OutputVS outVS = (OutputVS)0;

	float		texCoorMult = 6;

	float4		wPos = mul( float4(posL, 1.0f), gWorld );

	// calculates the height cordinates
	float2		heightCoords = texCoorMult * gInvSceneSize * (wPos.xz + gCellsOffset.xz) + float2( 0.5, 0.5 );
	float height = 0.0f;

	//adds noise to the height
	float2 heightCoordsA = heightCoords.xy;
	float2 heightCoordsB = heightCoords.xy * 16477;
	float aMultiplier = 60;

	// blends the height with the noise
	height += (tex2Dlod( HeightTexSampler, float4(heightCoordsA ,0.0,0.0) ).r * gHeightMultiplier - 0.5 * gHeightMultiplier) * aMultiplier;
	height += (tex2Dlod( NoiseTexSampler, float4(heightCoordsB ,0.0,0.0) ).r * gHeightMultiplier - 0.5 * gHeightMultiplier);
	height /= (aMultiplier + 1);
	wPos.y = height;

	float2		correctedPosXZ = wPos.xz + gCellsOffset.xz - gViewerPos.xz;

	outVS.posW = mul(float4(posL, 1.0f), gWorld).xyz;

	float3	normal = normalize( tex2Dlod( NormalTexSampler, float4(heightCoords ,0.0,0.0) ).rgb * 2 - 1 );

	outVS.posH = mul( wPos, gVP );

	outVS.texH = heightCoords;

	float dist = distance(wPos, gFogCenter);

	float fogLerp = saturate((dist - gFogStart) / gFogRange);

	outVS.fogLerpParam = fogLerp;
	 
	// Done--return the output.
    return outVS;
}

//------------------------------------------------------------------------------
float4 TransformSurfacePS( float2 tex : TEXCOORD0) : COLOR
{
	float3	normal = normalize( tex2D( NormalTexSampler, tex.xy ) * 2 - 1 );
	float3	shade = pow( 0.9 * dot( normal, normalize( float3(0.8,0.2,1.0) ) ), 2.0 );
	
	return float4( shade, 1.0 );
    return gColor;
}

//------------------------------------------------------------------------------
float4 TransformSurfaceWithTexturePS( float2 tex : TEXCOORD0, float3 posW : TEXCOORD1, float fogLerpParam : TEXCOORD2) : COLOR
{
	float3	groundBlend = tex2D( BlendTexSampler, tex.xy );		// the blend is according to the ground features

	//Normal from the normal map
	float3	normal =  normalize( tex2D( NormalTexSampler, tex ) * 2 - 1 );

	float2 coordA = tex.xy;
	float2 coordB = tex.xy * 16477;

	// gets the normals for the ground texture and blends them with a prime tex value for randomness
	float3	normal1A =  normalize( tex2D( GroundNormal1TexSampler, coordA )* 2 - 1) * groundBlend.r;
	float3	normal2A =  normalize( tex2D( GroundNormal2TexSampler, coordA )* 2 - 1) * groundBlend.g;
	float3	normal3A =  normalize( tex2D( GroundNormal3TexSampler, coordA )* 2 - 1) * groundBlend.b;
	float3	normal1B =  normalize( tex2D( GroundNormal1TexSampler, coordB )* 2 - 1) * groundBlend.r;
	float3	normal2B =  normalize( tex2D( GroundNormal2TexSampler, coordB )* 2 - 1) * groundBlend.g;
	float3	normal3B =  normalize( tex2D( GroundNormal3TexSampler, coordB )* 2 - 1) * groundBlend.b;

	float3 normalBlend = ((normal1A + normal1B) / 2) + ((normal2A + normal2B) / 2) + ((normal3A + normal3B) / 2);

	if(gNormalOn)
	{
		normal = (normal + normalBlend) / 2;
	}

	normal *= gHeightMultiplier;

	normal = normalize(normal);

	//calculate lighting
	float3 toEye = normalize(gViewerPos - posW);

	float3 r = reflect(-gLightVecW, normal);

	float t = pow(max(dot(r,toEye), 0.0f), gSpecularPower);

	float s = max(dot(gLightVecW, normal), 0.0f);

	float3 diffuseColor = s * (gDiffuseMtrl * gDiffuseLight).rgb * gDiffuseCoefficient;
	float3 specColor = t * ((gSpecularMtrl * gSpecularLight).rgb * gSpecularCoefficient);
	float3 ambientColor = (gAmbientMtrl * gAmbientLight).rgb * gAmbientCoefficient;

	// blends the ground textures with a prime number for randomness
	float3	ground1A = tex2D( Ground1TexSampler, coordA ) * groundBlend.r;
	float3	ground2A = tex2D( Ground2TexSampler, coordA ) * groundBlend.g;
	float3	ground3A = tex2D( Ground3TexSampler, coordA ) * groundBlend.b;
	float3	ground1B = tex2D( Ground1TexSampler, coordB ) * groundBlend.r;
	float3	ground2B = tex2D( Ground2TexSampler, coordB ) * groundBlend.g;
	float3	ground3B = tex2D( Ground3TexSampler, coordB ) * groundBlend.b;

	float3	groundColor = ((ground1A + ground1B) / 2) + ((ground2A + ground2B) / 2) + ((ground3A + ground3B) / 2);
	
	// turns the texture off dependent on the gTextureOn bool
	if(!gTextureOn)
	{
		groundColor = float3(1.0f,1.0f,1.0f);
	}

	//calculates the lighting
	float3 lighting = ((ambientColor + diffuseColor) * groundColor) + specColor;

	//blends the fog with the lighting
	float3 fog = lerp(lighting, gFogColor, fogLerpParam);
 
	return float4(fog, 1.0f);
}

//------------------------------------------------------------------------------
technique TransformTech
{
    pass P0
    {
        vertexShader = compile vs_3_0 TransformVS();
		pixelShader  = compile ps_3_0 TransformSurfaceWithTexturePS();
		AlphaRef = 200;
        AlphaFunc = GreaterEqual;
        AlphaTestEnable = false;
        
        CullMode = None;
    }
}
//------------------------------------------------------------------------------