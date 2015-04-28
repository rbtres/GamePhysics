#include "GameObject.h"
#include "ImageHandler.h"
#include "SOIL.h"

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::Draw()
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, m_Texture);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	glPushMatrix();

	glTranslatef(m_Pos.X, m_Pos.Y, m_Pos.Z);

	gluSphere(m_Sphere, m_Radius, 25, 25);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void GameObject::LoadTexture()
{
	//Turn texture on to be safe before using them.

	//Generates than binds textures
	m_Texture = *(ImageHandler::GetInstance()->GetImage(m_TexFileName));

	m_Sphere = gluNewQuadric();
	gluQuadricTexture(m_Sphere, m_Texture);
}