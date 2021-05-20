#include "road.h"
#include "shader.h"
#include "texture.h"

Road::Road()
{
    
    this->texture= Texture::Get("data/Road/Texture.tga");
    this->mesh = Mesh::Get("data/Road/roadstraight.obj");
    shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");//CARGAR LOS SHADER AQUI ES IGUAL LOCURA

}

