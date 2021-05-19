#include "world.h"
#include "game.h"


World* World::instance = NULL;

World::World(){
	assert(instance == NULL);

	instance = this;

	//create our camera
	camera = new Camera();
	camera->lookAt(Vector3(0.f, 100.f, 100.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f)); //position the camera and point to 0,0,0
	camera->setPerspective(70.f, Game::instance->window_width / (float)Game::instance->window_height, 0.1f, 10000.f); //set the projection, we want to be perspective

	
	//Number of cars at new level(provisional)
	cars_init = 5;
}

