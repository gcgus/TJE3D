#pragma once
#include "Stage.h"
#include "Car.h"



class EditorStage : public Stage
{

public:
	CarType current_car;
	int roadsize;
	int dir;
	Vector4 vec[4]= { Vector4(1,0,1,-1),Vector4(0,1,1,1),Vector4(-1,0,-1,1),Vector4(0,-1, -1,-1) };
	Vector3 pos;
	Vector3 trans;

	EditorStage();


	void render();
	void update(double* dt);
	void controlCamera(double* dt);
	void saveMap();

};

