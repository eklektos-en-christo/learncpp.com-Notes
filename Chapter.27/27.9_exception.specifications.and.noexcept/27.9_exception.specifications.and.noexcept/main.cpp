//
//  main.cpp
//  27.9_exception.specifications.and.noexcept
//
//  Created by Εκλεκτός εν Χριστώ on 12/4/23.
//

/*
 EXCEPTION SPECIFICATIONS: a language mechanism that was originally designed to document what kind of
 exceptions a function might throw as part of a function specification
 
 noexcept specifier:
 
 Non-throwing function: one that promises not to throw exceptions that are visible to the caller
 
 Potentially throwing function: may throw exceptions that are visible to the caller
 
 to define a function non-throwing: use the noexcept specifier at the right side of the function parameter
 parentheses
 
 noexcept: doesn't prevent the function from throwing exceptions of calling other functions that are
 potentially throwing, this is allowed so long as the noexcept function catches and handles those
 exceptions internally and those exceptions do not exit the noexcept function
 
 if an unhandled exception exits a noexcept function, std::terminate will be called, even if there is an
 exception handler that would otherwise handle such an exception somewhere up the stack
 
 if std::terminate is called inside a noexcept function, stack unwinding may or may not occur, which means
 the objects may or may not be destructed properly prior to termination
 
 it is best that noexcept don't mess with exceptions at all or call potentially throwing functions that
 could raise an exception, a noexcept function can't have an exception handling bug if no exceptions can
 possibly be raised in the first place
 
 functions that differ only in their return values can't be overloaded, functions differing only in their
 exception specification can not be overloaded
 
 -----------------------------------------------------------------------------------------------------------
 noexcept - has a boolean parameter, by default it is true, noexcept(true), noexcept(false) means the
 function is potentially throwing, these parameters are only used in template functions, so that a template
 function can be dynamically created as non-throwing or potentially throwing based on some parameterized
 value
 
 -----------------------------------------------------------------------------------------------------------
 Functions that are implicitly non-throwing:
 - destructors
 
 functions that are non-throwing by default for implicitly declared or defaulted functions
 - default constructors, copy constructors, move constructors
 - copy assignments, move assignments
 - comparison operators
 
 if any of these functions call another function which is potentially throwing, then the listed function
 will be treated as potentially throwing as well, example: if a copy assignment operator calls a potentially
 throwing assignment operator, then the copy assignment will be treated potentially throwing as well
 
 Functions that are potentially throwing if not implicitly declared or defaulted:
 - normal functions
 - user-defined constructors
 - user-defined operators
 
 -----------------------------------------------------------------------------------------------------------
 The noexcept operator: operator that can be used inside expressions, it takes an expression as an argument
 and returns false or true, true if expression is non-throwing and false if the expression is potentially
 throwing, it is checked at compile time, it doesn't evaluate the expression
 
 noexcept operator : can be used to conditionally execute code depending upon whether it is potentially
 throwing or not
 
 -----------------------------------------------------------------------------------------------------------
 EXCEPTION SAFETY GUARANTEES: a contractual guideline about how functions or classes will behave in the
 event an exception occurs
 
 four levels of exception safety:
 - no guarantee: no guarantees about what will happen if an exception is thrown
 
 - basic guarantee: if an exception is thrown, no memory will be leaked and object is still usable, program
   may be left in a modified state
 
 - strong guarantee: if an exception is thrown, no memory will be leaked and the program state will not be
   changed, means the function must either completely succeed or have no side effects if it fails, this is
   easy if the failure happens before anything is modified in the first place, but can also be achieved by
   rolling back any changes so the program is returned to the pre-failure state
 
 - no throw/no fail: the function will always succeed or fail without throwing an exception
 
 No throw guarantee: if a function fails then it won't throw an exception, Instead, it will return an error
 code or ignore the problem, No-throw guarantees are required during stack unwinding when an exception is
 already being handled; for example, all destructors should have a no-throw guarantee (as should any
 functions those destructors call). Examples of code that should be no-throw:
 
 - destructors and memory deallocation/cleanup functions
 - functions that higher-level no-throw functions need to call
 
 No fail guarantee: a function will always succeed in what it tries to do (and thus never has a need to
 throw an exception, thus, no-fail is a slightly stronger form of no-throw). Examples of code that
 should be no-fail:
 
 - move constructors and move assignment
 - swap functions
 - clear/erase/reset functions on containers
 - operations on std::unique_ptr
 - functions that higher-level no-fail functions need to call
 
 -----------------------------------------------------------------------------------------------------------
 When to use noexcept?
 
 - non-throwing functions can be safely called from functions that are not exception safe, such as
 destructors
 
 - functions that are noexcept can enable the compiler to perform some optimizations that would not
 otherwise be available, because a noexcept function can't throw an exception outside the function, the
 compiler doesn't have to worry about keeping the runtime stack in an unwindable state, which can allow it
 to produce faster code

 - There are significant cases where knowing a function is noexcept allows us to produce more efficient
 implementations in our own code: the standard library containers (such as std::vector) are noexcept aware
 and will use the noexcept operator to determine whether to use move semantics (faster) or copy
 semantics (slower) in some places.
 
 The standard library’s policy is to use noexcept only on functions that must not throw or fail.
 Functions that are potentially throwing but do not actually throw exceptions (due to implementation)
 typically are not marked as noexcept.
 
 there are two places that make sense to use noexcept:
 - On constructors and overloaded assignment operators that are no-throw (to take advantage of
 optimizations).
 
 - On functions for which you want to express a no-throw or no-fail guarantee (e.g. to document that they
 can be safely called from destructors or other noexcept functions)
 
 
 Best practice:
 Make constructors and overloaded assignment operators noexcept when you can. Use noexcept on other
 functions to express a no-fail or no-throw guarantee.
 
 Best practice:
 If you are uncertain whether a function should have a no-fail/no-throw guarantee, err on the side of
 caution and do not mark it with noexcept. Reversing a decision to use noexcept violates an interface
 commitment to the user about the behavior of the function, and may break existing code. Making
 guarantees stronger by later adding noexcept to a function that was not originally noexcept is
 considered safe.
 
 -----------------------------------------------------------------------------------------------------------
 Dynamic exception specifications:
 
 this syntax uses the throw keyword to list which exception types a function might directly or indirectly
 throw
 
 int doSomething() throw(); // does not throw exceptions
 
 int doSomething() throw(std::out_of_range, int*); // may throw either std::out_of_range or a pointer to an
 integer
 
 int doSomething() throw(...); // may throw anything
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>

/// defining a function which is non-throwing
void do_something() noexcept;
/// functions differing only in their exception specification can't be overloaded
/*void do_something();*/

class Doomed
{
public:
    ~Doomed()
    {
        std::cout << "Doomed destructed\n";
    }
};

void thrower()
{
    std::cout << "Throwing exception\n";
    throw 1;
}

void pt()
{
    std::cout << "pt(potentially throwing) called\n";
    Doomed doomed{};
    thrower();
    std::cout << "This statement never prints\n";
}

void nt() noexcept
{
    std::cout << "nt called\n";
    Doomed doomed{};
    thrower();
    std::cout << "this statement never prints\n";
}

/// this is a non-throwing function and promises not to expose any exception to the caller - main()
void tester(int c) noexcept
{
    std::cout << "tester noexcept case " << c << " called\n";
    try
    {
        (c == 1) ? pt() : nt();
    }
    catch(...)
    {
        std::cout << "tester caught exception\n";
    }
}

void foo() { throw -1; }

/// dynamic exception specifications - Before C++11, and until C++17
/*
int doSomething() throw(); /// does not throw exceptions
int doSomething() throw(std::out_of_range, int*); /// may throw either std::out_of_range or a pointer to an integer
int doSomething() throw(...); /// may throw anything
*/

int main()
{
    /// behavior of noexcept functions and exceptions
    std::cout << std::unitbuf;
    std::cout << std::boolalpha;
    tester(1);
    std::cout << "Test successful\n";
//    tester(2);
    std::cout << "Test successful\n";
    
    constexpr bool b1{ noexcept(2 + 1) };       /// true - ints are non-throwing
    constexpr bool b2{ noexcept(foo()) };       /// false - foo() throws an exception
    
    return 0;
}
