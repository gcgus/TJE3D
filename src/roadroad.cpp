#include "roadroad.h"
#include "shader.h"
#include "texture.h"

roadroad::roadroad(RoadType type)
{
   
	switch (type)
	{
    case STRAIGHT:
        this->mesh = Mesh::Get("data/Road/Straight1.obj");
        break;
    case LEFT:
        this->mesh = Mesh::Get("data/Road/Curve1.obj");
        this->model.rotate(M_PI_2, Vector3(0, 1, 0));
        break;
    case RIGHT:
        this->mesh = Mesh::Get("data/Road/Curve1.obj");
        break;
	}
    this->texture= Texture::Get("data/Road/roadtexture.tga");
   


    shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");//CARGAR LOS SHADER AQUI ES IGUAL LOCURA

}