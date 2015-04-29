#include "CubeGround.h"


CubeGround::CubeGround()
{
}


CubeGround::~CubeGround()
{
}

void CubeGround::Draw()
{
	m_InitPos = m_Pos;
	glPushMatrix();
	glTranslatef(m_Pos.X, m_Pos.Y + Scale.Y / 2, m_Pos.Z);
	glScalef(Scale.X,Scale.Y, Scale.Z);
	glutSolidCube(1);
	glPopMatrix();
}