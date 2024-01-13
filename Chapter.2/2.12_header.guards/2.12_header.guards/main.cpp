//
//  main.cpp
//  2.12_header.guards
//
//  Created by εκλεγμένοι εν Χριστώ on 9/8/22.
//

/*
 Header/include guards: conditional compilation directives
 
 #ifndef SOME_UNIQUE_NAME_HERE
 #define SOME_UNIQUE_NAME_HERE

 // your declarations (and certain types of definitions) here

 #endif
 
 When this header is #included, the preprocessor checks whether SOME_UNIQUE_NAME_HERE has been previously defined. If this is the first time we’re including the header, SOME_UNIQUE_NAME_HERE will not have been defined. Consequently, it #defines SOME_UNIQUE_NAME_HERE and includes the contents of the file. If the header is included again into the same file, SOME_UNIQUE_NAME_HERE will already have been defined from the first time the contents of the header were included, and the contents of the header will be ignored (thanks to the #ifndef).
 
 all header files : should have header guards on them
 naming convention: full filename of the header file, filename
 in all capital letters, underscores for spaces and
 punctuation
 
 Some good suggestions are a naming convention of
 <PROJECT>_<PATH>_<FILE>_H , <FILE>_<LARGE RANDOM
 NUMBER>_H, or <FILE>_<CREATION DATE>_H
 
 =============================================================
 Header guards do not prevent a header from being included
 once into different code files
 best way to work around this issue is simply to put the
 function definition in one of the .cpp files so that
 the header just contains a forward declaration
 -------------------------------------------------------------
 square.h:          // contains forward declarations

 #ifndef SQUARE_H
 #define SQUARE_H

 int getSquareSides(); // forward declaration for getSquareSides
 int getSquarePerimeter(int sideLength); // forward declaration for getSquarePerimeter

 #endif
--------------------------------------------------------------
 square.cpp:        // contains function definitions

 #include "square.h"

 int getSquareSides() // actual definition for getSquareSides
 {
     return 4;
 }

 int getSquarePerimeter(int sideLength)
 {
     return sideLength * getSquareSides();
 }
--------------------------------------------------------------
 main.cpp:

 #include "square.h" // square.h is also included once here
 #include <iostream>

 int main()
 {
     std::cout << "a square has " << getSquareSides() << "sides\n";
     std::cout << "a square of length 5 has perimeter length " << getSquarePerimeter(5) << '\n';

     return 0;
 }
--------------------------------------------------------------
 Now when the program is compiled, function getSquareSides
 will have just one definition (via square.cpp), so the
 linker is happy. File main.cpp is able to call this
 function (even though it lives in square.cpp) because
 it includes square.h, which has a forward declaration
 for the function (the linker will connect the call to
 getSquareSides from main.cpp to the definition of
 getSquareSides in square.cpp).
 =============================================================
 
 header guards: prevent a code file from receiving more than
 one copy of a guarded header
 
 it’s necessary to put non-function definitions in a header
 file.
 user-defined types are typically defined in header files
 type definitions can be propagated out to the code files
 that need to use them
 Without a header guard, a code file could end up with
 multiple (identical) copies of a given type definition
 
 alternate form of header guards: #pragma directive
 #pragma once: serves the same purpose as header guards
 #pragma once: is not an official part of the C++ language
 
 For maximum compatibility:  sticking to traditional header
 guards, they’re guaranteed to be supported on all compilers
 
 Best practice
 Favor header guards over #pragma once for maximum
 portability.
 
 duplicate declarations are fine
 declaration can be declared multiple times without incident
 header file is composed of all declarations: still a best
 practice to include header guards
 */

/// square.h content included here
/// SQUARE_H also defined here
#include "square.h"

/// geometry.h content included here
/// geometry.h contains square.h
/// square.h contents again included here
/// SQUARE_H also defined here
/// SQUARE_H defined previously
/// so none of the content from square.h included here
#include "geometry.h"

/// iostream content included here
#include <iostream>

int main()
{
    std::cout << "Square sides " << get_sq_sides() << '\n';
    return 0;
}
