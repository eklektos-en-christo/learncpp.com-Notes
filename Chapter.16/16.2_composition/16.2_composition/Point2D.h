//
//  Point2D.h
//  16.2_composition
//
//  Created by Εκλεκτός εν Χριστώ on 7/27/23.
//

#ifndef Point2D_h
#define Point2D_h

#include <iostream>

/// Point2D is a composition of its parts
/// it will have two dimensions X and Y
class Point2D
{
private:
    /// both are part of Point2D
    /// both's lifetime is tied to the Point2D instance
    int m_x;
    int m_y;
    
public:
    Point2D() : m_x{ 0 }, m_y{ 0 } {}
    
    Point2D(int x, int y) : m_x{ x }, m_y{ y } {}
    
    friend std::ostream& operator<<(std::ostream& out, const Point2D& point)
    {
        out << '(' << point.m_x << ", " << point.m_y << ')';
        return out;
    }
    
    void set_point(int x, int y)
    {
        m_x = x;
        m_y = y;
    }
};

#endif /* Point2D_h */
