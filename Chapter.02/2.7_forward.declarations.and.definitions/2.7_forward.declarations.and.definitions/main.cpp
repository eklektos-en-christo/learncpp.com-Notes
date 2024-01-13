//
//  main.cpp
//  2.7_forward.declarations.and.definitions
//
//  Created by εκλεγμένοι εν Χριστώ on 9/6/22.
//

/*
 Best practice

 When addressing compile errors in your programs, always resolve the first error produced first and then compile again.
 
 forward declaration: tells the compiler about the existence
 of an identifier before actually defining the identifier.
 
 
 function prototype: consists of function header(return type,
 name, parameter types) terminated with a semicolon. function
 body is not included in the prototype
 
 Best practice

 When defining function prototypes, keep the parameter names. You can easily create forward declarations by copy/pasting your function’s prototype and adding a semicolon
 
 If a forward declaration is made, but the function is never called, the program will compile and run fine. However, if a forward declaration is made and the function is called, but the program never defines the function, the program will compile okay, but the linker will complain that it can’t resolve the function call.
 
 forward declarations: can also be used with variables and
 user defined types
 
 declaration vs definition:
 definition: implements/instantiates
 declaration: tells the existence of an identifier and its
 type information
 
 using of identifier without definition: linker error
 
 ODR : one definition rule
 1
 within a given file, function, variable, type or template can
 only have one definition
 2
 within a given program, variable/normal function can only
 have one definition
 3
 types, templates, inline functions/variables are allowed
 to have identical definitions in different files
 
 1 violation: redefinition error
 2 violation: redefinition error
 3 violation: undefined behavior
 
 Functions that share an identifier but have different
 parameters are considered to be distinct functions.
 
 not all declarations are definitions
 
 pure declarations: declarations that aren't definitions
 
 ODR doesn’t apply to pure declarations, so multiple pure
 declarations for an identifier are okay, but they are
 redundant
 
 In common language, the term “declaration” is typically used to mean “a pure declaration”, and “definition” is used to mean “a definition that also serves as a declaration”. Thus, we’d typically call int x; a definition, even though it is both a definition and a declaration.
 */

#include <iostream>

/// function prototype: includes return type, name and parameter types
/// function body not required in function prototype
/// below is only the declaration and not the definition
/// forward declaration of subtract
/// semicolon at the end is necessary, since this is a statement
int subtract(int x, int y);

/// also a valid prototype
int add(int, int);

int main()
{
//    int x{};        /// first definition
//    int x{};        /// error: redefinition of x
}

/// definition of subtract
int subtract(int x, int y)
{
    return x - y;
}
