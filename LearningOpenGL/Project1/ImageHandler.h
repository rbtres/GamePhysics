#pragma once
#include <map>
#include <Windows.h>
#include "GL\Glut.h"
#include <string>

class ImageHandler
{
public:
	ImageHandler();
	static ImageHandler* GetInstance(){ if (m_ImageHandler != NULL) return m_ImageHandler; else m_ImageHandler = new ImageHandler();}
	~ImageHandler();
	GLuint* AddImage(std::string filePath, std::string name);
	GLuint* GetImage(std::string name);

	
private:
	std::map<std::string, GLuint*> m_Images;
	static ImageHandler* m_ImageHandler;
	
};

