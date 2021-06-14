#include "persistency.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include "extra/textparser.h"

persistency* persistency::instance = NULL;

persistency::persistency()
{
	assert(instance == NULL);

	instance = this;

	this->current_max = 0;
}

void persistency::ReadLevelFile(const char* path)
{
	TextParser tp;
	tp.create(path);

	float t;
	int i = 0;
	this->current_max = tp.getint();
	while (t = tp.getfloat()) {
		this->times[i] = t;
		i++;
	}
}

void persistency::WriteLevelFile(const char* path)
{
	std::ofstream outfile(path);

	outfile << this->current_max << std::endl;

	for (int i = 0; i < this->times.size(); i++)
	{
		outfile << this->times[i] << std::endl;
	}

	outfile.close();
	std::cout << "Map saved at data/Maps/" + std::string(path) << std::endl;
}
