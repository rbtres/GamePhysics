#pragma once
#include "RigidContact.h"
#include <vector>
class CollisionData
{
public:
	CollisionData();
	~CollisionData();

	inline RigidContact* GetContact(){ RigidContact* con = new RigidContact(); Contacts.push_back(con); return con; }
	inline int GetContactsLeft(){ return m_numContactsLeft; }
	//adds numbers ignore books naming
	inline void AddContacts(int num){ m_numContactsLeft += num; }
	float Restitution;
	float Friction;

private:
	int m_numContactsLeft;

	std::vector<RigidContact*> Contacts;
};

