#include "PlayStage.h"
#include "world.h"

World* world = NULL;

PlayStage::PlayStage()
{
	//Asigna la instancia de world
	world = World::instance;
	//LINEA DE PRUEBA, AÑADE DOS COCHES
	world->pool_cars[0].in_use = 1;
	world->pool_cars[1].in_use = 1;

	
}

void PlayStage::render()
{
	//Llamada al render para todos los coches de la pool
	for (int i = 0; i < length; i++)
	{

	}
}

void PlayStage::update(float* dt)
{
}
