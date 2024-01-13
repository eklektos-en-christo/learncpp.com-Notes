//
//  a.cpp
//  6.6_internal.linkage
//
//  Created by εκλεγμένοι εν Χριστώ on 11/10/22.
//

#include <iostream>

/// this variable is independent of the same named variable in main.cpp file
constexpr int g_x{20};

/// this function is not accessile outside of this file
/// static changed it linkage from external to internal
static void my_fun()
{
    std::cout << "STATIC FUNCTION" << '\n';
}
