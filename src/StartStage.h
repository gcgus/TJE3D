#pragma once
#include"Stage.h"
#include <string>

enum StartOptions : uint8
{
	NEW_GAME, LOAD_GAME, EDITOR_START, EXIT_GAME
};

class StartStage : public Stage
{
public:
	StartOptions option;
	static const std::string enumm_string[4];

	StartStage();

	void render();
	void update(double* dt);
};

