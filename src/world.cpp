#include "world.h"
#include "game.h"
#include "extra/textparser.h"
#include "road.h"
#include "mesh.h"
#include "shader.h"


World* World::instance = NULL;


World::World(){
	assert(instance == NULL);

	instance = this;

	//create our camera
	camera = new Camera();
	camera->lookAt(Vector3(0.f, 100.f, 100.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f)); //position the camera and point to 0,0,0
	camera->setPerspective(70.f, Game::instance->window_width / (float)Game::instance->window_height, 0.1f, 10000.f); //set the projection, we want to be perspective

	//INIT DEL SKYBOX
	skyBox = new EntityMesh();
	skyBox->mesh = Mesh::Get("data/space_cubemap.ASE");
	skyBox->texture = Texture::Get("data/sky.tga");
	skyBox->shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");

	ground = new EntityMesh();
	ground->mesh = new Mesh();
	ground->mesh->createPlane(10000);
	ground->texture = Texture::Get("data/grass2.tga");
	ground->shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	ground->model.translate(0, -5, 0);
	ground->setTiling(3.0f);

	//Number of cars at new level(provisional)
	cars_init = 5;
}

void World::render()
{

	drawSkyGround();
	glEnable(GL_DEPTH_TEST);
	//Llamada al render para todos los coches de la pool
	for (int i = 0; i < pool_cars.size(); i++)
	{
		if (pool_cars[i]->in_use) {
			pool_cars[i]->render();
		

		}
	}

	roadmap.render();


}

void World::drawSkyGround()
{
	skyBox->model.setTranslation(this->camera->eye.x, this->camera->eye.y, this->camera->eye.z);
	glDisable(GL_DEPTH_TEST);
	skyBox->render();
	ground->render();
}

void World::loadWorld(const char* path)
{
	//First reset everything:
	//CAMBIARA LA SKYBOX??
	//REVISAR COMO SE ELIMINAN LAS COSASS Y SI SE ACUMULA MEMORIA ETC ETC
	this->pool_cars.clear();
	this->roadmap.children.clear();



	//Then read the texfile
	TextParser tp;
	tp.create(path);

	this->wintime = tp.getfloat();

	char* w;

	while (w = tp.getword())
	{

		std::string str(w);

		if (str == "R") {
			RoadType t= RoadType(tp.getint());
			int s = tp.getint();
			Road *temp = new Road(t,s);
			
			//Leemos la model matrix


			for (int i = 0; i < 16; i++)
			{
				temp->model.m[i] = tp.getfloat();
			}
			this->roadmap.addChild(temp);
			tp.nextline();
		}
		else if (str == "C") {
			CarType t = CarType(tp.getint());
			int road = tp.getint();
			this->AddCar(t,road);
			Car* temp = pool_cars.back();

			for (int i = 0; i < 16; i++)
			{
				temp->model.m[i] = tp.getfloat();
			}

			tp.nextline();
		}

	}
	player.car = pool_cars[0];

	setEnd();

	std::cout << "Map Loaded" << std::endl;
	
}

void World::AddCar(CarType type,int road){
	Car *temp = new Car(type);
	temp->roadpos = road;
	temp->in_use = 1;
	pool_cars.push_back(temp);
}

void World::setEnd()
{
	Road* temp = dynamic_cast<Road*>(this->roadmap.children.back());
	
	this->endorigin = temp->model.getTranslation();
	this->endorigin.x = this->endorigin.x - ((69.9) / 2) * temp->size;
	this->endorigin.y = 0;
	this->enddir = Vector3(0, 0, 1);

	std::cout << "x y z" << endorigin.x <<"  "<< endorigin.y << "  " << endorigin.z << std::endl;
	std::cout << "x y z" << enddir.x << "  " << enddir.y << "  " << enddir.z << std::endl;
	


}
