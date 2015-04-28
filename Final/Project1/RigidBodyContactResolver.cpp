#include "RigidBodyContactResolver.h"


RigidBodyContactResolver::RigidBodyContactResolver()
{
}


RigidBodyContactResolver::~RigidBodyContactResolver()
{
}

void RigidBodyContactResolver::ResolveContacts(std::vector<RigidContact> contactArray, int numContacts, float duration)
{
	for (auto i : contactArray)
	{
		i.Resolve(duration);
	}
	contactArray.clear();
}