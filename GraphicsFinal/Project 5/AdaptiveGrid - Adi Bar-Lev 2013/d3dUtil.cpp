//=============================================================================
// d3dUtil.cpp by Frank Luna (C) 2005 All Rights Reserved.
//=============================================================================

#include "d3dUtil.h"

//------------------------------------------------------------------------------
// 'cellsPerSide' must comply: cellsPerSide % 4 = 0 -> this leaves the strip for the skirt.
// Currently the result contains the last strip reserved for the skirt.
//------------------------------------------------------------------------------
void CreateLPatchWithSkirt( int cellsPerSide, float cellSize,
				std::vector<VertexPosTex>& Vtx,
				std::vector<WORD>& Idx, int& vtxNum, int& triNum )
{
	int		startVtxPos = cellsPerSide >> 1;
	int		halfLineOffset = startVtxPos;
	int		halfCellsPerSide = cellsPerSide >> 1;
	int		vtxPerSide = cellsPerSide;	// since there is a skirt, ommiting border vertices
	int		vtxPerPatch = vtxPerSide * vtxPerSide - startVtxPos * startVtxPos;
	int		vtxPerSkirt = cellsPerSide + 1;
	int		triPerPatch = 2 * ((cellsPerSide - 1) * (cellsPerSide - 1) - startVtxPos * startVtxPos);
	int		triPerSkirt = 3 * (cellsPerSide - 2) + 4;	// -4 since I do not generate the corner yet
	float	size = (float) cellsPerSide * cellSize;

	vtxNum = vtxPerPatch + vtxPerSkirt;
	triNum = triPerPatch + triPerSkirt;

	//===========================================
	// Creating the vertices - notice that the last row and column do not exist.
	Vtx.resize( vtxNum );
	std::vector<WORD>		borderIdx;
	borderIdx.resize( 2 * vtxPerSide - 1 );

	// Creating the L-patch vertices
	int		k = 0, border = 0;
	for( int i=0 ; i<vtxPerSide ; ++i )
	{
		for( int j=0 ; j<vtxPerSide ; ++j )
		{
			if ((i < startVtxPos) && (j < startVtxPos))
				continue;

			Vtx[k].pos.x = j * cellSize;
			Vtx[k].pos.z = i * cellSize;
			Vtx[k].pos.y =  0.0f;

			Vtx[k].tex.x = (float) i / (float) cellsPerSide;
			Vtx[k].tex.y = (float) j / (float) cellsPerSide;

			if ((i == vtxPerSide-1) || (j == vtxPerSide-1))
				borderIdx[border++] = k;

			k++;
		}
	}

	// Creating the skirt outer vertices
	for( int i=0 ; i<vtxPerSide>>1 ; ++i )
	{
		Vtx[k].pos.x = size;
		Vtx[k].pos.z = i * 2 * cellSize;
		Vtx[k].pos.y = 0.0f;

		Vtx[k].tex.x = (float) i / (float) cellsPerSide;
		Vtx[k].tex.y = 1.0f;
		k++;
	}

	for( int i=0 ; i<(vtxPerSide>>1)+1 ; ++i )
	{
		Vtx[k].pos.x = i * 2 * cellSize;
		Vtx[k].pos.z = size;
		Vtx[k].pos.y = 0.0f;

		Vtx[k].tex.x = 1.0f;
		Vtx[k].tex.y = (float) i / (float) cellsPerSide;
		k++;
	}



	//===========================================
	// Creating the triangles' indices.
	Idx.resize(triNum * 3);
	 
	// Generate indices for each quad - last strip is NOT generated (skirt)
	k = 0;
	for( WORD i=0, offset=0 ; i<cellsPerSide-1 ; offset+= (i < startVtxPos) ? halfLineOffset : vtxPerSide, i++ )
	{
		int		addedOffset = (i < startVtxPos - 1) ? halfLineOffset : vtxPerSide;
		for( WORD j = 0; j<cellsPerSide-1 ; ++j )
		{
			if ((i < startVtxPos) && (j < startVtxPos))
				continue;

			int		indJ = (i < startVtxPos) ? j - startVtxPos : j;
			Idx[k]     = offset + indJ + 1;
			Idx[k + 1] = offset + indJ;
			Idx[k + 2] = addedOffset + offset + indJ;
					
			Idx[k + 3] = offset + indJ + 1;
			Idx[k + 4] = addedOffset + offset + indJ;
			Idx[k + 5] = addedOffset + offset + indJ + 1;

			// next quad
			k += 6;
		}
	}

	// Generate indices for the skirt - the corner is missing
	for ( WORD side=0, border=0, inner=0 ; side<2 ; ++side, ++border, ++inner )
		for( WORD i=0 ; i<halfCellsPerSide-1 ; ++i, ++border, inner+=2 )
		{
			Idx[k]     = side ? borderIdx[inner] : vtxPerPatch + border;
			Idx[k + 1] = side ? vtxPerPatch + border : borderIdx[inner];
			Idx[k + 2] = borderIdx[inner+1];
					
			Idx[k + 3] = side ? borderIdx[inner+1] : vtxPerPatch + border;
			Idx[k + 4] = side ? vtxPerPatch + border : borderIdx[inner+1];
			Idx[k + 5] = vtxPerPatch + border + 1;

			Idx[k + 6] = side ? borderIdx[inner+2] : borderIdx[inner+1];
			Idx[k + 7] = side ? borderIdx[inner+1] : borderIdx[inner+2];
			Idx[k + 8] = vtxPerPatch + border + 1;

			// next quad
			k += 9;
		}

	WORD	lastInnerIdx = 2 * vtxPerSide - 2;
	WORD	indices[6] = {	vtxPerPatch + halfCellsPerSide - 1, borderIdx[vtxPerSide-2], borderIdx[lastInnerIdx],
							borderIdx[lastInnerIdx-1], vtxNum -1 , vtxNum - 2  };
							
	WORD	cornerIdx[12] = { 0,1,2,	0,2,4,	2,4,5,	2,3,5 };
	for ( WORD idx=0 ; idx<12 ; idx++, k++ )
		Idx[k]  = indices[ cornerIdx[idx] ];

}

//------------------------------------------------------------------------------
// 'cellsPerSide' must comply: cellsPerSide % 4 = 0 -> this leaves the strip for the skirt.
// Currently the result contains the last strip reserved for the skirt.
//------------------------------------------------------------------------------
void CreateLPatch( int cellsPerSide, float cellSize,
				std::vector<VertexPosTex>& Vtx,
				std::vector<WORD>& Idx, int& vtxNum, int& triNum )
{
	int		startVtxPos = cellsPerSide >> 1;
	int		halfLineOffset = startVtxPos + 1;
	int		vtxPerSide = cellsPerSide + 1;
	float	size = (float) cellsPerSide * cellSize;

	vtxNum = vtxPerSide * vtxPerSide - startVtxPos * startVtxPos;
	triNum = 2 * (cellsPerSide * cellsPerSide - startVtxPos * startVtxPos);

	//===========================================
	// Build vertices.

	Vtx.resize( vtxNum );

	int		k = 0;
	for( int i=0 ; i<vtxPerSide ; ++i )
	{
		for( int j=0 ; j<vtxPerSide ; ++j )
		{
			if ((i < startVtxPos) && (j < startVtxPos))
				continue;

			Vtx[k].pos.x = j * cellSize;
			Vtx[k].pos.z = i * cellSize;
			Vtx[k].pos.y =  0.0f;

			Vtx[k].tex.x = (float) i / (float) cellsPerSide;
			Vtx[k].tex.y = (float) j / (float) cellsPerSide;
			k++;
		}
	}


	//===========================================
	// Build indices.
	Idx.resize(triNum * 3);
	 
	// Generate indices for each quad.
	k = 0;
	for( WORD i=0, offset=0 ; i<cellsPerSide ; offset+= (i < startVtxPos) ? halfLineOffset : vtxPerSide, i++ )
	{
		int		addedOffset = (i < startVtxPos - 1) ? halfLineOffset : vtxPerSide;
		for( WORD j = 0; j<cellsPerSide ; ++j )
		{
			if ((i < startVtxPos) && (j < startVtxPos))
				continue;

			int		indJ = (i < startVtxPos) ? j - startVtxPos : j;
			Idx[k]     = offset + indJ + 1;
			Idx[k + 1] = offset + indJ;
			Idx[k + 2] = addedOffset + offset + indJ;
					
			Idx[k + 3] = offset + indJ + 1;
			Idx[k + 4] = addedOffset + offset + indJ;
			Idx[k + 5] = addedOffset + offset + indJ + 1;

			// next quad
			k += 6;
		}
	}
}

//------------------------------------------------------------------------------
void CreateGrid( int vtxPerSide, float cellSize,
				std::vector<VertexPosTex>& Vtx,
				std::vector<WORD>& Idx )
{
	int		vtxNum = vtxPerSide * vtxPerSide;
	int		numCellPerSide = vtxPerSide-1;
	int		triNum = 2 * (numCellPerSide * numCellPerSide);
	float	size = (float) (vtxPerSide - 1) * cellSize;

	//===========================================
	// Build vertices.

	Vtx.resize( vtxNum );

	// Offsets to translate grid from quadrant 4 to center of 
	// coordinate system.
	float	xOffset = -size * 0.5f; 
	float	zOffset = -size * 0.5f;
	int		k = 0;

	for( int i=0 ; i<vtxPerSide ; ++i )
	{
		for( int j=0 ; j<vtxPerSide ; ++j, ++k )
		{
			// Negate the depth coordinate to put in quadrant four.  
			// Then offset to center about coordinate system.
			Vtx[k].pos.x = j * cellSize + xOffset;
			Vtx[k].pos.z = i * cellSize + zOffset;
			Vtx[k].pos.y =  0.0f;

			Vtx[k].tex.x = (float) i / (float) (vtxPerSide - 1);
			Vtx[k].tex.y = (float) j / (float) (vtxPerSide - 1);
		}
	}


	//===========================================
	// Build indices.
	Idx.resize(triNum * 3);
	/*
	std::vector<D3DXVECTOR3>* normals = new std::vector<D3DXVECTOR3>[vtxNum];
	 */
	// Generate indices for each quad.
	k = 0;
	for( WORD i = 0; i < (DWORD)numCellPerSide; ++i)
	{
		for( WORD j = 0; j < (DWORD)numCellPerSide; ++j)
		{
			Idx[k]     =   i   * vtxPerSide + j + 1; 
			Idx[k + 1] =   i   * vtxPerSide + j; 
			Idx[k + 2] = (i+1) * vtxPerSide + j; 

			Idx[k + 3] =  i   * vtxPerSide + j + 1;
			Idx[k + 4] =  (i+1) * vtxPerSide + j;
			Idx[k + 5] = (i+1) * vtxPerSide + j + 1;
			/*
			D3DXVECTOR3 BA = Vtx[Idx[k+1]].pos - Vtx[Idx[k]].pos;
			D3DXVECTOR3 CA = Vtx[Idx[k+2]].pos - Vtx[Idx[k]].pos;
			D3DXVECTOR3 normal;
			D3DXVec3Cross(&normal, &BA, &CA);
			normals[Idx[k]].push_back(normal);
			normals[Idx[k + 1]].push_back(normal);
			normals[Idx[k + 2]].push_back(normal);

					
			Idx[k + 3] =  i   * vtxPerSide + j + 1;
			Idx[k + 4] =  (i+1) * vtxPerSide + j;
			Idx[k + 5] = (i+1) * vtxPerSide + j + 1;

			BA = Vtx[Idx[k+4]].pos - Vtx[Idx[k+3]].pos;
			CA = Vtx[Idx[k+5]].pos - Vtx[Idx[k+3]].pos;
			D3DXVec3Cross(&normal, &BA, &CA);
			normals[Idx[k + 3]].push_back(normal);
			normals[Idx[k + 4]].push_back(normal);
			normals[Idx[k + 5]].push_back(normal);
			*/
			// next quad
			k += 6;
		}
	}
	/*
	for(int i = 0; i < vtxNum; i++)
	{
		D3DXVECTOR3 averageNormal = D3DXVECTOR3(0,0,0);
		
		for(int j = 0; j < normals[i].size(); ++j)
		{
			averageNormal += normals[i].at(j);
		}

		averageNormal = averageNormal / normals[i].size();
		D3DXVec3Normalize(&averageNormal,&averageNormal);
		int x = 5;

	}
	*/
}
/*
//------------------------------------------------------------------------------
void CreateGrid( int vtxPerSide, float cellSize,
				std::vector<VertexPosTex>& Vtx,
				std::vector<WORD>& Idx )
{
	int		vtxNum = vtxPerSide * vtxPerSide;
	int		numCellPerSide = vtxPerSide-1;
	int		triNum = 2 * (numCellPerSide * numCellPerSide);
	float	size = (float) (vtxPerSide - 1) * cellSize;

	//===========================================
	// Build vertices.

	Vtx.resize( vtxNum );

	// Offsets to translate grid from quadrant 4 to center of 
	// coordinate system.
	float	xOffset = -size * 0.5f; 
	float	zOffset =  size * 0.5f;
	int		k = 0;

	for( int i=0 ; i<vtxPerSide ; ++i )
	{
		for( int j=0 ; j<vtxPerSide ; ++j, ++k )
		{
			// Negate the depth coordinate to put in quadrant four.  
			// Then offset to center about coordinate system.
			Vtx[k].pos.x =  j * cellSize + xOffset;
			Vtx[k].pos.z = -i * cellSize + zOffset;
			Vtx[k].pos.y =  0.0f;

			Vtx[k].tex.x = (float) i / (float) (vtxPerSide - 1);
			Vtx[k].tex.y = (float) j / (float) (vtxPerSide - 1);
		}
	}


	//===========================================
	// Build indices.
	Idx.resize(triNum * 3);
	 
	// Generate indices for each quad.
	k = 0;
	for( WORD i = 0; i < (DWORD)numCellPerSide; ++i)
	{
		for( WORD j = 0; j < (DWORD)numCellPerSide; ++j)
		{
			Idx[k]     =   i   * vtxPerSide + j;
			Idx[k + 1] =   i   * vtxPerSide + j + 1;
			Idx[k + 2] = (i+1) * vtxPerSide + j;
					
			Idx[k + 3] = (i+1) * vtxPerSide + j;
			Idx[k + 4] =   i   * vtxPerSide + j + 1;
			Idx[k + 5] = (i+1) * vtxPerSide + j + 1;

			// next quad
			k += 6;
		}
	}
}
*/

//------------------------------------------------------------------------------
void GenTriGrid(int numVertRows, int numVertCols,
				float dx, float dz, 
				const D3DXVECTOR3& center, 
				std::vector<D3DXVECTOR3>& verts,
				std::vector<DWORD>& indices)
{
	int vtxNum = numVertRows*numVertCols;
	int numCellRows = numVertRows-1;
	int numCellCols = numVertCols-1;

	int triNum = numCellRows*numCellCols*2;

	float width = (float)numCellCols * dx;
	float depth = (float)numCellRows * dz;

	//===========================================
	// Build vertices.

	// We first build the grid geometry centered about the origin and on
	// the xz-plane, row-by-row and in a top-down fashion.  We then translate
	// the grid vertices so that they are centered about the specified 
	// parameter 'center'.

	verts.resize( vtxNum );

	// Offsets to translate grid from quadrant 4 to center of 
	// coordinate system.
	float xOffset = -width * 0.5f; 
	float zOffset =  depth * 0.5f;

	int k = 0;
	for(float i = 0; i < numVertRows; ++i)
	{
		for(float j = 0; j < numVertCols; ++j)
		{
			// Negate the depth coordinate to put in quadrant four.  
			// Then offset to center about coordinate system.
			verts[k].x =  j * dx + xOffset;
			verts[k].z = -i * dz + zOffset;
			verts[k].y =  0.0f;

			// Translate so that the center of the grid is at the
			// specified 'center' parameter.
			D3DXMATRIX T;
			D3DXMatrixTranslation(&T, center.x, center.y, center.z);
			D3DXVec3TransformCoord(&verts[k], &verts[k], &T);
			
			++k; // Next vertex
		}
	}

	//===========================================
	// Build indices.

	indices.resize(triNum * 3);
	 
	// Generate indices for each quad.
	k = 0;
	for(DWORD i = 0; i < (DWORD)numCellRows; ++i)
	{
		for(DWORD j = 0; j < (DWORD)numCellCols; ++j)
		{
			indices[k]     =   i   * numVertCols + j;
			indices[k + 1] =   i   * numVertCols + j + 1;
			indices[k + 2] = (i+1) * numVertCols + j;
					
			indices[k + 3] = (i+1) * numVertCols + j;
			indices[k + 4] =   i   * numVertCols + j + 1;
			indices[k + 5] = (i+1) * numVertCols + j + 1;

			// next quad
			k += 6;
		}
	}
}
//------------------------------------------------------------------------------
//Used Frank Lunas grass example as a reference for this function
void CreateBillBoard(VertexPosQuadTex* v, WORD* k, int& indexOffset, D3DXVECTOR3& worldPos, D3DXVECTOR3& scale)
{
	v[0] = VertexPosQuadTex(D3DXVECTOR3(-1.0f,-0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),  D3DXVECTOR2(0.0f, 1.0f));
	v[1] = VertexPosQuadTex(D3DXVECTOR3(-1.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),  D3DXVECTOR2(0.0f, 0.0f));
	v[2] = VertexPosQuadTex(D3DXVECTOR3( 1.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),  D3DXVECTOR2(1.0f, 0.0f));
	v[3] = VertexPosQuadTex(D3DXVECTOR3( 1.0f,-0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),  D3DXVECTOR2(1.0f, 1.0f));

	// Set indices.
	k[0] = 0 + indexOffset;
	k[1] = 1 + indexOffset;
	k[2] = 2 + indexOffset;
	k[3] = 0 + indexOffset;
	k[4] = 2 + indexOffset;
	k[5] = 3 + indexOffset;

	// Offset the indices by four to have the indices index into
	// the next four elements of the vertex buffer for the next cloud.
	indexOffset += 4;

	// Scale the clouds.
	for(int i = 0; i < 4; ++i)
	{
		v[i].pos.x *= scale.x;
		v[i].pos.y *= scale.y;
		v[i].pos.z *= scale.z;
	}

	// Set world center position for the quad.
	v[0].quad = worldPos;
	v[1].quad = worldPos;
	v[2].quad = worldPos;
	v[3].quad = worldPos;
}

//From Frank Lunas d3dUtil
float GetRandomFloat(float a, float b)
{
	if( a >= b ) // bad input
		return a;

	// Get random float in [0, 1] interval.
	float f = (rand()%10001) * 0.0001f;

	return (f*(b-a))+a;
}

float getDistance(D3DXVECTOR3 a, D3DXVECTOR3 b)
{
	return sqrt( pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}