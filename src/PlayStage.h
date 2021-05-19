#pragma once
#include "Stage.h"

class PlayStage:public Stage
{
public:
	PlayStage();

	void render();
	void update(double* dt);

	//funcion provisional para controlar la camara
	void controlCamera(double* dt);
};

