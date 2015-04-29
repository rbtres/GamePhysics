#include "SkyBox.h"
#include "GameApp.h"

//--------------------------------------------------------------------------------------------
GameApp::GameApp()
{
	p_InputManager = new InputManager();
	p_Level = new Level();
	//mp_Player = new Player();
	mp_SkyBox = new SkyBox();
	mp_Ground = new Ground();
	//p_CameraPos = new PhysicsObject();
	//mp_CameraToPlayer = new Bungie();
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
GameApp::~GameApp()
{

}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void GameApp::Update(float msTime, bool isPlaying)
{
	p_InputManager->Update((int)msTime);
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
	
	mp_SkyBox->Init();
	//mp_Player->Init();
	//mp_Player->GetPlayer()->setMass(1);
//	p_Level->AddGameObject(mp_Player->GetPlayer());
	
	//mp_CameraToPlayer->m_AnchorObject = mp_Player->GetPlayer();
	mp_Ground->Init();
	mp_Ground->setDamping(0);
	mp_Ground->setMass(1000000000);
	mp_Ground->SetTexture("grass.jpg");
	mp_Ground->setPos(Vector3D(0, -20, 0));
	mp_Ground->SetDim(Vector3D(50, -mp_Ground->getPos().Y, 50));
	p_Level->Init("hello", -20);
	
	p_Level->CreateSphere(Vector3D(0, 10, 0), .5f);
	
	p_Level->CreateSphere(Vector3D(-2.5, 10, 0), .5f);
	
	p_Level->CreateSphere(Vector3D(2.5, 10, 0), .5f);
	
	p_Level->CreateSphere(Vector3D(1, 10, 0), .5f);
	
	p_Level->CreateSphere(Vector3D(0, 10, 2), .5f);
	p_Level->CreateSphere(Vector3D(-2, 10, -2), .5f);
	p_Level->CreateSphere(Vector3D(2, 10, 0), .5f);
	p_Level->CreateSphere(Vector3D(2.5, 10, 2.5), .5f);
	p_Level->CreateSphere(Vector3D(0, 10, 1), .5f);
	p_Level->CreateSphere(Vector3D(-1.5, 10, -1), .5f);
	p_Level->CreateSphere(Vector3D(-1, 10, 1), .5f);
	p_Level->CreateSphere(Vector3D(2.5, 10, .5), .5f);
	p_Level->CreateSphere(Vector3D(0, 8, 0), .5f);
	p_Level->CreateSphere(Vector3D(-2.5, 8, 0), .5f);
	p_Level->CreateSphere(Vector3D(2.5, 8, 0), .5f);
	p_Level->CreateSphere(Vector3D(1, 8, 0), .5f);
	p_Level->CreateSphere(Vector3D(0, 8, 2), .5f);
	
	p_Level->CreateSphere(Vector3D(-2, 8, -2), .5f);
	
	p_Level->CreateSphere(Vector3D(2, 8, 0), .5f);
	p_Level->CreateSphere(Vector3D(2.5, 8, 2.5), .5f);
	p_Level->CreateSphere(Vector3D(0, 8     , 1), .5f);
	
	//p_Level->AddPyramid(Vector3D(10, 5, 5), 10);
	//p_Level->AddCube(Vector3D(-10, 15, 5), 10);
	//p_Level->AddCube(Vector3D(-65, 0, -15), 5);
	//p_Level->AddCube(Vector3D(20, 0, 15), 5);
	//p_Level->AddCube(Vector3D(-10, 0, -25), 5);
	//p_Level->AddRandomShape(Vector3D(0,10,-10), 5);
	//p_CameraPos->setMass(1);
	//p_CameraPos->Init(Vector3D(mp_Player->GetPlayer()->getPos().X, mp_Player->GetPlayer()->getPos().Y - 10, mp_Player->GetPlayer()->getPos().Z));
	//p_CameraPos->setRadius(1);
	//p_Level->AddPhysics(p_CameraPos);
//	p_InputManager->SetPlayer(mp_Player->GetPlayer());
	//p_InputManager->SetPos(p_CameraPos->getPos());

}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void GameApp::Draw()
{
	mp_SkyBox->RenderSkyBox();
	p_Level->Draw();
	mp_Ground->Draw();
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
void GameApp::update(float msTime)
{
	
	//mp_CameraToPlayer->UpdateForce(p_CameraPos);
	p_Level->Update(msTime);
	//p_CameraPos->Update(msTime);
	//p_InputManager->SetPos(p_CameraPos->getPos());
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void GameApp::Reset()
{
	//mp_Player->Reset();
	p_Level->Reset();
	//p_CameraPos->Reset();
	//p_InputManager->SetPos(p_CameraPos->getPos());
	//reset Level
}
//--------------------------------------------------------------------------------------------