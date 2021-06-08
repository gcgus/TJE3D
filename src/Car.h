#pragma once
#include "EntityMesh.h"

enum CarType : uint8 { CAR1, CAR2, CAR3, CAR4, CAR5, CAR6, TRUCK1, TRUCK2, TRUCK3, BUS1, BUS2, BUS3, COUNT };


class Car : public EntityMesh
{
public:
	//Contenedor de las strings de el enum
	static const std::string enum_string[12];

	CarType type;

	Car(CarType cartype);

	void update();
};

