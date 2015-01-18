//============================================================================================
//Create by Robert Bethune
//GameApp.h
//This will be base for our game app, or just physics test
//Creation Date 1/17/2015
//============================================================================================
#pragma once
#include"InputManager.h"
//============================================================================================
class GameApp
{
public:
	GameApp();
	~GameApp();
//--------------------------------------------------------------------------------------------
	void Update();
	void Init();
	void CleanUp();

	void HandleKeyDown(unsigned char key);
	void HandleMouse(Vector2D mousePos);
	void HandleMouseDown(Vector2D buttonAndState, Vector2D mousePos);
//--------------------------------------------------------------------------------------------
	InputManager* p_InputManager;
//============================================================================================
private:
};
//============================================================================================
