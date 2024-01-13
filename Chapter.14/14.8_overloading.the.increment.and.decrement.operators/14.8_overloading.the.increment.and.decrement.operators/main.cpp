//
//  main.cpp
//  14.8_overloading.the.increment.and.decrement.operators
//
//  Created by Εκλεκτός εν Χριστώ on 7/25/23.
//

/*
 -------------------------------------------------------------------------------------------
 Increment/decrement operators: Unary operators, they modify their operands, it's best to
 overload them as member functions
 
 -------------------------------------------------------------------------------------------
 OVERLOADING THE PREFIX INCREMENT & PREFIX DECREMENT:
 
 both ++ and -- return *this, so multiple objects can be "chained" together
 
 OVERLOADING THE POSTFIX INCREMENT & POSTFIX DECREMENT:

 C++ has special case, compiler looks for an int parameter in the postfix overload version
 if there is no int in the parameter then the compiler takes the overload prototype as a
 prefix overload version
 
 Postfix version is less efficient than the prefix version: because of the temporary
 instantiation and returning by value instead of reference
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>

/// class holds a number between 0 and 9
class Digit
{
private:
    int m_digit{};
    
public:
    Digit(int digit = 0) : m_digit{ digit } {}
    
    /// prefix version has no parameters
    Digit& operator++();
    Digit& operator--();
    
    /// postfix version has parameters to distinguish them from prefix version
    /// int parameter is without name because we aren't using it inside the function
    /// int is treated as a placeholder
    Digit operator++(int);
    Digit operator--(int);
    
    friend std::ostream& operator<<(std::ostream& out, const Digit& d);
};

Digit& Digit::operator++()
{
    /// if digit is already at 9, wrap around to 0
    if (m_digit == 9)
        m_digit = 0;
    else
        /// if not at 9, simply increment the digit
        ++m_digit;
    
    /// both ++ and -- return *this, so multiple objects can be "chained" together
    /// Note: returning the digit after it has been modified
    return *this;
}

Digit& Digit::operator--()
{
    /// if digit is already at 0, wrap around to 9
    if (m_digit == 0)
        m_digit = 9;
    else
        /// if not at 0, simply decrement the digit
        --m_digit;
    
    return *this;
}

/// int parameter means it is postfix version
/// not returning by reference because return value is temporary
/// so no need to return by reference
Digit Digit::operator++(int)
{
    /// save the current state of the digit in a temporary Digit variable
    Digit temp{ *this };
    
    /// use prefix version to increment the digit
    /// the prefix operator++ called here to do the work
    ++(*this);
    
    /// return the temporary saved digit
    /// behind the scenes, the original digit is incremented
    /// return value is destroyed after the function exits
    /// so we can't return a local variable by reference
    return temp;
}

/// int parameter means it is postfix version
/// this int parameter is a special case in C++
/// compiler looks for int parameter to distinguish between the prefix and postfix version
Digit Digit::operator--(int)
{
    Digit temp{ *this };
    
    /// the prefix operator-- called here to do the work
    --(*this);
    
    /// the caller receives a copy of the original digit
    /// the copy is the pre-modified state of original digit
    return temp;
}

std::ostream& operator<<(std::ostream& out, const Digit& d)
{
    out << d.m_digit;
    return out;
}

int main()
{
    Digit digit(8);
    
    std::cout << digit << '\n';
    std::cout << ++digit << '\n';
    std::cout << ++digit << '\n';
    std::cout << --digit << '\n';
    std::cout << --digit << '\n';
    
    Digit digit2(5);
    
    std::cout << digit2;
    std::cout << ++digit2;
    std::cout << digit2++;
    std::cout << digit2;
    std::cout << --digit2;
    std::cout << digit2--;
    std::cout << digit2 << '\n';
    
    return 0;
}
