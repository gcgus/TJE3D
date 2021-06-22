#pragma once
#include "Stage.h"
#include "collision.h"

class PlayStage:public Stage
{
public:
	bool start;
	bool finish;

	double elapsed;
	double last;
	double endtime;

	PlayStage();

	void init();
	void end(double *dt);

	void render();
	void update(double* dt);



private:
	float acc;
};

