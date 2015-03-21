#include "GameObject.h"
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
	gluQuadricTexture(m_Sphere, m_Texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	gluQuadricDrawStyle(m_Sphere, GLU_FILL);
	gluQuadricTexture(m_Sphere, GL_TRUE);
	gluQuadricNormals(m_Sphere, GLU_SMOOTH);

	glPushMatrix();

	glTranslatef(m_Pos.X, m_Pos.Y, m_Pos.Z);

	gluSphere(m_Sphere, m_Radius, 25, 25);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void GameObject::LoadTexture()
{
	int width;
	int height;
	//Turn texture on to be safe before using them.
	glEnable(GL_TEXTURE_2D);
	//Generates than binds textures
	glGenTextures(1, m_Texture);
	glBindTexture(GL_TEXTURE_2D, *m_Texture);

	//uses SOIL free gl library to do create image, than binds it to a GL_TEXTURE_2D
	//this is binded to the GLuint from above free it once its binded. The data is still there
	unsigned char* image = SOIL_load_image(m_TexFileName, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	m_Sphere = gluNewQuadric();
}