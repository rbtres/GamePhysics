//============================================================================================
//Create by Robert Bethune
//InputManager
//Does Two thnigs not just input. Does manage all input. While flushing out system in 
//first couple weeks it will also manager the camera for sometime
//Don't have time to fully implement a event system. I also don't want
//to couple input specifically with a camera class, so currently both in one is best solution
//til event system can be made.
//Creation Date 1/18/2015
//Last Updated 2/14/2015
//============================================================================================
#include "Vector2D.h"
#include "Vector3D.h"
#include "PlanetManager.h"
#pragma once
//============================================================================================
class InputManager
{
public:
	InputManager();
	~InputManager();
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
	void Init();
	void CleanUp();
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
	void HandleKeyDown(unsigned char key);
	void HandleMouse(Vector2D mousePos);
	void HandleMouseDown(Vector2D buttonAndState, Vector2D mosPos);
	void Update(int msTime);
	void Enable();
	int GetCurrentPlanet(){ return m_planetLookat; }
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
	Vector2D getOffset() { return m_offset; }
//============================================================================================
private:
//--------------------------------------------------------------------------------------------
	Vector2D m_oldPos;
	Vector2D m_movedPos;
	Vector2D m_offset;
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
	Vector2D m_rot;
	Vector3D m_pos;
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
	float m_mouseSpeed;
	float m_cameraSpeed;
//--------------------------------------------------------------------------------------------
	bool m_leftClickDown;
	int m_planetLookat;
};
//============================================================================================

