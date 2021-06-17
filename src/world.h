
#include "Car.h"
#include "camera.h"
#include "player.h"

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
    //Car pool_cars[MAX_CARS];
    std::vector<Car*>pool_cars;

    //player
    sPlayer player;
    
    //MAPA, carretera+proprs
    Entity roadmap;

    EntityMesh *skyBox;

    //ENDZONE
    Vector3 endorigin;
    Vector3 enddir;

    //Level
    int current_level;

    //Tiempo para ganar
    float wintime;

    //constructor
    World();
    
    void render();

    void drawSky();

    void loadWorld(const char* path);
    void AddCar(CarType type);
    void setEnd();
};
