#pragma once
#include "Stage.h"
#include "collision.h"
#include "renderGUI.h"
#include "utils.h"
//#include <string>

enum PauseOptions : uint8
{
	RESUME, RETRY, MENU
};

class PlayStage:public Stage
{
public:
	bool start;
	bool finish;

	double elapsed;
	double last;
	double endtime;
	std::string timeleft;

	PauseOptions option = RESUME;

	bool pause = false;
	std::stringstream ss;
	PlayStage* r_stage;

	Matrix44 camPos;

	renderGUI guiPause;

	Texture* tex1;
	Texture* tex2;

	PlayStage();

	void init();

	void render();
	void update(double* dt);

	void updateRoadPos(int i);

	void menuController();
	void playerController(double* dt);

	void end(double* dt);
	void endCheck(double* dt);

	void carWallCollision(double* dt);

	void physicsUpdate(double* dt);

	void cameraUpdate(double* dt);

private:
	float acc;
};

