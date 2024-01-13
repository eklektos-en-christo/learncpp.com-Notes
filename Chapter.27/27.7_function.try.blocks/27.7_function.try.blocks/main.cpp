//
//  main.cpp
//  27.7_function.try.blocks
//
//  Created by Εκλεκτός εν Χριστώ on 12/4/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 FUNCTION TRY BLOCKS: are designed to allow you to establish an exception handler around the body of an
 entire function rather than around a block of code
 
 -----------------------------------------------------------------------------------------------------------
 LIMITATIONS ON FUNCTION CATCH BLOCKS:
 
 A regular catch block inside a function:
 - can throw a new exception
 - rethrow the current exception
 - resolve the exception
 
 A function level catch block for a constructor:
 - must either throw a new exception
 - rethrow the existing exception
 - they are not allowed to resolve exceptions
 - return statements are also not allowed
 - reaching the end of the catch block will implicitly rethrow
 
 A function level catch for a destructor:
 - can throw, rethrow, or resolve the current exception via a return statement
 - reaching the end of the catch block will implicitly rethrow
 
 A function level catch block for other functions:
 - can throw, rethrow or resolve the current exception via a return statement
 - reaching the end of the catch block will implicitly resolve the exception for non-value returning
   functions and produce undefined behaviour for value-returning functions
 
 +---------------------------------------------------------------------------------------------------------+
    Function type          can resolve exceptions via return statement     behaviour at end of catch block
 +---------------------------------------------------------------------------------------------------------+
    Constructor            no, must throw or rethrow                       implicit rethrow
    destructor             yes                                             implicit rethrow
    void function          yes                                             resolve exception
    non-void function      yes                                             undefined behavior
 +---------------------------------------------------------------------------------------------------------+
 
 BEST PRACTICE: avoid letting control reach the end of a function level catch block, instead explicitly
 throw, rethrow or return
 
 function level try blocks: can be used with void functions but they are exclusively used with constructors
 
 -----------------------------------------------------------------------------------------------------------
 FUNCTION TRY BLOCKS CAN CATCH BOTH BASE AND THE CURRENT CLASS EXCEPTIONS
 
 Don't use function try to clean up resources:
 
 when construction of an object fails, the destructor of the class is not called, referring to members of
 the failed object is considered undefined behavior, since the object is dead before the the catch block
 executes, so function try can't be used to  clean up after a class, follow the standard rules for cleaning
 up classes that throw exceptions
 
 function try: is useful primarily for either logging failures before passing the exception up the stack or
 for changing the type of exception thrown
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>

class A
{
private:
    int m_x{};
    
public:
    A(int x) : m_x{ x }
    {
        /*if (x <= 0)
            throw 1;*/
    }
};

class B : public A
{
public:
    /// function try block
    /// try is added before the member initializer list
    /// this indicates that everything after this point until the end of the
    /// function should be considered inside of the try block
    B(int x) try : A{ x }
    {
        /// if we throw exception from B's constructor instead of A's
        /// the result will be same,
        /// B's function level try block can catch both A's and B's(current class) exceptions
        if (x <= 0)
            throw 1;
    }
    /// associated catch block should be at the same level of indentation as the entire function
    /// this catch will catch any exception that is thrown between the try keyword and the
    /// end of the function body
    catch(...)
    {
        std::cerr << "Exception caught\n";
        /// in this constructor if we don't explicitly rethrow the exception,
        /// control would reach the end of the function level catch block
        /// and an implicit rethrow would happen
        /// the result is same whether rethrow or not
        throw;
    }
};

int main()
{
    try
    {
        /// b begins construction, constructor of B is called,
        /// B's constructor calls constructor of A
        /// A raises an exception, A's constructor doesn't handle the exception
        /// the exception propagates up to the stack which is B's constructor
        /// B's constructor has function-level catch block
        /// catch block prints the error and then rethrows the current exception
        /// this exception is caught by the catch in main(),
        /// that prints the Oops
        B b{ 0 };
    }
    catch(int)
    {
        std::cout << "Oops\n";
    }
    
    return 0;
}
