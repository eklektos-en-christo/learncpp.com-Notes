//
//  main.cpp
//  10.1_intro.to.program.defined.types(user-defined.types)
//
//  Created by Εκλεκτός εν Χριστώ on 3/5/23.
//

/*
 Fundamental types : defined as a part of the core CPP language, they are available for
 immediate use as below -
 
 int x;     -   variable of fundamental type 'int'
 double d;  -   variable of fundamental type 'double'
 
 functions, pointers, references and arrays - these are compound types that are simple
 extensions of fundamental types, they are available for immediate use also as below -
 
 void func(int) {};     :   function of type void()(int)
 int* ptr;              :   variable of compound type - pointer to int
 int& ref;              :   variable of compound type - reference to int
 int arr[3];            :   array of 3 integers of type int[3]
 
 Type alias - introduces a new identifier into the program, type alias must be defined
 before it can be used, if we were to omit the definition of a type alias, the compiler
 wouldn't know the new name of the type that we try to give to create an object, the
 definition of a type alias doesn't create an object, it just tells the compiler what the
 new name is so it can be used later.
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 User-defined/Program-defined types : custom types for use in the programs
 
 C++ has two categories of compound types that allow to be defined by user/program:
 -enumerated types
    -unscoped enumerations
    -scoped enumerations
 -class types
    -structs
    -classes
    -unions
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Program-defined types : must be defined before they can be used
 
 Type definition : definition for a program-defined type
 
 Program-defined type definitions : always end in a semicolon, common error, hard to debug
 
 Warning: don't forget to end the type definitions with a semicolon
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Naming program-defined type :
 convention - program-defined types are named starting with a capital letter and don't use
 a suffix
 
 best practice
 name the program-defined types starting with a capital letter and don't use a suffix
 
 variable definitions : the type comes first, then the variable name and then an optional
 initializer
 
 example-
 Fraction fraction{};   -   capital F : we know it's a program-defined type
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Using program-defined types throughout a multi-file program:
 every code file that uses program-defined types needs to see the full type definition
 before it is used, a forward declaration is not sufficient, this is required so that the
 compiler knows how much memory to allocate for objects of that type
 
 to propagate type definitions into the code files that need them:
 program-defined types are typically defined in header files and the included into any code
 file that requires that type definition, these header files are typically given the same
 name as the program-defined type
 example - a program-defined type named Fraction would be defined in Fraction.h
 
 best practice:
 program-defined type used in only one code file - should be defined in that code file as
 close to the first point of use as possible
 
 program-defined type used in multiple code files- should be defined in a header file with
 the same name as the program-defined type and then included into each code file as needed
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Type definitions are partially exempt from the one-definition rule(ODR):
 
 each function and global variable - have one definition per program
 
 to use a given function or global variable in a file that doesn't contain the definition -
 we need a forward declaration, which we typically propagate via a header file, this works
 because declarations are enough to satisfy the compiler when it comes to functions and
 non-constexpr variables, linker can then connect everything up
 
 But-
 using forward declarations : doesn't work for types
 compiler - typically needs to see the full definition to use a given type
 we must be able to propagate the full type definition to each code file that needs it
 
 types are partially exempt from one-definition rule - a given type is allowed to be defined
 in multiple code files
 
 example- if the program has two code files that both include <iostream> header, into both
 files all of the input/output type definitions will be imported
 -two caveats worth knowing about :
    - you can still only have one type definition per code file, this isn't usually a
      problem, since the header guards will prevent this
    - all of type definitions for a given type must be identical, otherwise undefined
      behavior will result
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 User-defined types     vs.      program-defined types
 
 user-defined type - comes up in casual conversation, as well as being mentioned in language
 standard, the term tends to mean "a type defined within your own programs" such as Fraction
 type in this file
 
 in the language standard - a user-defined type is any class type or enumerated type that is
 defined by you, the std library or the implementation(compiler), std::string is considered
 to be a user-defined type
 
 C++20 language standard - defines the term program defined type to mean class types and
 enumerated types that are not defined as part of the std library, implementation or core
 language
 
 program-defined type - only includes class and enum types that are defined by us or a third
 party library
 
 program-defined : is a more precise definition
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 +-----------------------------------------------------------------------------------------+
 |TYPE          MEANING                                             EXAMPLES               |
 +-----------------------------------------------------------------------------------------+
 |Fundamental   built into the core language                        int, std::nullptr_t    |
 |Compound      built from fundamental types                        int&, double*, Fraction|
 |                                                                  std::string            |
 |User-defined  class or enumerated type                            std::string, Fraction  |
 |              includes those defined in std or implementation,                           |
 |              in casual use - typically used to mean program                             |
 |              defined types                                                              |
 |program       class or enumerated type                            Fraction               |
 |defined       excludes defined in std or implementation                                  |
 +-----------------------------------------------------------------------------------------+
 */

#include <iostream>
/// Fraction type defined in Fraction.h used in the main.cpp file
#include "Fraction.h"

/// program defined type definition
/// it is in the global scope, can use used anywhere in the rest of the file
/// it doesn't allocate memory
//struct Fraction
//{
//    int numerator{};
//    int denominator{};
//};

int main()
{
    /// instantiates a Fraction object
    Fraction f{2, 5};
    
    return 0;
}
