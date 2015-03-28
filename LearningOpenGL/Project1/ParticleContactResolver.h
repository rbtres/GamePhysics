#pragma once
#include "ParticleContact.h"
class ParticleContactResolver
{
public:
	ParticleContactResolver(int iterations);
	~ParticleContactResolver();

	inline void SetIterations(int iterations){ m_iterations = iterations; }
	void ResolveContacts(ParticleContact *contactArray, int numContacts, float duration);
	
protected:
	int m_iterations;
	int m_iterationsUsed;
};

