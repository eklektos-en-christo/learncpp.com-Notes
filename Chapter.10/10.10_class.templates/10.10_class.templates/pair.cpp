//
//  pair.cpp
//  10.10_class.templates
//
//  Created by Εκλεκτός εν Χριστώ on 3/14/23.
//

#include "pair.h"
#include <iostream>

void foo()
{
    /// my_pair type : defined in pair.h as a class template
    my_pair<int> pair{2, 3};
    std::cout << max(pair) << " is larger!" << '\n';
}
