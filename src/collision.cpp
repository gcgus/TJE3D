#include "collision.h"
#include "world.h"

Collision::Collision(){}

void Collision::carCollision(Car* car)
{
	center = World::instance->player.car->model.getTranslation() + Vector3(0, 1, 0);

	Vector3 coll;
	Vector3 collnorm;

	if (car->mesh->testSphereCollision(car->model, center, 30, coll, collnorm))
		{
		//Car* temp;
		//temp = player;
		World::instance->player.car->in_use = false;
		World::instance->player.car = car;
		std::cout << int(World::instance->player.car->type) << std::endl;
	}
}

