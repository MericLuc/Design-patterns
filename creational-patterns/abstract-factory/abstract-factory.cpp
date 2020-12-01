#include <iostream>
#include <string>

/**
 * @brief : Interface of productA.
 *          All the variants of productA must implement this interface.
 */
class AbstractProductA {
 public:
  virtual ~AbstractProductA(void) {};
  virtual std::string AFunction(void) const = 0;
};

/**
 * @brief : ConcreteProductA1 and ConcreteProductA2 
 *          both implement the AbstractProductA interface. 
 *          They define products created by the corresponding ConcreteFactory.
 */
class ConcreteProductA1 : public AbstractProductA {
 public:
  std::string AFunction(void) const override { return "Product A1"; }
};

class ConcreteProductA2 : public AbstractProductA {
 public:
  std::string AFunction(void) const override { return "Product A2"; }
};

/**
 * @brief : Interface of another product (productB).
 *          All the variants of productB must implement this interface.
 */
class AbstractProductB {
 public:
  virtual ~AbstractProductB(){};
  virtual std::string AnotherFunction(void) const = 0;
  
  /**
   * @brief : ProductB can collaborate with the ProductA.
   *
   * The Abstract Factory makes sure that all products it creates are of the
   * same variant and thus, compatible.
   */
  virtual std::string AnotherFunctionB(const AbstractProductA& pa) const = 0;
};

/**
* @brief : ConcreteProductB1 and ConcreteProductB2 
 *          both implement the AbstractProductB interface. 
 *          They define products created by the corresponding ConcreteFactory.
 */
class ConcreteProductB1 : public AbstractProductB {
 public:
  std::string AnotherFunction(void) const override { return "Product B1."; }

  std::string AnotherFunctionB(const AbstractProductA &pa) const override {
    const std::string result = pa.AFunction();
    return "B1 collaborating with " + result;
  }
};

class ConcreteProductB2 : public AbstractProductB {
 public:
  std::string AnotherFunction(void) const override { return "Product B2."; }

  std::string AnotherFunctionB(const AbstractProductA &pa) const override {
    const std::string result = pa.AFunction();
    return "B2 collaborating with " + result;
  }
};

/**
 * @brief : Interface that declares the required methods to create 
 *          all the AbstractProducts.
 *          The ConcreteFactory must implement this interface to
 *          create the corresponding ConcreteProducts.
 */
class AbstractFactory {
 public:
  virtual AbstractProductA *CreateProductA(void) const = 0;
  virtual AbstractProductB *CreateProductB(void) const = 0;
};

/**
 * @brief : Produce a family of products that belong to a single
 *          variant. The factory guarantees that resulting 
 *          products are compatible. 
 *
 * @Note : The signatures of the Concrete Factory's methods return 
 *         an abstract product, while inside the method a concrete 
 *         product is instantiated.
 *
 * @Note : The ConcreteFactories are implemented using the
 *         Singleton pattern.
 */
class ConcreteFactory1 : public AbstractFactory {
 public:
  static ConcreteFactory1& getInstance(void) {
    static ConcreteFactory1 f;
    return f;
  }
  AbstractProductA *CreateProductA(void) const override {
    return new ConcreteProductA1();
  }
  AbstractProductB *CreateProductB(void) const override {
    return new ConcreteProductB1();
  }

 private:
  ConcreteFactory1(void){}  /*!< Cstr */
  ~ConcreteFactory1()   {}  /*!< Dstr */

  ConcreteFactory1(const ConcreteFactory1&)            = delete; /*!< Cpy cstrc  */
  ConcreteFactory1(ConcreteFactory1&&)                 = delete; /*!< Mve cstrc  */
  ConcreteFactory1& operator=(const ConcreteFactory1&) = delete; /*!< Cpy assign */
  ConcreteFactory1& operator=(ConcreteFactory1&&)      = delete; /*!< Mve assign */

};


class ConcreteFactory2 : public AbstractFactory {
 public:
  static ConcreteFactory2& getInstance(void) {
    static ConcreteFactory2 f;
    return f;
  }
  AbstractProductA *CreateProductA(void) const override {
    return new ConcreteProductA2();
  }
  AbstractProductB *CreateProductB(void) const override {
    return new ConcreteProductB2();
  }

 private:
  ConcreteFactory2(void){}  /*!< Cstr */
  ~ConcreteFactory2()   {}  /*!< Dstr */

  ConcreteFactory2(const ConcreteFactory2&)            = delete; /*!< Cpy cstrc  */
  ConcreteFactory2(ConcreteFactory2&&)                 = delete; /*!< Mve cstrc  */
  ConcreteFactory2& operator=(const ConcreteFactory2&) = delete; /*!< Cpy assign */
  ConcreteFactory2& operator=(ConcreteFactory2&&)      = delete; /*!< Mve assign */

};

/**
 * @brief : The client code only works with Interfaces
 *          (i.e. AbstractProduct and AbstractFactory) 
 */

void ClientCode(const AbstractFactory& factory) {
  // Create products
  const AbstractProductA *pa = factory.CreateProductA();
  const AbstractProductB *pb = factory.CreateProductB();

  // Use them
  std::cout << "\t" << pb->AnotherFunction()     << "\n";
  std::cout << "\t" << pb->AnotherFunctionB(*pa) << "\n";

  // Release
  delete pa;
  delete pb;
}

int main() {

  std::cout << "Client: Test1:" << std::endl;
  ClientCode(ConcreteFactory1::getInstance());
  std::cout << std::endl;

  std::cout << "Client: Test2:" << std::endl;
  ClientCode(ConcreteFactory2::getInstance());

  return 0;
}