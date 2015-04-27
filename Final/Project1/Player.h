//Owns the player entity, but PhysicsManager does the physics and Level does the drawing
//of all GameObjects. This class will be used for reseting and factual numbers for players
#pragma once
#include "GameObject.h"
#include <vector>
class Player
{
public:
	Player();
	~Player();
	inline void SetPlayer(GameObject* gameObject){ mp_PlayerPieces = gameObject; }
	GameObject* GetPlayer(){ return mp_PlayerPieces; }
	inline void Reset(){// mp_PlayerPieces->Reset();
	}
	void Init();
	//inline void Update(float msGameTime){ for (auto i : mp_PlayerPieces) i->Update(msGameTime); }
	//inline void Draw(){ for (auto i : mp_PlayerPieces) i->Draw(); }

protected:
	GameObject* mp_PlayerPieces;
};

