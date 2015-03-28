//============================================================================================
//Create by Robert Bethune
//GameApp.h
//This will be base for our game app, or just physics test
//Creation Date 1/17/2015
//Last Modified 1/24/2015
//============================================================================================
#pragma once

#include "InputManager.h"
#include "PhysicsObject.h"
#include "Player.h"
#include "Level.h"
#include"Ground.h"
#include "Bungie.h"

class SkyBox;
//============================================================================================
class GameApp
{
public:
	GameApp();
	~GameApp();
//--------------------------------------------------------------------------------------------
	void Update(int msTime, bool isPlaying);
	void Init();
	void CleanUp();
	void Draw();
	void Reset();

	void HandleKeyDown(unsigned char key);
	void HandleMouse(Vector2D mousePos);
	void HandleMouseDown(Vector2D buttonAndState, Vector2D mousePos);
//--------------------------------------------------------------------------------------------
	InputManager* p_InputManager;
	Level* p_Level;
	PhysicsObject* p_CameraPos;
//============================================================================================
private:
	void update(int msTime);
	SkyBox* mp_SkyBox;
	Player* mp_Player;
	Ground* mp_Ground;
	Bungie* mp_CameraToPlayer;

};
//============================================================================================
