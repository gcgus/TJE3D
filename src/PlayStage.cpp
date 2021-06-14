#include "PlayStage.h"
#include "world.h"
#include "camera.h"
#include "utils.h"
#include "game.h"
#include "input.h"
#include "player.h"
#include "shader.h"
#include "framework.h"
#include "collision.h"

World* world = NULL;
Shader* shader = NULL;
sPlayer player;
Matrix44 camPos;
Collision collision;

PlayStage::PlayStage()
{
	//Asigna los singletons
	world = World::instance;

	//AÑADE DOS COCHES
		//this->AddCar(TRUCK1);
	world->AddCar(CAR1);
	world->AddCar(TRUCK1);

	player.car = world->pool_cars[0];

	player.car->in_use = 1;

	BoundingBox box = transformBoundingBox(player.car->model, player.car->mesh->box);

	world->pool_cars[1]->in_use = 1;
	world->pool_cars[1]->model.translate(70, 0, 0);


	player.car->physics.move = true;
	player.car->physics.engineForce = 0;

	camPos = player.car->model;

	for (size_t i = 0; i <= 1; i++)
	{
		world->pool_cars[i]->model.rotate(3*PI/2, Vector3(0, 1, 0));
	}


	//world->gamemap.loadMap("data/Maps/map.txt");
	//LINEA DE PRUEBA, AÑADE DOS COCHES le cambio la posi a uno de ellos
	//world->pool_cars[0].in_use = 1;
	//world->pool_cars[1].in_use = 1;
	//world->pool_cars[1].model.rotate(80, Vector3(0, 1, 0));
	//world->pool_cars[1].model.translate(70, 0, 0);
	//añadimos carretera de prueba:
	//world->gamemap.roadmap.push_back(new Road());

	
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
	world->camera->eye = camPos * Vector3(0.0f, 200.0f, 250.0f);
	world->camera->center = camPos * Vector3(0.0f, 0.0f, 0.0f);
	/*world->camera->eye = player.car->model * Vector3(0.0f, 100.0f, 150.0f);
	world->camera->center = player.car->model * Vector3(0.0f, 0.0f, 0.0f);*/
	player.car->mesh->renderBounding(player.car->model);

	//drawGrid();

	//render the FPS, Draw Calls, etc
	drawText(2, 2, getGPUStats(), Vector3(1, 1, 1), 2);

	SDL_GL_SwapWindow(Game::instance->window);
}

void PlayStage::update(double* dt)
{

	if (!Input::isKeyPressed(SDL_SCANCODE_UP) && player.car->physics.move)
	{
		if (player.car->physics.engineForce > 50)
		{
			player.car->physics.engineForce -= 50;
		}
		else
		{
			player.car->physics.engineForce = 0;
		}
	}

	
	//world->camera->move(Vector3(0.0f, -0.75f, 0.75f) * speed);

	if (Input::isKeyPressed(SDL_SCANCODE_UP))
	{
		player.car->physics.move = true;

		if (player.car->physics.engineForce < 500.0f)
		{
			player.car->physics.engineForce += 200.0f;
		}
	}
	if (Input::isKeyPressed(SDL_SCANCODE_DOWN))
	{
		player.car->physics.move = false;
	}

	if (Input::isKeyPressed(SDL_SCANCODE_LEFT))
	{
		if (player.car->physics.v > 0)
		{
			player.car->model.rotate(90.0f * *dt * DEG2RAD, Vector3(0.0f, -1.0f, 0.0f));
			//camPos.rotate(90.0f * *dt * DEG2RAD, Vector3(0.0f, -1.0f, 0.0f));
		}
	}
	if (Input::isKeyPressed(SDL_SCANCODE_RIGHT))
	{
		if (player.car->physics.v > 0)
		{
			player.car->model.rotate(90.0f * *dt * DEG2RAD, Vector3(0.0f, 1.0f, 0.0f));
			//camPos.rotate(90.0f * *dt * DEG2RAD, Vector3(0.0f, 1.0f, 0.0f));
		}
	}

	for (size_t i = 1; i < world->pool_cars.size(); i++)
	{
		player.car = collision.carCollision(player.car, world->pool_cars[i]);
	}

	int t = player.car->model.m[14];
	int t2 = camPos.m[14];



	for (size_t i = 0; i <= 1; i++)
	{
		world->pool_cars[i]->model.translate(1.0f * world->pool_cars[i]->physics.v, 0.0f, 0.0f);
		world->pool_cars[i]->physics.update(dt);

	}

	//player.car->model.translate(1.0f * player.car->physics.v, 0.0f, 0.0f);
	if (t2>=t)
	{
		camPos.translate(0.0f, 0.0f, -1.0f * player.car->physics.v);
	}


	//std::cout << world->pool_cars[1]->physics.v << std::endl;
	//std::cout << player.car->physics.move << std::endl;
}



