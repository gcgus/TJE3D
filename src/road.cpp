#include "road.h"
#include "shader.h"
#include "texture.h"
#include "roadborder.h"
#include "roadroad.h"

Road::Road(RoadType type,int s)
{
	this->roadtype = type;
	this->size = s;

	this->addChild(new roadborder(type,s));
	this->addChild(new roadroad(type,s));
}
