#pragma once
#include "RigidBody.h"
#include <string>
#include "GL/glut.h"
class RigidRender :
	public RigidBody
{
public:
	RigidRender();
	~RigidRender();
	inline void SetTexture(std::string fileName){ m_TexFileName = fileName; LoadTexture(); }
	inline void SetMass(float mass){ m_inverseMass = 1/mass; }
	virtual void Draw();
protected:
	virtual void renderObject() = 0;
	void LoadTexture();
	std::string m_TexFileName;
	GLUquadric* m_Sphere;
	GLuint m_Texture;
};

