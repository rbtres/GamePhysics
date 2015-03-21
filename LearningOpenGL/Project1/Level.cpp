#include "Level.h"


Level::Level()
{
	mp_PhysicsManager = new PhysicsManager();
}


Level::~Level()
{
}

void Level::Draw()
{

	for (auto i : mp_GameObjects)
	{
		i->Draw();
	}
}

void Level::Update(float msTime)
{
	mp_PhysicsManager->Update( msTime);
}

void Level::AddGameObject(GameObject* gameObject, bool needsPhysics)
{
	mp_GameObjects.push_back(gameObject);
	if (needsPhysics)
	{
		mp_PhysicsManager->AddPhysicsObject(gameObject);
	}
}