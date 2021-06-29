#include "endStage.h"
#include "world.h"
#include "game.h"
#include "StageManager.h"
#include "input.h"
#include "persistency.h"
#include "PlayStage.h"

endStage::endStage()
{
	gui = renderGUI(Game::instance->window_width, Game::instance->window_height);

	endOption = RESTART;
}

void endStage::render()
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

	gui.renderGUIMenu(410, 200, 500, 250, Texture::Get("data/tit.tga"), Game::instance->time, false, false);

	gui.renderGUIMenu(410, 425, 150, 150, Texture::Get("data/end_options.png"), Game::instance->time, false, false);

	if (endOption == RESTART)
	{
		gui.renderGUIMenu(330, 400, 10, 10, Texture::Get("data/dot.png"), Game::instance->time, false, false);
	}
	else if (endOption == NEXT_LEVEL)
	{
		gui.renderGUIMenu(330, 475, 10, 10, Texture::Get("data/dot.png"), Game::instance->time, false, false);
	}
	else if (endOption == EMENU)
	{
		gui.renderGUIMenu(330, 550, 10, 10, Texture::Get("data/dot.png"), Game::instance->time, false, false);
	}

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	SDL_GL_SwapWindow(Game::instance->window);
}

void endStage::update(double *dt)
{
	if (Input::wasKeyPressed(SDL_SCANCODE_DOWN) && int(endOption) < 2) {
		endOption = EndOptions(int(endOption) + 1);
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_UP) && int(endOption) > 0) {
		endOption = EndOptions(int(endOption) - 1);
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_RETURN)) {
		switch (endOption)
		{
		case RESTART:
			ss << "data/Maps/level" << World::instance->current_level + 1 << ".txt";
			std::cout << ss.str().c_str() << std::endl;
			World::instance->loadWorld(ss.str().c_str());

			r_stage = dynamic_cast<PlayStage*>(StageManager::instance->getStage(PLAY));
			r_stage->init();
			break;
		case NEXT_LEVEL:
			ss << "data/Maps/level" << World::instance->current_level + 2 << ".txt";
			std::cout << ss.str().c_str() << std::endl;
			World::instance->loadWorld(ss.str().c_str());

			r_stage = dynamic_cast<PlayStage*>(StageManager::instance->getStage(PLAY));
			r_stage->init();
			break;
		case EMENU:
			Game::instance->current_stage = StageManager::instance->getStage(START);
			break;
		default:
			break;
		}
	}
}