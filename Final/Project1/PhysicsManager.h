#pragma once
#include "GravityGenerator.h"
#include "PhysicsObject.h"
#include <vector>
#include "ParticleContactResolver.h"
#include "ParticleContact.h"
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

struct ForceRegistrationRigid
{
	RigidBody* object;
	GravityGenerator* Generator;
	ForceRegistrationRigid(){ Generator = new GravityGenerator(); }
	
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
typedef std::vector<ForceRegistrationRigid*> RigidRegistry;


class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

	void AddPhysicsObject(PhysicsObject* object);
	void RemovePhysicsObject(PhysicsObject* object);
	void AddRigidBody(RigidBody* object);
	void RemoveRigidBody(RigidBody* object);
	
	inline std::vector<PhysicsObject*> GetPhysicsVector(){ return mp_physicsObjects; }
	inline void AddContact(ParticleContact contact){ m_ContactVector.push_back(contact); }
	//Just Updates registrys
	void Update(float msTime);


private:
	void AddRegistry(PhysicsObject* object);
	void RemoveRegistry(PhysicsObject* object);
	void updateComponents(float msTime);

	Registry PhysicsRegistry;
	RigidRegistry RigidBodyRegistry;
	std::vector<PhysicsObject*> mp_physicsObjects;
	std::vector<ParticleContact> m_ContactVector;
	std::vector<RigidBody*> mp_rigidBodies;

	ParticleContactResolver m_Resolver;
};

