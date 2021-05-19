#include "world.h"


World* World::instance = NULL;

World::World(){
	assert(instance == NULL);

	instance = this;

	
}

