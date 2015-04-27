#pragma once
#include "RigidRender.h"
class SphereRender :
	public RigidRender
{
public:
	SphereRender();
	~SphereRender();
	inline void SetRadius(float rad){ m_radius = rad; }
	inline float GetRadius(){ return m_radius; }
protected:
	virtual void renderObject();
	float m_radius;
};

