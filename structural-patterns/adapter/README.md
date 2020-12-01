Also known as **Wrapper**.

# Intend

__" Get the interface you want from the interface you have "__

**Convert the interface** of a class into another interface expected by the client.

_Adapter_ allows class that have incompatible interfaces to work together.

You should use the _Adapter_ pattern in the following situations :
 - You want to use an existing class whose interface does not match the one you expect.
 - You want to create a class that can cooperate with unrelated classes.

# How it's done

![UML](UML.jpg)

**Participants**

 - _Target_ : The domain-specific interface that the client uses.
 - _Adapter_ : Adapts the _Adaptee_ interface to _Target_ interface.
 - _Adaptee_ : The existing interface that needs adapting.
 - _Client_ : Uses the _Target_ interface.

**How to implement**

 1. **Identify** the two classes constituting the _Target_ and the _Adaptee_.
   - The _Target_ class will often be a _service class_ that you cannot change (3rd-party, legacy, dependencies...).
   - The _Adaptee_ class is the class that would benefit from using the _service class_.
 2. **Declare** the _Client_ interface.
 3. **Create** the _Adapter_ class to follow the _Client_ interface without implementing its methods.
 4. **Add** a reference to the _Target_ to the _Adapter_.
 5. **Implement** all the methods of the _Client_ interface in the _Adapter_ class (The _Adapter_ should delegate most of the work to the _Target_.
 6. The client will use the _Adapter_ via the _Client_ inerface such that it will not need any change in its code.

Note : Your _Adapter_ will inherit publicly from _Target_ and privately from _Adaptee_.

Note : UML class diagram taken from [**here**](https://upload.wikimedia.org/wikipedia/commons/e/e5/W3sDesign_Adapter_Design_Pattern_UML.jpg)

# Pros & cons

**Pros**

 - **Single responsability principle** : It lets you separate the interface from the business logic of the programm.
 - **Open/Closed principle** : You can introduce new types of _Adapter_ without breaking the client code.

**Cons**

 - **Complexity** : Overall complexity is increasing because of the need to introduce a set of new interfaces and classes. This is of course simpler, if you can change the interface of the _Target_ without having too much changes in your code.

# Notes

**Did you know?** 

In the STL, stack, queue and priority_queue are _Adaptors_ from deque and vector. So when you call ```stack::push()``` the underlying vector does ```vector::push_back()```

**Ressources**

 - An interesting article on _Adapters_ in modern c++ [**here**](https://dzone.com/articles/adapter-design-pattern-in-modern-c)
 - A clear example on [**Refactoring guru**](https://refactoring.guru/design-patterns/adapter)
 - [**Another example**](https://www.bogotobogo.com/DesignPatterns/adapter.php)