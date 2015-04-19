#include "Player.h"


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
	g->Init(Vector3D(0, 15, 0));
	g->SetRadius(2);
	g->SetTexture("snake");

	mp_PlayerPieces = g;
}
