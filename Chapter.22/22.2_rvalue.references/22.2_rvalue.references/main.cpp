//
//  main.cpp
//  22.2_rvalue.references
//
//  Created by Εκλεκτός εν Χριστώ on 12/6/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 L-value references: can only be initialized with modifiable L-values
 L-value references to const: can be initialized with modifiable and non-nonmodifiable L-values and R-values
 
 R-value reference: is designed to be initialized with an r-value only
 R-value reference: is created using a double ampersand &&, l-value is created using single ampersand &
 R-value references: can't be initialized with L-values
 
 R-value properties:
 - rvalue references extend the lifespan of the object they are initialized with to the lifespan of the
   rvalue reference
 - non-const rvalue references allow to modify the rvalue
 
 When initializing an r-value reference with a literal, a temporary object is constructed from the literal
 so that the reference is referencing a temporary object, not a literal value.
 
 R-value references: are more often used as function parameters, this is most useful for function overloads
 when you want to have different behavior for l-value and r-value arguments
 
 R-value reference variables: are l-values
 
 The type of an object and its value category are independent, the general rule is that named variables are
 lvalues, regardless of their type or how they were initialized.
 
 A literal (2) is an rvalue of type (int) and (int x) is an lvalue of type (int), similarly (int&& ref) is
 an lvalue of type (int&&)
 
 When you bind an rvalue to an rvalue reference, the result is an lvalue.
 
 Returning an r-value reference: never return an r-value reference, it might end up returning a hanging
 reference when the referenced object goes out of scope at the end of the function
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };
    
public:
    Fraction(int num=0, int den=1)
    : m_numerator{ num }, m_denominator{ den }
    {
    }
    
    /// parameter f1 binds to the temporary Fraction object being passed from main,
    /// no copy of Fraction will be created
    friend std::ostream& operator<<(std::ostream& out, const Fraction& f1)
    {
        out << f1.m_numerator << '/' << f1.m_denominator;
        return out;
    }
};

void fun(const int& lvalue_ref)
{
    std::cout << "lvalue reference to const: " << lvalue_ref << '\n';
}

void fun(int&& rvalue_ref)
{
    std::cout << "rvalue reference: " << rvalue_ref << '\n';
}

int main()
{
    int x{ 8 };
    int& lvalue_reference{ x };
    int&& rvalue_reference{ 8 };
    
    /// Fraction{ 2, 4 } is a temporary object
    /// r-value reference rvalue_ref is bound to temporary fraction
    /// Fraction temporary would go out of scope after the expression but
    /// it's lifetime has been extended because of initializing an rvalue reference with it
    /// Fraction temporary will remain until the end of the block
    auto&& rvalue_ref{ Fraction{ 2, 4 } };
    
    /// rvalue_ref can be used to print the Fraction's value
    std::cout << rvalue_ref << '\n';
    
    /// rvalue_ref1 is referencing a temporary object and not a literal 98696
    int&& rvalue_ref1{ 98696 };
    rvalue_ref1 = 28989;
    std::cout << rvalue_ref1 << '\n';
    
    /// overloaded fun called differently depending upon the type of arguments, either rvalue or lvalue
    fun(2);             /// 2 is r-value
    fun(x);             /// x is l-value
    
    /// rvalue_reference is an rvalue reference variable
    /// fun(int&) is called
    /// rvalue_reference is of type int&& but when used in an expression it is an lvalue, as are all named variable
    /// rvalue_reference behaves as n lvalue in the function call,
    /// this is consistent with the general rule that named variables are lvalues, regardless of their type or how they were initialized.
    fun(rvalue_reference);
    
    return 0;
}   /// temporary Fraction and rvalue_ref goes out of scope here
