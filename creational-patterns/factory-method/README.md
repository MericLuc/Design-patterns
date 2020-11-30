Also know as **Virtual constructor**.

# Intend

Factory Method is a creational design pattern that provides an interface for **creating objects in a superclass**, but **let subclasses decide the type of objects** that will be created.

It provides an encapsulation to objects instanciation and can therefore be seen as a **wrapper to the _new_ keyword**.

It allows to hide the business logic behind the objects creation and build it into the _factory_ instead of distributing it all around the code base.

In the end, the client knows about the abstract class but not the concrete subclass - this is the subclass that decides which class to instantiate **on run-time**.

# How it's done

![UML](https://en.wikipedia.org/wiki/Factory_method_pattern#/media/File:W3sDesign_Factory_Method_Design_Pattern_UML.jpg)

**Participants**
 - _Product_ Interface for the objects the _Factory method_ can create.
 - _Product1_ Implements the _Product_ interface.
 - _Creator_ Declares the factory method (can also provide a default implementation) returning a _Product_ object.
 - _Creator1_ Implements the factory method to return the right _Product_ type.

**Some more explanations**
 - The _Creator class_ that requires a _Product object_ **doesn't instantiate the Product1 class directly**. Instead, the Creator refers to a separate factoryMethod() to create a product object, which makes the Creator independent of which concrete class is instantiated. 

In this example, the Creator1 subclass implements the abstract factoryMethod() by instantiating the Product1 class.

Note : Example taken from [here](https://en.wikipedia.org/wiki/Factory_method_pattern)

# Pros & cons

**Pros**

As stated [here](https://www.bogotobogo.com/DesignPatterns/factorymethod.php), the _Factory method_ is a way of circumventing some C++ constructor limitaions :
 - _No return type_
 - _Naming_
 - _Compile time bound_
 - _There is no virtual constructor_

It provides a good solution in the following cases :
 - The client wants to delegate the decision of the type of object to create.
 - The client does not know the actual class from which subclass to create the object.

**Cons**

The _Factory Method pattern_ can expand the total number of classes in a system. Every concrete Product class also requires a concrete Creator class. The _parameterized Factory Method_ avoids this downs.

# Notes

 - The _Factory method_ is closely related to [_Abstract factory_](../abstract-factory) and [_Prototype_](../prototype) patterns.
 - A [Youtube video](https://www.youtube.com/watch?v=EcFVTgRHJLM) clearly illustrating this concept.
 - An interesting [brief article](http://www.cs.unc.edu/~stotts/GOF/hires/pat3cfso.htm) on the subject.