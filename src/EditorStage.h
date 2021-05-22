#pragma once
#include "Stage.h"
class EditorStage : public Stage
{
public:

	EditorStage();

	void render();
	void update(double* dt);
	void controlCamera(double* dt);
	void saveMap();
};

