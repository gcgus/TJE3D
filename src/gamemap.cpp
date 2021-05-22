#include "gamemap.h"

Gamemap::Gamemap()
{
}

void Gamemap::render()
{

	for (int i = 0; i < roadmap.size(); i++)
	{
		roadmap[i]->render();
	}
}
