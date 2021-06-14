#include "StartStage.h"
#include "game.h"
#include "input.h"
#include "StageManager.h"

const std::string StartStage::enumm_string[] = { "NEW_GAME", "LOAD_GAME", "EDITOR_START", "EXIT_GAME" };

StartStage::StartStage()
{
	this->option = NEW_GAME;
}

void StartStage::render(){
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
	drawText(100, 100, "START STAGE PROVISIONAL, FLECHAS CAMBIAR DE OPCION, ENTER ENTRAR", Vector3(1, 1, 1), 2);

	std::stringstream ss;

	ss << "opcion seleccionada:" << enumm_string[int(option)];
	drawText(100, 200, ss.str(), Vector3(1, 1, 1), 2);


	SDL_GL_SwapWindow(Game::instance->window);
}

void StartStage::update(double* dt)
{
	if (Input::wasKeyPressed(SDL_SCANCODE_RIGHT)) {
	this->option = StartOptions(int(this->option) + 1);
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_LEFT)) {
		this->option = StartOptions(int(this->option) -1);
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_RETURN)) {
		switch (option)
		{
		case NEW_GAME:
			Game::instance->current_stage = StageManager::instance->getStage(PLAY);
			break;
		case LOAD_GAME:
			Game::instance->current_stage = StageManager::instance->getStage(LEVELS);
			break;
		case EDITOR_START:
			Game::instance->current_stage = StageManager::instance->getStage(EDITOR);
			break;
		case EXIT_GAME:
			Game::instance->must_exit = true;
			break;
		default:
			break;
		}
	}
}
