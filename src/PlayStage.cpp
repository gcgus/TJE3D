#include "PlayStage.h"
#include "world.h"
#include "camera.h"
#include "utils.h"
#include "game.h"
#include "input.h"
#include "player.h"
#include "shader.h"
#include "framework.h"

World* world = NULL;
Shader* shader = NULL;
sPlayer player;
Matrix44 camPos;

PlayStage::PlayStage()
{
	acc = 0;
	//Asigna los singletons
	world = World::instance;

	player.car = &world->pool_cars[0];

	player.car->in_use = 1;

	camPos = player.car->model;


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

	world->camera->eye = camPos * Vector3(0.0f, 100.0f, 150.0f);
	world->camera->center = camPos * Vector3(0.0f, 0.0f, 0.0f);

	drawGrid();

	//render the FPS, Draw Calls, etc
	drawText(2, 2, getGPUStats(), Vector3(1, 1, 1), 2);

	SDL_GL_SwapWindow(Game::instance->window);
}

void PlayStage::update(double* dt)
{
	float speed = 100.0f * acc * *dt;
	player.car->model.translate(0.0f, 0.0f, -1.0f * speed);
	camPos.translate(0.0f, 0.0f, -1.0f * speed);

	//std::cout << acc << std::endl;
	
	//world->camera->move(Vector3(0.0f, -0.75f, 0.75f) * speed);

	if (Input::isKeyPressed(SDL_SCANCODE_UP))
	{
		if (acc < 3)
		{
			acc += 0.0075f;
		}
	}
	if (Input::isKeyPressed(SDL_SCANCODE_DOWN))
	{
		if (acc >= 0.015)
		{
			acc -= 0.015f;
		}
		if (acc < 0.015)
		{
			acc = 0;
		}
	}
	if (Input::isKeyPressed(SDL_SCANCODE_LEFT))
	{
		player.car->model.rotate(90.0f * *dt * DEG2RAD, Vector3(0.0f, -1.0f, 0.0f));
	}
	if (Input::isKeyPressed(SDL_SCANCODE_RIGHT))
	{
		player.car->model.rotate(90.0f * *dt * DEG2RAD, Vector3(0.0f, 1.0f, 0.0f));
	}
}



