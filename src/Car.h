#pragma once

#include "EntityMesh.h"
#include "physics.h"
#include "CarCommons.h"



class Car : public EntityMesh
{
public:
	//Contenedor de las strings de el enum
	static const std::string enum_string[3];

	CarType type;

	Physics physics;

	Car();


	void update();
};

