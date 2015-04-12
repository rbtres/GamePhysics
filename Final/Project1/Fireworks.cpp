#include "Fireworks.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
//--------------------------------------------------------------------------------------------
Fireworks::Fireworks()
{

}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
Fireworks::~Fireworks()
{

}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void Fireworks::Init(int maxVel, int minVel, int life)
{
	m_MaxVel = maxVel;
	m_MinVel = minVel;
	m_ParticleLife = life;

	m_ParticleVector = CreateParticle(Vector3D::Zero,1);
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void Fireworks::Update(int msTime)
{
	std::vector<Particle*>::iterator it = m_ParticleVector.begin();
	std::vector<std::vector<Particle*>::iterator> toBeDeleted;
	std::vector<Particle*> toBeAdded;

	while (it != m_ParticleVector.end())
	{
		(*it)->UpdateLife(msTime);
		
		it++;
	}

	it = m_ParticleVector.begin();

	while (it != m_ParticleVector.end() && toBeAdded.size() < (unsigned int) MAXPARTICLES)
	{
		if (!(*it)->Alive())
		{
			int amount = (rand() % 5) + 5;

			std::vector<Particle*> newParticles = CreateParticle((*it)->getPos(), amount);
			std::vector<Particle*>::iterator iter = newParticles.begin();
			while (iter != newParticles.end())
			{
				toBeAdded.push_back(*iter);
				iter++;
			}
		}
		it++;
	}

	for (unsigned int i = 0; i < m_ParticleVector.size(); i++)
	{
		if (!m_ParticleVector[i]->Alive())
		{
			delete m_ParticleVector[i];
			m_ParticleVector.erase(m_ParticleVector.begin() + i);
			i--;
		}
	}
	std::vector<Particle*>::iterator iter = toBeAdded.begin();
	if (m_ParticleVector.size() < (unsigned int)MAXPARTICLES)
	{
		while (iter != toBeAdded.end() && m_ParticleVector.size() < (unsigned int)MAXPARTICLES)
		{
			m_ParticleVector.push_back(*iter);
			iter++;
		}
	}
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
//got the velocity from Jake who took it from a website
//Just using it to caculate real fireworks look
std::vector<Particle*> Fireworks::CreateParticle(Vector3D pos, int amount)
{
	std::vector<Particle*> newParticles;
	for (int i = 0; i < amount; i++)
	{
		Vector3D velocity;
		float randomRotation = (float)(rand() / (float)(RAND_MAX / (M_PI))); //random value 0-PI
		float randomZ = -1.0f + (float)(rand() / (float)(RAND_MAX / (2))); //random value from -1-1
		velocity.X = sqrt(1 - pow(randomZ, 2)) * cos(randomRotation);
		velocity.Y = sqrt(1 - pow(randomZ, 2)) * sin(randomRotation);
		velocity.Z = randomZ;
		velocity = velocity.Normalized() / 10;

		Particle* newParticle = new Particle();
//		newParticle->Init(.1f,pos, velocity);
		newParticle->SetLife(m_ParticleLife);
		newParticles.push_back(newParticle);
	}
	return newParticles;
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void Fireworks::Draw()
{
	/*std::vector<Particle*>::iterator it = m_ParticleVector.begin();

	while (it != m_ParticleVector.end())
	{
		(*it)->Draw();
		it++;
	}*/
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void Fireworks::CleanUp()
{
	for (std::vector<Particle*>::iterator it = m_ParticleVector.begin(); it != m_ParticleVector.end(); ++it)
	{
		delete (*it);
	}
	m_ParticleVector.clear();
}
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void Fireworks::Reset()
{
	CleanUp();
	m_ParticleVector = CreateParticle(Vector3D::Zero, 1);
}
