//
//  main.cpp
//  4.20_quiz2
//
//  Created by εκλεγμένοι εν Χριστώ on 10/11/22.
//

#include <iostream>

double tower_height()
{
    std::cout << "Enter the height of the tower in meters: ";
    double height{};
    std::cin >> height;
    
    return height;
}

double calc_height(double tower_height, int seconds)
{
    constexpr double gravity{9.8};
    
    double height_fallen{(gravity * (seconds * seconds))/2.0};
    const double new_height{tower_height - height_fallen};
    
    return new_height;
}

void print_height(double height, int seconds)
{
    if (height > 0.0)
    {
        std::cout << "At " << seconds << " seconds, the ball is at: " << height << " meters." << '\n';
    }
    else
    {
        std::cout << "At " << seconds << " seconds, the ball is on the ground." << '\n';
    }
}

void calc_print_height(double height, int seconds)
{
    const double height_t{calc_height(height, seconds)};
    print_height(height_t, seconds);
}

int main()
{
    double height{tower_height()};
    
    calc_print_height(height, 0);
    calc_print_height(height, 1);
    calc_print_height(height, 2);
    calc_print_height(height, 3);
    calc_print_height(height, 4);
    calc_print_height(height, 5);
}
