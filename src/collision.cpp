#include "collision.h"
#include "world.h"




Collision::Collision(){

}



void Collision::carCollision(Car* car)
{
	center = World::instance->player.car->model.getTranslation() + Vector3(0, 1, 0);

	Vector3 coll;
	Vector3 collnorm;

	if (car->mesh->testSphereCollision(car->model, center, car->mesh->radius/2, coll, collnorm))
		{
		//Car* temp;
		//temp = player;
		World::instance->player.car->in_use = false;
		World::instance->player.car = car;
		std::cout << int(World::instance->player.car->type) << std::endl;
	}
}

void Collision::wallCollision(EntityMesh* border, RoadType type, bool side, double* dt)
{
	center = World::instance->player.car->model.getTranslation() + Vector3(0, 1, 0);

	Vector3 coll;
	Vector3 collnorm;

	Matrix44 a_min1;
	Matrix44 a_min2;
	Matrix44 a_max1;
	Matrix44 a_max2;
	Matrix44 b_min;
	Matrix44 b_max;

	/*matrix1.translate(World::instance->player.car->mesh->box.center.x, World::instance->player.car->mesh->box.center.y, World::instance->player.car->mesh->box.center.z);
	matrix1.scale(World::instance->player.car->mesh->box.halfsize.x, World::instance->player.car->mesh->box.halfsize.y, World::instance->player.car->mesh->box.halfsize.z);
	matrix2.translate(border->mesh->box.center.x, border->mesh->box.center.y, border->mesh->box.center.z);
	matrix2.scale(border->mesh->box.halfsize.x, border->mesh->box.halfsize.y, border->mesh->box.halfsize.z);*/

	a_min1.translate(World::instance->player.car->mesh->aabb_min.x, World::instance->player.car->mesh->aabb_min.y, World::instance->player.car->mesh->aabb_min.z);
	a_max1.translate(World::instance->player.car->mesh->aabb_max.x, World::instance->player.car->mesh->aabb_max.y, World::instance->player.car->mesh->aabb_max.z);
	a_min2.translate(World::instance->player.car->mesh->aabb_max.x, World::instance->player.car->mesh->aabb_min.y, World::instance->player.car->mesh->aabb_min.z);
	a_max2.translate(World::instance->player.car->mesh->aabb_min.x, World::instance->player.car->mesh->aabb_max.y, World::instance->player.car->mesh->aabb_max.z);
	b_min.translate(border->mesh->aabb_min.x, border->mesh->aabb_min.y, border->mesh->aabb_min.z);
	b_max.translate(border->mesh->aabb_max.x, border->mesh->aabb_max.y, border->mesh->aabb_max.z);

	a_min1 = a_min1 * World::instance->player.car->model;
	a_max1 = a_max1 * World::instance->player.car->model;
	a_min2 = a_min2 * World::instance->player.car->model;
	a_max2 = a_max2 * World::instance->player.car->model;
	b_min = b_min * border->getGlobalMatrix();
	b_max = b_max * border->getGlobalMatrix();

	//border->mesh->testSphereCollision(border->model, center, World::instance->player.car->mesh->radius, coll, collnorm);
	if (side == 0)
	{
		if (AABBIntersectionright(a_min1, a_max1, b_min, b_max))
		{
			//Vector3 push_away = normalize(coll - center) * *dt;

			//Vector3 targetPos = World::instance->player.car->model.getTranslation() - push_away;

			//targetPos.y = World::instance->player.car->model.getTranslation().y;

			//World::instance->player.car->model.translate(targetPos.x, targetPos.y, targetPos.z);

			World::instance->player.car->model.rotate(5.0f * DEG2RAD, Vector3(0.0f, -1.0f, 0.0f));

		}
	}
	if (side == 1)
	{
		if (AABBIntersectionleft(a_min2, a_max2, b_min, b_max))
		{
			World::instance->player.car->model.rotate(5.0f * DEG2RAD, Vector3(0.0f, 1.0f, 0.0f));
		}
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

bool Collision::AABBIntersectionright(Matrix44 a_min, Matrix44 a_max, Matrix44 b_min, Matrix44 b_max)
{
	//std::cout << b->aabb_min.z << std::endl;
	if (a_min.getTranslation().x > b_max.getTranslation().x || a_min.getTranslation().z > b_max.getTranslation().z)
	{
		return false;
	}
	if (a_max.getTranslation().x < b_min.getTranslation().x || a_max.getTranslation().z < b_min.getTranslation().z)
	{
		return false;
	}
	return true;
}

bool Collision::AABBIntersectionleft(Matrix44 a_min, Matrix44 a_max, Matrix44 b_min, Matrix44 b_max)
{
	//std::cout << b->aabb_min.z << std::endl;
	if (a_min.getTranslation().x > b_max.getTranslation().x || a_min.getTranslation().z > b_max.getTranslation().z)
	{
		return false;
	}
	if (a_max.getTranslation().x < b_min.getTranslation().x || a_max.getTranslation().z < b_min.getTranslation().z)
	{
		return false;
	}
	return true;
}