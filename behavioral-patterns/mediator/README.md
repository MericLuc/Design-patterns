# Intend

As stated in [_GoF_, p273](https://fr.wikipedia.org/wiki/Design_Patterns) :
> Define an object that encapsulates how a set of objects interact. Mediator promotes loose coupling by keeping objects from refereing to each other explicitly, an it lets you vary their interaction independently.

**In other words, make mediation between various items an independent concept by introducing an object that deals with it.**

# How it's done

![UML](UML.jpg)

**Participants**

 - _Mediator_ : Interface for communicating with _Colleague_ objects.
 - _ConcreteMediator_: Implements _Mediator_ interface by coordinating _Colleague_ objects. Knows and maintains _Colleagues_.
 - _Colleagues classes_ : 
   - Each instance has a reference to its _Mediator_ object (or knows about it in some way). 
   -  Communicates with other _Colleague_ using _Mediator_ only.

**How to implement**

 1. **Identify** a collection of objects that would benefit from mutual decoupling.
 2. **Encapsulate** those interactions in the abstraction of the _Mediator_.
 3. **Create** your _Mediator_ and rework all "peer" objects to interact with it only.
 4. Be careful not to create a _God object_.


Note : UML class diagram taken from [**here**](https://upload.wikimedia.org/wikipedia/commons/9/92/W3sDesign_Mediator_Design_Pattern_UML.jpg)

# Pros & cons

**Pros**

 - **Decouples colleagues** : Promotes loose coupling between colleagues.
 - **Abstracts how objects interact**
 - **Centralizes control**
 - **Simplify objects protocol** (from many to many to many to one.)


**Cons**

 - The complexity that previously was in the interaction between objects is now in the _Mediator_. This can produce a complex object.

# Notes

Here are some _usefull ressources_ :
 - [**w3sdesign**](http://w3sdesign.com/#gf)
 - A [**Refactoring guru**](https://refactoring.guru/design-patterns/mediator) article.