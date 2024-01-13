//
//  main.cpp
//  13.7_non.static.member.initialization
//
//  Created by Εκλεκτός εν Χριστώ on 7/7/23.
//

/*
 Normal class member variables: those that don't use static keyword
 
 It is possible: to give normal class member variables a default initialization value
 directly
 
 NON STATIC MEMBER INITIALIZATION:
 provides default values to the member variables that the constructors will use if the
 constructor don't provide initialization values for the members via the member initializer
 list
 
 NOTE: constructors still determine what kind of objects may be created
 
 If a default value is provided and constructor initializes the member via the member
 initializer list: then initializer list will take precedence
 
 Parentheses() initialization: won't work when initializing members using non-static member
 initialization, either an equals sign or a brace initializer will work
 
 RULE:
 -favor use of non-static member initialization to give default values for the member
 variables
 */

#include <iostream>
#include <string>
#include <string_view>

class Rectangle
{
private:
    /// these both are normal member variables(non static)
    /// they can be initialized to default values directly
    /// only {} or = can be used to initialize, () won't work
    double m_length{ 1.0 };
    double m_width{ 1.0 };
    /// parentheses won't work when initializing a member using non-static member initialization
//    double test(1.0);
    
public:
    void print()
    {
        std::cout << "Length: " << m_length << '\n';
        std::cout << "Width: " << m_width << '\n';
    }
};

class Rectangle2
{
private:
    double m_length{ 1.0 };
    double m_width{ 1.0 };
    
public:
    /// no default constructor provided
    /// the members are initialized by the parameterized constructor
    /// the default values aren't used
    Rectangle2(double length, double width) : m_length{ length }, m_width{ width }
    {
    }
    
    /// m_length is initialized by the constructor
    /// m_width used the default value 1.0
    Rectangle2(double length) : m_length{ length }
    {
    }
    
    void print()
    {
        std::cout << "Length: " << m_length << '\n';
        std::cout << "Width: " << m_width << '\n';
    }
};

class Ball
{
private:
    std::string m_color { "black" };
    double m_radius { 10.0 };

public:
    // Default constructor with no parameters
    Ball() = default;

    // Constructor with only color parameter (radius will use default value)
    Ball(std::string_view color) : m_color{ color }
    {
    }

    // Constructor with only radius parameter (color will use default value)
    Ball(double radius) : m_radius{ radius }
    {
    }

    // Constructor with both color and radius parameters
    Ball(std::string_view color, double radius) : m_color{ color }, m_radius{ radius }
    {
    }

    void print()
    {
        std::cout << "color: " << m_color << ", radius: " << m_radius << '\n';
    }
};

int main()
{
    Rectangle x{};
    x.print();
    
    /// error: no default values are provided in the parameterized constructor
    /// no default constructor provided
    /// members have default initialization values but still
    /// the constructor determines what kind of objects may be created
    /// y{} - calls constructor with no arguments, but no constructor provided with empty parameters
    Rectangle2 y{ 2.2 };
    y.print();
    
    Rectangle2 z{ 2.1, 7.8 };
    z.print();
    
    Ball def;
    def.print();

    Ball blue{ "blue" };
    blue.print();

    Ball twenty{ 20.0 };
    twenty.print();

    Ball blueTwenty{ "blue", 20.0 };
    blueTwenty.print();
    
    return 0;
}
