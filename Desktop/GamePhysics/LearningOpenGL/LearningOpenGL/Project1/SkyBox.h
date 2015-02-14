#pragma once
#include <string>
#include "SOIL.h"
#include "GL/glut.h"
#include "GL\glxew.h"

class SkyBox
{
public:
	SkyBox();
	~SkyBox();

	void LoadSkybox(std::string locname);
	void RenderSkyBox();
	void ReleaseSkybox();
private:
	GLuint m_Tex;
	char* m_FileLoc;
	
};

