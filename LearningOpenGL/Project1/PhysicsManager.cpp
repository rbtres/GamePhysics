#include "PhysicsManager.h"


PhysicsManager::PhysicsManager()
{
}


PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::AddRegistry(PhysicsObject* object)
{
	ForceRegistration* r = new ForceRegistration();
	r->object = object;
	PhysicsRegistry.push_back(r);
}

void PhysicsManager::RemoveRegistry(PhysicsObject* object)
{
	//Should remove stuff later
}

void PhysicsManager::AddPhysicsObject(PhysicsObject* object)
{
	mp_physicsObjects.push_back(object);
	AddRegistry(object);
}

void PhysicsManager::RemovePhysicsObject(PhysicsObject* object)
{
	//Should Remove stuff and call remove registry
}

void PhysicsManager::Update(float msTime)
{
	for (auto i : PhysicsRegistry)
	{
		i->UpdateForces();
	}
	for (auto i : mp_physicsObjects)
	{
		i->Update(msTime);
	}
}

