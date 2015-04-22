#pragma once
#include "RigidContact.h"
class CollisionData
{
public:
	CollisionData();
	~CollisionData();

	inline RigidContact* GetContact(){ return m_Contact; }
	inline int GetContactsLeft(){ return m_numContactsLeft; }
	//adds numbers ignore books naming
	inline void AddContacts(int num){ m_numContactsLeft += num; }
	float Restitution;
	float Friction;
private:
	int m_numContactsLeft;

	RigidContact* m_Contact;
};

