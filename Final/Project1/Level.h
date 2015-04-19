#pragma once

#include "PhysicsManager.h"
#include "GameObject.h"
#include <string>
#include "GroundContactGenerator.h"
#include "ParticleRod.h"
#include "WallContact.h"
#include "ImageHandler.h"

typedef std::vector<GameObject*> GameObjectVec;
typedef std::vector<PhysicsObject*> PhysicObjectVec;

class Level
{
public:
	Level();
	~Level();
	void Draw();
	//Will know how to read file and create level besides player who starts at 0,0,0
	void Init(std::string filePath, int height);
	void Update(float msTime);
	void AddGameObject(GameObject* gameObject, bool needsPhysics = true);
	void AddPyramid(Vector3D center, float length);
	void AddCube(Vector3D center, float length);
	void AddRandomShape(Vector3D center, float length);
	inline void AddPhysics(PhysicsObject* object){ mp_PhysicsManager->AddPhysicsObject(object); };
	inline void AddPhysics(RigidBody* object){ mp_PhysicsManager->AddRigidBody(object); }
	void remove(GameObject* gameObject){};
	void Reset();

private:
	int m_GroundHeight;
	GameObjectVec mp_GameObjects;
	PhysicsManager* mp_PhysicsManager;
	GroundContactGenerator* mp_GroundGenerator;
	WallContact* mp_WallContact;
	std::vector<ParticleRod*> mp_Rods;
};

