#pragma once

#include "includes.h"
#include "utils.h"
#include "Car.h"

class Collision
{
public:
	Vector3 center;

	Collision();

	void carCollision(Car* car);
	void endCollision();
};
