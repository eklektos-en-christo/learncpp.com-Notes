//
//  Cents.cpp
//  14.3_overloading.operators.using.normal.functions
//
//  Created by Εκλεκτός εν Χριστώ on 7/22/23.
//

#include "Cents.hpp"

/// this is a normal function
Cents operator+(const Cents& c1, const Cents& c2)
{
    return Cents{ c1.get_cents() + c2.get_cents() };
}
