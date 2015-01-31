#include "GameApp.h"

//--------------------------------------------------------------------------------------------
GameApp::GameApp()
{
	p_InputManager = new InputManager();

	mp_PlanetManager = new PlanetManager;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
GameApp::~GameApp()
{

}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void GameApp::Update(int msTime, bool isPlaying)
{
	p_InputManager->Update(msTime);

	if (isPlaying)
	{
		update(msTime);
	}
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void GameApp::CleanUp()
{
	p_InputManager->CleanUp();
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void GameApp::Init()
{
	p_InputManager->Init();
	mp_PlanetManager->Init();

}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void GameApp::Draw()
{
	mp_PlanetManager->Draw();
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void GameApp::HandleKeyDown(unsigned char key)
{
	p_InputManager->HandleKeyDown(key);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void GameApp::HandleMouse(Vector2D mousePos)
{
	p_InputManager->HandleMouse(mousePos);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void GameApp::HandleMouseDown(Vector2D buttonAndState, Vector2D mousePos)
{
	p_InputManager->HandleMouseDown(buttonAndState, mousePos);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void GameApp::update(int msTime)
{
	mp_PlanetManager->Update(msTime);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void GameApp::Reset()
{
	mp_PlanetManager->Reset();
}