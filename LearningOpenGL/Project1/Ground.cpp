#include "Ground.h"


Ground::Ground()
{
}


Ground::~Ground()
{
}
void Ground::SetDim(Vector3D dim)
{
	m_Dim = dim;
}
void Ground::Draw()
{
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-m_Dim.X, -m_Dim.Y, -m_Dim.Z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(m_Dim.X, -m_Dim.Y, -m_Dim.Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(m_Dim.X, -m_Dim.Y, m_Dim.Z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-m_Dim.X, -m_Dim.Y, m_Dim.Z);
	glEnd();
	glPushMatrix();


	glPopMatrix();
}
