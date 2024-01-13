//
//  main.cpp
//  14.3_overloading.operators.using.normal.functions
//
//  Created by Εκλεκτός εν Χριστώ on 7/21/23.
//

/*
 -------------------------------------------------------------------------------------------
 Overloaded operators: can be written as normal/non-friend functions, in this case the
 normal function can't access the private members directly but through the access functions
 
 Friend function declaration inside the class: serves as a prototype as well
 
 With normal functions: we have to provide our own function prototype
 
 Normal function: should be preferred over a friend function if it's possible to do so with
 the existing member functions available, the less touching the classes' internals, the
 better
 
 BEST PRACTICE:
 -prefer overloading operators as normal functions instead of friend it it's possible to
 do so without adding additional access functions to the class
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>
#include "Cents.hpp"

int main()
{
    Cents cents1{ 6 };
    Cents cents2{ 8 };
    Cents cents_sum{ cents1 + cents2 };
    std::cout << "I've " << cents_sum.get_cents() << " cents.\n";
    
    return 0;
}
