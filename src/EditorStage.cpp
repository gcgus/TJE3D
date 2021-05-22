#include "EditorStage.h"
#include "input.h"
#include "world.h"
#include "game.h"



EditorStage::EditorStage()
{
}

void EditorStage::render()
{
	//set the clear color (the background color)
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//set the camera as default
	World::instance->camera->enable();

	//set flags
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	World::instance->render();

	drawGrid();

	//render the FPS, Draw Calls, etc
	drawText(2, 2, getGPUStats(), Vector3(1, 1, 1), 2);

	SDL_GL_SwapWindow(Game::instance->window);
}

void EditorStage::update(double* dt)
{
	if (Input::wasKeyPressed(SDL_SCANCODE_UP)) {
		Road* temp = new Road(STRAIGHT);
		temp->model.translate(World::instance->gamemap.roadmap.size()*2,0,0);
		World::instance->gamemap.roadmap.push_back(temp);
	};
	if (Input::wasKeyPressed(SDL_SCANCODE_LEFT)) {
		Road* temp = new Road(LEFT);
		temp->model.translate(World::instance->gamemap.roadmap.size() * 2, 0, 0);
		World::instance->gamemap.roadmap.push_back(temp);
	};
	if (Input::wasKeyPressed(SDL_SCANCODE_RIGHT)) {
		Road* temp = new Road(RIGHT);
		temp->model.translate(World::instance->gamemap.roadmap.size() * 2, 0, 0);
		World::instance->gamemap.roadmap.push_back(temp);
	};
	controlCamera(dt);

}

void EditorStage::controlCamera(double* dt)
{

	float speed = 100 * *dt;

	//mouse input to rotate the cam
	if ((Input::mouse_state & SDL_BUTTON_LEFT)) //is left button pressed?
	{
		World::instance->camera->rotate(Input::mouse_delta.x * 0.005f, Vector3(0.0f, -1.0f, 0.0f));
		World::instance->camera->rotate(Input::mouse_delta.y * 0.005f, World::instance->camera->getLocalVector(Vector3(-1.0f, 0.0f, 0.0f)));
	}

	//async input to move the camera around
	if (Input::isKeyPressed(SDL_SCANCODE_LSHIFT)) speed *= 10; //move faster with left shift
	if (Input::isKeyPressed(SDL_SCANCODE_W) ) World::instance->camera->move(Vector3(0.0f, 0.0f, 1.0f) * speed);
	if (Input::isKeyPressed(SDL_SCANCODE_S) ) World::instance->camera->move(Vector3(0.0f, 0.0f, -1.0f) * speed);
	if (Input::isKeyPressed(SDL_SCANCODE_A) ) World::instance->camera->move(Vector3(1.0f, 0.0f, 0.0f) * speed);
	if (Input::isKeyPressed(SDL_SCANCODE_D) ) World::instance->camera->move(Vector3(-1.0f, 0.0f, 0.0f) * speed);


}
