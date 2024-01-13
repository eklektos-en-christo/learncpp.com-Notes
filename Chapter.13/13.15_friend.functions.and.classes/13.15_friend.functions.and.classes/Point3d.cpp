//
//  Point3d.cpp
//  13.15_friend.functions.and.classes
//
//  Created by Εκλεκτός εν Χριστώ on 7/17/23.
//

#include "Point3d.hpp"
#include "Vector3d.hpp"

#include <iostream>

Point3d::Point3d(double x, double y, double z)
: m_x{ x }, m_y{ y }, m_z{ z }
{
}

void Point3d::print() const
{
    std::cout << "Point(" << m_x << " , " << m_y << " , " << m_z << ")\n";
}

void Point3d::move_by_vector(const Vector3d& v)
{
    m_x += v.m_x;
    m_y += v.m_y;
    m_z += v.m_z;
}
