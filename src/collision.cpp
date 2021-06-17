#include "collision.h"
#include "world.h"




Collision::Collision(){

}



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

void Collision::endCollision()
{
	Vector3 coll;
	Vector3 collnorm;

	if (World::instance->player.car->mesh->testRayCollision(World::instance->player.car->model, World::instance->endorigin, World::instance->enddir, coll, collnorm, 23423423423424234)) {
		std::cout << "END OF THE LEVEL REACHED" << std::endl;
	}

}

