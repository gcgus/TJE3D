#pragma once
#include "Stage.h"
#include "collision.h"

class PlayStage:public Stage
{
public:
	//Collision *collision;


	PlayStage();

	void init();

	void render();
	void update(double* dt);



private:
	float acc;
};

