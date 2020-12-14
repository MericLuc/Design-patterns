# Design-patterns ![Language](https://img.shields.io/badge/language-C++14-orange.svg) [![License](https://img.shields.io/badge/license-MIT-blue.svg)](./LICENSE.md)

This repository contains a list of **common Design patterns** and their **_c++ implementation_**.

We will also briefly discuss the _situations_ that calls for those designs as well as the _benefits/cons_ you can expect from them. 

Nothing new under the sun, this repository is highly inspirated by the book "[Design patterns](https://fr.wikipedia.org/wiki/Design_Patterns)".

Design patterns divided into three categories as below :

Creational
----------

Those designs are involved in the **objects creation mechanisms**.

They abstract the instantiation process in a way that is the most suitable for the situation and therefore increase the flexibility of the existing code.

 - [**Abstract Factory**](creational-patterns/abstract-factory) [:book:](creational-patterns/abstract-factory/README.md) [:computer:](creational-patterns/abstract-factory/abstract-factory.cpp)
 - [**Builder**](creational-patterns/builder) [:book:](creational-patterns/builder/README.md) [:computer:](creational-patterns/builder/builder.cpp)
 - [**Factory Method**](creational-patterns/factory-method) [:book:](creational-patterns/factory-method/README.md) [:computer:](creational-patterns/factory-method/factory-method.cpp)
  - [**Monostate**](creational-patterns/monostate-pattern) [:book:](creational-patterns/monostate-pattern/README.md) [:computer:](creational-patterns/monostate-pattern/monostate-pattern.cpp)
 - [**Prototype**](creational-patterns/prototype) [:book:](creational-patterns/prototype/README.md) [:computer:](creational-patterns/prototype/prototype.cpp)
 - [**Singleton**](creational-patterns/singleton) [:book:](creational-patterns/singleton/README.md) [:computer:](creational-patterns/singleton/singleton.cpp)
 

Structural
----------
Structural patterns are involved in **classes and objects compositions** to form larger structures.

They allow us to compose interfaces or implementations in order to obtain larger structures that are still flexible.

They are also very usefull to achieve new functionalities using objects compositions.

 - [**Adapter**](structural-patterns/adapter) [:book:](structural-patterns/adapter/README.md) [:computer:](structural-patterns/adapter/adapter.cpp)
 - [**Bridge**](structural-patterns/bridge) [:book:](structural-patterns/bridge/README.md) [:computer:](structural-patterns/bridge/bridge.cpp)
 - [**Composite**](structural-patterns/composite) [:book:](structural-patterns/composite/README.md) [:computer:](structural-patterns/composite/composite.cpp)
 - [**Decorator**](structural-patterns/decorator) [:book:](structural-patterns/decorator/README.md) [:computer:](structural-patterns/decorator/decorator.cpp)
 - [**Facade**](structural-patterns/facade) [:book:](structural-patterns/facade/README.md) [:computer:](structural-patterns/facade/facade.cpp)
 - [**Flyweight**](structural-patterns/flyweight) [:book:](structural-patterns/flyweight/README.md) [:computer:](structural-patterns/flyweight/flyweight.cpp)
 - [**Proxy**](structural-patterns/proxy) [:book:](structural-patterns/proxy/README.md) [:computer:](structural-patterns/proxy/proxy.cpp)

Behavioral
----------
Behavioral patterns are concerned with **algorithms and assignement of responsabilities** between objects.

On class, they use inheritance to distribute behaviour between classes while they use object composition to perform tasks that no single object can carry by itself.

 - [**Chain Of Responsibility**](behavioral-patterns/chain-of-responsability) [:book:](behavioral-patterns/chain-of-responsability/README.md) [:computer:](behavioral-patterns/chain-of-responsability/chain-of-responsability.cpp)
 - [**Command**](behavioral-patterns/command) [:book:](behavioral-patterns/command/README.md) [:computer:](behavioral-patterns/command/command.cpp)
 - [**Interpreter**](behavioral-patterns/interpreter) [:book:](behavioral-patterns/interpreter/README.md) [:computer:](behavioral-patterns/interpreter/interpreter.cpp)
 - [**Iterator**](behavioral-patterns/iterator) [:book:](behavioral-patterns/iterator/README.md) [:computer:](behavioral-patterns/iterator/iterator.cpp)
 - [**Mediator**](behavioral-patterns/mediator) [:book:](behavioral-patterns/mediator/README.md) [:computer:](behavioral-patterns/mediator/Mediator/main.cpp)
 - [**Momento**](behavioral-patterns/momento) [:book:](behavioral-patterns/momento/README.md) [:computer:](behavioral-patterns/momento/momento.cpp)
 - [**Observer**](behavioral-patterns/observer) [:book:](behavioral-patterns/observer/README.md) [:computer:](behavioral-patterns/observer/observer.cpp)
 - [**Specification**](behavioral-patterns/specification-pattern) [:book:](behavioral-patterns/specification-pattern/README.md) [:computer:](behavioral-patterns/specification-pattern/specification-pattern.cpp)
 - [**State**](behavioral-patterns/state) [:book:](behavioral-patterns/state/README.md) [:computer:](behavioral-patterns/state/state.cpp)
 - [**Strategy**](behavioral-patterns/strategy) [:book:](behavioral-patterns/strategy/README.md) [:computer:](behavioral-patterns/strategy/strategy.cpp)
 - [**Template Method**](behavioral-patterns/template-method) [:book:](behavioral-patterns/template-method/README.md) [:computer:](behavioral-patterns/template-method/template-method.cpp)
 - [**Visitor**](behavioral-patterns/visitor) [:book:](behavioral-patterns/visitor/README.md) [:computer:](behavioral-patterns/visitor/visitor.cpp)
 
