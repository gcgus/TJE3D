#pragma once
#include "EntityMesh.h"

enum CarType : uint8 { CAR1, CAR2, CAR3 };


class Car : public EntityMesh
{
public:
	//Contenedor de las strings de el enum
	static const std::string enum_string[3];

	CarType type;

	Car();

	void update();
};

