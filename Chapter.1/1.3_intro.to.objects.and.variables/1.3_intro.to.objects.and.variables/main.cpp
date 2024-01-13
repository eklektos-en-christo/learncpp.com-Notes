//
//  main.cpp
//  1.3_intro.to.objects.and.variables
//
//  Created by Judah's Leon on 7/14/22.
//

/*
 Data : In computing, data is any information that can be moved, processed, or stored by a computer.
 
 Programs are collections of instructions that manipulate data to produce a desired result.
 
 
 
 Objects and variables :
 A single piece of data, stored in memory somewhere, is called a value.

 In C++, direct memory access is not allowed but through object
 
 Object : region of storage that has value and other associated
 properties, we can say, go get the value stored by this object.
 Objects can be named or unnamed (anonymous).
 named objects : variables, name of the object : identifier
 
 In general programming, the term object typically refers to a variable, data structure in memory, or function. In C++, the term object has a narrower definition that excludes functions.
 
 Variable instantiation : special kind of declaration statement used
 to create a variable
 */

int x;      // variable named x of type int

/*  At compile time, when the compiler sees this statement, it makes a note to itself that we are defining a variable, giving it the name x, and that it is of type int (more on types in a moment). From that point forward (with some limitations that we’ll talk about in a future lesson), whenever the compiler sees the identifier x, it will know that we’re referencing this variable.*/

/*
 Instantiation : means object will be created and assigned a memory
 address.
 Variables must be instantiated before they can be used to store values.
 An instantiated object is sometimes also called an instance.
 */

/*
 Data types : tell the compiler about type of data, ex : number letter text etc
 
 In c++ the type of a variable must be known at compile time and that type cannot be changed
 without recompiling the program
 
 C++ also allows you to create your own user-defined types.
 */

// multiple variables in same line separated by comma
int a,b;

/*
 The first mistake is giving each variable a type when defining variables in sequence.
 The second mistake is to try to define variables of different types in the same statement, which is not allowed. Variables of different types must be defined in separate statements.
 
 */

//int p, double q;  // wrong

/*
 Best practice

 Although the language allows you to do so, avoid defining multiple variables in a single statement (even if they are the same type). Instead, define each variable in a separate statement (and then use a single-line comment to document what it is used for).
 */


// summary : in cpp we use variables to access memory
// variables :have a type, a name and a value
// variable type : used to determine how the value in memory should be interpreted
