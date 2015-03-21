#pragma once

#include "PhysicsManager.h"
#include "GameObject.h"
#include <string>

typedef std::vector<GameObject*> GameObjectVec;
typedef std::vector<PhysicsObject*> PhysicObjectVec;

class Level
{
public:
	Level();
	~Level();
	void Draw();
	//Will know how to read file and create level besides player who starts at 0,0,0
	void Init(std::string filePath) {};
	void Update(float msTime);
	void AddGameObject(GameObject* gameObject, bool needsPhysics = true);
	void remove(GameObject* gameObject){};

private:
	GameObjectVec mp_GameObjects;
	PhysicsManager* mp_PhysicsManager;
	
};

