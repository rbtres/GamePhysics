#include "ParticleContactResolver.h"


ParticleContactResolver::ParticleContactResolver()
{
}


ParticleContactResolver::~ParticleContactResolver()
{
}

void ParticleContactResolver::ResolveContacts(std::vector<ParticleContact> contactArray, int numContacts, float duration)
{

	for (auto i : contactArray)
	{
		i.resolve(duration);
	}
	contactArray.clear();
}