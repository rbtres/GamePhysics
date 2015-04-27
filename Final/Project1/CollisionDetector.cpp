#include "CollisionDetector.h"
#include "RigidContact.h"
#include "CollisionUtils.h"

//this class is highly from book same with utils + github worked with Evan and jake
CollisionDetector::CollisionDetector()
{
}


CollisionDetector::~CollisionDetector()
{
}
unsigned int CollisionDetector::SphereandSphere(const CollisionSphere &sphereOne,const CollisionSphere &sphereTwo, CollisionData* data)
{
	if (data->GetContactsLeft() <= 0)
	{
		return 0;
	}
	
	Vector3D posOne = sphereOne.GetAxis(3);
	Vector3D posTwo = sphereTwo.GetAxis(3);

	Vector3D dif = posOne - posTwo;

	float mag = dif.Magnitude();

	if (mag <= 0 || mag >= sphereOne.Radius + sphereTwo.Radius)
	{
		return 0;
	}
	Vector3D normal = dif * (1.0f / mag);
	RigidContact* contact = data->GetContact();
	contact->Initialize(posOne + dif * .5f, normal, sphereOne.Radius + sphereTwo.Radius - mag, data->Restitution, data->Friction, sphereOne.Body, sphereTwo.Body);

	data->AddContacts(1);
	return 1;
}

unsigned int CollisionDetector::SphereandHalfSpace(const CollisionSphere &sphereOne, const CollisionPlane &planeOne, CollisionData* data)
{
	if (data->GetContactsLeft() <= 0)
	{
		return 0;
	}

	Vector3D posOne = sphereOne.GetAxis(3);

	float sphereDistance = planeOne.Direction.Dot(posOne);
	
	if (sphereDistance >= 0)
		return 0;
	
	RigidContact*contact = data->GetContact();
	contact->Initialize(posOne - planeOne.Direction * (sphereDistance + sphereOne.Radius), planeOne.Direction, -sphereDistance, data->Restitution, data->Friction, sphereOne.Body, nullptr);

	data->AddContacts(1);

	return 1;
}

unsigned int CollisionDetector::SphereandTruePlane(const CollisionSphere &sphereOne, const CollisionPlane &planeOne, CollisionData* data)
{
	if (data->GetContactsLeft() <= 0)
	{
		return 0;
	}

	Vector3D posOne = sphereOne.GetAxis(3);

	float sphereDistance = planeOne.Direction.Dot(posOne) - planeOne.Offset;

	if (sphereDistance * sphereDistance >= sphereOne.Radius * sphereOne.Radius)
		return 0;
	RigidContact* contact = data->GetContact();

	contact->Initialize(posOne - planeOne.Direction * (sphereDistance + sphereOne.Radius), planeOne.Direction, -sphereDistance, data->Restitution, data->Friction, sphereOne.Body, nullptr);

	data->AddContacts(1);

	return 1;

}

unsigned int CollisionDetector::BoxandPlane(const CollisionBox &box, const CollisionPlane &plane, CollisionData* data)
{
	if (data->GetContactsLeft() <= 0)return 0;

	if (!CollisionUtils::CollisionBoxPlane(box, plane))
	{
		return 0;
	}


	static float mults[8][3] = { { 1, 1, 1 }, { -1, 1, 1 }, { 1, -1, 1 }, { -1, -1, 1 }, { 1, 1, -1 }, { -1, 1, -1 }, { 1, -1, -1 }, { -1, -1, -1 } };
	int contactUsed = 0;

	for (int i = 0; i < 8; i++)
	{

		RigidContact* contact = data->GetContact();
		Vector3D vertextPos = Vector3D(mults[i][0],mults[i][1], mults[i][2]);
		//vertextPos.ComponentProductUpdate(Box.HalfSize);
		vertextPos = box.Transform.Transform(vertextPos);
		float vertexDistance = vertextPos.Dot(plane.Direction);

		if (vertexDistance <= plane.Offset)
		{
			Vector3D contactPoint = plane.Direction;
			contactPoint = contactPoint * (vertexDistance - plane.Offset);
			contactPoint += vertextPos;
			Vector3D contactNormal = plane.Direction;
			float pen = plane.Offset - vertexDistance;

			contact->Initialize(contactPoint, contactNormal, pen, data->Restitution, data->Friction, box.Body, nullptr);

			contactUsed++;
			if (contactUsed == data->GetContactsLeft())
				return contactUsed;
		}
	}
	data->AddContacts(contactUsed);
	return contactUsed;
}

unsigned int CollisionDetector::BoxandSphere(const CollisionBox &box, const CollisionSphere &sphere, CollisionData* data)
{
	Vector3D center = sphere.GetAxis(3);
	Matrix inverse = box.Transform.InvMatrix();
	Vector3D relCenter = inverse.Transform(center);
	Vector3D closestPt = Vector3D(0, 0, 0);
	if ((relCenter.X - sphere.Radius) > box.HalfSize.X || (relCenter.Y - sphere.Radius) > box.HalfSize.Y
		|| (relCenter.X - sphere.Radius) > box.HalfSize.Z)
		return 0;

	float dist;

	dist = relCenter.X;

	if (dist > box.HalfSize.X) dist = box.HalfSize.X;

	if (dist < -box.HalfSize.X) dist = -box.HalfSize.X;

	closestPt.X = dist;

	dist = relCenter.Y;

	if (dist > box.HalfSize.Y) dist = box.HalfSize.Y;

	if (dist < -box.HalfSize.Y) dist = -box.HalfSize.Y;

	closestPt.Y = dist;
	

	dist = relCenter.Z;

	if (dist > box.HalfSize.Z) dist = box.HalfSize.Z;

	if (dist < -box.HalfSize.Z) dist = -box.HalfSize.Z;

	closestPt.Z = dist;

	dist = (closestPt - relCenter).MagnitudeSq();
	if (dist > sphere.Radius * sphere.Radius) return 0;

	Vector3D closestPtWorld = box.Transform.Transform(closestPt);

	RigidContact* contact = data->GetContact();

	Vector3D contactNormal = (closestPtWorld - center);
	contactNormal.Normalize();
	Vector3D contactPoint = closestPtWorld;
	float pen = sphere.Radius - sqrtf(dist);

	contact->Initialize(contactPoint, contactNormal, pen, data->Restitution, data->Friction, box.Body, sphere.Body);

	data->AddContacts(1);

	return 1;
}

//Book and Github
unsigned int CollisionDetector::BoxandBox(const CollisionBox &boxOne, const CollisionBox &boxTwo, CollisionData* data)
{
	Vector3D toCenter = boxTwo.GetAxis(3) - boxOne.GetAxis(3);

	float pen = FLT_MAX;

	int best = 0xffffff;

	if (!CollisionUtils::TryAxis(boxOne, boxTwo, boxOne.GetAxis(0), toCenter, 0, pen, best)) return 0;
	if (!CollisionUtils::TryAxis(boxOne, boxTwo, boxOne.GetAxis(1), toCenter, 1, pen, best)) return 0;
	if (!CollisionUtils::TryAxis(boxOne, boxTwo, boxOne.GetAxis(2), toCenter, 2, pen, best)) return 0;

	if (!CollisionUtils::TryAxis(boxOne, boxTwo, boxOne.GetAxis(0), toCenter, 3, pen, best)) return 0;
	if (!CollisionUtils::TryAxis(boxOne, boxTwo, boxOne.GetAxis(1), toCenter, 4, pen, best)) return 0;
	if (!CollisionUtils::TryAxis(boxOne, boxTwo, boxOne.GetAxis(2), toCenter, 5, pen, best)) return 0;

	unsigned int bestSingleAxis = best;

	if (!CollisionUtils::TryAxis(boxOne, boxTwo, boxOne.GetAxis(0).Cross(boxTwo.GetAxis(0)), toCenter, 6, pen, best)) return 0;
	if (!CollisionUtils::TryAxis(boxOne, boxTwo, boxOne.GetAxis(0).Cross(boxTwo.GetAxis(1)), toCenter, 7, pen, best)) return 0;
	if (!CollisionUtils::TryAxis(boxOne, boxTwo, boxOne.GetAxis(0).Cross(boxTwo.GetAxis(2)), toCenter, 8, pen, best)) return 0;
	if (!CollisionUtils::TryAxis(boxOne, boxTwo, boxOne.GetAxis(1).Cross(boxTwo.GetAxis(0)), toCenter, 9, pen, best)) return 0;
	if (!CollisionUtils::TryAxis(boxOne, boxTwo, boxOne.GetAxis(1).Cross(boxTwo.GetAxis(1)), toCenter, 10, pen, best)) return 0;
	if (!CollisionUtils::TryAxis(boxOne, boxTwo, boxOne.GetAxis(1).Cross(boxTwo.GetAxis(2)), toCenter, 11, pen, best)) return 0;
	if (!CollisionUtils::TryAxis(boxOne, boxTwo, boxOne.GetAxis(2).Cross(boxTwo.GetAxis(0)), toCenter, 12, pen, best)) return 0;
	if (!CollisionUtils::TryAxis(boxOne, boxTwo, boxOne.GetAxis(2).Cross(boxTwo.GetAxis(1)), toCenter, 13, pen, best)) return 0;
	if (!CollisionUtils::TryAxis(boxOne, boxTwo, boxOne.GetAxis(2).Cross(boxTwo.GetAxis(2)), toCenter, 14, pen, best)) return 0;


	if (best == 0xffffff)
	{
		return 0;
	}

	if (best < 3)
	{
		FillPointFaceBoxBox(boxOne, boxTwo, toCenter, data, best, pen);
		data->AddContacts(1);
		return 1;
	}
	else if (best < 6)
	{
		FillPointFaceBoxBox(boxTwo, boxOne, toCenter* -1.0f, data, best - 3, pen);
		data->AddContacts(1);
		return 1;
	}
	else
	{
		best -= 6;
		unsigned int oneAxisIndex = best / 3;
		unsigned int twoAxisIndex = best % 3;
		Vector3D oneAxis = boxOne.GetAxis(oneAxisIndex);
		Vector3D twoAxis = boxTwo.GetAxis(twoAxisIndex);
		Vector3D normal = oneAxis.Cross(twoAxis);
		normal.Normalize();

		if (normal.Dot(toCenter) > 0)
		{
			normal = normal * -1.0f;
		}

		Vector3D pointOnEdgeOne = boxOne.HalfSize;
		Vector3D pointOnEdgeTwo = boxTwo.HalfSize;

		for (unsigned int i = 0; i < 3; i++)
		{
			if (i == oneAxisIndex) pointOnEdgeOne.SetIndex(i, 0);
			else if (boxOne.GetAxis(i).Dot(normal) > 0) pointOnEdgeOne.SetIndex(i, -pointOnEdgeOne.GetIndex(i));

			if (i == twoAxisIndex) pointOnEdgeTwo.SetIndex(i, 0);
			else if (boxTwo.GetAxis(i).Dot(normal) > 0) pointOnEdgeTwo.SetIndex(i, -pointOnEdgeOne.GetIndex(i));
		}

		pointOnEdgeOne = boxOne.Transform * pointOnEdgeOne;
		pointOnEdgeTwo = boxTwo.Transform * pointOnEdgeTwo;

		Vector3D contactPoint = GetContactPoint(pointOnEdgeOne, oneAxis, boxOne.HalfSize.GetIndex(oneAxisIndex),
			pointOnEdgeTwo, twoAxis, boxTwo.HalfSize.GetIndex(twoAxisIndex), bestSingleAxis > 2);

		RigidContact* contact = data->GetContact();;

		contact->Initialize(contactPoint,normal,pen,data->Restitution, data->Friction,boxOne.Body, boxTwo.Body);
		data->AddContacts(1);
		return 1;
	}
	return 0;
}


//Straight from Github confusing section
Vector3D CollisionDetector::GetContactPoint(Vector3D& pointOne,const  Vector3D& directionOne, float oneSize,
	Vector3D& pointTwo, const Vector3D& directionTwo, float twoSize, bool useOne)
{
	Vector3D toSt, cOne, cTwo;
	float dpStaOne, dpStaTwo, dpOneTwo, smOne, smTwo;
	float denom, mua, mub;

	smOne = directionOne.MagnitudeSq();
	smTwo = directionTwo.MagnitudeSq();
	dpOneTwo = directionTwo.Dot(directionOne);

	toSt = pointOne - pointTwo;
	dpStaOne = directionOne.Dot(toSt);
	dpStaTwo = directionTwo.Dot(toSt);

	denom = smOne * smTwo - dpOneTwo * dpOneTwo;

	if (abs(denom) < 0.00001f)
	{
		return useOne ? pointOne : pointTwo;
	}

	mua = (dpOneTwo * dpStaTwo - smTwo * dpStaOne) / denom;
	mub = (smOne * dpStaTwo - dpOneTwo * dpStaTwo) / denom;

	if (mua > oneSize || mua < -oneSize || mub > smTwo || mub < -twoSize)
	{
		return useOne ? pointOne : pointTwo;
	}
	else
	{
		cOne = pointOne + directionOne * mua;
		cTwo = pointTwo + directionTwo * mub;

		return cOne * 0.5 + cTwo * 0.5;
	}
}

void CollisionDetector::FillPointFaceBoxBox(const CollisionBox& boxOne, const CollisionBox& boxTwo, const Vector3D center, CollisionData* data, int best, float pen)
{
	RigidContact* contact = data->GetContact();

	Vector3D normal = boxOne.GetAxis(best);
	if (boxOne.GetAxis(best).Dot(center) > 0)
	{
		normal = normal * -1;
	}

	Vector3D vertex = boxTwo.HalfSize;
	if (boxTwo.GetAxis(0).Dot(normal) < 0)
	{
		vertex.X = -vertex.X;
	}
	if (boxTwo.GetAxis(1).Dot(normal) < 0)
	{
		vertex.Y = -vertex.Y;
	}
	if (boxTwo.GetAxis(2).Dot(normal) < 0)
	{
		vertex.Z = -vertex.Z;
	}

	Vector3D contactPoint = boxTwo.Transform* vertex;

	contact->Initialize(contactPoint,normal,pen,data->Restitution, data->Friction,
		boxOne.Body, boxTwo.Body);

}