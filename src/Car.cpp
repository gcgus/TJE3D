#include "Car.h"
#include "shader.h"

Car::Car()
{
	//Cargar la textura(ahora mismo es temporal, la textura difiere segun el coche
	this->texture= Texture::Get("data/Car_03.tga");
	//Lo mismo con el mesh
	this->mesh = Mesh::Get("data/car1.obj");
	//
	shader = shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");

}

void Car::update()
{
}
