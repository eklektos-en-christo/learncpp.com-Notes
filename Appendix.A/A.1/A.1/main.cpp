//
//  main.cpp
//  A.1
//
//  Created by Εκλεκτός εν Χριστώ on 12/15/23.
//

/*
 Library: a package of code that is meant to be reused by many programs
 
 C++ library comes in two pieces:
 - header file, defines the functionality the library is exposing to the programs using it
 - a precompiled library, contains the implementation of the header file functionality into machine code
 
 Types of libraries: static and dynamic
 
 Static library/archive: consists of routines that are compiled and linked directly into the program, the
 have .lib extension on windows and .a on linux, they becomes part of the executable, to update the
 library, the entire executable needs to be replaced
 
 Dynamic library/shared library: consists of routines that loaded into the program at runtime, the library
 doesn't become part of the executable, it remains as a separate unit, they have .dll extension on windows
 and .so on linux, many programs can share one copy, saves space, it can be upgraded to a newer version
 without replacing all of the executables that use it, programs using these libraries must explicitly load
 and interface with the dynamic library
 
 Import library: a library that automates the process of loading and using a dynamic library, on windows, it
 is done via a small static library of the same name as dynamic library, static library is linked into the
 program at compile time, then the functionality of the dynamic library can effectively be used as if it
 were a static library, on linux .so works as both a dynamic and an import library
 */

#include <iostream>

int main()
{
    
    
    return 0;
}
