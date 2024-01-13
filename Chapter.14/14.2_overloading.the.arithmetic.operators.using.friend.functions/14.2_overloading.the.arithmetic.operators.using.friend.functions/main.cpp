//
//  main.cpp
//  14.2_overloading.the.arithmetic.operators.using.friend.functions
//
//  Created by Εκλεκτός εν Χριστώ on 7/21/23.
//

/*
 -------------------------------------------------------------------------------------------
 Most commonly used operators in C++: Arithmetic operators( +, -, *, / )
 
 Arithmetic operators: are binary operators, they take two operands on each side of operator
 
 This means they all four are overloaded in the exact same way
 
 THREE DIFFERENT WAYS TO OVERLOAD OPERATORS:
 -member functions way
 -friend function way
 -normal function way
 
 -------------------------------------------------------------------------------------------
 OVERLOADING OPERATORS USING FRIEND FUNCTIONS:
 
 Overloading the operator+ : is simple as declaring a function with name operator+, giving
 it two parameters of the type of the operands we want to add, picking up appropriate return
 type and writing the function
 
 -------------------------------------------------------------------------------------------
 FRIEND FUNCTIONS: can be defined inside the class but it is not recommended
 
 -non-trivial function definitions are better kept in a separate .cpp file, outside of the
 class
 
 -------------------------------------------------------------------------------------------
 OVERLOADING OPERATORS FOR OPERANDS OF DIFFERENT TYPES:
 
 int x;
 int y;
 
 x + y; or y + x; - the same version of operator+ gets called, because both types are same
 
 int x;
 double y;
 
 x + y or y + x; - the same version of operator+ isn't called, because operands are of
 different types
 
 Solution:
 Whenever we overload binary operators for operands of different types: we actually need to
 write two functions, one for each case
 
 -------------------------------------------------------------------------------------------
 IMPLEMENTING OPERATORS USING OTHER OPERATORS:
 
 It is often possible: to define overloaded operators by calling other overloaded operators
 
 It is useful: when doing so produces simpler code
 
 In cases: where the implementation is trivial(e.g. a single line) , it may or may not be
 worth it
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <numeric>      /// for std::gcd


/*----------------------------------------------------------------------------------------*/
class Cents
{
private:
    int m_cents{};
    
public:
    Cents(int cents) : m_cents{ cents } {}
    int get_cents() const { return m_cents; }
    
    /// add two Cents objects using a friend function
    friend Cents operator+(const Cents& c1, const Cents& c2);
    
    /// subtract two Cents objects using a friend function
    friend Cents operator-(const Cents& c1, const Cents& c2);
    
    /// add Cents + int using a friend function, order of parameters is Cents, int
    friend Cents operator+(const Cents& c1, int value);
    
    /// add int + Cents using a friend function, here the order is different
    friend Cents operator+(int value, const Cents& c1);
};

/// this is an outer function, not a member function of the Cents class
/// but it is a friend of Cents, so it can work with Cents objects
/// function takes two Cents(parameters) objects and return an Cent object(return type)
Cents operator+(const Cents& c1, const Cents& c2)
{
    /// + here is already implemented in the library for int datatype, so this works
    /// constructor is implicitly called here to create a new Cents object which stores the result of subtraction
    return c1.m_cents + c2.m_cents;
}

Cents operator-(const Cents& c1, const Cents& c2)
{
    return c1.m_cents - c2.m_cents;
}

/// adds Cents + int, both operands are of different types
Cents operator+(const Cents& c1, int value)
{
    std::cout << "operator+(Cents, int) called!\n";
    return c1.m_cents + value;
}

/// adds int + Cents, only the order of parameter is different, different operands both
Cents operator+(int value, const Cents& c1)
{
    std::cout << "operator+(int, Cents) called!\n";
    return c1.m_cents + value;
}
/*----------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------*/
/// class keeps track of the minimum and maximum values that it has seen so far
class MinMax
{
private:
    int m_min{};
    int m_max{};
    
public:
    MinMax(int min, int max) : m_min{ min }, m_max{ max } {}
    
    int get_min() const { return m_min; }
    int get_max() const { return m_max; }
    
    friend MinMax operator+(const MinMax& m1, const MinMax& m2);
    friend MinMax operator+(const MinMax& m, int value);
    friend MinMax operator+(int value, const MinMax& m);
};

/// add two MinMax objects together
MinMax operator+(const MinMax& m1, const MinMax& m2)
{
    /// get the minimum value seen in m1 and m2
    int min{ m1.m_min < m2.m_min ? m1.m_min : m2.m_min };
    
    /// get the maximum value seen in m1 and m2
    int max{ m1.m_max > m2.m_max ? m1.m_max : m2.m_max };
    
    return { min, max };
}

/// add MinMax and integer
MinMax operator+(const MinMax& m, int value)
{
    /// get the minimum value seen in m and value
    int min{ m.m_min < value ? m.m_min : value };
    
    /// get the maximum value seen in m and value
    int max{ m.m_max > value ? m.m_max : value };
    
    return { min, max };
}

/// add integer and MinMax
MinMax operator+(int value, const MinMax& m)
{
    /// parameters' position interchanged in return statement
    /// this statement will call the operator+(MinMax, int)
    /// reduces the implementation, minimizes redundancy,
    /// makes the function simpler to understand
    return m + value;
}
/*----------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------*/
class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };
    
public:
    Fraction(int num, int den = 1)
        : m_numerator{ num }, m_denominator{ den }
    {
        reduce();
    }
    
    void print() const
    {
        std::cout << "Fraction: " << m_numerator << '/';
        std::cout << m_denominator << '\n';
    }
    
    void reduce()
    {
        int gcd{ std::gcd(m_numerator, m_denominator) };
        if (gcd) // Make sure we don't try to divide by 0
        {
            m_numerator /= gcd;
            m_denominator /= gcd;
        }
    }
    
    friend Fraction operator*(const Fraction& f1, const Fraction& f2);
    friend Fraction operator*(const Fraction& f, int value);
    friend Fraction operator*(int value, const Fraction& f);
};

Fraction operator*(const Fraction& f1, const Fraction& f2)
{
    /*int numerator{ f1.m_numerator * f2.m_numerator };
    int denominator{ f1.m_denominator * f2.m_denominator };*/
    
    return { f1.m_numerator * f2.m_numerator, f1.m_denominator * f2.m_denominator };
}

Fraction operator*(const Fraction& f, int value)
{
    /*int numerator{ f.m_numerator * value };*/
    
    return { f.m_numerator * value, f.m_denominator };
}

Fraction operator*(int value, const Fraction& f)
{
    return f * value;
}

/*----------------------------------------------------------------------------------------*/



int main()
{
    Cents c1{ 23 };
    Cents c2{ 18 };
    Cents sum_of_cents{ c1 + c2 };
    std::cout << "I've " << sum_of_cents.get_cents() << " cents.\n";
    
    Cents c3{ 100 };
    Cents c4{ 10 };
    Cents sub_of_cents{ c3 - c4 };
    std::cout << "I've " << sub_of_cents.get_cents() << " cents.\n";
    
    /// operator+(Cents, int) called, first version
    Cents c5{ Cents{ 10 } + 2 };
    /// operator+(int, Cents) called, second version
    Cents c6{ 8 + Cents{ 10 } };
    std::cout << "I've " << c5.get_cents() << " cents.\n";
    std::cout << "I've " << c6.get_cents() << " cents.\n";
    
    MinMax m1{ 10, 15 };
    MinMax m2{ 8, 11 };
    MinMax m3{ 3, 12 };
    
    /// operator+ evaluates from left to right
    /// m1+m2 : evaluates first
    /// MinMax(8, 15) + 5 : evaluates next
    /// MinMax(5, 15) + 8 : evaluates next
    /// MinMax(5, 15) + m3 : evaluates next
    /// MinMax(3, 15) + 16 : evaluates next
    /// at last the return value initializes the m_final object
    /// each successive operation returning a MinMax object
    /// that object becomes the left hand operand for the following operator
    MinMax m_final{ m1 + m2 + 5 + 8 + m3 + 16 };
    
    std::cout << "Result: (" << m_final.get_min() << ", ";
    std::cout << m_final.get_max() << ")\n";
    
    /*Fraction f1{ 1, 4 };
    f1.print();
    
    Fraction f2{ 1, 2 };
    f2.print();*/
    
    Fraction f1{2, 5};
    f1.print();

    Fraction f2{3, 8};
    f2.print();

    Fraction f3{ f1 * f2 };
    f3.print();

    Fraction f4{ f1 * 2 };
    f4.print();

    Fraction f5{ 2 * f2 };
    f5.print();

    Fraction f6{ Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4} };
    f6.print();

    
    return 0;
}
