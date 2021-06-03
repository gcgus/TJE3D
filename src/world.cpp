#include "world.h"
#include "game.h"
#include "extra/textparser.h"
#include "road.h"


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

void World::render()
{
	glDisable(GL_DEPTH_TEST);
	drawSky();
	glEnable(GL_DEPTH_TEST);
	//Llamada al render para todos los coches de la pool
	for (int i = 0; i < cars_init; i++)
	{
		if (pool_cars[i].in_use) {
			pool_cars[i].render();
		}
	}

	roadmap.render();
}

void World::drawSky()
{
}

void World::loadWorld(const char* path)
{
	TextParser tp;
	tp.create(path);

	char* w;

	while (w = tp.getword())
	{

		std::string str(w);
		if (str == "R") {
			RoadType t= RoadType(tp.getint());
			int s = tp.getint();
			Road *temp = new Road(t,s);
			
			//Leemos la model matrix
			for (int i = 0; i < 16; i++)
			{
				temp->model.m[i] = tp.getfloat();
			}
			this->roadmap.addChild(temp);
			tp.nextline();
		}

	}
	std::cout << "Map Loaded" << std::endl;
	
}

