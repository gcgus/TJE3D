#include "endStageFail.h"
#include "world.h"
#include "game.h"
#include "StageManager.h"
#include "input.h"
#include "persistency.h"
#include "PlayStage.h"

endStageFail::endStageFail()
{
	gui = renderGUI(Game::instance->window_width, Game::instance->window_height);
	endOptionF = RESTARTF;
}

void endStageFail::init()
{
	endOptionF = RESTARTF;
}

void endStageFail::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	World::instance->camera->enable();

	//set flags
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	World::instance->render();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	gui.renderGUIMenu(420, 100, 500, 150, Texture::Get("data/level_fail.png"), Game::instance->time, false, false);

	gui.renderGUIMenu(410, 295, 150, 150, Texture::Get("data/end_options.png"), Game::instance->time, false, false);

	if (endOptionF == RESTARTF)
	{
		gui.renderGUIMenu(320, 240, 10, 10, Texture::Get("data/dot.png"), Game::instance->time, false, false);
	}
	else if (endOptionF == NEXT_LEVELF)
	{
		gui.renderGUIMenu(320, 290, 10, 10, Texture::Get("data/dot.png"), Game::instance->time, false, false);
	}
	else if (endOptionF == EMENUF)
	{
		gui.renderGUIMenu(320, 340, 10, 10, Texture::Get("data/dot.png"), Game::instance->time, false, false);
	}

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	SDL_GL_SwapWindow(Game::instance->window);
}

void endStageFail::update(double* dt)
{
	if (Input::wasKeyPressed(SDL_SCANCODE_DOWN) && int(endOptionF) < 2) {
		endOptionF = EndOptionsF(int(endOptionF) + 1);
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_UP) && int(endOptionF) > 0) {
		endOptionF = EndOptionsF(int(endOptionF) - 1);
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_RETURN)) {
		std::stringstream ssF;

		switch (endOptionF)
		{
		case RESTARTF:
			ssF << "data/Maps/level" << World::instance->current_level + 1 << ".txt";
			std::cout << ssF.str().c_str() << std::endl;
			World::instance->loadWorld(ssF.str().c_str());

			r_stageF = dynamic_cast<PlayStage*>(StageManager::instance->getStage(PLAY));
			r_stageF->init();
			break;
		case NEXT_LEVELF:
			ssF << "data/Maps/level" << World::instance->current_level + 2 << ".txt";
			std::cout << ssF.str().c_str() << std::endl;
			World::instance->loadWorld(ssF.str().c_str());

			r_stageF = dynamic_cast<PlayStage*>(StageManager::instance->getStage(PLAY));
			r_stageF->init();

			World::instance->current_level = World::instance->current_level + 1;

			Game::instance->current_stage = StageManager::instance->getStage(PLAY);

			break;
		case EMENUF:
			Game::instance->current_stage = StageManager::instance->getStage(START);
			break;
		default:
			break;
		}
	}
}