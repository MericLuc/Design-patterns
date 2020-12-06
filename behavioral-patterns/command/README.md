Also known as **Action, Transaction**.

# Intend

As stated in [_GoF_, p233](https://fr.wikipedia.org/wiki/Design_Patterns) :
> Encapsulate a request as an object, thereby letting you parameterize clients with different requests, queue or log requests, and support undoable operations. 

In a few words : 
  - **An object that represents a request (an operation)**
  - Contains all the necessary information for the request to be taken.

You should use the _Command_ pattern in the following cases :
 - **Parameterize objects by an action** to perform (just like callback functions in procedural languages).
 - **Specify, order, queue and execute requests at different times** (even remotely).
 - You want to implement **reversible commands**.

**Examples of use** 

  - GUI Commands
  - Multi-level do/undo/redo 
  - ...

**Command VS Query**

  - A **Command** is asking an object for a change and therefore induces a mutation of that object.
  - A **Query** asks an object for informations - it does not change the object.

# How it's done

![UML](UML.jpg)

**Participants**

 - _Command_ : Interface defining two operations
   - _do()_
   - _undo()_
 - _ConcreteCommand_ : Implements _Command_ interface by invoking the corresponding operation(s) on the _Receiver_.
 - _Client_ : Creates _ConcreteCommands_ and sets their _Reveiver_.
 - _Invoker_ : Asks the _Command_ to carry out the request.
 - _Receiver_ : Knows how to perform the operations associated with carrying out a request.

**How to implement**

 1. **Declare** the _Command_ interface with _do()_ _undo()_ operations.
 2. **Extract** request into _ConcreteCommands_ classes that implement _Command_ interface.
 3. **Identify** classes that will act as _senders_. Add fields for storing commands into these classes.
 4. Change the senders so they execute the command instead of sending a request to the receiver directly.

Note : _Invoker_ should communicate with their commands only via the _Command_ interface. _Invokers_ usually do not create _Commands_ on their own but rather receive them from the _Client_.

Note : UML class diagram taken from [**here**](https://upload.wikimedia.org/wikipedia/commons/c/c8/W3sDesign_Command_Design_Pattern_UML.jpg)

# Pros & cons

**Pros**

 - **Separation of concerns principle** : Classes that invoke operations are decoupled from the one that perform the operations.
 - **Open/Closed principle** : Pretty easy to introduce new _ConcreteCommands_ without breaking any existing _Client_ code.
 -**Composition** : Create complex command by assembling a set of simple commands.
 - **Do/Undo** operations.

**Cons**

 - **Complexity** : The code might become more complicated with the multiplication of classes. Also you just introduced a layer between _senders_ and _receivers_.

# Notes

Here are some _usefull ressources_ :
 - [**w3sdesign**](http://w3sdesign.com/#gf)
 - A [**Refactoring guru**](https://refactoring.guru/design-patterns/command) article.
 - A complete example on [**bogotobogo**](https://www.bogotobogo.com/DesignPatterns/command.php)