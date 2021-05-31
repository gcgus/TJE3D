#include "gamemap.h"
#include "extra/textparser.h"

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

void Gamemap::loadMap(const char* path)
{

	TextParser tp;
	tp.create(path);

	char* w;

	while (w = tp.getword())
	{
		std::string str(w);
		if (str == "R") {
			Road *temp = new Road(RoadType(tp.getint()),1);
			
			//Leemos la model matrix
			for (int i = 0; i < 16; i++)
			{
				temp->model.m[i] = tp.getfloat();
			}
			this->roadmap.push_back(temp);
			tp.nextline();
		}

	}
	std::cout << "Map Loaded" << std::endl;
}
