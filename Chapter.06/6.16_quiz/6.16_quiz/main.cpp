//
//  main.cpp
//  6.16_quiz
//
//  Created by εκλεγμένοι εν Χριστώ on 12/12/22.
//

#include <iostream>
#include "constants.h"

bool pass_or_fail()
{
    static int s_passes{3};
    --s_passes;
    return (s_passes >= 0);
}

int main()
{
    std::cout << "Enter students: ";
    int students{};
    std::cin >> students;
    
    if (students > constants::max_class_size)
        std::cout << "Too many students!" << '\n';
    else
        std::cout << "Not too large!" << '\n';
    
    std::cout << "USER 1 : " << (pass_or_fail() ? "PASS\n" : "FAIL\n");
    std::cout << "USER 2 : " << (pass_or_fail() ? "PASS\n" : "FAIL\n");
    std::cout << "USER 3 : " << (pass_or_fail() ? "PASS\n" : "FAIL\n");
    std::cout << "USER 4 : " << (pass_or_fail() ? "PASS\n" : "FAIL\n");
    std::cout << "USER 5 : " << (pass_or_fail() ? "PASS\n" : "FAIL\n");
    
    return 0;
}
