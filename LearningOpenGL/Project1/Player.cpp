#include "Player.h"
#include "ImageHandler.h"

Player::Player()
{
}


Player::~Player()
{
}

//init first circle for this case
void Player::Init()
{
	GameObject* g = new GameObject();
	g->Init(Vector3D(-40, 15, 0));
	g->SetRadius(2);
	ImageHandler* m = ImageHandler::GetInstance();
	g->SetTexture(m->GetImage("snake"));

	mp_PlayerPieces = g;
}
