#pragma once
#include "PhysicsObject.h"
#include <string>
class GameObject : public PhysicsObject
{
public:
	GameObject();
	~GameObject();
	inline void SetTexture(std::string fileName){ m_TexFileName = fileName.c_str; }
	void Draw();
	
protected:
	void LoadTexture();
	char* m_TexFileName;
	GLUquadric* m_Sphere;
	GLuint* m_Texture;
	float m_Radius;

};

