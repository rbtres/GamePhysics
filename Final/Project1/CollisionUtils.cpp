#include "CollisionUtils.h"
#include <cmath>

CollisionUtils::CollisionUtils()
{
}


CollisionUtils::~CollisionUtils()
{
}

bool CollisionUtils::TryAxis(const CollisionBox& boxOne, const CollisionBox& boxTwo, Vector3D normal, const Vector3D center, int index, float &smallestPenetration, int &smallestCase)
{
	if (normal.MagnitudeSq() < .0001f) return true;

	float projOne = boxOne.HalfSize.X * abs(normal.Dot(boxOne.GetAxis(0)));
	projOne += boxOne.HalfSize.Y * abs(normal.Dot(boxOne.GetAxis(1)));
	projOne += boxOne.HalfSize.Z * abs(normal.Dot(boxOne.GetAxis(2)));

	float projTwo = boxTwo.HalfSize.X * abs(normal.Dot(boxTwo.GetAxis(0)));
	projOne += boxTwo.HalfSize.Y * abs(normal.Dot(boxTwo.GetAxis(1)));
	projOne += boxTwo.HalfSize.Z * abs(normal.Dot(boxTwo.GetAxis(2)));

	float distance = abs(center.Dot(normal));

	float pen = projOne + projTwo - distance;
	if (pen < 0)
	{
		return false;
	}

	if (pen < smallestPenetration)
	{
		smallestPenetration = pen;
		smallestCase = index;
	}

	return true;
}