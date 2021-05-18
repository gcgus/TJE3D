#include "road.h"
#include "shader.h"
#include "texture.h"

Road::Road()
{
    
    this->texture= Texture::Get("data/Road/7.tga");
    this->mesh = Mesh::Get("data/Road/Road.obj");
    //this->shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");

}

void Road::update()
{
}

