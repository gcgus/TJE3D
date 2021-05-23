#pragma once
#include "road.h"
class Gamemap
{
public:
	std::vector<Road*> roadmap;

	Gamemap();

	void render();

	void loadMap(const char* path);
};

