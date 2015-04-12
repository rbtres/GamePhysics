#include "SkyBox.h"
//https://www.opengl.org/discussion_boards/showthread.php/182361-Skybox
#include "SOIL.h"
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
SkyBox::SkyBox()
{

}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
SkyBox::~SkyBox()
{
}
//--------------------------------------------------------------------------------------------
void SkyBox::Init()
{
	//this method in case I wanted to save things later.
	//As well this can be moved into an init requiring the vector
	//Could do double vector for future.
	//this way it can be in a texture class.
	//Call get textures(vector<char*> location, vector<GLuint> texLoc);
	std::vector<char*> stars;
	stars.push_back("Stars/blood_front.jpg");
	stars.push_back("Stars/blood_back.jpg");
	stars.push_back("Stars/blood_left.jpg");
	stars.push_back("Stars/blood_right.jpg");
	stars.push_back("Stars/blood_top.jpg");
	//stars.push_back("Stars/Stars_bottom.jpg");

	LoadSkybox(stars[0], &m_Front);
	LoadSkybox(stars[1], &m_Back);
	LoadSkybox(stars[2], &m_Left);
	LoadSkybox(stars[3], &m_Right);
	LoadSkybox(stars[4], &m_Top);
	//LoadSkybox(stars[5], &m_Bottom);
}
//--------------------------------------------------------------------------------------------
void SkyBox::LoadSkybox(char* locname, GLuint* tex)
{
	int width;
	int height;
	//Turn texture on to be safe before using them.
	glEnable(GL_TEXTURE_2D);
	//Generates than binds textures
	glGenTextures(1, tex);
	glBindTexture(GL_TEXTURE_2D, *tex);
	
	//uses SOIL free gl library to do create image, than binds it to a GL_TEXTURE_2D
	//this is binded to the GLuint from above free it once its binded. The data is still there
	unsigned char* image = SOIL_load_image(locname, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void SkyBox::RenderSkyBox()
{
	//Renders a cube in basic format than around you.
	//Currently having problems because disabling lighting causes white background
	//and with lighting on it reflects etc. weird problem.
	//each GLuint tells which piece of a skybox is rendering there
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	GLfloat width = 50;
	GLfloat height = 50;
	GLfloat length = 50;

	glBindTexture(GL_TEXTURE_2D, m_Top);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(width, height, -length);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-width, height, -length);
	glTexCoord2d(0.0, 1.0f);
	glVertex3f(-width, height, length);
	glTexCoord2d(0.0, 0.0f);
	glVertex3f(width, height, length);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_Front);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_QUADS);
	
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(width, height, length);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(-width, height, length);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-width, -height, length);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(width, -height, length);
	
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_Left);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(-width, height, -length);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-width, -height, -length);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-width, -height, length);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-width, height, length);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_Back);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(width, -height, -length);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-width, -height, -length);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(-width, height, -length);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(width, height, -length);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_Right);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(width, height, -length);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(width, height, length);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(width, -height, length);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(width, -height, -length);

	glEnd();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_TEXTURE_2D);
}
//--------------------------------------------------------------------------------------------
