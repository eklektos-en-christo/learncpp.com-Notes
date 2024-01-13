//
//  main.cpp
//  14.6_overloading.unary.operators.+.-.and.!
//
//  Created by Εκλεκτός εν Χριστώ on 7/24/23.
//

/*
 -------------------------------------------------------------------------------------------
 Positive(+), Negative(-) and logical NOT(!) : all are unary operators, they operate only on
 one operand
 
 Unary operators: typically overloaded as a member function, all three operators are
 implemented in an identical manner.
 
 -------------------------------------------------------------------------------------------
 OVERLOADING UNARY OPERATORS:
 
 
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>



/*----------------------------------------------------------------------------------------*/
class Cents
{
private:
    int m_cents{};
    
public:
    Cents(int cents) : m_cents{ cents } {}
    
    /// overloading unary operator- as a member function
    /// operator- isn't modifying the Cents object, so should be const
    /// it can be called on const objects too because it is a const now
    Cents operator-() const;
    
    int get_cents() const { return m_cents; }
};

/// definition the overloaded member function
/// this operator operates on the implicit object *this
Cents Cents::operator-() const
{
    /// return type is Cents but this statement return an int
    /// implicit conversion from int to Cents using Cents(int) constructor
    return -m_cents;
}
/*----------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------*/
class Point
{
private:
    double m_x{};
    double m_y{};
    double m_z{};
    
public:
    Point(double x = 0.0, double y = 0.0, double z = 0.0)
    : m_x{ x }, m_y{ y }, m_z{ z }
    {
    }
    
    Point operator+() const;
    Point operator-() const;
    bool operator!() const;
    
    double get_x() const { return m_x; }
    double get_y() const { return m_y; }
    double get_z() const { return m_z; }
};

/// return a copy by value rather than const reference because
/// users of this function will probably expect the returned object to be modifiable
Point Point::operator+() const
{
    return *this;
}

/// convert the Point to its negative equivalent
Point Point::operator-() const
{
    return { -m_x, -m_y, -m_z };
}

/// overloading operator! as a member function
/// returns true if the point is set at the origin otherwise false
bool Point::operator!() const
{
    return (m_x == 0.0 && m_y == 0.0 && m_z == 0.0);
}

/*----------------------------------------------------------------------------------------*/



int main()
{
    const Cents cents1{ 10 };
    std::cout << "A nickel of debt is worth " << (-cents1).get_cents() << " cents.\n";
    
    Point point{};

    if (!point)
        std::cout << "Point is set at the origin!\n";
    else
        std::cout << "Point is not set at the origin!\n";
    
    return 0;
}
