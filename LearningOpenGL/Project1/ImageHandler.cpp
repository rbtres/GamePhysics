#include "ImageHandler.h"
#include <SOIL.h>
ImageHandler *ImageHandler::m_ImageHandler = new ImageHandler();

ImageHandler::ImageHandler()
{

}


ImageHandler::~ImageHandler()
{
}

GLuint* ImageHandler::AddImage(std::string filePath, std::string name)
{

	GLuint *tex = new GLuint();
	int width;
	int height;
	//Turn texture on to be safe before using them.
	glEnable(GL_TEXTURE_2D);
	//Generates than binds textures
	glGenTextures(1, tex);
	glBindTexture(GL_TEXTURE_2D, *tex);

	//uses SOIL free gl library to do create image, than binds it to a GL_TEXTURE_2D
	//this is binded to the GLuint from above free it once its binded. The data is still there
	unsigned char* image = SOIL_load_image(filePath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	m_Images[name] = tex;

	std::map<std::string, GLuint*>::iterator it;
	for (it = m_Images.begin(); it != m_Images.end(); ++it)
	{
		if (it->first == name)
		{
			return it->second;
		}
	}
	
}
GLuint* ImageHandler::GetImage(std::string name)
{
	return m_Images[name];
}