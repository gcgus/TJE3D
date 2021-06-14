#pragma once
#include "Stage.h"



class LevelStage: public Stage
{
public:
	int selected_level;
	
	LevelStage();

	void render();
	void update(double* dt);

};

