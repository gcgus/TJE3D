#pragma once

class Stage
{
public:
	Stage();

	virtual void render();
	virtual void update(double* dt);
};

