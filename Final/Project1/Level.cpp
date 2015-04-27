#include "Level.h"


Level::Level()
{
	mp_PhysicsManager = new PhysicsManager();
	mp_GroundGenerator = new GroundContactGenerator();
	mp_WallContact = new WallContact();
}


Level::~Level()
{
	delete mp_GroundGenerator;
	mp_GroundGenerator = nullptr;
	delete mp_WallContact;
	mp_WallContact = nullptr;
	for (unsigned int i = 0; i < mp_GameObjects.size(); i++)
	{
		delete mp_GameObjects[i];
		mp_GameObjects[i] = nullptr;
	}
	mp_GameObjects.clear();
}
void Level::Init(std::string filePath, int height)
{
	m_GroundHeight = height; 
	mp_GroundGenerator->GroundHeight = (float)m_GroundHeight; 
}
void Level::Draw()
{
	for (auto i : mp_GameObjects)
	{
		i->Draw();
	}
	for (auto i : mp_RenderBodies)
	{
		i->Draw();
	}
}

void Level::Update(float msTime)
{
	mp_GroundGenerator->AddContact(mp_PhysicsManager);
	mp_WallContact->AddContact(mp_PhysicsManager);
	for (auto i : mp_Rods)
	{
		i->AddContact(mp_PhysicsManager);
	}
	mp_PhysicsManager->Update( msTime);

}
void Level::AddRenderObject(RigidRender* renderObject, bool needsPhysics)
{
	mp_RenderBodies.push_back(renderObject);
	if (needsPhysics)
	{
		AddPhysics(renderObject);
	}
}
void Level::AddGameObject(GameObject* gameObject, bool needsPhysics)
{
	mp_GameObjects.push_back(gameObject);
	if (needsPhysics)
	{
		AddPhysics(gameObject);
	}
}

void Level::AddRandomShape(Vector3D center, float length)
{
	GameObject* t = new GameObject();
	t->Init(Vector3D(center.X, center.Y + length / 2, center.Z));
	t->SetRadius(1);
	t->SetTexture("snake");
	t->setMass(1);

	GameObject* br = new GameObject();
	br->Init(Vector3D(center.X + length / 2, center.Y, center.Z + length / 2));
	br->SetRadius(1);
	br->SetTexture("snake");
	br->setMass(1);

	GameObject* bl = new GameObject();
	bl->Init(Vector3D(center.X - length / 2, center.Y , center.Z + length / 2));
	bl->SetRadius(1);
	bl->SetTexture("snake");
	bl->setMass(1);

	GameObject* bt = new GameObject();
	bt->Init(Vector3D(center.X, center.Y, center.Z - length / 2));
	bt->SetRadius(1);
	bt->SetTexture("snake");
	bt->setMass(1);

	GameObject* b = new GameObject();
	b->Init(Vector3D(center.X, center.Y - length / 2, center.Z));
	b->SetRadius(1);
	b->SetTexture("snake");
	b->setMass(1);

	AddGameObject(t);
	AddGameObject(bl);
	AddGameObject(br);
	AddGameObject(bt);
	AddGameObject(b);

	ParticleRod* rod = new ParticleRod();
	rod->particle_b = t;
	rod->particle_a = br;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = t;
	rod->particle_a = bl;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = t;
	rod->particle_a = bt;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = t;
	rod->particle_a = b;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_a = bl;
	rod->particle_b = br;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_a = bl;
	rod->particle_b = bt;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_a = bl;
	rod->particle_b = b;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_a = bt;
	rod->particle_b = br;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_a = bt;
	rod->particle_b = b;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_a = br;
	rod->particle_b = b;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);
}

void Level::AddCube(Vector3D center, float length)
{
	GameObject* tfl = new GameObject();
	tfl->Init(Vector3D(center.X - length / 2, center.Y + length / 2, center.Z - length / 2));
	tfl->SetRadius(1);
	tfl->SetTexture("snake");
	tfl->setMass(1);

	GameObject* tfr = new GameObject();
	tfr->Init(Vector3D(center.X + length / 2, center.Y + length / 2, center.Z - length / 2));
	tfr->SetRadius(1);
	tfr->SetTexture("snake");
	tfr->setMass(1);

	GameObject* tbl = new GameObject();
	tbl->Init(Vector3D(center.X - length / 2, center.Y + length / 2, center.Z + length / 2));
	tbl->SetRadius(1);
	tbl->SetTexture("snake");
	tbl->setMass(1);

	GameObject* tbr = new GameObject();
	tbr->Init(Vector3D(center.X + length / 2, center.Y + length / 2, center.Z + length / 2));
	tbr->SetRadius(1);
	tbr->SetTexture("snake");
	tbr->setMass(1);

	GameObject* bfl = new GameObject();
	bfl->Init(Vector3D(center.X - length / 2, center.Y - length / 2, center.Z - length / 2));
	bfl->SetRadius(1);
	bfl->SetTexture("snake");
	bfl->setMass(1);

	GameObject* bfr = new GameObject();
	bfr->Init(Vector3D(center.X + length / 2, center.Y - length / 2, center.Z - length / 2));
	bfr->SetRadius(1);
	bfr->SetTexture("snake");
	bfr->setMass(1);

	GameObject* bbl = new GameObject();
	bbl->Init(Vector3D(center.X - length / 2, center.Y - length / 2, center.Z + length / 2));
	bbl->SetRadius(1);
	bbl->SetTexture("snake");
	bbl->setMass(1);

	GameObject* bbr = new GameObject();
	bbr->Init(Vector3D(center.X + length / 2, center.Y - length / 2, center.Z + length / 2));
	bbr->SetRadius(1);
	bbr->SetTexture("snake");
	bbr->setMass(1);

	AddGameObject(bfl);
	AddGameObject(bfr);
	AddGameObject(bbl);
	AddGameObject(bbr);
	AddGameObject(tfl);
	AddGameObject(tfr);
	AddGameObject(tbl);
	AddGameObject(tbr);

	ParticleRod* rod = new ParticleRod();
	rod->particle_b = bfl;
	rod->particle_a = bfr;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = bfl;
	rod->particle_a = bbl;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = bfl;
	rod->particle_a = bbr;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = bfl;
	rod->particle_a = tfl;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = bfl;
	rod->particle_a = tfr;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = bfl;
	rod->particle_a = tbl;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = bfl;
	rod->particle_a = tbr;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = bfr;
	rod->particle_a = bbl;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = bfr;
	rod->particle_a = bbr;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = bfr;
	rod->particle_a = tfl;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = bfr;
	rod->particle_a = tfr;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = bfr;
	rod->particle_a = tbl;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = bfr;
	rod->particle_a = tbr;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = bbl;
	rod->particle_a = bbr;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = bbl;
	rod->particle_a = tfl;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = bbl;
	rod->particle_a = tfr;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = bbl;
	rod->particle_a = tbl;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = bbl;
	rod->particle_a = tbr;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = bbr;
	rod->particle_a = tfl;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = bbr;
	rod->particle_a = tfr;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = bbr;
	rod->particle_a = tbl;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = bbr;
	rod->particle_a = tbr;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = tfl;
	rod->particle_a = tfr;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = tfl;
	rod->particle_a = tbl;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = tfl;
	rod->particle_a = tbr;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = tfr;
	rod->particle_a = tbl;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = tfr;
	rod->particle_a = tbr;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = tbl;
	rod->particle_a = tbr;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);


}

void Level::AddPyramid(Vector3D center, float length)
{
	
	GameObject* t = new GameObject();
	t->Init(Vector3D(center.X, center.Y + length / 2, center.Z));
	t->SetRadius(1);
	t->SetTexture("snake");
	t->setMass(1);

	GameObject* br = new GameObject();
	br->Init(Vector3D(center.X + length / 2, center.Y - length / 2, center.Z + length / 2));
	br->SetRadius(1);
	br->SetTexture("snake");
	br->setMass(1);

	GameObject* bl = new GameObject();
	bl->Init(Vector3D(center.X - length / 2, center.Y - length / 2, center.Z + length / 2));
	bl->SetRadius(1);
	bl->SetTexture("snake");
	bl->setMass(1);

	GameObject* bt = new GameObject();
	bt->Init(Vector3D(center.X, center.Y - length / 2, center.Z - length / 2));
	bt->SetRadius(1);
	bt->SetTexture("snake");
	bt->setMass(1);

	AddGameObject(t);
	AddGameObject(bl);
	AddGameObject(br);
	AddGameObject(bt);

	ParticleRod* rod = new ParticleRod();
	rod->particle_b = t;
	rod->particle_a = br;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = t;
	rod->particle_a = bl;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_b = t;
	rod->particle_a = bt;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_a = bl;
	rod->particle_b = br;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_a = bt;
	rod->particle_b = br;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);

	rod = new ParticleRod();
	rod->particle_a = bt;
	rod->particle_b = bl;
	rod->max_length = rod->particle_b->getPos().Distance(rod->particle_a->getPos());

	mp_Rods.push_back(rod);
	
	
}

void Level::Reset()
{
	for (auto i : mp_GameObjects)
	{
		i->Reset();
	}
	for (auto i : mp_RenderBodies)
	{
		i->Reset();
	}
}