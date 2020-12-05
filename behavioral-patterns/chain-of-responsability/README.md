# Intend

As stated in [_GoF_, p223](https://fr.wikipedia.org/wiki/Design_Patterns) :
> Avoid coupling the sender of a request to its receiver by giving more than one object a chance to handle the request. Chain the receiving objects and pass the request along the chain untill an object handles it. 


You should use the _Chain of responsibility_ pattern in the following cases :
 - You want to **avoid coupling** between your request sender and its receiver.
 - You want to be able to **address the request to more than one object**.
 - You want to perform **sequential checks** or operations on a request in a **particular order**.
 - You want to be able to **specify the order of handles at runtime**.

# How it's done

![UML](UML.jpg)

**Participants**

 - _Handler_ : 
   - Interface for handling requests.
   - Can implement the successor link.
 - _ConcreteHandler_ : 
   - Implement the _Handler_ interface.
   - Processes (handles) the requests it is reponsible for.
   - Otherwise, forwards the requests to its successor.
 - _Client_ : Initiates the request to a _ConcreteHandler_ object on the chain.

**How to implement**

 1. **Declare** the _Handler_ interface with the signature of the method to handle requests (it might be worth defining a default behaviour i.e. forward the request to the successor if possible). You may implement the successor link in here.
 2. You may want to **define an object to represent your requests**. That way, you will just have to pass the _Request_ object as an argument to the handling method.
 3. **Implement** _ConcreteHandlers_ and their handling methods. At that point, the handling method should consist in two parts :
   - "Process the request ?"
   - "Pass the request along the chain ?"
 4. You might want to **provide your client with pre-built chains**. In that case, consider defining some [**_Factories_**](../../creational-pattern/factory-pattern) to create those pre-built chains.

Note : UML class diagram taken from [**here**](https://upload.wikimedia.org/wikipedia/commons/6/6a/W3sDesign_Chain_of_Responsibility_Design_Pattern_UML.jpg)

# Pros & cons

**Pros**

 - **Reduced coupling**
 - **Order control**
 - **Single responsability principle** : It is easy to decouple classes that invoke operations from classes that perform operations.
 - **Open/Closed principle** : You can introduce new _ConcreteHandlers_ without breaking any existing _Client_ code.

**Cons**

 - **Receipt is not garanteed** : No explicit receiver also means no garantee for a request to be handled.

# Notes

Here are some _usefull ressources_ :
 - [**w3sdesign**](http://w3sdesign.com/#gf)
 - A [**Refactoring guru**](https://refactoring.guru/design-patterns/chain-of-responsibility) article.