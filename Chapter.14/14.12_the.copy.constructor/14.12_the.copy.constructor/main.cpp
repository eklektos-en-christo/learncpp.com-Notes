//
//  main.cpp
//  14.12_the.copy.constructor
//
//  Created by Εκλεκτός εν Χριστώ on 7/26/23.
//

/*
 -------------------------------------------------------------------------------------------
 TYPES OF INITIALIZATION IN C++:
 -direct initialization (())
 -uniform initialization ({})
 -copy initialization (=)
 
 With direct and uniform: the object being created is directly initialized
 
 Copy initialization: is a little more complicated
 
 -------------------------------------------------------------------------------------------
 COPY CONSTRUCTOR: special type of constructor used to create a new object as a copy of an
 existing object of the same type
 
 COPY CONSTRUCTOR: if not provided by the user, compiler provides a public copy constructor
 
 MEMBER-WISE INITIALIZATION: an initialization method that a copy constructor utilizes
 
 MEMBER-WISE INITIALIZATION: simply means that each member of the copy is initialized
 directly from the member of the class being copied
 
 We can explicitly define a copy constructor
 
 Member functions of a class: can access the private members of parameters of the same class
 type
 
 -------------------------------------------------------------------------------------------
 COPY CONSTRUCTOR'S PARAMETER: must be a reference
 
 Parameter of a copy constructor: must be a const reference, if the argument were passed
 by value then we'd need the copy constructor to copy the argument into the parameter of the
 copy constructor, which would result in an infinite recursion
 
 -------------------------------------------------------------------------------------------
 PREVENTING COPIES:
 
 to prevent the copies of our classes from being made, we should make the copy constructor
 private
 
 -------------------------------------------------------------------------------------------
 THE COPY CONSTRUCTOR MAYBE ELIDED:
 
 ELISION: the process of omitting certain copy or move steps for performance purposes
 
 Prior to C++17: a copy constructor must be accessible even if the actual copy is elided
 
 As of C++17: elision have been made mandatory in certain cases, copy constructor is not
 needed or be accessible or present in the class
 
 -------------------------------------------------------------------------------------------
 THE RULE OF THREE AND THE RULE OF ZERO:
 
 RULE OF THREE: states that if a class requires a user-defined destructor, copy constructor
 or copy assignment operator, then it probably requires all three, not following the rule of
 three is likely to lead to malfunctioning code
 
 RULE OF ZERO: states that classes that have custom destructors, copy/move constructors or
 copy/move assignment operators should deal exclusively with ownership of dynamic memory or
 resources. Other classes should not have custom destructors, copy/move constructor or copy/
 move assignment operators.
 
 KEY INSIGHT:
 A class should either model data or manage ownership of memory/resources but not try to do
 both, as this would muddle the responsibility of the class
 
 
 For example, let’s say we want to implement a Classroom that contains a room number, a teacher name, and a list of students. This class should model data, not manage ownership of memory. The room number is easy -- it can be an integral data member. What about the teacher name? We’d expect that to be a std::string data member. We would not expect the Classroom class to implement its own string management capabilities: doing so would be both redundant and make the class far more complex (as some of the functions would be about managing classroom data and other functions would be about string allocation and management). The list of students may be a little less obvious, but it’s the same as for the teacher name: The class should use a std::array or std::vector data member, not implement its own list management functionality inside the class.

 In the rare case that no existing resource management class meets the requirements of our Classroom, we still shouldn’t implement resource management in the Classroom class. Instead, we should define a new resource management class that implements whatever kind of resource management we require. Our Classroom class can then use an instance of our resource management class as a data member.
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <cassert>

class Fraction
{
private:
    int m_numerator{};
    int m_denominator{};
    
public:
    /// the default constructor
    Fraction(int num=0, int den=1) : m_numerator{ num }, m_denominator{ den }
    {
        std::cout << "DEFAULT CONSTRUCTOR CALLED!\n";
        assert(m_denominator != 0);
    }
 
/// if we make the copy constructor private, then inside the main()
/// five_thirds_copy will try to call copy constructor, but it won't work because copy constructor is private now
/*private:*/
    
    /// copy constructor
    /// member wise initialization happening, directly from the existing Fraction object f
    /// parameter f's member are accessed directly because we're inside the class, allowed
    /// default copy constructor provided will also be the same except that print statement inside the body
    /// the parameter f must be a reference to make sure the copy constructor doesn't modify the source object
    /// if f is not passed by reference, then copy constructor will be called recursively
    Fraction(const Fraction& f) : m_numerator{f.m_numerator}, m_denominator{f.m_denominator}
    {
        std::cout << "COPY CONSTRUCTOR CALLED!\n";
    }
    
public:
    friend std::ostream& operator<<(std::ostream& out, const Fraction& f);
};

std::ostream& operator<<(std::ostream& out, const Fraction& f)
{
    out << f.m_numerator << '/' << f.m_denominator;
    return out;
}

int main()
{
    Fraction five_thirds { 5, 3 };              /// brace initialization, calls Fraction(int, int) constructor
    
    /// copy constructor is called because it is public
    /// it won't be called if the copy constructor is private in the class
    /// this is done to avoid the copies of class objects being made
    Fraction five_thirds_copy{ five_thirds };   /// brace initialization, calls what? A copy constructor
    
    
    std::cout << five_thirds_copy << '\n';
    
    /// something interesting is happening here
    /// first, anonymous object is created
    /// 2nd the anonymous object is then used to direct initialize the two_thirds object
    /// the end result is still the same, which takes only one step to do direct initialization
    /// anonymous object here is just an mediator here, we don't need it
    /// compiler optimizes the code to Fraction two_thirds{ 2, 3 }
    /// no need of copy constructor, one step reduced
    Fraction two_thirds { Fraction{ 2, 3} };    /// default constructor called, Fraction(int, int), elision used
    std::cout << two_thirds << '\n';
    
    return 0;
}
