#pragma once
#include "GameObject.h"
class Ground :
	public GameObject
{
public:
	Ground();
	~Ground();
	virtual void Draw();
	void SetDim(Vector3D dim);
protected:
	Vector3D m_Dim;
};

