#include <iostream>
#include <string>
#include <functional>

/* ------------------- LEGACY CODE  ------------------- */

/*!
 * @brief : Interface of the Target. (AbstractTarget)
 */
class Beverage {
public :
    virtual void prepare(void) const = 0;
};

/*!
 * @brief : Target implementing the Interface we need to
 *          make our Adaptee compatible with.
 */
class Coffee : public Beverage {
public :
    void prepare(void) const override { 
        std::cout << "Brewing the coffee" << std::endl; 
    }
};

/*!
 * @brief : Interface already shipped to the client
 */
void prepare_drink(Beverage &drink) { drink.prepare(); } 

/* -------------- CODE INTRODUCED LATER  -------------- */

class FruitJuice {
public :
    void squeeze(void) const { 
        std::cout << "Squeezing the FruitJuice" << std::endl; 
    }
};

/* ------------------ ADAPTER CODE  ------------------- */

/*!
 * @brief Adapter making Adaptee (JuiceMaker) compatible 
 *        with Target (Beverage) interface.
 */
class Adapter : public Beverage {
private:
    std::function<void()>    m_request;

public:
    Adapter(const Beverage*   b ) { m_request = [b] ( ) { b->prepare(); }; }
    Adapter(const FruitJuice* f ) { m_request = [f] ( ) { f->squeeze(); }; }

    void prepare(void) const { m_request(); }
};

int main() {
    Coffee     coffee;
    FruitJuice fruitJuice;

    Adapter adp1(&coffee);
    prepare_drink(adp1);

    Adapter adp2(&fruitJuice);
    prepare_drink(adp2);

    return 0;
}