# Intend

The Singleton pattern **ensures a class has only one instance**, and **provides a global point of access** to it.

# How it's done

This is all pretty simple.

A singleton-class has its constructors (cstr, cpy, move...) private so that it cannot be instatiated.
The only way to use it is by calling a static method that is responsible of instanciating the required instance.
```cplusplus
static Singleton& getInstance(void);
``` 

# Pros & cons

The _Singleton pattern_ has some advantages over global variables :
 - It enforces that only one instance of the class can be instantiated.
 - It provides thread-safe access to the object's global state.
 - It prevents the global namespace from being polluting.

All in all, the _Singleton pattern_ is considered to reflect a _poor design choice_ as it is only a way to store global data.

# Alternatives

There are several alternatives to the _Singleton pattern_ :
 - [**Dependency injection**](https://en.wikipedia.org/wiki/Dependency_injection)
 - [**Monostate pattern**](https://www.simplethread.com/the-monostate-pattern)
 - **Session context**

# Notes

Some interesting links on _why singleton pattern is evil_ :
- [accu singleton anti-pattern article](https://accu.org/journals/overload/11/57/radford_337)
- [scott densmore on singletons being evil](https://docs.microsoft.com/en-us/archive/blogs/scottdensmore)
- [stack overload about singletons](https://stackoverflow.com/questions/137975/what-is-so-bad-about-singletons)
