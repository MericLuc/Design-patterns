Also known as **Surrogate**.

# Intend

**Provide an interface to a particular ressource to control access to it**.

The ressource may be **remote**, **expensive to construct** or **require any kind of additional functionality** (such a logging for example).

Note : **The interface provided by the _Proxy_ should look exactly the same as the _Object_**. (Well, it can provide additional enhancements, but it has to implement the _object_ interface.)

Note : There are many different types of _Proxy_ :
  - Virtual proxy
  - Protection proxy
  - Remote proxy
  - ...

You should use the _Proxy_ pattern in the following cases :
 - You want to **add access restrictions to an object** (make it read-only, add a logging control operation...) (**Protection proxy**)
 - You have an **heavyweight service object that wastes system ressources** by being always up and you want to provide some kind of **Lazy initialisation** to that object (**Virtual proxy**)
 - You want to **provide local execution of a remote service** - Your service object is therefore located on a remote server. (**Remote proxy**)

# How it's done

![UML](UML.jpg)

**Participants**

 - _Proxy_ : 
   - **Maintains a reference** to the _RealSubject_ (proxied object).
   - **Provide an identical interface** to _Subject's_.
   - **Controls access** to the _RealSubject_.
 - _Subject_ : Degines the common interface of _RealSubject_ and _Proxy_ so that the _Proxy_ can be used anywhere the _RealSubject_ is needed.
 - _RealSubject_ : The real object represented by the _Proxy_.
 - _Client_ : Uses the _Proxy_ as if it was the _RealSubject_. The _Client_ might actually not even know about it.

 **Notes about the _Proxy_ object**

  - If the interface of both _Subject_ and _RealSubject_ are the same, then _Proxy_ might yield a reference to _Subject_ instead.
  - The _Proxy_ might also be responsible of the **Life cycle** of the _RealSubject_.
  - Additional responsabilities can depend of the kind of proxy :
    - **Remote proxy** : Encoding requests.
    - **Virtual proxy** : Caching additional informations about the _RealSubject_ so that they can postpone accessing it.
    - **Protection proxy** : Permissions checking.

**How to implement**

 1. **Create** the _Proxy_ class with a field to a _RealSubject_ reference.
 The _Proxy_ might actually own the _RealSubject_ and be responsible of its creation/deletion, but not necessarily.
 2. **Implement** the _RealSubject_ interface (or _Subject's_ one, see the Notes above) into your _Proxy_ class. In most cases, a consequent part of the hard-work is delegated to the underlying _RealSubject_.
 3.  Consider introducing a creation method that decides whether the client gets a proxy or a real service. (using a [**Factory**](../../creational-patterns/factory-method) for example).

Note : You also might want to use [**lazy initialization**](https://en.wikipedia.org/wiki/Lazy_initialization) for the service object.

Note : UML class diagram taken from [**here**](https://upload.wikimedia.org/wikipedia/commons/6/6e/W3sDesign_Proxy_Design_Pattern_UML.jpg)

# Pros & cons

**Pros**

 - **Simplifies client** : Hide implementations details from clients.
 - **Open/Closed principle:** You can easily introduce new proxies without changing the service or client.

**Cons**

 - **Complexity** : Increases the number of classes (as the majority of _Design patterns_).
 - The response from teh service might get delayed.
 - **Dependency inversion principle**: Usually, the _Proxy_ **has to know the concrete class** of the _RealSubject_. 

# Notes

**Did you know ?**

  - [_Smart pointers_](https://en.cppreference.com/w/cpp/memory) from the standard library is an example of the _Proxy_ design pattern.
  Indeed, consider the following code snippet :
    ```
    aPointer->aFunction();
    *aPointer = aValue;
    ```
    - There is no way you can know whether `aPointer` is a raw pointer or a smart pointer.
    - That is because _smart pointers_ provide an interface to access an underlying raw pointer that looks just like the interface of a raw pointer.

**Ressources**

Here are some _usefull ressources_ :
 - The [**w3sdesign**](http://w3sdesign.com/#gf) is really clear and concise !
 - A [**blog article**](http://www.vishalchovatiya.com/proxy-design-pattern-in-modern-cpp/) with examples of :
   - _Property Proxy_
   - _Virtual Proxy_
   - _Communication Proxy_
 - A [**Refactoring guru**](https://refactoring.guru/design-patterns/proxy) article.
