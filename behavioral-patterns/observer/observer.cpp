/*!
 * Example largely inspired by
 * http://www.vishalchovatiya.com/observer-design-pattern-in-modern-cpp
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/*!
 * @brief Observer
 *        Defines an updating interface for objects that
 *        should be notified of changes in a Subject.
 */
template <typename T>
class Observer
{
public :
    virtual ~Observer() = default;
    virtual void update(T &p_src, const std::string &p_field) = 0;

protected:
    Observer() = default;
};

/*!
 * @brief Subject
 *        Defines an interface for adding/removing subcribers
 *        Keeps track of its Observers.
 */
template <typename T>
class Subject
{
public:
    virtual ~Subject() = default;

    void notify(T &p_src, const std::string &p_field)
    {
        for ( auto l_obs : m_observers )
            l_obs->update(p_src, p_field);
    }
    void subscribe  (Observer<T>* p_obs) { m_observers.push_back(p_obs); }
    void unsubscribe(Observer<T>* p_obs) 
    {
        m_observers.erase(std::remove(std::begin(m_observers), 
                                      std::end  (m_observers), 
                                      p_obs), 
                          std::end(m_observers) );
    }

protected:
    Subject() = default;
    
private:
    std::vector<Observer<T>* > m_observers;
};

struct Person : Subject<Person>
{
    void set_age(uint8_t age)
    {
        auto old_can_vote = get_can_vote();
        this->m_age = age;
        notify(*this, "age");

        if (old_can_vote != get_can_vote())
            notify(*this, "can_vote");
    }
    uint8_t get_age() const { return m_age; }
    bool get_can_vote() const { return m_age >= 16; }

private:
    uint8_t m_age{0};
};

struct TrafficAdministration : Observer<Person>
{
    void update(Person &p_src, const std::string &p_field)
    {
        if ( p_field == "age" )
        {
            if ( p_src.get_age() < 17 )
                std::cout << "Not old enough to drive!\n";
            else
            {
                std::cout << "Mature enough to drive!\n";
                p_src.unsubscribe(this);
            }
        }
    }
};

int main()
{
    Person p;
    TrafficAdministration ta;
    p.subscribe(&ta);
    p.set_age(16);
    p.set_age(17);

    return EXIT_SUCCESS;
}