//
//  Vector3d.cpp
//  13.15_friend.functions.and.classes
//
//  Created by Εκλεκτός εν Χριστώ on 7/17/23.
//

#include "Vector3d.hpp"

#include <iostream>

Vector3d::Vector3d(double x, double y, double z)
: m_x{ x }, m_y{ y }, m_z{ z }
{
}

void Vector3d::print() const
{
    std::cout << "Vector(" << m_x << " , " << m_y << " , " << m_z << ")\n";
}