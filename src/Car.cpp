#include "Car.h"
#include "shader.h"
#include "texture.h"

const std::string Car::enum_string[] = {"CAR1","CAR2","CAR3"};

Car::Car()
{
	//Cargar la textura(ahora mismo es temporal, la textura difiere segun el coche
	this->texture= Texture::Get("data/Cars/Car_03.tga");
	//Lo mismo con el mesh
	this->mesh = Mesh::Get("data/Cars/car1.obj");
	//
	shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");

}

void Car::update()
{
}
