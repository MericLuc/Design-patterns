#include <iostream>
#include <string>
#include <vector>

/*!
 * @brief
 *        Defines possible operations
 */
class BankAcc {
public:
    BankAcc() = default;

    bool deposit(int p_amount) {
        if ( p_amount > 0 ) {
            m_balance += p_amount;
            std::cout << "Deposit " << p_amount << " => " << m_balance << std::endl;
            return true;
        }
        return false;
    }

    bool withdraw(int p_amount) {
        if ( p_amount > 0 && p_amount <= m_balance ) {
            m_balance -= p_amount;
            std::cout << "Withdraw " << p_amount << " => " << m_balance << std::endl;
            return true;
        }
        return false;
    }

private:
    int m_balance{0};
};

// -------- COMMAND INTERFACE -------- //
/*!
 * \brief Command interface
 */
class IOperations {
public:
    IOperations(BankAcc& p_ba): m_ba(p_ba) {}
    virtual ~IOperations() = default;

    virtual void DO  (void) = 0;
    virtual void UNDO(void) = 0;

protected:
    bool     m_succeeded{false};
    BankAcc& m_ba;
};

// -------- CONCRETE COMMANDS -------- //
/*!
 * \brief Concrete commands implement the command
 *        interface.
 */
class BankOperations : public IOperations {
public:
    enum Action { deposit, withraw };

    BankOperations(BankAcc& p_ba,
                   Action   p_ac,
                   int      p_amount): IOperations(p_ba), m_action(p_ac), m_amount(p_amount) {}
    virtual ~BankOperations() = default;

    virtual void DO  (void) override {
        switch( m_action )
        {
        case deposit :
            m_succeeded = m_ba.deposit (m_amount);
            break;
        case withraw:
            m_succeeded = m_ba.withdraw(m_amount);
            break;
        }
    }

    virtual void UNDO(void) override {
        if ( !m_succeeded ) { return; }

        switch( m_action )
        {
        case deposit :
            m_succeeded = m_ba.withdraw(m_amount);
            break;
        case withraw:
            m_succeeded = m_ba.deposit (m_amount);
            break;
        }
    }

private:
    Action m_action;
    int    m_amount;
};

// ----------- CLIENT CODE ---------- //
/*!
 * \brief Client creates ConcreteCommand(s) and set their receiver(s).
 *        He interracts with the Receiver via the Commands only.
 */
void clientCode(BankAcc& clientAcc) {
    std::vector<BankOperations> operations =
    {
        {clientAcc, BankOperations::Action::deposit, 200},
        {clientAcc, BankOperations::Action::withraw, 200},
        {clientAcc, BankOperations::Action::deposit, 300},
        {clientAcc, BankOperations::Action::withraw, 800}, // Should fail
        {clientAcc, BankOperations::Action::withraw, 200}
    };

    for ( auto& op : operations ) { op.DO();   } // Do the operations
    for ( auto op  = operations.rbegin();
               op != operations.rend  ();
               op++ )            { op->UNDO(); } // Undo them
}

// ------------- MAIN --------------- //
/*!
 * \brief Command interface
 */
int main()
{
    BankAcc clientAcc;

    clientCode(clientAcc);

    return 0;
}
