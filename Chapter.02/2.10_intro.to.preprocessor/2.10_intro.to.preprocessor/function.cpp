//
//  function.cpp
//  2.10_intro.to.preprocessor
//
//  Created by εκλεγμένοι εν Χριστώ on 9/8/22.
//

#include <iostream>

/// PRINT is not defined in this file, so "not printing" will execute
void print_something()
{
#ifdef PRINT
    std::cout << "Printing" << '\n';
#endif
    
#ifndef PRINT
    std::cout << "Not Printing" << '\n';
#endif
}
