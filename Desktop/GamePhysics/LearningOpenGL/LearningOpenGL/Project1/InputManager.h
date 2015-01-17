#include "Vector2D.h"
#pragma once
class InputManager
{
public:
	InputManager();
	~InputManager();

	void Init();

private:
	Vector2D m_oldPos;
	Vector2D m_movedPos;
};

