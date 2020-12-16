/*!
 * Example largely inspired by
 * http://www.vishalchovatiya.com/memento-design-pattern-in-modern-cpp/
 */

#include <iostream>
#include <ostream>
#include <cstdint>
#include <vector>
#include <memory>

/*!
 * @brief Originator object
 *        The object we want to produce snapshots from.
 *        Is responsible for creating Mementos objects and restoring
 *        itself with it.
 * 
 *        In that case, he is also storing and managing its Mementos but
 *        in a real-life example, this should be delegated to a CareTaker.
 * 
 *        Also note that in this example, there is absolutely no lifecycle 
 *        management for Mementos and their history can grow indefinetly.
 */
class BankAccount
{
    struct Memento;

public:
    BankAccount(const int32_t p_balance) : m_balance(p_balance)
    {
        m_changes.emplace_back( std::make_shared<const Memento>(m_balance) );
    }

    const std::shared_ptr<const Memento> deposit(int32_t p_amount)
    {
        m_balance += p_amount;
        m_changes.emplace_back( std::make_shared<const Memento>(m_balance) );
        return m_changes[m_current++];
    }

    void restore(const std::shared_ptr<const Memento>& p_memento)
    {
        if ( p_memento )
        {
            m_balance = p_memento->m_balance;
            m_changes.push_back(p_memento);
            m_current = m_changes.size() - 1;
        }
    }

    const std::shared_ptr<const Memento> undo()
    {
        if ( m_current > 0 )
        {
            m_balance = m_changes[--m_current]->m_balance;
            return m_changes[m_current];
        }

        return {};
    }

    const std::shared_ptr<const Memento> redo()
    {
        if ( (m_current + 1) < m_changes.size() )
        {
            m_balance = m_changes[++m_current]->m_balance;
            return m_changes[m_current];
        }
        return {};
    }

    friend std::ostream& operator<<(std::ostream &p_os, const BankAccount &p_ac)
    {
        return p_os << "balance: " << p_ac.m_balance;
    }

private:
    int32_t  m_balance{0};
    uint32_t m_current{0};

    /*!
     * @brief Memento object
     *        Immutable object, its states are fixed at
     *        creation by its constructor.
     * 
     *        Used by Originator to save/load a state.
     * 
     *        Note that this Memento does not provide any
     *        interface but in real-life examples, you might
     *        want to provide one like "getProductionDate()"
     *        or "getProductionCause()"...
     */
    struct Memento
    {
        Memento() = delete;
        Memento(int32_t p_balance) : m_balance(p_balance) {}
        int32_t m_balance;
    };

    /*!
     * The history of changes.
     */
    std::vector<std::shared_ptr<const Memento> > m_changes;
};

int main()
{
    BankAccount myAcc{1000};
    myAcc.deposit(200);
    myAcc.deposit( 50);

    std::cout << myAcc << "\n";

    myAcc.undo();
    std::cout << "Undo 1: " << myAcc << "\n";
    myAcc.undo();
    std::cout << "Undo 2: " << myAcc << "\n";
    myAcc.redo();
    std::cout << "Redo 2: " << myAcc << "\n";

    return EXIT_SUCCESS;
}
