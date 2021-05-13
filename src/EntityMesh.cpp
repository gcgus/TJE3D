#include "EntityMesh.h"
#include "game.h"
#include "shader.h"

EntityMesh::EntityMesh()
{
	shader = NULL;
}

void EntityMesh::render()
{
	//get the last camera that was activated
	Camera* camera = Camera::current;
	Matrix44 model = this->model;

	//enable shader and pass uniforms
	shader->enable();
	shader->setUniform("u_model", model);
	shader->setUniform("u_viewprojection", camera->viewprojection_matrix);

	texture->load("data/Car_03.tga");
	//shader->setTexture("u_texture", texture);

	//render the mesh using the shader //PONER EL SHADER?
	mesh->render(GL_TRIANGLES);

	//disable the shader after finishing rendering
	shader->disable();
}

void EntityMesh::update(float elapsed_time)
{
}
