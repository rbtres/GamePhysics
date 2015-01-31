#include "PlanetManager.h"

//--------------------------------------------------------------------------------------------
PlanetManager::PlanetManager()
{

}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
PlanetManager::~PlanetManager()
{
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void PlanetManager::Init()
{
	PhysicsObject* earth = new PhysicsObject();
	earth->Init(Vector3D(1.5, 0, 0));
	earth->setMass(5.9726  );
	earth->setVel(Vector3D(0, 0, 1));
	GravityGenerator* earthsGenerator = new GravityGenerator();
	AddForceReg(earth, earthsGenerator);

	PhysicsObject* sun = new PhysicsObject();
	sun->Init(Vector3D(0, 0, 0));
	sun->setMass(1988500 );
	GravityGenerator* sunsGenerator = new GravityGenerator();
	AddForceReg(sun, sunsGenerator);

}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void PlanetManager::Update(int msTime)
{
	for (int i = 0; i < m_SolarSystemRegistry.size(); i++)
	{
		for (int j = 0; j < m_SolarSystemRegistry.size(); j++)
		{
			if (i != j)
			{
				m_SolarSystemRegistry[i]->UpdateForces( m_SolarSystemRegistry[j]->Planet);
			}
		}
	}
	for (auto i : m_SolarSystemRegistry)
	{
		i->UpdatePlanet(msTime);
	}
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void PlanetManager::AddForceReg(PhysicsObject* planet, GravityGenerator* generator)
{
	ForceRegistration* newReg = new ForceRegistration();
	newReg->Planet = planet;
	newReg->Generator = generator;
	m_SolarSystemRegistry.push_back(newReg);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void PlanetManager::AddForceReg(ForceRegistration* reg)
{
	m_SolarSystemRegistry.push_back(reg);
}
//--------------------------------------------------------------------------------------------