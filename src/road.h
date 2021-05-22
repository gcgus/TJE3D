#pragma once
#include "EntityMesh.h"

enum RoadType : uint8 { STRAIGHT, LEFT,RIGHT };

class Road : public EntityMesh
{
public:
    RoadType roadtype;
    Road(RoadType type);

};


