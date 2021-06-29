#pragma once
#include "Stage.h"
#include "collision.h"
#include "renderGUI.h"
#include "utils.h"
#include "PlayStage.h"

enum EndOptions : uint8
{
	RESTART, NEXT_LEVEL, EMENU
};

class endStage :public Stage
{
public:

	EndOptions endOption;
	renderGUI gui;

	std::stringstream ss;
	PlayStage* r_stage;

	endStage();

	//void init();

	void render();
	void update(double* dt);
};