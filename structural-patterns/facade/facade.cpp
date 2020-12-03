#include <iostream>
#include <string>
#include <memory>

/**
 * @brief: Facade Design Pattern provides a simplified interface 
 *         to a possibly complex subsystem.
 */

// -------- SUBSYSTEMS -------- //
/**
 * @brief: The Subsystem can accept requests either from the facade or client
 * directly. In any case, to the Subsystem, the Facade is yet another client
 */
class Subsystem1 {
 public:
  std::string Operation1(void) const { return "\tSS1: Init done!\n";      }
  // ...
  std::string OperationN(void) const { return "\tSS1: Operation done!\n"; }
};

/**
 * @brief: Some facades can work with multiple subsystems at the same time.
 */
class Subsystem2 {
 public:
  std::string Operation1(void) const { return "\tSS2: Init done!\n";      }
  // ...
  std::string OperationN(void) const { return "\tSS2: Operation done!\n"; }
};


// ---------- FACADE ---------- //

/**
 * @brief: The Facade class provides a simple interface to the 
 *         complex logic of one or several subsystems. The Facade delegates 
 *         the client requests to the appropriate objects within the subsystem. 
 *         The Facade is also responsible for managing their lifecycle. 
 *         All of this shields the client from the undesired complexity 
 *         of the subsystem.
 */
class Facade {
 public:
  /*!
   * @brief: The _Facade_ class is responsible
   *         for its subsystem initialization and life cycle.
   */
  Facade(void) : m_ss1(std::unique_ptr<Subsystem1>()),
                 m_ss2(std::unique_ptr<Subsystem2>()) {}

  ~Facade() = default;

  /*!
   * @brief: The Facade's methods are convenient shortcuts to the sophisticated
   * functionality of the subsystems. However, clients get only to a fraction
   * of a subsystem's capabilities.
   */
  void Operation(void) const {

    std::string result = "Subsystems Initializing...\n";
    result += m_ss1->Operation1();
    result += m_ss2->Operation1();

    result += "Subsystems Performing the required request...\n";
    result += m_ss1->OperationN();
    result += m_ss2->OperationN();

    std::cout << result << std::endl;
  }

 protected:
  std::unique_ptr<Subsystem1> m_ss1;
  std::unique_ptr<Subsystem2> m_ss2;
};

// ------- CLIENT CODE ------- //
/*!
 * @brief: The client code works with complex subsystems 
 *         through a simple interface provided by the Facade.
 *         It does not even have to know about the subsystems 
 *         existence.
 */
void ClientCode(Facade& myFacade) {
  // ...
  myFacade.Operation();
  // ...
}

// ---------- MAIN ---------- //

int main() {

  Facade facade;
  ClientCode(facade);

  return 0;
}