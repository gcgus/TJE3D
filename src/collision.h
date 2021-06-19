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

	//void wallCollision(EntityMesh* border,RoadType type, bool side, double* dt);

	void wallCollision(Matrix44 model, RoadType type, int size, bool side, double* dt);

	void endCollision();

	bool AABBIntersectionright(Matrix44 a_min, Matrix44 a_max, Matrix44 b_min, Matrix44 b_max);
	bool AABBIntersectionleft(Matrix44 a_min, Matrix44 a_max, Matrix44 b_min, Matrix44 b_max);
};
