#include "InputManager.h"
#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
//used http://www.swiftless.com/tutorials/opengl/camera2.html
using namespace std;

//--------------------------------------------------------------------------------------------
InputManager::InputManager()
{
	m_pos = Vector3D();
	m_rot = Vector2D();

	m_mouseSpeed = .1f;
	m_cameraSpeed = .1f;
	m_planetLookat = -1;
	m_leftClickDown = false;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
InputManager::~InputManager()
{
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void InputManager::Init()
{
	m_oldPos.X = -1;
	m_oldPos.Y = -1;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void InputManager::Update(int msTime)
{
	glLoadIdentity();
	glRotatef(90, 1.0, 0.0, 0.0);  //rotate our camera on teh x - axis(left and right)
	glRotatef(m_rot.Y, 0.0, 1.0, 0.0);  //rotate our camera on the y - axis(up and down)
	glTranslated(-m_pos.X, -m_pos.Y, -m_pos.Z); //translate the screen to the position of our camera
	

}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void InputManager::Enable()
{

}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void InputManager::CleanUp()
{

}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void InputManager::HandleKeyDown(unsigned char key)
{
	if (key == 'o')
	{
		//PlanetManager::ModifyDaysPerSecond(-5);
	}
	if (key == 'p')
	{
		//PlanetManager::ModifyDaysPerSecond(5);
	}
	if (key == 'w')
	{
		mp_Player->addForce(Vector3D(0, 0, -10));
	}

	if (key == 's')
	{
		mp_Player->addForce(Vector3D(0, 0, 10));
	}

	if (key == 'e')
	{
		mp_Player->addForce(Vector3D(0, 30, 0));
	}
	if (key == 'c')
	{
		
	}

	if (key == 'd')
	{
		mp_Player->addForce(Vector3D(10, 0, 0));
	}

	if (key == 'a')
	{
		mp_Player->addForce(Vector3D(-10, 0, 0));
	}
	if (key == 'f')
	{
		glutFullScreen();
	}

	if (key == 27)
	{
		exit(0);
	}

	if (key == '0')
	{

	}

	if (key == '1')
	{
		m_planetLookat = 1;
	}

	if (key == '2')
	{
		m_planetLookat = 2;
	}

	if (key == '3')
	{
		m_planetLookat = 3;
	}

	if (key == '4')
	{
		m_planetLookat = 4;
	}

	if (key == '5' )
	{
		m_planetLookat = 5;
	}

	if (key == '6' )
	{
		m_planetLookat = 6;
	}

	if (key == '7' )
	{
		m_planetLookat = 7;
	}
	if (key == '8')
	{
		m_planetLookat = 8;
	}
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void InputManager::HandleMouse(Vector2D mousePos)
{
	/*
	m_movedPos = mousePos;
	if (m_oldPos.X == -1)
	{
		m_oldPos = mousePos;
	}
	else if (m_movedPos != m_oldPos && !m_leftClickDown)
	{
		m_offset = m_oldPos - m_movedPos;
		m_oldPos = m_movedPos;
		
		m_rot.X += m_offset.Y * m_mouseSpeed;
		m_rot.Y += m_offset.X * m_mouseSpeed;
		m_planetLookat = -1;
	}
	*/
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void InputManager::HandleMouseDown(Vector2D buttonAndState, Vector2D mousePos)
{
	/*
	switch ((int)buttonAndState.X)
	{
	case GLUT_LEFT_BUTTON:
		if (buttonAndState.Y == GLUT_DOWN)
		{
			m_leftClickDown = !m_leftClickDown;
		}
		else
		{
			m_oldPos = mousePos;
		}
	}
	*/
}

