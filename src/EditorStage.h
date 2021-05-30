#pragma once
#include "Stage.h"
#include "Car.h"



class EditorStage : public Stage
{

public:
	CarType current_car;
	int dir;
	Vector2 vec[4]= { Vector2(1,0),Vector2(0,1),Vector2(-1,0),Vector2(0,-1) };
	Vector3 pos;
	Vector3 trans;

	EditorStage();


	void render();
	void update(double* dt);
	void controlCamera(double* dt);
	void saveMap();

};

