#include "SkyBox.h"

#include "SOIL.h"

SkyBox::SkyBox()
{
	std::vector<char*> stars;
	stars.push_back("Stars/Stars_front.jpg");
	stars.push_back("Stars/Stars_back.jpg");
	stars.push_back("Stars/Stars_left.jpg");
	stars.push_back("Stars/Stars_right.jpg");
	stars.push_back("Stars/Stars_top.jpg");
	stars.push_back("Stars/Stars_bottom.jpg");

	LoadSkybox(stars);
}


SkyBox::~SkyBox()
{
}
void SkyBox::LoadSkybox(std::vector<char*> locname)
{
	int width;
	int height;
	glGenTextures(1, &m_Tex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Tex);
	
	//_front _back _left _right _top _bottom
	unsigned char* image = SOIL_load_image(locname[0], &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	image = SOIL_load_image(locname[1], &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 1, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	image = SOIL_load_image(locname[2], &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 2, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	image = SOIL_load_image(locname[3], &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 3, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	image = SOIL_load_image(locname[4], &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 4, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	image = SOIL_load_image(locname[5], &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 5, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}

void SkyBox::RenderSkyBox()
{
	glDepthMask(0);
	glEnable(GL_TEXTURE_CUBE_MAP);

	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Tex);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//gluQuadricDrawStyle(m_SkyBox, GLU_FILL);
	//gluQuadricTexture(m_SkyBox, GL_TRUE);
	//gluQuadricNormals(m_SkyBox, GLU_SMOOTH);

	glPushMatrix();

	glDepthMask(1);

}