//
//  main.cpp
//  14.13_copy.initialization
//
//  Created by Εκλεκτός εν Χριστώ on 7/26/23.
//

/*
 -------------------------------------------------------------------------------------------
 COPY INITIALIZATION FOR CLASSES:
 
 from the previous lesson
 
    Fraction six = Fraction(6);
 
 this form of copy initialization is evaluated the same way as the following:
 
    Fraction six(Fraction(6));
 
 this can potentially call both constructor and copy constructor, however elision isn't
 guaranteed, it's better to avoid copy initialization for classes
 
 BEST PRACTICE:
 avoid using copy initialization and use uniform initialization instead for classes
 
 -------------------------------------------------------------------------------------------
 OTHER PLACES WHERE THE COPY INITIALIZATION IS USED:
 
 -when you pass a class by value, this uses copy initialization
 -when you return a class by value, this uses copy initialization
 -------------------------------------------------------------------------------------------
 */

#include <iostream>

class Fraction
{
private:
    int m_numerator;
    int m_denominator;

public:
    /// Default constructor
    Fraction(int numerator=0, int denominator=1)
        : m_numerator(numerator), m_denominator(denominator)
    {
        assert(denominator != 0);
    }

    /// Copy constructor
    Fraction(const Fraction& copy) :
        m_numerator(copy.m_numerator), m_denominator(copy.m_denominator)
    {
        /// no need to check for a denominator of 0 here since copy must already be a valid Fraction
        std::cout << "Copy constructor called\n"; /// just to prove it works
    }

    friend std::ostream& operator<<(std::ostream& out, const Fraction& f1);
    int getNumerator() { return m_numerator; }
    void setNumerator(int numerator) { m_numerator = numerator; }
};

std::ostream& operator<<(std::ostream& out, const Fraction& f1)
{
    out << f1.m_numerator << '/' << f1.m_denominator;
    return out;
}

/// this function takes the Fraction by value and also returns the Fraction by value
/// the copy constructor is called twice, once when object fiveThirds is passed as an argument to this function
/// secondly, when function returns the Fraction back to the main()
/// in both cases elision doesn't take place
Fraction makeNegative(Fraction f) /// ideally we should do this by const reference
{
    f.setNumerator(-f.getNumerator());
    return f;
}


///if the argument or return value meet specific criteria, the compiler may opt to elide the copy constructor, like in below case:
class Something
{
public:
    Something() = default;
    Something(const Something&)
    {
        std::cout << "Copy constructor called\n";
    }
};

/// returning by value
Something foo()
{
    return Something(); /// copy constructor normally called here
}

/// returning by value
Something goo()
{
    Something s;
    return s; /// copy constructor normally called here
}


int main()
{
    Fraction fiveThirds(5, 3);
    
    /// when fiveThirds is passed, the copy constructor is called
    /// when the return value from makeNegative is passed back to main(), copy constructor is also called
    std::cout << makeNegative(fiveThirds);
    
    /// this would call copy constructor 4 times
    /// but due to copy elision it's likely that clang on this system will elide most or all of the cases
    /// clang is eliding all the cases
    std::cout << "Initializing s1\n";
    Something s1 = foo(); /// copy constructor normally called here

    std::cout << "Initializing s2\n";
    Something s2 = goo(); /// copy constructor normally called here
    
    return 0;
}
