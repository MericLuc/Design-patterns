/*! SOURCE from https://github.com/RefactoringGuru/design-patterns-cpp/blob/master/src/Flyweight/Conceptual/main.cc */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

/**
 * @brief: Flyweight Design Pattern
 *         Share common parts of state between multiple objects 
 *         instead of keeping every field in each object.
 * common parts of state between multiple objects, instead of keeping all of the
 * data in each object.
 */

struct SharedState
{
    std::string m_brand, m_model, m_color;

    SharedState(const std::string& p_brand, 
                const std::string& p_model, 
                const std::string& p_color)
        : m_brand(p_brand), m_model(p_model), m_color(p_color) {}

    friend std::ostream &operator<<(std::ostream &os, const SharedState &ss)
    {
        return os << "[ " << ss.m_brand << " , " << ss.m_model << " , " << ss.m_color << " ]";
    }
};

struct UniqueState
{
    std::string m_owner;
    std::string m_plates;

    UniqueState(const std::string &owner, 
                const std::string &plates)
        : m_owner(owner), m_plates(plates) {}

    friend std::ostream &operator<<(std::ostream &os, const UniqueState &us)
    {
        return os << "[ " << us.m_owner << " , " << us.m_plates << " ]";
    }
};

class Flyweight
{
private:
    SharedState *m_shared;

public:
    Flyweight(const SharedState *shared_state) : 
        m_shared(new SharedState(*shared_state)) {}

    Flyweight(const Flyweight &other) : 
        m_shared(new SharedState(*other.m_shared)) {}

    ~Flyweight() { delete m_shared; }

    SharedState *shared_state() const { return m_shared; }

    void Operation(const UniqueState &unique_state) const
    {
        std::cout << "Flyweight: Displaying shared (" << *m_shared << ") and unique (" << unique_state << ") state.\n";
    }
};
/**
 * @brief: Flyweight Factory
 *         Creates and manages the Flyweight objects.
 */
class FlyweightFactory
{
private:
    std::unordered_map<std::string, Flyweight> m_flyweights;
    /**
     * @brief: Returns a Flyweight's string hash for a given state.
     */
    std::string GetKey(const SharedState &ss) const
    {
        return ss.m_brand + "_" + ss.m_model + "_" + ss.m_color;
    }

public:
    FlyweightFactory(std::initializer_list<SharedState> share_states)
    {
        for (const SharedState &ss : share_states)
        {
            m_flyweights.insert(std::make_pair<std::string, Flyweight>(this->GetKey(ss), Flyweight(&ss)));
        }
    }

    /**
     * @brief: Returns an existing Flyweight with a given state or creates a new
     * one.
     */
    Flyweight GetFlyweight(const SharedState &shared_state)
    {
        std::string key = GetKey(shared_state);
        if ( m_flyweights.find(key) == m_flyweights.end())
        {
            std::cout << "FlyweightFactory: Can't find a flyweight, creating new one.\n";
            m_flyweights.insert(std::make_pair(key, Flyweight(&shared_state)));
        }
        else
        {
            std::cout << "FlyweightFactory: Reusing existing flyweight.\n";
        }
        return m_flyweights.at(key);
    }

    void ListFlyweights() const
    {
        size_t count = this->m_flyweights.size();
        std::cout << "\nFlyweightFactory: I have " << count << " flyweights:\n";
        for (std::pair<std::string, Flyweight> pair : this->m_flyweights)
        {
            std::cout << pair.first << "\n";
        }
    }
};

// ...
void AddCarToPoliceDatabase(
    FlyweightFactory &ff, const std::string &plates, const std::string &owner,
    const std::string &brand, const std::string &model, const std::string &color)
{
    std::cout << "\nClient: Adding a car to database.\n";
    const Flyweight &flyweight = ff.GetFlyweight({brand, model, color});

    // @brief: The client code either stores or calculates extrinsic state and
    // passes it to the flyweight's methods.
    flyweight.Operation({plates, owner});
}

/**
 * @brief: The client code usually creates a bunch of pre-populated flyweights in
 * the initialization stage of the application.
 */

int main()
{
    FlyweightFactory *factory = new FlyweightFactory(
    {
         {"Chevrolet", "Camaro2018", "pink"}, 
         {"Mercedes Benz", "C300", "black"}, 
         {"Mercedes Benz", "C500", "red"},
         {"BMW", "M5", "red"}, 
         {"BMW", "X6", "white"}
     }
    );

    factory->ListFlyweights();

    AddCarToPoliceDatabase(*factory,
                            "CL234IR",
                            "James Doe",
                            "BMW",
                            "M5",
                            "red");

    AddCarToPoliceDatabase(*factory,
                            "CL234IR",
                            "James Doe",
                            "BMW",
                            "X1",
                            "red");

    factory->ListFlyweights();
    delete factory;

    return 0;
}
