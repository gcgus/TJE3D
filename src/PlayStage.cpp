#include "PlayStage.h"
#include "world.h"
#include "camera.h"
#include "utils.h"
#include "game.h"

World* world = NULL;

PlayStage::PlayStage()
{
	//Asigna los singletons
	world = World::instance;



	//LINEA DE PRUEBA, AÑADE DOS COCHES le cambio la posi a uno de ellos
	world->pool_cars[0].in_use = 1;
	world->pool_cars[1].in_use = 1;
	world->pool_cars[1].model.rotate(80, Vector3(0, 1, 0));
	world->pool_cars[1].model.translate(70, 10, 0);

	
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

	//Llamada al render para todos los coches de la pool
	for (int i = 0; i < world->cars_init; i++)
	{
		if (world->pool_cars[i].in_use) {
			world->pool_cars[i].render();
		}
	}

	drawGrid();

	//render the FPS, Draw Calls, etc
	drawText(2, 2, getGPUStats(), Vector3(1, 1, 1), 2);

	//swap between front buffer and back buffer
	SDL_GL_SwapWindow(Game::instance->window);
}

void PlayStage::update(float* dt)
{
}
