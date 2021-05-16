

template <class T>
class world
{
public:
    static T& GetInstance()
    {
        static T worldinstance; //asumir T posee un constructor por defecto (T será Entity)
        return worldinstance;
    }
    
};


class world : public world<world>
{
friend class world<world>; //para dar acceso al constructor privado de Solo Uno

public:

    
private:
    
    world(){}
    
}



/*
class Singleton
{
public:
    //delete the copy constructor
    Singleton(const Singleton&) = delete;
    
    static Singleton& GetInstance()
    {
        return s_instance;
    }
    
    void Function(){}
    static float Float() { return Get().IFloat(); }
    
private:
    float IFloat() { return member; }
    
    Singleton(){} //constructor is private meaning it can't be instantiated outside of within this class
    
    memeber = 0.5f;
    
    static Singleton s_instance; //Static instance
};

Singleton Singleton::s_instance; // Definition of static member

int main()
{
    Singleton& instance = Singleton::Get(); //To avoid the copy of data
    Singleton::Get().Function(); //I can access the singleton instance and call the function like this
}
*/
