#pragma once
#include "PhysicsObject.h"
#include <string>
class GameObject : public PhysicsObject
{
public:
	GameObject();
	~GameObject();
	inline void SetTexture(std::string fileName){ m_TexFileName = fileName; LoadTexture(); }
	inline void SetRadius(float radius){ m_Radius = radius; }
	virtual void Draw();
	inline void SetTexture(GLuint* in){ m_Texture = in; m_Sphere = gluNewQuadric();  gluQuadricTexture(m_Sphere, *m_Texture); }
	
protected:
	void LoadTexture();
	std::string m_TexFileName;
	GLUquadric* m_Sphere;
	GLuint* m_Texture;

};

