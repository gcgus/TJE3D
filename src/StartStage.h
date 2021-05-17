#pragma once
#include"Stage.h"
class StartStage : public Stage
{
public:
	StartStage();

	void render();
	void update(double* dt);
};

