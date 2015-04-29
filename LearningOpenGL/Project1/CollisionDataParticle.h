#pragma once
#include "ParticleContact.h"
#include <vector>
class CollisionDataParticle
{
public:
	CollisionDataParticle();
	~CollisionDataParticle();

	inline ParticleContact* GetContact(){ ParticleContact* con = new ParticleContact(); Contacts.push_back(con); return con; }
	inline int GetContactsLeft(){ return m_numContactsLeft; }
	//adds numbers ignore books naming
	inline void AddContacts(int num){ m_numContactsLeft += num; }
	inline std::vector<ParticleContact*> GetContacts() { return Contacts; }
	inline void Clear(){ for (int i = 0; i < Contacts.size(); i++) delete Contacts[i]; Contacts.clear(); }
	float Restitution;

private:
	int m_numContactsLeft;

	std::vector<ParticleContact*> Contacts;
};

