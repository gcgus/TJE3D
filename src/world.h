
#include "Car.h"
#include "camera.h"

const int MAX_CARS = 5;

class World
{
public:
    
    //delete the copy constructor
    //World(const World&) = delete;
    
    static World* instance;

    int cars_init;

    //Camera
    Camera *camera;
    
    //Pool de cars
    Car pool_cars[MAX_CARS];
    
    //constructor
    World();
    
};
