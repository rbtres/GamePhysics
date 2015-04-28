#pragma once
#include <vector>
#include "RigidContact.h"
class RigidBodyContactResolver
{
public:
	RigidBodyContactResolver();
	~RigidBodyContactResolver();

	inline void SetIterations(int iterations){ m_iterations = iterations; }
	void ResolveContacts(std::vector<RigidContact> contactArray, int numContacts, float duration);

protected:
	int m_iterations;
	int m_iterationsUsed;
};

