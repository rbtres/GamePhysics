//============================================================================================
//Create by Robert Bethune
//Planet Manager
//Owns a vector of force Registries Also created in this file
//Creation Date 1/31/2015
//============================================================================================
#pragma once
#include "GravityGenerator.h"
#include "PhysicsObject.h"
#include <vector>
//============================================================================================
struct ForceRegistration
{
	PhysicsObject* Planet;
	GravityGenerator* Generator;
	ForceRegistration(){ Planet = new PhysicsObject(); Generator = new GravityGenerator(); }
	~ForceRegistration() { CleanUp(); }
	void CleanUp()
	{
		delete Generator;
		Generator = NULL;
		delete Planet;
		Planet = NULL;
	}
	void UpdateForces(PhysicsObject* planet)
	{
		Generator->UpdateForce(Planet, planet);
	}
	void UpdatePlanet(int msTime)
	{
		Planet->Update(msTime);
	}
};
//============================================================================================
typedef std::vector<ForceRegistration*> Registry;
//============================================================================================
class PlanetManager
{
public:
//--------------------------------------------------------------------------------------------
	PlanetManager();
	~PlanetManager();

	void AddForceReg(PhysicsObject* planet, GravityGenerator* generator);
	void AddForceReg(ForceRegistration* reg);
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
	void Update(int msTime);
	void Init();
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
	void CleanUp(){
		for (auto i : m_SolarSystemRegistry){ i->CleanUp(); delete i; i = NULL; } m_SolarSystemRegistry.clear();
	}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
	inline void Reset(){ for (auto i : m_SolarSystemRegistry) { i->Planet->Reset(); } };
	inline void Draw(){ for (auto i : m_SolarSystemRegistry){ i->Planet->Draw(); } }
	inline ForceRegistration GetForceReg(int index){ return *m_SolarSystemRegistry[index]; }
	static int DaysPerSecond;
	std::vector<PhysicsObject*> gp_Planets;
//--------------------------------------------------------------------------------------------
//============================================================================================
private:
	Registry m_SolarSystemRegistry;
};
//============================================================================================


