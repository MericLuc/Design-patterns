#include <iostream>
#include <string>


// ------ Elements of the "complex" object to be constructed ------ //
class Wheel {
    public:
        Wheel(int p_size = 0): m_size(p_size) {}
        int getSize(void) const { return m_size; }
    private:
        int m_size;
};

class Engine {
    public:
        Engine(int p_power = 0): m_power(p_power) {}
        int getPower(void) const { return m_power; }

    private:
        int m_power;
};

class Body {
    public:
        Body(std::string&& p_shape = ""): m_shape(p_shape) {}
        std::string getShape(void) const { return m_shape; }

    private:        
        std::string m_shape;
};

// ------ PRODUCT ------ //
/* Defines a common interface to every Products
   In that case, a Car interface is only :
       - 4 Wheels
       - 1 Engine
       - 1 Body
       - A number of seats
*/
class Car {
    public:
        void specifications(void) const {
            std::cout<< "Body : "      << m_body->getShape    () << std::endl;
            std::cout<< "Power : "     << m_engine->getPower  () << std::endl;
            std::cout<< "Seats : "     << m_seats                << std::endl;
            std::cout<< "Tire Size : " << m_wheels[0]->getSize() << std::endl;
        }

        void setBody  (Body  * p_body  ) { m_body   = p_body;   }
        void setEngine(Engine* p_engine) { m_engine = p_engine; }
        void setWheel (Wheel * p_wheel,
                       int     p_pos) { 
            if ( p_pos < 4) { m_wheels[p_pos] = p_wheel; } 
        }
        void setSeats (int p_seats) { m_seats = p_seats; }

    private:
        Wheel * m_wheels[4];
        Engine* m_engine;
        Body  * m_body;
        int     m_seats;
};

// ------ BUILDER ------ //
class Builder{
    public:
        virtual Wheel*  getWheel (void) { return nullptr; }
        virtual Engine* getEngine(void) { return nullptr; }
        virtual Body*   getBody  (void) { return nullptr; }
        virtual int     getSeats (void) { return 4;       }
};

// ------ CONCRETE BUILDER 1 ------ //
class JeepBuilder : public Builder {
    public:
        Wheel*  getWheel (void) override { return new Wheel (40);  }    
        Engine* getEngine(void) override { return new Engine(500); }
        Body*   getBody  (void) override { return new Body("SUV"); }
};

// ------ CONCRETE BUILDER 2 ------ //
class NissanBuilder : public Builder {
    public:
        Wheel*  getWheel (void) override { return new Wheel (12);        }    
        Engine* getEngine(void) override { return new Engine(90);        }
        Body*   getBody  (void) override { return new Body("hatchback"); }
};

// ------ DIRECTOR ------ //
class Director {
    public:
        Director(Builder* p_builder = nullptr) : m_builder(p_builder) {}

        void setBuilder(Builder* p_builder) { m_builder = p_builder; }

        Car* buildCar(void) {

            if ( !m_builder ) { return nullptr; }

            Car* car = new Car();

            car->setBody  ( m_builder->getBody  () );
            car->setEngine( m_builder->getEngine() );
            for ( int i = 0; i < 4; i++ )
                car->setWheel(m_builder->getWheel(), i); 
            car->setSeats ( m_builder->getSeats () );

            return car;
        }

    private:
        Builder* m_builder;
};

int main() {
    Car*          car;
    Director      director;
    JeepBuilder   jeepBuilder;
    NissanBuilder nissanBuilder;

    std::cout<<"--- Jeep ---"<<std::endl;
    director.setBuilder(&jeepBuilder);
    car = director.buildCar();

    if ( car ) {
        car->specifications();
        delete(car);
    }

    std::cout<<std::endl;

    std::cout<<"--- Nissan ---"<<std::endl;
    director.setBuilder(&nissanBuilder);
    car = director.buildCar();
    if ( car ) {
        car->specifications();
        delete(car);
    }

    return 0;
}