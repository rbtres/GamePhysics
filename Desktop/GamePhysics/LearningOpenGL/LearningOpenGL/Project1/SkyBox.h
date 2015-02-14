#pragma once
#include <Windows.h>
#include "GL\glew.h"
#include <vector>
class SkyBox
{
public:
	SkyBox();
	~SkyBox();

	void LoadSkybox(std::vector<char*> locname);
	void RenderSkyBox();
	void ReleaseSkybox();
private:
	GLuint m_Tex;
	char* m_FileLoc;

	
};

