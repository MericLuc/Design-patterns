Also known as **Handle/Body**.

Note : When there is only one fixed implementation - also known as **Pimpl**.

# Intend

**Decouple an abstraction from its implementation** so that the two can vary independently.

It lets you split a large class into two separate hierarchies :
 - **Abstraction**
 - **Implementation**
Which can be developed independently.

You should use the _Bridge_ pattern in the following cases :
 - _The class_ (abstraction) and _what it does_ (implementation) both vary often.
 - You want to **extend a class** in several **independent dimensions**.
 - You want to **select an implementation at runtime** (Need to avoid a compile-time binding between the abstraction and its implementation).
 - Both abstraction and implementation should be **opened to subclassing**.
 - You want to completely **hide the implementation of the abstraction** to the client.
 - You want to **share an implementation** among multiple objects while hiding it to the client.

# How it's done

![UML](UML.jpg)

**Participants**

 - _Abstraction_ : 
   - The **abstraction interface**. 
   - It will **maintain a reference** to an _Implementor_.
 - _RefinedAbstraction_ : An extension to the _Abstraction_ interface.
 - _Implementator_ : 
   - **The interface for implementation classes**.
   - Provide implementation classes with **primitive operations**.
 - _ConcreteImplementator_ : Implements the _Implementator_ interface and defines its **concrete implementation**.

 Note : The _Abstraction_ will forward the client requests to its _Implementator_ object.

**How to implement**

 1. **Identify** the orthogonal dimensions of your class.
 2. **Put** the operations the client needs in the _Abstraction_ class. Provide this _Abstraction_ with a reference of the _Implementator_.
 3. **Determine** the operations availables on every plateforms and declare them in the _RefinedAbstraction_ interface.
 4. **Create** _ConcreteImplementators_ for every plateform.

Note : In case you have several variants of high-level logic, create _RefinedAbstractions_ for each one of them.

Note : UML class diagram taken from [**here**](https://upload.wikimedia.org/wikipedia/commons/f/fd/W3sDesign_Bridge_Design_Pattern_UML.jpg)

# Pros & cons

**Pros**

 - Allows you to create **plateforme independent apps**.
 - The client code works with **high-level abstractions** and is not exposed to implementation details.
 - **Open/Closed principle** : Easy to introduce new abstractions and implementations independently of the existing ones.
 - **Single responsability principle**: Separate high-level logic from details.

**Cons**

 - Can produce a complicated code if you are dealing with a highly cohesive class.

# Notes

Here are some _usefull ressources_ :
 - An interesting article on [**Refactoring guru**](https://refactoring.guru/design-patterns/bridge)
 - A complete example on [**bogotobogo**](https://www.bogotobogo.com/DesignPatterns/bridge.php)
 - A complete course on [**Udemy**](https://www.udemy.com/course/patterns-cplusplus)