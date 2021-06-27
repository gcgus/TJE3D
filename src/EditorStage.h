#pragma once
#include "Stage.h"
#include "Car.h"
#include "road.h"

enum PropType : uint8 { TREE1, TREE2, ROCK1, ROCK2, BUSH1, BUSH2 };

class EditorStage : public Stage
{

public:
	CarType current_car;
	int roadsize;
	int dir;
	Vector4 vec[4] = { Vector4(1,0,1,-1),Vector4(0,1,1,1),Vector4(-1,0,-1,1),Vector4(0,-1, -1,-1) };
	Vector3 pos;
	Vector3 trans;
	int current_road_i;
	Road* current_road;
	int selected_lane;

	EditorStage();


	void render();
	void update(double* dt);
	void controlCamera(double* dt);
	void saveMap();
	void selectRoad(int cr);
	void AddFront(PropType type);
};