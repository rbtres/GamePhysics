#include "PlanetManager.h"
#include "Planet.h"
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
	Planet* mercury = new Planet("mercury");
	mercury->Init(.05f, Vector3D(.31f, 0, 0), Vector3D(0,0, .0000003925392803303289f));
	mercury->setDamping((float).99999999999999999);
	mercury->setMass((float).0000001666);
	mercury->SetImgLoc("Planet/merurymap.jpg");
	mercury->LoadImg();
	GravityGenerator* mercuryGen = new GravityGenerator();
	AddForceReg(mercury, mercuryGen);
	gp_Planets.push_back(mercury);

	Planet* venus = new Planet("venus");
	venus->Init(.1, Vector3D(.718f, 0, 0), Vector3D(0,0, .0000002377854700252f));
	venus->setDamping((float).99999999999999999);
	venus->setMass((float).000002447);
	venus->SetImgLoc("Planet/venusmap.jpg");
	venus->LoadImg();
	GravityGenerator* venusGen = new GravityGenerator();
	AddForceReg(venus, venusGen);
	gp_Planets.push_back(venus);

	Planet* earth = new Planet("earth");
	earth->Init(.03,Vector3D(.98f, 0, 0), Vector3D(0,0, .000000202542998f));
	earth->setMass((float).000003003);
	earth->setDamping((float).99999999999999999);
	earth->SetImgLoc("Planet/earthmap.jpg");
	earth->LoadImg();
	GravityGenerator* earthsGenerator = new GravityGenerator();
	AddForceReg(earth, earthsGenerator);
	gp_Planets.push_back(earth);

	Planet* moon = new Planet("moon");
	moon->Init(.01, Vector3D(.95f, 0, 0), Vector3D(0, 0, (float)(.000000202542998 + .00000000683833262649141)));
	moon->setMass((float).000000123);
	moon->setDamping((float).99999999999999999);
	moon->SetImgLoc("Planet/moonmap.jpg");
	moon->LoadImg();
	GravityGenerator* moonGenerator = new GravityGenerator();
	AddForceReg(moon, moonGenerator);

	Planet* mars = new Planet("mars");
	mars->Init(.08f, Vector3D(1.38f, 0, 0), Vector3D(0,0, .0000001624394778196f));
	mars->setDamping((float).99999999999999999);
	mars->setMass((float).0000003232);
	mars->SetImgLoc("Planet/marsmap.jpg");
	mars->LoadImg();
	GravityGenerator* marsGen = new GravityGenerator();
	AddForceReg(mars, marsGen);
	gp_Planets.push_back(mars);

	Planet* jupiter = new Planet("jupiter");
	jupiter->Init(1.1f, Vector3D(4.95f, 0, 0), Vector3D(0, 0,.0000000879036575732f));
	jupiter->setDamping((float).99999999999999999);
	jupiter->setMass((float).0009547919);
	jupiter->SetImgLoc("Planet/jupitermap.jpg");
	jupiter->LoadImg();
	GravityGenerator* jupiterGen = new GravityGenerator();
	AddForceReg(jupiter, jupiterGen);
	gp_Planets.push_back(jupiter);

	Planet* saturn = new Planet("saturn");
	saturn->Init(.941f, Vector3D(9.02f, 0, 0), Vector3D(0,0, .0000000654213857054f));
	saturn->setDamping((float).99999999999999999);
	saturn->setMass((float).000285885);
	saturn->SetImgLoc("Planet/saturnmap.jpg");
	saturn->LoadImg();
	GravityGenerator* saturnGen = new GravityGenerator();
	AddForceReg(saturn, saturnGen);
	gp_Planets.push_back(saturn);

	Planet* uranus = new Planet("uranus");
	uranus->Init(.4f, Vector3D(18.3f, 0, 0), Vector3D(0, 0,.0000000461798016744f));
	uranus->setDamping((float).99999999999999999);
	uranus->setMass((float).000043662);
	uranus->SetImgLoc("Planet/uranusmap.jpg");
	uranus->LoadImg();
	GravityGenerator* uranusGen = new GravityGenerator();
	AddForceReg(uranus, uranusGen);
	gp_Planets.push_back(uranus);

	Planet* neptune = new Planet("neptune");
	neptune->Init(.388f, Vector3D(30.0f, 0, 0), Vector3D(0,0, .0000000368628241436f));
	neptune->setDamping((float).99999999999999999);
	neptune->setMass((float).000051513);
	neptune->SetImgLoc("Planet/neptunemap.jpg");
	neptune->LoadImg();
	GravityGenerator* neptuneGen = new GravityGenerator();
	AddForceReg(neptune, neptuneGen);
	gp_Planets.push_back(neptune);

	Planet* sun = new Planet("sun");
	sun->Init(.2f,Vector3D(0, 0, 0));
	sun->setMass(1);
	sun->setDamping(0);
	sun->SetImgLoc("Planet/sunmap.jpg");
	sun->LoadImg();
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