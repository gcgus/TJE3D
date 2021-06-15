#include "LevelStage.h"
#include "game.h"
#include "persistency.h"
#include "input.h"
#include "world.h"
#include "StageManager.h"

LevelStage::LevelStage()
{
this->selected_level = 0;
}

void LevelStage::render()
{
	//RENDER TEMPORAL
	//set the clear color (the background color)
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	//set flags
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);



	//render the FPS, Draw Calls, etc
	drawText(2, 2, getGPUStats(), Vector3(1, 1, 1), 2);
	drawText(100, 100, "LEVEL STAGE PROVISIONAL, FLECHAS CAMBIAR DE OPCION, ENTER ENTRAR", Vector3(1, 1, 1), 2);

	std::stringstream ss;

	ss << "Level selected:" << this->selected_level;
	drawText(100, 200, ss.str(), Vector3(1, 1, 1), 2);


	SDL_GL_SwapWindow(Game::instance->window);
}

void LevelStage::update(double* dt)
{
	if (Input::wasKeyPressed(SDL_SCANCODE_RIGHT)) {
		if (this->selected_level >= persistency::instance->current_max)this->selected_level = 0;
		else this->selected_level++;
	}
	
	if (Input::wasKeyPressed(SDL_SCANCODE_LEFT)) {
		if (this->selected_level <= 0)this->selected_level = persistency::instance->current_max;
		else this->selected_level--;
	}

	if (Input::wasKeyPressed(SDL_SCANCODE_RETURN)) {
		//INICIAR EL NIVEL Y PASAR A LA PLAYSTAGE
		std::stringstream ss;
		ss <<"data/Maps/level"<<this->selected_level + 1<<".txt";
		World::instance->loadWorld(ss.str().c_str());

		World::instance->current_level = this->selected_level;

		Game::instance->current_stage = StageManager::instance->getStage(PLAY);
	}
}

