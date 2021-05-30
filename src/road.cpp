#include "road.h"
#include "shader.h"
#include "texture.h"
#include "roadborder.h"
#include "roadroad.h"

Road::Road(RoadType type)
{
	this->roadtype = type;

	this->addChild(new roadborder(type));
	this->addChild(new roadroad(type));
}
