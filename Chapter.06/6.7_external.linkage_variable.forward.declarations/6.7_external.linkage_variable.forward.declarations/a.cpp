//
//  a.cpp
//  6.7_external.linkage_variable.forward.declarations
//
//  Created by εκλεγμένοι εν Χριστώ on 11/11/22.
//

#include <iostream>

/// this function has external linkage, can be seen by other files
/// forward declaration for this function is in main.cpp file
void say_hello()
{
    std::cout << "HELLO!" << '\n';
}

/// external global variables below
int g_x{1};                 /// non constant global variable, external by default
extern const int g_y{2};    /// const global variable, extern used to make it external

/// external linkage by default
/// g_a has the file scope - can be used from the point of definition to the end of this file
/// g_a can't be seen directly outiside of this file
int g_a{3};
/// g_a goes out of scope here
