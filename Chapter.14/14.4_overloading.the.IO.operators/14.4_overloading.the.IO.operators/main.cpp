//
//  main.cpp
//  14.4_overloading.the.IO.operators
//
//  Created by Εκλεκτός εν Χριστώ on 7/22/23.
//

/*
 -------------------------------------------------------------------------------------------
 Case:
 
 Classes that have multiple member variables, printing each of the individual variables on
 the screen can get tiresome fast.
 
 -------------------------------------------------------------------------------------------
 OVERLOADING operator<<
 
 operator<< : is a binary operator
 
            std::cout << variable;
 
 cout: is the left operand, a count object
 variable: is the right operand, maybe a user-defined type object
 
 std::cout - is an object of type std::ostream
 
 our overloaded function will look like this:
 
            friend std::ostream& operator<<(std::ostream& out, const Type& type);
 
 std::ostream specifically disallows being copied, so return type should be a reference
 
 Anytime we want our overloaded operators to be chainable in a statement: the left operand
 should be returned by reference
 
 Returning the left hand parameter by reference is okay in this case: since the left-hand
 parameter was passed in by the caller function (main in this case), it must still exist
 when the called function(overloaded function) returns, so we don't have to worry about
 referencing something that will go out of scope and get destroyed when the operator returns
 
 -------------------------------------------------------------------------------------------
 OVERLOADING operator>>
 
 this is done in the same way as operator<< but-
 
 std::cin - is an object of type std::istream
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <numeric>      /// for std::gcd
#include <limits>



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
    
    friend std::ostream& operator<<(std::ostream& out, const Point& point);
    friend std::istream& operator>>(std::istream& in, Point& point);
};

/// return type should be a reference
/// if return type is return by value then the compiler will error
/// reason: std::ostream specifically disallows being copied
/// we return the left hand parameter as a reference
/// this prevents a copy of std::ostream from being made
/// it also allows to chain output commands together
std::ostream& operator<<(std::ostream& out, const Point& point)
{
    /// C++ already knows how to output doubles using operator<<
    /// we can use operator<< to output the member variables of our Point
    out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ")\n";
    
    return out;
}

/// parameter point is a non-const why?
/// so that we can modify the class members with the input values
std::istream& operator>>(std::istream& in, Point& point)
{
    in >> point.m_x;
    in >> point.m_y;
    in >> point.m_z;
    
    return in;
}
/*----------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------*/
class Fraction
{
private:
    int m_numerator{};
    int m_denominator{};

public:
    Fraction(int numerator=0, int denominator=1):
        m_numerator{numerator}, m_denominator{denominator}
    {
        /// We put reduce() in the constructor to ensure any new fractions we make get reduced!
        /// Any fractions that are overwritten will need to be re-reduced
        reduce();
    }

    void reduce()
    {
        int gcd{ std::gcd(m_numerator, m_denominator) };
        if (gcd)
        {
            m_numerator /= gcd;
            m_denominator /= gcd;
        }
    }

    friend Fraction operator*(const Fraction& f1, const Fraction& f2);
    friend Fraction operator*(const Fraction& f1, int value);
    friend Fraction operator*(int value, const Fraction& f1);
    
    friend std::ostream& operator<<(std::ostream& out, const Fraction& f1);
    friend std::istream& operator>>(std::istream& in, Fraction& f1);

    void print() const
    {
        std::cout << m_numerator << '/' << m_denominator << '\n';
    }
};

Fraction operator*(const Fraction& f1, const Fraction& f2)
{
    return Fraction(f1.m_numerator * f2.m_numerator, f1.m_denominator * f2.m_denominator);
}

Fraction operator*(const Fraction& f1, int value)
{
    return Fraction(f1.m_numerator * value, f1.m_denominator);
}

Fraction operator*(int value, const Fraction& f1)
{
    return Fraction(f1.m_numerator * value, f1.m_denominator);
}

std::ostream& operator<<(std::ostream& out, const Fraction& f1)
{
    out << f1.m_numerator << '/' << f1.m_denominator;
    return out;
}

std::istream& operator>>(std::istream& in, Fraction& f1)
{
    /// overwrite the values of f1
    in >> f1.m_numerator;
    
    /// ignore the '/' is user enters it when inputting the fraction
    in.ignore(std::numeric_limits<std::streamsize>::max(), '/');
    
    in >> f1.m_denominator;
    
    /// existing f1 was overwritten, so reduce it again
    f1.reduce();
    
    return in;
}

/*----------------------------------------------------------------------------------------*/



int main()
{
    Point point1{ 2.2, 3.9, 4.1 };
    Point point2{ 4.1, 6.7, 9.6 };
    
    /// here the std::cout has become the parameter out of the overloaded function -
    /// std::ostream& operator<<(std::ostream& out, const Point& point)
    /// out parameter will be a reference to std::cout when the function is called
    /// std::cout << point1 - returns std::cout
    /// then remaining expression std::cout << '\n' gets evaluated itself
    std::cout << point1 << '\n';
    
    /// chaining the binary operator<<
    std::cout << point1 << ", " << point2 << '\n';
    
    std::cout << "Enter the point: ";
    
    /// std::cin object - gets the input values and inserts them into point3 object
    Point point3{};
    std::cin >> point3;
    
    std::cout << "You entered: " << point3 << '\n';
    
    Fraction f1;
    std::cout << "Enter fraction 1: ";
    std::cin >> f1;

    Fraction f2;
    std::cout << "Enter fraction 2: ";
    std::cin >> f2;

    /// NOTE: the result of f1 * f2 - is an r-value
    std::cout << f1 << " * " << f2 << " is " << f1 * f2 << '\n';
    
    return 0;
}
