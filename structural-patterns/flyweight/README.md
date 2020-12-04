# Intend

**Avoid redundancy when storing data !**

Or, as stated in [_GoF_](https://fr.wikipedia.org/wiki/Design_Patterns) :
> Use sharing to support large numbers of fine-grained objects efficiently.

To put it in a nutshell : **Space optimization technique** ;)

Note : The _Flyweight_ is a shared object that can be used simultaneously in multiple contexts but the _Client_ will not even be able to know that this object is shared in another context.

You should use the _Flyweight_ pattern in the following cases :
 - The **naive approach** (create as many objects as you need) would be **prohibitively expensive**.
   - For example, using an object for each particle of a _particles system_ or each character of a _text editor_ probably would not fit into the available RAM.
 - Your application should be able to support a **large number of objects** which barely fit into available RAM.
 - You application contains objects with **duplicate states that could be extracted** and shared between multiple objects. (_Extrinsic states_)
 - Your application does **not depend on objects identity**.

# How it's done

![UML](UML.jpg)

**Participants**

 - _Flyweight_ : Interface on which _Flyweights_ act on extrinsic state.
 - _ConcreteFlyweight_ : 
   - Implements _Flyweight_ interface.
   - Declares the storage of intrinsic state if needed.
   - Must be **shareable** and **context-independent** (i.e. the states it stores have to be context-independent).
 - _UnsharedConcreteFlyweight_ : For the _Flyweight_ objects that do not need to be shared.
 - _FlyweightFactory_ :
   - **Creates and manages** _Flyweight_ objects.
   - Control proper sharing between clients calls.
 - _Client_ :
   - Maintains a reference to a _Flyweight_.
   - Computes or stores the extrinsic state of _Flyweights_.

**How to implement**

 1. **Separate the fields** of the class to become a Flyweight
   - _Intrinsic states_
     - Contextual data unique to each object that cannot be shared.
   - _Extrinsic states_
     - Independents from context and shared by many objects
     - To be removed from shared objects.
 2. Leave the fields that represent the intrinsic state in the class, but make sure they’re immutable. They should take their initial values only inside the constructor.
 3. You might consider **creating a _FlyweightFactory_** class to **manage the pool of _Flyweights_** (check for existence at _Client_ calls and provide it with an existing or new _Flyweight_).
 4. You might consider **moving** the _Flyweight_ referencing field of the _Client_ as well as the _extrinsic state_ **to a separate context class**.

Note : UML class diagram taken from [**here**](https://upload.wikimedia.org/wikipedia/commons/4/4e/W3sDesign_Flyweight_Design_Pattern_UML.jpg)

# Pros & cons

**Pros**

 - **Memory** : Save lots of RAM.
 - **Response time** : Data caching is likely to improve the response time of your application.
 - **Centralize** the managing mechanism of your objects states.

**Cons**

 - **Memory/CPU tradeoff**
 - **Concurrency** : In a concurrent environment, you might be ending up with multiples instances of the same _Flyweight_ object.
 This problem can be eliminated using the [**Factory**]("../../creational-patterns/factory-pattern") pattern such that _Clients_ obtain flyweights from the **FlyWeightFactory** only.
 - **Provides no reliability on object identity**
    - The same physically created object represents many logically different objects.
    - Therefore, applications that depend on object identity should not use flyweights.

# Notes

Here are some _usefull ressources_ :
 - The [**w3sdesign**](http://w3sdesign.com/#gf) is really clear and concise !
 - A [**blog article**](http://www.vishalchovatiya.com/flyweight-design-pattern-in-modern-cpp/)
 - A [**Refactoring guru**](https://refactoring.guru/design-patterns/flyweight) article.