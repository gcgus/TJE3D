#include "collision.h"
#include "world.h"




Collision::Collision(){

}



void Collision::carCollision(Car* car)
{
	center = World::instance->player.car->model.getTranslation() + Vector3(0, 1, 0);

	Vector3 coll;
	Vector3 collnorm;

	if (car->mesh->testSphereCollision(car->model, center, car->mesh->radius, coll, collnorm))
		{
		//Car* temp;
		//temp = player;
		World::instance->player.car->in_use = false;
		World::instance->player.car = car;
		std::cout << int(World::instance->player.car->type) << std::endl;
	}
}

void Collision::wallCollision(EntityMesh* border, RoadType type, double* dt)
{
	/*center = World::instance->player.car->model.getTranslation() + Vector3(0, 1, 0);

	Vector3 coll;
	Vector3 collnorm;

	if (car->mesh->testSphereCollision(car->model, center, car->mesh->radius, coll, collnorm))
	{
		Vector3 push_away = normalize(coll - center) * *dt;

		Vector3 targetPos = World::instance->player.car->model.getTranslation() - push_away;

		targetPos.y = World::instance->player.car->model.getTranslation().y;

		World::instance->player.car->model.translate(targetPos.x, targetPos.y, targetPos.z);
	}*/
}

void Collision::endCollision()
{
	Vector3 coll;
	Vector3 collnorm;

	if (World::instance->player.car->mesh->testRayCollision(World::instance->player.car->model, World::instance->endorigin, World::instance->enddir, coll, collnorm, 23423423423424234)) {
		std::cout << "END OF THE LEVEL REACHED" << std::endl;
	}

}

