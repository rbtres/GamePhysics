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
#include "PlanetManager.h"

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
//============================================================================================
private:
	void update(int msTime);
	PlanetManager* mp_PlanetManager;
	SkyBox* mp_SkyBox;

};
//============================================================================================
