#pragma once
#include "GameObject.h"
class CubeGround :
	public GameObject
{
public:
	CubeGround();
	~CubeGround();
	virtual void Draw();

	Vector3D Scale;
};

