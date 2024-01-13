//
//  main.cpp
//  27.11_summary.and.quiz
//
//  Created by Εκλεκτός εν Χριστώ on 12/8/23.
//

/*
 Exception handling - provides a mechanism to decouple the handling of errors or other exceptional
 circumstances from the typical control flow  of the code
 
 Throw statement: is used to raise an exception
 
 Try blocks: look for exceptions thrown by code written or called within them
 
 Catch blocks:  exceptions detected by the try blocks are routed to the catch blocks, if the type of an
 exception matches the catch block then it is considered handled
 
 Exceptions: are handled immediately, when an exception is raised, the control jumps to the nearest
 enclosing try block, looking for catch handlers, if no match is found, the stack is unwound to the point of
 the catch block and control resumes at the top of the matching catch block
 
 If no match and try block is found then program terminates, calls std::terminate, which will terminate with
 an unhandled exception error
 
 Exception of any data type can be thrown, including classes
 
 catch blocks - can be configured to catch exceptions of a particular data type
 
 catch all block: can be set up by using the ellipsis(...)
 
 A catch block catching a base class reference will also catch exceptions of derived class
 
 std::exception - an exception class, all exceptions thrown by the std lib are derived from this class
 
 Catching a std::exception by reference will catch all std lib exceptions
 
 what() - is a member function of std::exception, can be used to determine what kind of std::exception was
 thrown
 
 A new exception can be thrown from a catch block but it won't be caught by the same catch block
 
 Exceptions may be rethrown from a catch block by using the keyword throw by itself
 
 Do not rethrow the exception variable that was caught, this may slice the object
 
 Function try blocks: a way to catch any exception that occurs within a function or an associated member
 initialization list, they are typically only used with derived class constructors
 
 Never throw an exception from a destructor
 
 noexcept - specifier, can be used to denote that a function is no-throw/no-fail
 
 std::move_if_noexcept - returns a movable rvalue if the object has a noexcept move constructor, otherwise
 it will return a copyable lvalue
 
 We can use the noexcept specifier in conjunction with std::move_if_noexcept to use move semantics only when
 a strong exception guarantee exists, otherwise copy semantics are used if strong exception guarantee
 doesn't exist
 
 Only use exceptions to handle exceptional cases, cost of handling an exception is very high, code using
 exceptions will run slightly slower
 */

#include <iostream>
#include <stdexcept>
#include <exception>

class Fraction
{
private:
    int m_numerator{0};
    int m_denominator{1};
    
public:
    Fraction(int num=0, int den=1) : m_numerator{ num }, m_denominator{ den }
    {
        if (m_denominator <= 0)
            throw std::runtime_error("Denominator can't be zero or less");
    }
    
    friend std::ostream& operator<<(std::ostream& out, const Fraction& f1)
    {
        out << f1.m_numerator << '/' << f1.m_denominator;
        return out;
    }
};

int main()
{
    int x{};
    int y{};
    std::cout << "Enter two integers: ";
    std::cin >> x >> y;
    
    try
    {
        Fraction f{ x, y };
        std::cout << "Fraction is: " << f << '\n';
    }
    catch (const std::exception& e)
    {
        std::cerr << "Invalid fraction: " << e.what() << '\n';
    }
    
    return 0;
}
