Also known as **Cursor**.

# Intend

As stated in [_GoF_, p257](https://fr.wikipedia.org/wiki/Design_Patterns) :
> Provide a way to access the elements of an aggregate object sequentially, without exposing its underlying representation.

**That is, give a sequential access to various containers (stacks, vector, list, array, map...)**

You should use the _Iterator_ pattern in the following cases :
 - When you have a collection that has a complex structure and you want to hide its complexity from clients. You can have various reasons to do so.
   - Security : A client could be able to perform careless or malicious actions on the collection. convenience...
   - Convenience : Provide the client with simple methods to access elements will improve the clarity and the readability of the produced code.
 - To reduce code duplication : The code for the traversal of the collection can indeed be duplicated alot in different places of the application.
 - When you want to iterate through different containers or when you actually do not know the type of containers you will have. (See [_Polymorphic iteration_](https://stackoverflow.com/questions/4852658/polymorphic-iterators-in-c))

# How it's done

![UML](UML.jpg)

**Participants**

 - _Iterator_ : Defines an interface for accessing/traversing elements.
 - _ConcreteIterator_ :
   - Implements the _Iterator_ interface.
   - Keeps track of the current position in the traversal.
 - _Aggregate_ : Defines an interface for creating an _Iterator_ object.
 - _ConcreteAggregate_ : Implements the _Iterator_ creation interface to return an instance of the proper _ConcreteIterator_.

**How to implement**

 1. **Declare** the _Iterator_ interface with - at least - a method to get the next element of the _Aggregate_.
 2. **Declare** the _ConcreteIterator_ that implements _Iterator_ for the collections you want to use.
 3. **Implement** the interface of _Aggregate_ responsible for creating an _Iterator_. (begin(), end() ...).
 4. **Replace** the client code traversal codes with iterators.


Note : UML class diagram taken from [**here**](https://upload.wikimedia.org/wikipedia/commons/c/c5/W3sDesign_Iterator_Design_Pattern_UML.jpg)

# Pros & cons

**Pros**

 - **Single responsability principle** : Clean up client code for the collection iterations.
 - **Open/closed principle** : You can simply implement new kinds of structures and their corresponding iterators interface and pass them to an existing code without breaking it.
 - Perform multiple parallel iterations : Iterators contain their own iteration state.

**Cons**

 - Using an iterator may be less efficient than going through elements of some specialized collections directly.

# Notes

Here are some _usefull ressources_ :
 - The [**cppreference**](https://en.cppreference.com/w/cpp/iterator/iterator) documentation.
 - A [**complete example**](https://www.robertlarsononline.com/2017/04/24/iterator-pattern-using-cplusplus/#Iterator_Pattern_Example)
 - [**w3sdesign**](http://w3sdesign.com/#gf)
 - A [**Refactoring guru**](https://refactoring.guru/design-patterns/iterator) article.