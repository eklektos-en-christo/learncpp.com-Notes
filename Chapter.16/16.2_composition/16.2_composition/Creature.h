//
//  Creature.h
//  16.2_composition
//
//  Created by Εκλεκτός εν Χριστώ on 7/27/23.
//

#ifndef Creature_h
#define Creature_h

#include <iostream>
#include <string>
#include "Point2D.h"

/// Creature have a few properties: a name and a location
/// name will be a string, location will be our Point2D class
/// Creature is also a composition of its parts
/// name and location have one parent i.e. Creature
/// both's lifetime is tied to the instance of Creature
class Creature
{
private:
    std::string m_name;
    Point2D m_location;
    
public:
    Creature(const std::string& name, const Point2D& location)
    : m_name{ name }, m_location{ location }
    {
    }
    
    friend std::ostream& operator<<(std::ostream& out, const Creature& creature)
    {
        out << creature.m_name << " is at " << creature.m_location;
        return out;
    }
    
    void move_to(int x, int y)
    {
        m_location.set_point(x, y);
    }
};

#endif /* Creature_h */
