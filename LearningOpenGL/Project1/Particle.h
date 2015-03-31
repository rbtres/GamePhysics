//============================================================================================
//Create by Robert Bethune
//Particle
//An object with a life and returns if it should die;
//Creation Date 1/18/2015
//============================================================================================
#pragma once
#include "PhysicsObject.h"
//============================================================================================
class Particle :
	public PhysicsObject
{
public:
//--------------------------------------------------------------------------------------------
	
	Particle();
	~Particle();
//--------------------------------------------------------------------------------------------
	
//--------------------------------------------------------------------------------------------
	inline void SetLife(int life){ m_Life = life; }
	void UpdateLife(float msTime);

	bool Alive();
//--------------------------------------------------------------------------------------------
//============================================================================================
private:
//--------------------------------------------------------------------------------------------
	int m_Life;
//--------------------------------------------------------------------------------------------
};
//============================================================================================

