# Intend

As stated in [_GoF_, p325](https://fr.wikipedia.org/wiki/Design_Patterns) :
> Define the skeleton of an algorithm in an operation, deferring some steps to subclasses. Template Method lets subclasses redefine certain steps of an algorithm without changing the algorithm's structure.

It looks like the "inheritence" version of the "composition" pattern [_Strategy pattern_](../strategy)

_Template Method_ works at the class level, so it is static when _Strategy_ works on the object level, letting you switch behaviors at runtime.

You should use the _Template method_ pattern in the following cases :
 - You want clients to be able to extend certain parts of an algorithm, but not the complete algorithm.
 - You want to implement the skeleton of an algorithm once and leave the responsability of implementation to subclasses.
 - You have multiple classes with common behavior and you want to factor the common parts.

# How it's done

![UML](UML.jpg)

**Participants**

 - _Abstract class_
   - Defines the primitive operations that need to be implemented by the _ConcreteClasses_ in order to implement the algorithm.
   - Implements a template-method defining the skeleton of the algorithm.
 - _ConcreteClass_
   - Implements the primitive operations of the _Abstract class_ to define the algorithm.

**How to implement**

 1. **Break** your algorithm into two parts : common steps VS unique steps.
 2. **Create** an interface to put the steps of the algorithm and only leave the unique steps open to subclassing.
 3. **Add** hooks between crucial steps of the algorithm.
 4. **Create** as many subclasses as particular algorithms and implement their unique steps.


Note : UML class diagram taken from [**here**](https://upload.wikimedia.org/wikipedia/commons/2/2a/W3sDesign_Template_Method_Design_Pattern_UML.jpg)

# Pros & cons

**Pros**

 - **Clarity/readability** : Remove duplicate code and factor it into a superclass.
 - **Control** : You can let clients override only certain parts of a large algorithm.

**Cons**

 - The skeleton provided by the _Template method_ pattern might limit clients.
 - Might become difficult to maintain if there are many steps.

# Notes

Here are some _usefull ressources_ :
 - [**w3sdesign**](http://w3sdesign.com/#gf)
 - A [**Refactoring guru**](https://refactoring.guru/design-patterns/template-method) article.
 - A complete example [**here**](http://www.vishalchovatiya.com/template-method--design-pattern-in-modern-cpp/)
