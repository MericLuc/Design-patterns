# Intend

The Monostate pattern is usually referred to as a _conceptual Singleton_.

It **ensures that every instances of a class have the same data**.

_Monostate pattern_ and _Singleton pattern_ are actually the two faces of the same medal :
 - The _Monostate pattern_ forces a **behaviour** - One data representation to all the instances.
 - The _Singleton pattern_ forces a **structural constraint** - One instance of the class.

# How it's done

Nothing fancy !

All you need to do is to **declare every data member of the class static**.

This way, any number of instances can be created (in a transparent way) but they all share the same data.

NB : You will need getter/setter functions for every data members.

# Pros & cons

**Pros**
 - _Transparency_ :
   - _Monostate pattern_, unlike _Singleton pattern_, is transparent to the user.
   - There is no way to tell a class uses the _Monostate pattern_ unless being aware of the implementation. 
 - _Derivability_ :
   - Derivates of a MonoState are MonoStates (since they all share the same static variables).
 - _Well-defined creation/destruction_ :
   - Static variables have a well-defined lifetime.
 - _Inheritence_ :
   - Easy to inherit, use and maintain.
 - _Conversions_ :
   - Making an existing class similar to a Singleton is easy without writting extra code.

**Cons**
 - _Efficiency_ :
   - Allows for many objects creation/destruction which are CPU costly.
 - _Presence_ :
   - Static variables take up space irrespective of the fact these objects are used or not.

