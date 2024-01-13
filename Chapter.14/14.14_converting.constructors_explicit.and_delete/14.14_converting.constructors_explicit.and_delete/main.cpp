//
//  main.cpp
//  14.14_converting.constructors_explicit.and_delete
//
//  Created by Εκλεκτός εν Χριστώ on 7/26/23.
//

/*
 -------------------------------------------------------------------------------------------
 BY DEFAULT: C++ will treat any constructor as an implicit conversion operator
 
 constructor can be used as an implicit conversion operator when it can be invoked with a
 single argument(other than the class itself) and is not marked with the 'explicit'
 It means C++ will use the constructor to convert an object of the argument type to an
 object of the class type when needed
 
 CONVERTING CONSTRUCTORS/CONVERSION CONSTRUCTORS: constructors eligible to be used for
 implicit conversions
 
 IMPLICIT CONVERSION: works for all kinds of initialization(copy & direct)
 
 -------------------------------------------------------------------------------------------
 THE explicit KEYWORD:
 
 Doing implicit conversions: may be undesirable or lead to unexpected behaviors in some
 cases
 
 To address this issue: make constructors and conversion functions explicit
 
 explicit: keyword, placed in front of the function's name
 
 explicit constructors & conversion functions: will not be used for implicit conversions or
 copy initialization
 
 Note: explicit only prevents the implicit conversions, explicit conversions via casting
 are still allowed
 
 Direct or uniform initialization: still convert parameters to match
 
 Uniform initialization will not do narrowing but it will do other types of conversions
 
 BEST PRACTICE:
 consider making the constructors and user-defined conversion member functions explicit to
 prevent implicit conversion errors
 
 -------------------------------------------------------------------------------------------
 THE delete KEYWORD:
 
 one way to partially disallow implicit/explicit conversion is to add a MyString(char)
 constructor and make it private
 
 Better way: is to use the "delete" keyword to delete the function
 
 When a function has been deleted: any use of that function is considered a compile error
 
 COPY CONSTRUCTOR & OVERLOADED OPERATORS: may also be deleted in order to prevent those
 function from being used for conversion
 
 -------------------------------------------------------------------------------------------
 */

#include <cassert>
#include <iostream>
#include <string>



/*----------------------------------------------------------------------------------------*/
class Fraction
{
private:
    int m_numerator;
    int m_denominator;

public:
    /// Default constructor
    Fraction(int numerator = 0, int denominator = 1)
         : m_numerator(numerator), m_denominator(denominator)
    {
        assert(denominator != 0);
    }

    /// Copy constructor
    Fraction(const Fraction& copy)
        : m_numerator(copy.m_numerator), m_denominator(copy.m_denominator)
    {
        /// no need to check for a denominator of 0 here since copy must already be a valid Fraction
        std::cout << "Copy constructor called\n"; /// just to prove it works
    }

    friend std::ostream& operator<<(std::ostream& out, const Fraction& f1);
    int getNumerator() { return m_numerator; }
    void setNumerator(int numerator) { m_numerator = numerator; }
};

void printFraction(const Fraction& f)
{
    std::cout << f << '\n';
}

std::ostream& operator<<(std::ostream& out, const Fraction& f1)
{
    out << f1.m_numerator << '/' << f1.m_denominator;
    return out;
}
/*----------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------*/
class MyString
{
private:
    std::string m_string{};
    
    /// one way to disallow the 'x' from being converted to MyString
    /// making constructor private, so it won't we called outside of the class
    /*MyString(char) {}*/
    
public:
    /// another way to completely disallow the conversion
    /// this constructor can't be used, if used, it will produce an error
    MyString(char) = delete;
    
    /// constructor is marked as explicit
    /// now it is ineligible for implicit conversions
    explicit MyString(int x)
    {
        m_string.resize(x);
    }
    
    MyString(const char* string)
    {
        m_string = string;
    }
    
    friend std::ostream& operator<<(std::ostream& out, const MyString& s);
};

std::ostream& operator<<(std::ostream& out, const MyString& s)
{
    out << s.m_string;
    return out;
}

void print_string(const MyString& s)
{
    std::cout << s << '\n';
}
/*----------------------------------------------------------------------------------------*/



int main()
{
    /// printFraction is expecting a Fraction type, but we provided an integer literal
    /// Fraction has a constructor that can take a single integer
    /// compiler will implicitly convert the 6 into a fraction object with the help of default constructor
    /// then parameter f or printFraction is initialized
    /// so the constructor was treated as an implicit conversion operator
    printFraction(6);
    
    /// trying to initialize a string with a char
    /// the compiler will use the converting constructor MyString(int) to implicitly convert the char to MyString
    /// but when printing the results, it has unexpected results
    /*MyString mine = 'x';
    std::cout << mine << '\n';*/
    
    /// error:  conversion function is explicit, it can't be called for implicit conversion of 'x' to MyString
    /*MyString mine = 'x';
    std::cout << mine << '\n';*/
    
    /// call to this function causes implicit conversion of x to MyString
    /// the result is unexpected
    /*print_string('x');*/
    
    /// error:  conversion function is explicit, it can't be called for implicit conversion of 'x' to MyString
    /*print_string('x');*/
    
    /// explicit casts are allowed
    /// not working because constructor MyString(char) is deleted
    /*print_string(static_cast<MyString>('x'));*/
    
    /// 'x' implicitly converted to MyString because of the uniform {} initialization
    /// not working because constructor MyString(char) is deleted
    /*MyString string{ 'x' };
    print_string(string);*/

    return 0;
}
