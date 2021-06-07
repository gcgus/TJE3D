#include "physics.h"


Physics::Physics(/*CarType type*/)
{
	a = 0;
	v = 0;
	fDrag = 0;
	fRR = 0;
	fTotal = 0;
	move = true;

	/*if (type == 1)
	{
		engineForce = 300;
	}
	else
	{
		engineForce = 0;
	}*/
	engineForce = 300;
}

void Physics::update(double* dt)
{
	if (move)
	{
		v = Speed(dt);
	}
	else
	{
		if (v < 0.1f)
		{
			v = 0;
			fTotal = 0;
		}
		else
		{
			v = Brake(dt);
		}
	}
}