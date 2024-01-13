//
//  main.cpp
//  25.12_summary.and.quiz
//
//  Created by Εκλεκτός εν Χριστώ on 11/14/23.
//

/*
 SUMMARY:
 
 C++ - allows to set base pointers/references to a derived object, this is useful when we want to write a
 function or array that can work with any type of object derived from a base class
 
 Without virtual functions, base class pointers/references to a derived class will only have access to base
 class member variables and versions of functions
 
 Virtual function: special type of function that resolves to the most-derived version of the function that
 exists between the base and derived class
 
 The derived class function must have the same signature and return type as the virtual base class function
 
 Covariant return types: they allow an override to return a pointer or reference to a derived class if the
 base class function returns a pointer or reference to the base class
 
 override specifier: should be used for the function that is intended to be an override to ensure that it is
 actually an override
 
 final specifier: can be used to prevent overrides of a function or inheritance from a class
 
 If you intend to use the inheritance, you should make the destructor virtual, so the proper destructor is
 called if a pointer to the base class is deleted
 
 To ignore the virtual function resolution: simply specify which class's version of the function you want by
 using the :: operator e.g. base.Base::get_name()
 
 Early binding: when compiler encounters a direct function call
 
 Late binding: when a function pointer is called, in these cases function that is to be called will not be
 resolved until runtime
 
 Virtual functions: use late binding and a virtual table to determine which version of the function to call
 
 Virtual table: increases the size of every object containing a virtual function by one pointer
 
 Virtual function: can be made pure virtual/abstract by adding =0 to the end of the prototype
 
 Class: containing a pure virtual function is called an abstract class and can't be instantiated
 
 A class that inherits pure virtual functions must concretely define them or it will also be considered
 an abstract class
 
 Pure virtual functions: can have a body but they are still considered abstract
 
 Interface class: one with no member variables and all pure virtual functions, these are often named
 starting with a capital I
 
 Virtual base class: a base class that is only included once, no matter how many times it is inherited by an
 object
 
 When a derived class is assigned to a base class, the base class only receives a copy of the base portion
 of the derived class, this is called object slicing
 
 Dynamic casting: used to convert a pointer to a base class object into a pointer to a derived class object
 this is called downcasting, a failed dynamic cast will return a null pointer
 
 the easiest way to overload operator<< for  inherited classes is to write an overloaded operator<< for the
 most-base class and then call a virtual member function to do the printing
 
 Override: the most derived version of the function
 */

#include <iostream>
#include <vector>
#include <algorithm>

class Point
{
private:
    int m_x{};
    int m_y{};

public:
    Point(int x, int y)
        : m_x{ x }, m_y{ y }
    {
    }

    friend std::ostream& operator<<(std::ostream& out, const Point& p)
    {
        return out << "Point(" << p.m_x << ", " << p.m_y << ')';
    }
};

class Shape
{
public:
    virtual std::ostream& print(std::ostream& out) const = 0;
    friend std::ostream& operator<<(std::ostream& out, const Shape& s)
    {
        return s.print(out);
    }
    virtual ~Shape() = default;
};

class Triangle : public Shape
{
private:
    Point m_p1;
    Point m_p2;
    Point m_p3;
    
public:
    Triangle(const Point& p1, const Point& p2, const Point& p3)
    : m_p1{ p1 }, m_p2{ p2 }, m_p3{ p3 }
    {
    }
    
    std::ostream& print(std::ostream& out) const override
    {
        return out << "Triangle(" << m_p1 << ", " << m_p2 << ", " << m_p3 << ")";
    }
};

class Circle : public Shape
{
private:
    Point m_center;
    int m_radius{};
    
public:
    Circle(const Point& p, int radius)
    : m_center{ p }, m_radius{ radius }
    {
    }
    
    std::ostream& print(std::ostream& out) const override
    {
        return out << "Circle(" << m_center << ", " << m_radius << ")";
    }
    
    int get_radius() const { return m_radius; }
};

int getLargestRadius(const std::vector<Shape*>& v)
{
    int largest_radius{ 0 };
    
    for (const auto* element : v)
    {
        if (auto * c{ dynamic_cast<const Circle*>(element) })
            largest_radius = std::max(largest_radius, c->get_radius());
    }
    
    return largest_radius;
}

int main()
{
    Circle c{ Point{ 1, 2 }, 7 };
    std::cout << c << '\n';

    Triangle t{Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 }};
    std::cout << t << '\n';
    
    std::vector<Shape*> v
    {
        new Circle{Point{ 1, 2 }, 7},
        new Triangle{Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 }},
        new Circle{Point{ 7, 8 }, 3}
    };
    
    for (const auto* element : v)
        std::cout << *element << '\n';
    
    std::cout << "The largest radius is: " << getLargestRadius(v) << '\n';
    
    for (const auto* element : v)
        delete element;
    
    return 0;
}
