Also know as **Kit**.

# Intend

Provide an interface for the __creation of families of related objects__ _without specifying their concrete classes_.

You should use this pattern in the following cases :
 - **The system should be independant** of how its products are created, composed and represented.
 - The system might be **configured with multiple product families**.
 - When you need to _enforce_ the fact that **a family of products should be used together**.
 - You want to provide a library class of products but **only reveal the interface** (_hide the implementation_).

# How it's done

![UML](UML.jpg)

**Participants**

 - _AbstractFactory_ : Interface for operations that create _AbstractProduct_ objects.
 - _ConcreteFactory_ : Implement _AbstractFactory_ interface to produce _ConcreteProduct_ objects.
 - _AbstractProduct_ : Interface for a type of product.
 - _ConcreteProduct_ : 
   - Implement _AbstractProduct_ interface.
   - Defines a product object to be created by the corresponding _ConcreteFactory_.
 - _Client_ : Only uses the interfaces declared by _AbstractFactory_ and _AbstractProduct_.

**How to implement**

You should implement the _Abstract factory_ pattern following these steps :
 1 - __Define a matrix__ of your products families (products families \* products type)
 2 - __Declare an abstract interface__ (_AbstractProduct_) for every product types. All the _ConcreteProduct_ classes have to implement these interfaces.
 3 - __Declare an abstract factory interface__ (_AbstractInterface_) with the required methods to create every abstract product.
 4 - __Implement the corresponding concrete factory classes__ (_ConcreteFactory_) for each product variant. They will create the Products with the help of _ConcreteProduct_.
 5 - __Initialize the factories__ and make it accessible to every classes that construct the products (_Client_).

NB : You can implement the factories as [_Singleton_](../singleton/README.md). Indeed, your application will likely need only one instance of  _ConcreteFactory_ per product family.

Note : UML class diagram taken from [**here**](https://en.wikipedia.org/wiki/Abstract_factory_pattern#/media/File:W3sDesign_Abstract_Factory_Design_Pattern_UML.jpg)

# Pros & cons

**Pros**
 - __Compatibility__ : All the products created via a Factory are compatible with eatch other.
 - __Coupling__ : Avoid tight coupling between _ConcreteProduct_ and client code.
 - __Maintainability__ : The product creation takes place in a single, well-identified, place. It makes the code easier to maintain.
 - __Flexible__ : It is easy to introduce new product families without breaking the _Client_ code.

**Cons**
 - __Complexity__ : The code might become more complicated than it should be with the multiplication of interfaces and classes.

# Notes

As you can see in the _How to implement_ section, the _Abstract factory_ pattern are often implemented using the [_Factory method_](../factory-method/README.md) pattern.

The _ConcreteFactory_ are also often implemented as [_Singleton_](../singleton/README.md).

Here are some _usefull ressources_ :
 - [Refactoring guru](https://refactoring.guru/design-patterns/abstract-factory)
 - [Bogotobogo](https://www.bogotobogo.com/DesignPatterns/abstractfactorymethod.php)
 - A step-by-step interactive example on [Codingame](https://www.codingame.com/playgrounds/36103/design-pattern-factory-abstract-factory/design-pattern-abstract-factory) (FR)