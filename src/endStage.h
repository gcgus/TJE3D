#pragma once
#include "Stage.h"
#include "collision.h"
#include "renderGUI.h"
#include "utils.h"


class endStage :public Stage
{
public:

	endStage();

	void init();

	void render();
	void update(double* dt);
};