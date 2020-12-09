# Intend

As stated in [_GoF_, p243](https://fr.wikipedia.org/wiki/Design_Patterns) :
> Given a language, define a repreentation for its grammar along with an interpreter that uses the representation to interpret sentences in the language.

In a few words : 
  - **Process structured text data by tokenizing && parsing**

**Examples of use** 

**_Interpreters_ are everywhere** - especially in programming languages - where the front end of every compiler is an _Interpreter_.
They are also used for mathematical expressions that need to be interpreted before being processed. (_See the [provided sample code](./interpreter.cpp) for an example_).

# How it's done

![UML](UML.jpg)

**Participants**

 - _AbstractExpression_ : Abstract interpret operation common to all nodes in the abstract syntax tree.
 - _TerminalExpression_ : Implements an interpret operation associated with terminal symbols in the grammar.
 - _NonTerminalExpression_ : 
   - One for each rule in the grammar.
   - Implements an interpret operation for nonterminal symbols in the grammar.
 _Context_ : Contains informations that's global to the interpreter.
 _Client_ :
   - Builds (or is given) an abstract syntax tree representing a particular sentence in the language that the grammar defines.
   - Inokes the interpret operation.


Note : UML class diagram taken from [**here**](https://upload.wikimedia.org/wikipedia/commons/3/33/W3sDesign_Interpreter_Design_Pattern_UML.jpg)

# Pros & cons

**Pros**

 - Easy to change and extend the grammar.

# Notes

Here are some _usefull ressources_ :
 - [**w3sdesign**](http://w3sdesign.com/#gf)
 - A [**blog**](http://www.vishalchovatiya.com/interpreter-design-pattern-in-modern-cpp/) article implementing a complete example.
 - A [**Udemy**](https://www.udemy.com/course/patterns-cplusplus) course.