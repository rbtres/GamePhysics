#include "Planet.h"
#include <GL\glut.h>
#include "SOIL.h"
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Planet::Planet(std::string name)
{
	m_Name = name;
	m_Pos = Vector3D::Zero;
	m_Vel = Vector3D::Zero;
	m_Acc = Vector3D::Zero;
	m_Rot = Vector3D::Zero;

	m_InitPos = m_Pos;
	m_InitVel = m_Vel;
	m_InitAcc = m_Acc;
	m_InitRot = m_Rot;

	m_Mass = 0;
	m_Force = Vector3D::Zero;
	m_Damping = 0.9999f;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Planet::~Planet()
{
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void Planet::LoadImg()
{	
	int width;
	int height;
	//same as SkyBox.cpp load
	glGenTextures(1, &m_Tex);
	glBindTexture(GL_TEXTURE_2D, m_Tex);

	unsigned char* image = SOIL_load_image(m_FileLoc, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	m_Sphere = gluNewQuadric();
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void Planet::Draw()
{
	//This draw reqires an actual gluQuadrice texture over just the GLuint like skybox
	//Create it in new than set it at each draw to the current text.
	//Not binding nad setting before tends to use just one texture for all planets
	//glEnable(GL_TEXTURE_2D);

	//glBindTexture(GL_TEXTURE_2D, m_Tex);
	//gluQuadricTexture(m_Sphere, m_Tex);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//gluQuadricDrawStyle(m_Sphere, GLU_FILL);
	//gluQuadricTexture(m_Sphere, GL_TRUE);
	//gluQuadricNormals(m_Sphere, GLU_SMOOTH);

	//glPushMatrix();

	//glTranslatef(m_Pos.X, m_Pos.Y, m_Pos.Z);

	//gluSphere(m_Sphere,m_Radius, 25, 25);
	//
	//glPopMatrix();
	//glDisable(GL_TEXTURE_2D);
}
//--------------------------------------------------------------------------------------------

