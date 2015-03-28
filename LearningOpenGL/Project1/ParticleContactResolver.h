#pragma once
#include "ParticleContact.h"
#include <vector>
class ParticleContactResolver
{
public:
	ParticleContactResolver();
	~ParticleContactResolver();

	inline void SetIterations(int iterations){ m_iterations = iterations; }
	void ResolveContacts(std::vector<ParticleContact> contactArray, int numContacts, float duration);
	
protected:
	int m_iterations;
	int m_iterationsUsed;
};

