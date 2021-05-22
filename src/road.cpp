#include "road.h"
#include "shader.h"
#include "texture.h"

Road::Road(RoadType type)
{
    this->roadtype = type;
	switch (roadtype)
	{
    case STRAIGHT:
        this->mesh = Mesh::Get("data/Road/roadstraight.obj");
        break;
    case LEFT:
        this->mesh = Mesh::Get("data/Road/roadstraight.obj");
        break;
    case RIGHT:
        this->mesh = Mesh::Get("data/Road/roadstraight.obj");
        break;
	}
    this->texture= Texture::Get("data/Road/Texture.tga");
   


    shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");//CARGAR LOS SHADER AQUI ES IGUAL LOCURA

}

