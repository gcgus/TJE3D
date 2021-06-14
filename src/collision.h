#pragma once

#include "includes.h"
#include "utils.h"
#include "Car.h"

class Collision
{
public:
	Vector3 center;

	Car* carCollision(Car* player, Car* car)
	{
		center = player->model.getTranslation() + Vector3(0, 1, 0);

		Vector3 coll;
		Vector3 collnorm;

		if (car->mesh->testSphereCollision(car->model, center, 30, coll, collnorm))
		{
			//Car* temp;
			//temp = player;
			player->in_use = false;
			player = car;
		}
		return player;
	}
};
