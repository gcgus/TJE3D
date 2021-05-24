#pragma once
#include "Stage.h"
#include "Car.h"
class EditorStage : public Stage
{

public:
	CarType current_car;

	EditorStage();


	void render();
	void update(double* dt);
	void controlCamera(double* dt);
	void saveMap();

};

