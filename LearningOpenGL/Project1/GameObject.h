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
	
protected:
	void LoadTexture();
	std::string m_TexFileName;
	GLUquadric* m_Sphere;
	GLuint m_Texture;
	float m_Radius;

};

