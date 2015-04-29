#include "PhysicsManager.h"


PhysicsManager::PhysicsManager()
{ 
	m_Resolver.SetIterations(50);
	m_Detector = ParticleColDetector();
	m_Data = new CollisionDataParticle();
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
	for (unsigned int i = 0; i < mp_physicsObjects.size(); i++)
	{
		for (unsigned int j = i + 1; j < mp_physicsObjects.size(); j++)
		{
			m_Detector.SphereandSphere(*mp_physicsObjects[i], *mp_physicsObjects[j], m_Data);
		}
	}

	std::vector<ParticleContact*>  sphere = m_Data->GetContacts();
	
	for (int i = 0; i < sphere.size(); i++)
	{
		m_ContactVector.push_back(*sphere[i]);
	}
	m_Resolver.ResolveContacts(m_ContactVector, m_ContactVector.size(), msTime);
	m_ContactVector.clear();
	m_Data->Clear();
	for (auto i : PhysicsRegistry)
	{
		i->UpdateForces();
	}
	for (auto i : mp_physicsObjects)
	{
		i->Update(msTime);
	}
	
}

