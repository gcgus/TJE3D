#pragma once
#include "Stage.h"

class PlayStage:public Stage
{
public:
	PlayStage();

	void render();
	void update(double* dt);



private:
	float acc;
};

