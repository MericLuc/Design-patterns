/*!
 * Example from Udemy course at
 * https://www.udemy.com/course/patterns-cplusplus/
 */

#include <iostream>
#include <string>

/*!
 * @brief Abstract Class
 *        Defines the skeleton of the algorithm
 *        that shall be implemented by subclasses
 *        to become particular algorithms.
 * 
 * Note : Here, every method is pure virtual but we
 *        can provide default implementation if some
 *        parts of the algorithms are always the same.
 * 
 * Note : We could also make some method non-virtual
 *        and not let clients override them if we have
 *        some parts of the algorithms that should not
 *        be modified. 
 */
class Game
{
public:
    explicit Game(int p_nb) : m_nb(p_nb) {}

    void run()
    {
        start();
        while ( !have_winner() ) { take_turn(); }
        std::cout << "Player " << get_winner() << " wins.\n";
    }

protected:
    virtual void start      () = 0;
    virtual bool have_winner() = 0;
    virtual void take_turn  () = 0;
    virtual int  get_winner () = 0;

    int m_cur{0};
    int m_nb;
};

/*!
 * @brief Concrete Class
 *        Implements the skeleton of the algorithm.
 */
class Chess : public Game
{
public:
    explicit Chess() : Game{2} {}

protected:
    void start() override { std::cout << "Starting a game of chess\n"; }

    // The condition is silly, but you get the point.
    bool have_winner() override { return m_turn == m_max; }

    void take_turn  () override
    {
        std::cout << "Turn " << m_turn++ << " taken by player " << m_cur << "\n";
        m_cur = (m_cur + 1) % m_nb;
    }

    int get_winner  () override { return m_cur; }

private:
    int              m_turn{ 0};
    static const int m_max {10};
};

int main()
{
    Chess chess;
    chess.run();

    return EXIT_SUCCESS;
}
