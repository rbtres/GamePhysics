//============================================================================================
//Create by Robert Bethune
//SkyBox
//Creates a skybox using images from a skybox folder.. Can't see starts like in the
//Skybox image. Could be rendering problem
//using Gl's Soil
//Creation Date 2/14/2015
//============================================================================================
#pragma once
#include <Windows.h>
#include "GL\Glut.h"
#include <vector>
//============================================================================================
class SkyBox
{
public:
	SkyBox();
	~SkyBox();
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
	void LoadSkybox(char* locname, GLuint* te);
	void RenderSkyBox();
	void ReleaseSkybox();
	void Init();
//--------------------------------------------------------------------------------------------
//============================================================================================
private:
	GLuint m_Top, m_Front, m_Back, m_Left, m_Right, m_Bottom;
	char* m_FileLoc;

	
};
//============================================================================================
