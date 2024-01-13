//
//  main.cpp
//  14.5_overloading.operators.using.member.functions
//
//  Created by Εκλεκτός εν Χριστώ on 7/22/23.
//

/*
 -------------------------------------------------------------------------------------------
 OPERATORS: can be overloaded as a member function
 
 When overloading an operator using a member function:
 
 -overloaded operator must be added as a member function of the left operand
 -the left operand becomes the implicit *this object
 -all other operands become function parameters
 
 -------------------------------------------------------------------------------------------
 NOT EVERYTHING CAN BE OVERLOADED AS A FRIEND FUNCTION:
 
 following operators must be overload as a member function, C++ requires that:
 operator=
 operator[]
 operator()
 operator->
 
 NOT EVERYTHING CAN BE OVERLOADED AS A MEMBER FUNCTION:
 
 Example: we can't overload operator<< as a member function when left operand is an object
 of type std::ostream or similar type, overloaded operator must be added as a member of the
 left operand, std::ostream class is fixed, we can't modify the class declaration to add
 operator<< as a member function of std::ostream
 
 this necessitates that operator<< should be overloaded as a normal(preferred) or friend
 function
 
 We can overload operator+(Cents, int) as a member function, but we can't overload
 operator+(int, Cents) because int isn't a class we can add members to
 
 FINALLY:
 WE WON'T BE ABLE TO USE A MEMBER OVERLOAD IF THE LEFT OPERAND IS A CLASS WHICH WE CAN'T
 MODIFY like std::ostream or IF THE LEFT OPERAND ISN'T A CLASS like int
 
 -------------------------------------------------------------------------------------------
 WHEN TO USE NORMAL, FRIEND OR MEMBER FUNCTION OVERLOAD?
 
 Binary operators that don't modify the left operand:
 
 -the normal or friend function version is typically preferred because it works for all
 parameter types, even when the left operand isn't a class object or is a class that is not
 modifiable, all the operands become explicit parameters
 
 Binary operators that do modify the left operand:
 
 -the member function version is typically preferred, in these cases the leftmost operand
 will always be a class type and having the object being modified become the one pointed to
 by *this is natural, the rightmost operand becomes an explicit parameter, so no confusion
 who is getting modified and who is getting evaluated
 
 UNARY OPERATORS: usually overloaded as member functions as well because the member version
 has not parameters, unary operator works on the implicit object itself
 
 RULES THAT CAN HELP TO DETERMINE WHICH FOR IS BEST FOR A GIVEN SOLUTION:
 
 If overloading assignment=, subscript[], function call(), member selection->, do so as a
 member function
 
 If overloading a unary operator, do so as a member function
 
 If overloading a binary operator that doesn't modify left operand, do so as a normal
 function or friend function
 
 If overloading a binary operator that do modify the left operand but you can't add members
 to the class definition of the left operand, do so as a normal function or friend function
 
 If overloading a binary operator that modifies the left operand and you can modify the
 definition of the left operand, do so as a member function
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>

class Cents
{
private:
    int m_cents{};
    
public:
    Cents(int cents) : m_cents{ cents } {}
    
    /// overloading the operator+ as a member function
    Cents operator+(int value);
    
    int get_cents() const { return m_cents; }
};

/// this is a member function
/// the left operand is the implicit object and right operand in the int value
Cents Cents::operator+(int value)
{
    return Cents{ m_cents + value };
}

int main()
{
    Cents cents1 { 2 };
    
    /// cents1 + 6 becomes function call cents1.operator+(6)
    /// implicitly cents1+6 becomes operator+(&cents1, 6) which is same as the friend function
    Cents cents2 { cents1 + 6 };
    std::cout << "I've " << cents2.get_cents() << " cents.\n";
    
    return 0;
}
