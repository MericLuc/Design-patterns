# Intend

The **Builder pattern** is a creational design pattern that **lets you construct complex objects step by step**. 

It allows you to produce different types and representations of an object using the same construction code.

Use it when :
 - You need to have a construction process that allow for different representations of the constructed object.
 - The algorithm behind the complex object creation is independant of the parts constituting the object.

# How it's done

![UML](UML.jpg)

**Participants**
 - __Builder__ : Specifies an abstract interface for creating parts of the _Product_ object.
 - __ConcreteBuilder__ :
   - Constructs the different parts of the _Product_ by implementing the _Builder_ interface.
   - Provide an interface to retrieve the _Product_.
 - __Director__ : Uses/reuses _ConcreteBuilder(s)_ to construct a _Product_ variant from the same set of parts.
 - __Product__ : The complex object in construction.

 All the client has to do is to associate a _ConcreteBuilder_ object to the _Director_.

After that, the _Director_ uses the _ConcreteBuilder_ to build a _Product_.

 NB : UML class and sequence diagram from [**here**](https://en.wikipedia.org/wiki/Builder_pattern)

# Pros & cons

**Pros**
 - Isolates code for construction and representation - enforcing modularity.
 - Gives better control over the construction process and the resulting object - The product is constructed step by step, under the Director's control.
 - Allow for easy variations over Product's internal representation.

**Cons**
 - The builder interface shall be general enough to allow the creation of Products for every type of ConcreteBuilder. That means that you can clearly define a common construction sequence for every products representation.
 - The overall complexity of the code increases since the pattern requires creating multiple new classes.

NB : The methods of the _Builder_ are empty by default (not pure virtual) - so that the _ConcreteBuilder_ can override only the operations they are interested in. 

# Notes

 - You can find a great article about _Builder pattern_ [**here**](https://refactoring.guru/design-patterns/builder).
 - Detailed interactive example on [CodinGame](https://www.codingame.com/playgrounds/7105/pattern-builder/exemple) [FR]
 - The related [Wiki page](https://en.wikipedia.org/wiki/Builder_pattern)