Also known as **Objects for states**.

# Intend

As stated in [_GoF_, p305](https://fr.wikipedia.org/wiki/Design_Patterns) :
> Allow an object to alter its behaviour when its internal state changes. The object ill appear to change its class.

You should use the _State_ pattern in the following cases :
 - You want to change an object's behaviour at runtime depending on its state.
 - When you have a class polluted with massive conditionals that alter how it behaves.
 - When you have a lot of duplicate code across similar states and transitions of a condition-based state machine.

# How it's done

![UML](UML.jpg)

**Participants**

 -_Context_
  - Interface of interest to clients.
  - Maintains an instance of a _ConcreteState_ subclass that defines the current state and its behaviour.
 - _State_ Interface for the behaviour associated with a particular state of the _Context_.
 - _ConcreteStates_ implement a behaviour associated with a state of the _Context_.

**How to implement**

 1. **Declare** the _State_ interface - that is, the behaviour that depends on the state.
 2. **Create** a _ConcreteState_ subclass for every identified state of the _Context_. Implement the behaviours of those states.
 3. **Add** a reference field of the _State_ in the _Context_ class and its associated setter.
 4. **Replace** where needed in the methods of the _Context_ the conditionals with the corresponding calls to the _State_ object.


Note : UML class diagram taken from [**here**](https://upload.wikimedia.org/wikipedia/commons/e/ec/W3sDesign_State_Design_Pattern_UML.jpg)

# Pros & cons

**Pros**

 - **Open/Closed principle** : It is easy to introduce new _ConcreteStates_ without breaking any existing code.
 - **Single responsability principle** : Separate states/behaviours are defined within separate classes.
 - Simplify the code of the _Context_ by eliminating a lot of conditionals.

**Cons**

 - Can be overkill if there are only a few states and they should never change.

# Notes

Here are some _usefull ressources_ :
 - [**w3sdesign**](http://w3sdesign.com/#gf)
 - A [**Refactoring guru**](https://refactoring.guru/design-patterns/state) article.
 - A complete example [**here**](http://www.vishalchovatiya.com/state-design-pattern-in-modern-cpp/)