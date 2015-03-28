#include "ParticleContactResolver.h"


ParticleContactResolver::ParticleContactResolver(int iterations)
{
	m_iterations = iterations;
}


ParticleContactResolver::~ParticleContactResolver()
{
}

void ParticleContactResolver::ResolveContacts(ParticleContact *contactArray, int numContacts, float duration)
{
	int i;
	m_iterationsUsed = 0;

	while (m_iterationsUsed < m_iterations)
	{
		int max = 50;
		int maxIndex = numContacts;
		for (i = 0; i < numContacts; i++)
		{
			float sepVel = contactArray[i].calculateSeparatingVelocity();
			if (sepVel < max && contactArray[i].penetration > 0)
			{
				max = sepVel;
				maxIndex = i;
			}
		}

		if (maxIndex == numContacts) break;

		contactArray[maxIndex].resolve(duration);
		m_iterationsUsed++;
	}
}