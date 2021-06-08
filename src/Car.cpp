#include "Car.h"
#include "shader.h"
#include "texture.h"
#include <sstream>

const std::string Car::enum_string[] = {"CAR1","CAR2","CAR3","CAR4","CAR5","CAR6","TRUCK1","TRUCK2" ,"TRUCK3","BUS1","BUS2","BUS3" };

Car::Car(CarType cartype)
{
	this->type = cartype;

	std::stringstream ss;
	ss << "data/Cars/car"<<int(cartype)+1<<".obj";

	this->mesh = Mesh::Get(ss.str().c_str());
	//Cargar la textura(ahora mismo es temporal, la textura difiere segun el coche
	this->texture= Texture::Get("data/Cars/Car_03.tga");
	//Lo mismo con el mesh
	//this->mesh = Mesh::Get("data/Cars/car8.obj");
	//
	shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");

}

void Car::update()
{
}
