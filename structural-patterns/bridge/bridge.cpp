#include <iostream>
#include <string>

/**
 * @brief : Bridge Design Pattern
 *
 * Intent: Split a large class into two separate hierarchies :
 *    - abstraction
 *    - implementation
 * that you can develop independently.
 */

/**
 * @brief : Implementator - Interface for the "implementation" hierarchy.
 *
 * Note : It doesn't have to match the abstraction interface but should
 *        provide primitive operations that are needed in every cases.
 */
class Implementator {
public:
  virtual ~Implementator() = default;
  virtual std::string PrimitiveOperation(void) const = 0;
};

/**
 * @brief : ConcreteImplementator - Concrete implementation of a logic
 */
class ConcreteImplementatorA : public Implementator {
public:
  std::string PrimitiveOperation(void) const override { return someLogic(); }

private:
  std::string someLogic(void) const { return "Operation performed by ConcreteImplementatorA.\n"; }
};

class ConcreteImplementatorB : public Implementator {
public:
  std::string PrimitiveOperation(void) const override { return someOtherLogic(); }

private:
  std::string someOtherLogic(void) const { return "Operation performed by ConcreteImplementatorB.\n"; }
};

/**
 * @brief : Abstraction - Interface for the "abstraction".
 *          Maintains a reference to an object of the
 *         "Implementator" hierarchy it delegates the work to.
 */
class Abstraction {
public:
  Abstraction(Implementator& p_impl) : pimpl(p_impl) {}
  virtual ~Abstraction() = default;

  virtual std::string Operation(void) const {
    return "Abstraction : " + pimpl.PrimitiveOperation();
  }

protected:
  Implementator& pimpl;
};

/**
 * @brief : RefinedAbstraction - Extend the "abstraction" interface
 *          without the need to change the Implementator.
 */
class RefinedAbstraction : public Abstraction {
public:
  RefinedAbstraction(Implementator& p_impl) : Abstraction(p_impl) {}
  ~RefinedAbstraction() = default;

  std::string Operation(void) const override {
    return "RefinedAbstraction: " + pimpl.PrimitiveOperation();
  }
};

/**
 * @brief : Client code - depends only on the Abstraction class.
 */
void ClientCode(const Abstraction& p_abstraction) {
  std::cout << p_abstraction.Operation() << std::endl;
}

int main() {
  ConcreteImplementatorA implA;
  ConcreteImplementatorB implB;
  Abstraction  abstA(implA), abstB(implB);
  ClientCode(abstA);
  ClientCode(abstB);

  return 0;
}