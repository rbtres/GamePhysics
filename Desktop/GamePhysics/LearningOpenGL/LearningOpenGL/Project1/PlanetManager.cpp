#include "PlanetManager.h"

int PlanetManager::DaysPerSecond = 50;
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
//https://solarsystem.nasa.gov/scitech/display.cfm?ST_ID=2517 for distance
//http://en.wikipedia.org/wiki/Planetary_mass for mass
//Velocity caculations from jake & Evan trade off for mass and distance caculated
void PlanetManager::Init()
{
	PhysicsObject* mercury = new PhysicsObject();
	mercury->Init(.05f, Vector3D(.31f, 0, 0), Vector3D(0,0, .0000003925392803303289f));
	mercury->setDamping((float).99999999999999999);
	mercury->setMass((float).0000001666);
	GravityGenerator* mercuryGen = new GravityGenerator();
	AddForceReg(mercury, mercuryGen);
	gp_Planets.push_back(mercury);

	PhysicsObject* venus = new PhysicsObject();
	venus->Init(.1, Vector3D(.718f, 0, 0), Vector3D(0,0, .0000002377854700252f));
	venus->setDamping((float).99999999999999999);
	venus->setMass((float).000002447);
	GravityGenerator* venusGen = new GravityGenerator();
	AddForceReg(venus, venusGen);
	gp_Planets.push_back(venus);

	PhysicsObject* earth = new PhysicsObject();
	earth->Init(.03,Vector3D(.98f, 0, 0), Vector3D(0,0, .000000202542998f));
	earth->setMass((float).000003003);
	earth->setDamping((float).99999999999999999);
	GravityGenerator* earthsGenerator = new GravityGenerator();
	AddForceReg(earth, earthsGenerator);
	gp_Planets.push_back(earth);

	PhysicsObject* moon = new PhysicsObject();
	moon->Init(.01, Vector3D(1.02f, 0, 0), Vector3D(0, 0, .000000007197722768554639f));
	moon->setMass((float).0000000123);
	moon->setDamping((float).99999999999999999);
	GravityGenerator* moonGenerator = new GravityGenerator();
	//AddForceReg(moon, moonGenerator);

	PhysicsObject* mars = new PhysicsObject();
	mars->Init(.08f, Vector3D(1.38f, 0, 0), Vector3D(0,0, .0000001624394778196f));
	mars->setDamping((float).99999999999999999);
	mars->setMass((float).0000003232);
	GravityGenerator* marsGen = new GravityGenerator();
	AddForceReg(mars, marsGen);
	gp_Planets.push_back(mars);

	PhysicsObject* jupiter = new PhysicsObject();
	jupiter->Init(1.1f, Vector3D(4.95f, 0, 0), Vector3D(0, 0,.0000000879036575732f));
	jupiter->setDamping((float).99999999999999999);
	jupiter->setMass((float).0009547919);
	GravityGenerator* jupiterGen = new GravityGenerator();
	AddForceReg(jupiter, jupiterGen);
	gp_Planets.push_back(jupiter);

	PhysicsObject* saturn = new PhysicsObject();
	saturn->Init(.941f, Vector3D(9.02f, 0, 0), Vector3D(0,0, .0000000654213857054f));
	saturn->setDamping((float).99999999999999999);
	saturn->setMass((float).000285885);
	GravityGenerator* saturnGen = new GravityGenerator();
	AddForceReg(saturn, saturnGen);
	gp_Planets.push_back(saturn);

	PhysicsObject* uranus = new PhysicsObject();
	uranus->Init(.4f, Vector3D(18.3f, 0, 0), Vector3D(0, 0,.0000000461798016744f));
	uranus->setDamping((float).99999999999999999);
	uranus->setMass((float).000043662);
	GravityGenerator* uranusGen = new GravityGenerator();
	AddForceReg(uranus, uranusGen);
	gp_Planets.push_back(uranus);

	PhysicsObject* neptune = new PhysicsObject();
	neptune->Init(.388f, Vector3D(30.0f, 0, 0), Vector3D(0,0, .0000000368628241436f));
	neptune->setDamping((float).99999999999999999);
	neptune->setMass((float).000051513);
	GravityGenerator* neptuneGen = new GravityGenerator();
	AddForceReg(neptune, neptuneGen);
	gp_Planets.push_back(neptune);

	PhysicsObject* sun = new PhysicsObject();
	sun->Init(.2f,Vector3D(0, 0, 0));
	sun->setMass(1);
	sun->setDamping(0);
	GravityGenerator* sunsGenerator = new GravityGenerator();
	AddForceReg(sun, sunsGenerator);

}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void PlanetManager::Update(int msTime)
{
	for (int k = 0; k < DaysPerSecond; k++)
	{
		for (unsigned int i = 0; i < m_SolarSystemRegistry.size(); i++)
		{
			for (unsigned int j = 0; j < m_SolarSystemRegistry.size(); j++)
			{
				if (i != j)
				{
					m_SolarSystemRegistry[i]->UpdateForces(m_SolarSystemRegistry[j]->Planet);
				}
			}
		}
		for (auto i : m_SolarSystemRegistry)
		{
			i->UpdatePlanet(msTime);
		}
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