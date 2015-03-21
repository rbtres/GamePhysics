#pragma once
#include "GravityGenerator.h"
#include "PhysicsObject.h"
#include <vector>

struct ForceRegistration
{
	PhysicsObject* object;
	//Once I get forward write base Generator
	//this way I can have a registration that does more than 1 thing
	GravityGenerator* Generator;
	ForceRegistration(){Generator = new GravityGenerator(); }
	void CleanUp()
	{
		delete Generator;
		Generator = NULL;
		delete object;
		object = NULL;
	}
	void UpdateForces()
	{
		Generator->UpdateForce(object);
	}
};

typedef std::vector<ForceRegistration*> Registry;

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

	void AddPhysicsObject(PhysicsObject* object);
	void RemovePhysicsObject(PhysicsObject* object);
	//Just Updates registrys
	void Update(float msTime);
private:
	void AddRegistry(PhysicsObject* object);
	void RemoveRegistry(PhysicsObject* object);

	Registry PhysicsRegistry;
	std::vector<PhysicsObject*> mp_physicsObjects;
};

