#pragma once
#include "RigidRender.h"

class BoxRender:public RigidRender
{
public:
	BoxRender();
	~BoxRender();

	inline void SetWH(Vector2D widthHeight){ m_sizeWH = widthHeight; }
	inline Vector2D GetWH(){ return m_sizeWH; }
protected:
	virtual void renderObject();
	Vector2D m_sizeWH;
};

