//
//  main.cpp
//  13.6_constructor.member.initializer.lists
//
//  Created by Εκλεκτός εν Χριστώ on 7/6/23.
//

/*
 -------------------------------------------------------------------------------------------
 Assigning values to const or reference member variables in the body of the constructor:
 not possible in some cases
 
 MEMBER INITIALIZER LISTS: a method for initializing class member variables, rather than
 assigning values to them after they are created, they can be initialized using member
 initialization list
 
 MEMBER INITIALIZER LISTS: not same as initializer list that we can use to assign values to
 arrays
 
 MEMBER INITIALIZATION LIST: is almost identical to doing direct or uniform initialization
 
 MEMBER INITIALIZATION LIST: is inserted after the constructor parameters, it begins with a
 colon(:), then lists each variable to initialize along with the value for that variable
 separated by a comma
 
 MEMBER INITIALIZATION LIST: doesn't end in a semicolon, construction body remains empty
 
 Caller: can also pass the arguments to constructor when constructor has parameters
 specified
 
 BEST PRACTICE
 Use member initializer lists to initialize your class member variables instead of
 assignment.
 
 -------------------------------------------------------------------------------------------
 INITIALIZING CONST MEMBER VARIABLES:
 
 Classes: can contain const member variables too, they acts same like the normal const
 variables, once initialized, their values cannot be changed thereafter
 
 Constructor member initialization list: we can use to initialize the const members in the
 constructor, the initialization value can be either constant or non-constant
 
 RULE:
 const member variables must be initialized
 
 -------------------------------------------------------------------------------------------
 INITIALIZING ARRAY MEMBERS WITH MEMBER INITIALIZATION LIST:
 
 A member array: can be fully initialized using uniform initialization in the constructor
 via the member initializer list
 
 -------------------------------------------------------------------------------------------
 INITIALIZING THE MEMBER VARIABLES THAT ARE CLASSES:
 
 Member initialization list: can also be used to initialize the members that are classes
 
 -------------------------------------------------------------------------------------------
 FORMATTING THE INITIALIZER LISTS:
 
 -If the initializer list fits on the same line as the function name, then it’s fine to put
 everything on one line
 
 -If the initializer list doesn’t fit on the same line as the function name, then it should
 go indented on the next line.
 
 -If all of the initializers don’t fit on a single line (or the initializers are
 non-trivial), then you can space them out, one per line
 
 -------------------------------------------------------------------------------------------
 INITIALIZER LIST ORDER:
 
 Variables in the initializer list: not initialized in the order that they are specified
 
 Variables in the initializer list: initialized in the order in which they are declared
 inside the class
 
 For best results:
 
 - don't initialize the member variables in such a way that they are dependent upon other
 member variables being initialized first, ensure your member variables will properly
 initialize even if the initialization ordering is different
 
 - initialize the variables in the initializer list in the same order in which they are
 declared in the class, this isn't strictly required so long as the prior recommendation has
 been followed
 
 -------------------------------------------------------------------------------------------
 SUMMARY:
 
 Member initializer lists: allow to initialize the members rather than assign values to them
 
 Member initializer lists: this is the only way to initialize the members that require
 values upon initialization e.g. const or reference members
 
 Member initializer lists: can be more performant then using assignments in the constructor
 
 Member initializer lists: work with fundamental types and members that are classes
 themselves
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <cstdint>

class Something
{
private:
    int m_value1 {};
    double m_value2 {};
    char m_value3 {};
    
public:
    /// initialize the member variables using member initialization list
    /// no need of semicolon at the end of the initialization list
    /// : and , - are necessary
    Something() : m_value1{ 1 }, m_value2{ 2.2 }, m_value3{ 'c' }
    {
        /// no need to do assignments inside the constructor body
    }
    
    /// caller can also pass in the initialization values
    /// value3 - default parameter if user doesn't provide the value
    Something(int value1, double value2, char value3 = 'c')
    : m_value1{ value1 }, m_value2{ value2 }, m_value3{ value3 }
    {
    }
    
    void print()
    {
        std::cout << "Something(" << m_value1 << ", " << m_value2 << ", ";
        std::cout << m_value3 << ")\n";
    }
};

class Const
{
private:
    /// const member variable
    const int m_value {};

public:
    /// using the constructor member initialization to initialize the const member m_value
    /// the value is provided by the user
    Const(int x) : m_value{ x }
    {
    }
    
    void print() { std::cout << "Const: " << m_value << '\n'; }
};

class Array
{
private:
    /// constant array as the member of class Array
    const int m_array[5];
    
public:
    /// zero initialize the const member array using constructor member initializer list
    /*Array() : m_array {}
    {
    }*/
    
    /// fully initialize the const member array using uniform initialization in the constructor
    Array() : m_array { 1, 2, 3, 4, 5}
    {
    }
    
    void print()
    {
        std::cout << "Array: ";
        for (int i{ 0 }; i < std::size(m_array); ++i)
            std::cout << m_array[i] << ' ';
        std::cout << '\n';
    }
};

class A
{
public:
    A(int x = 0) { std::cout << "Class A: " << x << '\n'; }
};

class B
{
private:
    A m_a {};
    
public:
    /// m_a is a class member variable in B
    /// using member initializer list to initialize the m_a
    /// constructor A(int) of class A will be called to initialize m_a
    /// then B(int)'s body executes
    B(int y) : m_a{ y - 1 }
    {
        std::cout << "Class B: " << y << '\n';
    }
};

/*----------------------------------------------------------------------------------------*/
class RGBA
{
private:
    std::uint8_t m_red {};
    std::uint8_t m_green {};
    std::uint8_t m_blue {};
    std::uint8_t m_alpha {};
    
public:
    RGBA(std::uint8_t red = 0, std::uint8_t green = 0, std::uint8_t blue = 0, std::uint8_t alpha = 255) : m_red{ red }, m_green{ green }, m_blue{ blue }, m_alpha{ alpha }
    {
    }
    
    void print()
    {
        std::cout << "Red: \t" << static_cast<int>(m_red) << '\n';
        std::cout << "Green: \t" << static_cast<int>(m_green) << '\n';
        std::cout << "Blue: \t" << static_cast<int>(m_blue) << '\n';
        std::cout << "Alpha: \t" << static_cast<int>(m_alpha) << '\n';
    }
};
/*----------------------------------------------------------------------------------------*/

int main()
{
    Something s1{};
    s1.print();
    
    Something s2{ 2, 2.3 };
    s2.print();
    
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;
    
    Const c{ x };
    c.print();
    
    Array a{};
    a.print();
    
    B b{ 20 };
    
    RGBA teal{ 0, 127, 127 };
    teal.print();
    
    return 0;
}
