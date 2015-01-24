#include "GameApp.h"

//--------------------------------------------------------------------------------------------
GameApp::GameApp()
{
	p_InputManager = new InputManager();

	m_Firework = Fireworks();
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
	m_Firework.CleanUp();
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void GameApp::Init()
{
	p_InputManager->Init();
	m_Firework.Init(5,-5,1000);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void GameApp::Draw()
{
	m_Firework.Draw();
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
	m_Firework.Update(msTime);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void GameApp::Reset()
{
	m_Firework.Reset();
}