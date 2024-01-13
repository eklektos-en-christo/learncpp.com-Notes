//
//  add.cpp
//  2.11_header.files
//
//  Created by εκλεγμένοι εν Χριστώ on 9/8/22.
//

/// Source files should include their paired header
/// like below: add.h is the header of add.cpp
/// This allows the compiler to catch certain kinds of errors at compile time instead
/// of link time
/*
 something.h:

 int something(int); // return type of forward declaration is int
------------------------------------------------------------
 something.cpp:

 #include "something.h"

 void something(int) // error: wrong return type
 {
 }
 */
#include "add.h"

/// this is the function definition, this function is forward declared in  add.h file
int add(int x, int y)
{
    return x + y;
}
