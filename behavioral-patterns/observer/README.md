Also known as **Publish-Subscribe, Dependents**.

# Intend

As stated in [_GoF_, p293](https://fr.wikipedia.org/wiki/Design_Patterns) :
> Define a one-to-many dependency between objects so that when one object changes state, all its dependents are notified and updated automatically.

**"How to define a subscription mechanism to notify objects about an event ?"**

Yup, just like Emails subscription, RSS feeds, GUI libraries and so on !

You should use the _Observer_ pattern in the following cases :
 - When you need changes on an object to affect other objects.
 - When you want to **manage the subscribers dynamically** ( or you do not know them beforehand )
 - When you objects that must observe others but only under particular circumstances (time, conditions...).

# How it's done

![UML](UML.jpg)

**Participants**

 - _Subject_
   - Provides an interface to add/remove _Observers_.
   - Maintains an list (an array of references for example) of its _Observers_.
 - _Observer_ : Defines an updating interface for objects that should be notified of changes in a subject.
 - _ConcreteSubject_ 
   - Stores the state of interest to _ConcreteObserver_ objects.
   - Implements the notify() method to notify its _Observers_ when a change occurs.
 - _ConcreteObserver_
   - Maintains a reference to a _ConcreteSubject_ object.
   - Implements the _Observer_ updating() interface to keep its state consistent with the _ConcreteSubject's_.

**How to implement**

 1. **Break** your business logic into two parts :
    - The core functionality (independent from other code) that will be the _Subject_.
    - The rest will be the _Observers_.
 2. **Declare** the _Observer_ interface with at least an update() method.
 3. **Declare** the _Subject_ interface with methods to add/remove _Observers_.
 4. Optionally, you can declare an interface derived from the _Subject_ interface that will **implement the subscription list mechanism**.
 5. **Create** your _ConcreteSubject_ classes.
 6. **Create** the _ConcreteObserver_ classes and implement their update() method.


Note : UML class diagram taken from [**here**](https://upload.wikimedia.org/wikipedia/commons/0/01/W3sDesign_Observer_Design_Pattern_UML.jpg)

# Pros & cons

**Pros**

 - **Open/Closed principle** : It is easy to add new _ConcreteObservers_ without breaking any existing code (not even the _Subject's_ code).
 - **Support broadcast communications** (allthough the _Observers_ are notified in a random order).

**Cons**

 - **Unexpected updates** : A small operation on a _ConcreteSubject_ can cause a lot of updates to the associated _Observers_.

# Notes

Here are some _usefull ressources_ :
 - [**w3sdesign**](http://w3sdesign.com/#gf)
 - A [**Refactoring guru**](https://refactoring.guru/design-patterns/observer) article.
 - A complete example [**here**](http://www.vishalchovatiya.com/observer-design-pattern-in-modern-cpp/)