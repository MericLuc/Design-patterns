Also known as **Wrapper**.

# Intend

**Dynamically attach responsabilities to an object**.

It provides a flexible alternative to subclassing for extending functionality.

You should use the _Decorator_ pattern in the following cases :
 - You want to **provide individual objects** (not an entire class) **with a new behaviour**.
 - You want to **add responsabilities _dynamically_ and _transparently_**.
 - When the alternative (_extension by subclassing_) is impractical :
   - When it would produce an explosion of subclasses to support every combination.
   - The class definition is hidden or unavailable for subclassing.

# How it's done

![UML](UML.jpg)

**Participants**

 - _Component_ : The interface for objects that can have responsabilities dynamically added.
 - _ConcreteComponent_ : The objects to which responsabilities can be added.
 - _Decorator_ : Defines an interface that conforms to _Component_'s interface.
 Maintain a reference to a _Component_ object (_wrappee_).
 - _ConcreteDecorator_ : The object that adds responsabilities to _ConcreteComponent_.

**How to implement**

 1. **Create an interface** and declare the methods common to both the primary _Component_ and the optional layers.
 2. **Create your _ConcreteComponent_** class with its base behaviour.
 3. **Create your _Decorator_** class with a field storing a reference to the wrapped object (Your _Component_). The _Decorator_ will delegate all the work (i.e. except for the additional responsabilities) to the wrapped object.
 4. **Create your _ConcreteDecorator_** and implement the additional responsabilities before or after the call to the _wrappee_ behaviour.

Note : The _Client_ can then **create and compose _ConcreteDecorators_** in the way he needs.

Note : UML class diagram taken from [**here**](https://upload.wikimedia.org/wikipedia/commons/8/83/W3sDesign_Decorator_Design_Pattern_UML.jpg)

# Pros & cons

**Pros**

 - **Extend** an object's behaviour without subclassing.
 - **Add responsabilities at runtime**.
 - **Combine behaviours** (decorators composition) to suit your needs.
 - **Single responsability principle** : Divide monolithic classes into many classes with unique responsabilities.


**Cons**

 - It is hard to **remove a decorator** once it has been added.
 - **Order** : It might be difficult to implement decorators in a way they are order-independant.

# Notes

Here are some _usefull ressources_ :
 - A [Refactoring guru](https://refactoring.guru/design-patterns/decorator) article.
 - A complete example [here](https://www.bogotobogo.com/DesignPatterns/decorator.php)
