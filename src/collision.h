#pragma once

#include "includes.h"
#include "utils.h"
#include "Car.h"
#include "road.h"

class Collision
{
public:
	Vector3 center;

	Collision();

	void carCollision(Car* car);

	void wallCollision(EntityMesh* border,RoadType type ,double* dt);

	void endCollision();
};
