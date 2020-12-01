# Intend

Specify the kind of objects to create using a prototypical instance, and **create new objects by copying this prototype**.

It allows you to **clone** (even complex) **objects without coupling 
to their specific classes**.

You should use the _Prototype_ pattern in the following cases :
 - Whenever creation of new object requires setting many parameters and some (or all) are optional.
 - To avoid building a class hierarchy of factories.
 - When instances of a class can only have a few different states.
 - When the class to instantiate are specified at run-time (_dynamic loading_)

# How it's done

![UML](UML.jpg)

**Participants**

 - _Prototype_ : Defines an interface to clone itself.
 - _ConcretePrototype_ : Implement the interface of _Prototype_.
 - _Client_ : **Creates new objects** by asking a _Prototype_ to clone itself.

**How to implement**

 1. __Create the *Prototype* interface__ (with the clone() method).
 2. __Create the *ConcretePrototypes*__ that implement the _Prototype_ interface to copy() themselves.
 3. Optionally, __Add a registry__
    - It is easy to define a **Registry** using the [**Factory**](../factory-method/README.md) template that will **store a catalog of frequently used prototype**.
    - As the client ask for a Prototype (based on any search criteria such as a enum or a combination of params...), the Registry will find it in its catalog and retrieve a copy() of it.
    - This will simplify the management of the different possible prototypes as well as provide a _unique point of creation_.

Note : UML class diagram taken from [**here**](https://upload.wikimedia.org/wikipedia/commons/c/c4/W3sDesign_Prototype_Design_Pattern_UML.jpg)

# Pros & cons

**Pros**
 - __Readability__ : Produce complex objects more conveniently.
 You will also get rid of repeated initialization code in favor of cloning pre-built prototypes.
 - __Reducing subclassing__
 - __Dynamically configure__ an application

**Cons**
 - Implementing the _clone()_ operation can be difficult when object structures contain _circular references_.
 - Shallow copy vs deep copy problem : Should the _clone()_ operation make a copy of the object parameters or should the original and clone share the parameters ?
 - Initializing clones : The client might want to initialize some of the internal states of its clone. But you cannot pass those as parameters to your _clone()_ operation (because their numbers will vary between prototypes).
 The client might have to use setters (if you provided them) just after the _clone()_ operation or you might need to provide him with a _initialize()_ operation.

# Notes

The _Prototype pattern_ is **available in C++** with a **Cloneable interface**.

Here are some _usefull ressources_ :
 - A [Refactoring guru](https://refactoring.guru/design-patterns/prototype/cpp/example) article.
 - A complete example [here](http://www.vishalchovatiya.com/builder-design-pattern-in-modern-cpp/)
