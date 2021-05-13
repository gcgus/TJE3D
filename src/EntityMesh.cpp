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

	if (shader)
	{
		//enable shader
		shader->enable();

		//upload uniforms
		shader->setUniform("u_color", Vector4(1, 1, 1, 1));
		shader->setUniform("u_viewprojection", camera->viewprojection_matrix);
		shader->setUniform("u_texture", texture, 0);
		shader->setUniform("u_model", model);
		//shader->setUniform("u_time", time);

		//do the draw call
		mesh->render(GL_TRIANGLES);

		//disable shader
		shader->disable();
	}
}

void EntityMesh::update(float elapsed_time)
{
}
