#include "Particle.h"

//--------------------------------------------------------------------------------------------
Particle::Particle()
:PhysicsObject()
{
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Particle::~Particle()
{
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void Particle::UpdateLife(float msTime)
{
	m_Life -= msTime;
	Update(msTime);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
bool Particle::Alive()
{
	if (m_Life > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------------------------------


