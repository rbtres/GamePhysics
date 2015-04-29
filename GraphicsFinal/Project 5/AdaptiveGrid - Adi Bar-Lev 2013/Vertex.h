//=============================================================================
// Vertex.h by Frank Luna (C) 2005 All Rights Reserved.
//
// This file contains all of our vertex structures.  We will add to it
// as needed throughout the book.
//=============================================================================

#ifndef VERTEX_H
#define VERTEX_H

#include <d3dx9.h>


// Call in constructor and destructor, respectively, of derived application class.
void InitAllVertexDeclarations();
void DestroyAllVertexDeclarations();


//===============================================================
struct VertexPos
{
	VertexPos():pos(0.0f, 0.0f, 0.0f){}
	VertexPos(float x, float y, float z):pos(x,y,z){}
	VertexPos(const D3DXVECTOR3& v):pos(v){}

	D3DXVECTOR3 pos;
	static IDirect3DVertexDeclaration9* Decl;
};

//===============================================================
struct VertexPosTex
{
	VertexPosTex() : pos(0.0f, 0.0f, 0.0f), tex(0.0f, 0.0f) {}
	VertexPosTex(float x, float y, float z) : pos(x,y,z), tex(0.0f, 0.0f) {}
	VertexPosTex(const D3DXVECTOR3& v, const D3DXVECTOR2& t):pos(v), tex(t) {}

	D3DXVECTOR3		pos;
	D3DXVECTOR2		tex;

	static IDirect3DVertexDeclaration9* Decl;
};

//===============================================================
struct VertexPosQuadTex
{
	VertexPosQuadTex() : pos(0.0f, 0.0f, 0.0f), quad(0.0f, 0.0f, 0.0f), tex(0.0f, 0.0f) {}
	VertexPosQuadTex(float x, float y, float z) : pos(x,y,z), quad(0.0f,0.0f,0.0f), tex(0.0f, 0.0f) {}
	VertexPosQuadTex(const D3DXVECTOR3& v, const D3DXVECTOR3& q, const D3DXVECTOR2& t):pos(v), quad(q), tex(t) {}

	D3DXVECTOR3		pos;
	D3DXVECTOR3		quad;
	D3DXVECTOR2		tex;

	static IDirect3DVertexDeclaration9* Decl;
};

#endif // VERTEX_H