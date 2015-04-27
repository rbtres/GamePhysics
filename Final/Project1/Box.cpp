#include "Box.h"


CollisionBox::CollisionBox()
{

}


CollisionBox::~CollisionBox()
{

}

void CollisionBox::Init(Vector3D halfsize)
{
	HalfSize = halfsize;
	Vertices[0] = Vector3D(-HalfSize.X, -HalfSize.Y, -HalfSize.Z);
	Vertices[1] = Vector3D(-HalfSize.X, -HalfSize.Y, HalfSize.Z);
	Vertices[2] = Vector3D(-HalfSize.X, HalfSize.Y, -HalfSize.Z);
	Vertices[3] = Vector3D(-HalfSize.X, HalfSize.Y, HalfSize.Z);
	Vertices[4] = Vector3D(HalfSize.X, -HalfSize.Y, -HalfSize.Z);
	Vertices[5] = Vector3D(HalfSize.X, -HalfSize.Y, HalfSize.Z);
	Vertices[6] = Vector3D(HalfSize.X, HalfSize.Y, -HalfSize.Z);
	Vertices[7] = Vector3D(HalfSize.X, HalfSize.Y, HalfSize.Z);

	for (unsigned int i = 0; i < 8; i++)
	{
		Vertices[i] = Offset.Transform(Vertices[i]);
	}

}
