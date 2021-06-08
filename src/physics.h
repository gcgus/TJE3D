#pragma once

#include "includes.h"
#include "utils.h"

class Physics
{
public:
	float engineForce;
	float mass = 1500;
	float cDrag = 0.4257;
	float cRR = 12.8;
	float cBraking = 2000.0f;
	float fDrag;
	float fRR;
	float fTotal;
	float a;
	float v;

	bool move;

	Physics(/*CarType type*/);

	float Speed(double* dt)
	{
		fDrag = cDrag * v * v;
		cDrag = cRR * v;

		fTotal = engineForce - fDrag - cDrag;

		a = fTotal / mass;

		return v + *dt *  a;
	}

	float Brake(double* dt)
	{
		fDrag = cDrag * v * v;
		cDrag = cRR * v;

		fTotal = -cBraking - fDrag - cDrag;

		a = fTotal / mass;

		return v + *dt * a;
	}

	void update(double* dt);

};