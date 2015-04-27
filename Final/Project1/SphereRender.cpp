#include "SphereRender.h"


SphereRender::SphereRender()
{
	m_radius = 5;
}


SphereRender::~SphereRender()
{
}

void SphereRender::renderObject()
{
	gluSphere(m_Sphere, m_radius, 25, 25);
}
