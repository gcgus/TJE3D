#include "PlayStage.h"
#include "world.h"
#include "camera.h"
#include "utils.h"
#include "game.h"
#include "input.h"
#include "shader.h"
#include "framework.h"
#include "road.h"

World* world = NULL;
Shader* shader = NULL;
Matrix44 camPos;

Road* temproad;
EntityMesh* wall;

PlayStage::PlayStage()
{
	//Asigna los singletons
	world = World::instance;

	//AÑADE DOS COCHES

	//world->gamemap.loadMap("data/Maps/map.txt");
	//LINEA DE PRUEBA, AÑADE DOS COCHES le cambio la posi a uno de ellos
	//world->pool_cars[0].in_use = 1;
	//world->pool_cars[1].in_use = 1;
	//world->pool_cars[1].model.rotate(80, Vector3(0, 1, 0));
	//world->pool_cars[1].model.translate(70, 0, 0);
	//añadimos carretera de prueba:
	//world->gamemap.roadmap.push_back(new Road());
	
}

void PlayStage::init()
{
	//BoundingBox box = transformBoundingBox(world->player.car->model, world->player.car->mesh->box);


	//world->player.car->physics.move = false;
	//world->player.car->physics.engineForce = 0;
	world->player.car->physics.v = 0;


	//camPos = world->player.car->model;
}


void PlayStage::render()
{

	//set the clear color (the background color)
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//set the camera as default
	world->camera->enable();

	//set flags
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	world->render();

	//Player Camera
	world->camera->eye = camPos * Vector3(-250.0f, 200.0f, 0.0f);
	world->camera->center = camPos * Vector3(0.0f, 0.0f, 0.0f);
	/*world->camera->eye = player.car->model * Vector3(0.0f, 100.0f, 150.0f);
	world->camera->center = player.car->model * Vector3(0.0f, 0.0f, 0.0f);*/
	world->player.car->mesh->renderBounding(world->player.car->model);

	temproad = dynamic_cast<Road*>(world->roadmap.children[1]);
	wall = dynamic_cast<EntityMesh*>(temproad->children[1]);
	wall->mesh->renderBounding(wall->getGlobalMatrix());
	//drawGrid();

	//render the FPS, Draw Calls, etc
	drawText(2, 2, getGPUStats(), Vector3(1, 1, 1), 2);

	SDL_GL_SwapWindow(Game::instance->window);
}

void PlayStage::update(double* dt)
{

	if (!Input::isKeyPressed(SDL_SCANCODE_UP) && world->player.car->physics.move)
	{
		if (world->player.car->physics.engineForce > 50)
		{
			world->player.car->physics.engineForce -= 50;
		}
		else
		{
			world->player.car->physics.engineForce = 0;
		}
	}

	
	//world->camera->move(Vector3(0.0f, -0.75f, 0.75f) * speed);

	if (Input::isKeyPressed(SDL_SCANCODE_UP))
	{
		world->player.car->physics.move = true;

		if (world->player.car->physics.engineForce < 500.0f)
		{
			world->player.car->physics.engineForce += 200.0f;
		}
	}
	if (Input::isKeyPressed(SDL_SCANCODE_DOWN))
	{
		world->player.car->physics.move = false;
	}

	if (Input::isKeyPressed(SDL_SCANCODE_LEFT))
	{
		if (world->player.car->physics.v > -10)
		{
			world->player.car->model.rotate(90.0f * *dt * DEG2RAD, Vector3(0.0f, -1.0f, 0.0f));
			//camPos.rotate(90.0f * *dt * DEG2RAD, Vector3(0.0f, -1.0f, 0.0f));
		}
	}
	if (Input::isKeyPressed(SDL_SCANCODE_RIGHT))
	{
		if (world->player.car->physics.v > -10)
		{
			world->player.car->model.rotate(90.0f * *dt * DEG2RAD, Vector3(0.0f, 1.0f, 0.0f));
			//camPos.rotate(90.0f * *dt * DEG2RAD, Vector3(0.0f, 1.0f, 0.0f));
		}
	}

	for (size_t i = 0; i < world->pool_cars.size(); i++)
	{
		if (world->pool_cars[i] != world->player.car && world->pool_cars[i]->in_use)
		{
			world->player.collision.carCollision(world->pool_cars[i]);
		}
	}

	for (size_t i = 0; i < world->roadmap.children.size(); i++)
	{
		Road* temp = dynamic_cast<Road*>(world->roadmap.children[i]);

		world->player.collision.wallCollision(dynamic_cast<EntityMesh*>(temp->children[0]), temp->roadtype, false,dt);
		world->player.collision.wallCollision(dynamic_cast<EntityMesh*>(temp->children[1]), temp->roadtype, true, dt);

	}

	world->player.collision.endCollision();

	int t = world->player.car->model.m[12];
	int t2 = camPos.m[12];

	//ESTO K ES, aqui llama para q actualizen las físicas
	for (size_t i = 0; i < world->pool_cars.size(); i++)
	{
		if (world->pool_cars[i] == world->player.car)
		{
			world->pool_cars[i]->model.translate(1.0f * 1.5 * world->pool_cars[i]->physics.v, 0.0f, 0.0f);
		}
		else
		{
			world->pool_cars[i]->model.translate(1.0f * world->pool_cars[i]->physics.v, 0.0f, 0.0f);
		}
		world->pool_cars[i]->physics.update(dt);

	}

	//player.car->model.translate(1.0f * player.car->physics.v, 0.0f, 0.0f);
	if (t2<=t)
	{
		//camPos.translate(0.0f, 0.0f, -1.0f * world->player.car->physics.v);
		camPos.translate(1.0f * 1.5 * world->player.car->physics.v, 0.0f, 0.0f);
	}


	//std::cout << wall->getGlobalMatrix().getTranslation().z << std::endl;
	//std::cout << world->player.car->physics.engineForce << std::endl;
}



