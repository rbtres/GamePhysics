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
	if (m_planetLookat < 0)
	{
		glLoadIdentity();
		glRotatef(m_rot.X, 1.0, 0.0, 0.0);  //rotate our camera on teh x - axis(left and right)
		glRotatef(m_rot.Y, 0.0, 1.0, 0.0);  //rotate our camera on the y - axis(up and down)
		glTranslated(-m_pos.X, -m_pos.Y, -m_pos.Z); //translate the screen to the position of our camera
	}
	else if (m_planetLookat == 0)
	{
		m_pos.X = 0;
		m_pos.Z = 25;
		m_pos.Y = 0;
		m_planetLookat = 0;
		m_rot = Vector2D(0, 0);
		glLoadIdentity();
		glRotatef(m_rot.X, 1.0, 0.0, 0.0);  //rotate our camera on teh x - axis(left and right)
		glRotatef(m_rot.Y, 0.0, 1.0, 0.0);  //rotate our camera on the y - axis(up and down)
		glTranslated(-m_pos.X, -m_pos.Y, -m_pos.Z);
	}
	else if ( m_planetLookat > 0)
	{
		m_pos.X = 0;
		m_pos.Z = 25;
		m_pos.Y += 2.5;
		m_rot.X = 90;
		glLoadIdentity();
		glRotatef(m_rot.X, 1.0, 0.0, 0.0);  //rotate our camera on teh x - axis(left and right)
		glRotatef(m_rot.Y, 0.0, 1.0, 0.0);  //rotate our camera on the y - axis(up and down)
		glTranslated(-m_pos.X, -m_pos.Y, -m_pos.Z);
	}
	
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
	Vector2D radianRot = Vector2D();
	radianRot.Y = (m_rot.Y / 180 * M_PI);
	radianRot.X = (m_rot.X / 180 * M_PI);
	if (key == 'o')
	{
		PlanetManager::ModifyDaysPerSecond(-5);
	}
	if (key == 'p')
	{
		PlanetManager::ModifyDaysPerSecond(5);
	}
	if (key == 'w')
	{
		m_pos.X += float(sin(radianRot.Y)) * m_cameraSpeed;
		m_pos.Z -= float(cos(radianRot.Y)) * m_cameraSpeed;
		m_pos.Y -= float(sin(radianRot.X)) * m_cameraSpeed;
		m_planetLookat = -1;
	}

	if (key == 's')
	{
		m_pos.X -= float(sin(radianRot.Y)) * m_cameraSpeed;
		m_pos.Z += float(cos(radianRot.Y)) * m_cameraSpeed;
		m_pos.Y += float(sin(radianRot.X)) * m_cameraSpeed;
		m_planetLookat = -1;
	}

	if (key == 'e')
	{
		m_pos.Y += float(cos(radianRot.Y)) * m_cameraSpeed;
		m_planetLookat = -1;
	}
	if (key == 'c')
	{
		m_pos.Y -= float(cos(radianRot.Y)) * m_cameraSpeed;
		m_planetLookat = -1;
	}

	if (key == 'd')
	{
		m_pos.X += float(cos(radianRot.Y)) * m_cameraSpeed;
		m_pos.Z += float(sin(radianRot.Y)) * m_cameraSpeed;
		m_planetLookat = -1;
	}

	if (key == 'a')
	{
		m_pos.X -= float(cos(radianRot.Y)) * m_cameraSpeed;
		m_pos.Z -= float(sin(radianRot.Y)) * m_cameraSpeed;
		m_planetLookat = -1;
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
		m_pos.X = 0;
		m_pos.Z = 25;
		m_pos.Y = 0;
		m_planetLookat = 0;
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
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void InputManager::HandleMouseDown(Vector2D buttonAndState, Vector2D mousePos)
{
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
}

