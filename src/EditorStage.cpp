#include "EditorStage.h"
#include "input.h"
#include "world.h"
#include "game.h"
#include <iostream>
#include <fstream>  
#include "framework.h"




EditorStage::EditorStage()
{
	dir = 0;
	//temporal
	current_car = CAR1;

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
	drawText(600,2, "Selected:"+Car::enum_string[int(current_car)], Vector3(1, 1, 1), 2);

	SDL_GL_SwapWindow(Game::instance->window);
}

void EditorStage::update(double* dt)
{
	if (Input::wasKeyPressed(SDL_SCANCODE_UP)) {
		Road* temp = new Road(STRAIGHT);

		temp->model.rotateGlobal(dir * M_PI_2, Vector3(0, 1, 0));
		temp->model.translateGlobal(pos.x, pos.y, pos.z);
		
		pos.set(pos.x + 80*2*vec[dir].x, 0, pos.z + 80 * 2 * vec[dir].y);

		std::cout << "dir" << std::endl;
		std::cout << dir << std::endl;
		std::cout<<"xyz"<<std::endl;
		std::cout <<pos.x << std::endl;
		std::cout << pos.y << std::endl;
		std::cout << pos.z << std::endl;
		World::instance->gamemap.roadmap.push_back(temp);
	};
	if (Input::wasKeyPressed(SDL_SCANCODE_LEFT)) {

		Road* temp = new Road(LEFT);

		temp->model.rotateGlobal(dir * M_PI_2, Vector3(0, 1, 0));
		temp->model.translateGlobal(pos.x, pos.y, pos.z);

		World::instance->gamemap.roadmap.push_back(temp);
		dir = (dir + 3) % 4;
		
		pos.set(pos.x+80 * 2 * vec[dir].x, 0, pos.z + 80*2 * vec[dir].y);
		std::cout << "xyz" << std::endl;
		std::cout << pos.x << std::endl;
		std::cout << pos.y << std::endl;
		std::cout << pos.z << std::endl;

	};
	if (Input::wasKeyPressed(SDL_SCANCODE_RIGHT)) {

		Road* temp = new Road(RIGHT);

		temp->model.rotateGlobal(dir * M_PI_2, Vector3(0, 1, 0));
		temp->model.translateGlobal(pos.x, pos.y, pos.z);

		World::instance->gamemap.roadmap.push_back(temp);
		dir = (dir + 1) % 4;

		pos.set(pos.x + 80 * 2 * vec[dir].x, 0, pos.z + 80 * 2 * vec[dir].y);
		std::cout << "xyz" << std::endl;
		std::cout << pos.x << std::endl;
		std::cout << pos.y << std::endl;
		std::cout << pos.z << std::endl;
	};
	if (Input::wasKeyPressed(SDL_SCANCODE_G)) {
		saveMap();
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_L)) {
		std::cout << "Escribe el mapa a cargar:";

		std::string mapname;
		std::cin >> mapname;
		World::instance->gamemap.loadMap(mapname.c_str());

	}
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

void EditorStage::saveMap()
{
	std::string name;
	std::cin >> name;
	std::ofstream outfile("data/Maps/"+name+".txt");

	for (int i = 0; i < World::instance->gamemap.roadmap.size(); i++)
	{
		World::instance->gamemap.roadmap[i];
		outfile << "r" << " " << (int)World::instance->gamemap.roadmap[i]->roadtype  ;
		
		//Escribimos la model matrix
		for (int j = 0; j < 16; j++)
		{
			outfile << " "<<World::instance->gamemap.roadmap[i]->model.m[j];
		}
		outfile<<std::endl;
	}
	outfile.close();
	std::cout << "Map saved at data/Maps/" + name + ".txt" << std::endl;
}



