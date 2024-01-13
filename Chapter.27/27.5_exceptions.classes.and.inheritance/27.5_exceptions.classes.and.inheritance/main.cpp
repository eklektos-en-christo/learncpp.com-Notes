//
//  main.cpp
//  27.5_exceptions.classes.and.inheritance
//
//  Created by Εκλεκτός εν Χριστώ on 11/28/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 Exceptions: can also be put in overloaded operator functions and member functions
 
 -----------------------------------------------------------------------------------------------------------
 WHEN CONSTRUCTORS FAIL: exceptions can be put in the constructors as well, e.g. if the user enters an
 invalid input and the constructor fails for some reason, simply throw an exception to indicate that object
 failed to create, in such a case the object's construction is aborted and all class members are destructed
 as per usual
 
 class's destructor is never called if the object never finished construction, so destructor can't be relied
 upon to clean up any resources that have already been allocated
 
 If the resources are allocated in the constructor and an exception occurs prior to the
 constructor finishing:
 
 - one way is to wrap up any code that can fail in a try block and then use a corresponding catch block to
   catch the exception and do necessary cleanup and then re-throw the exception
 - a better way is taking advantage of the fact that class members are destructed even if the constructor
   fails, if you do the resource allocations inside the members of the class rather than in a constructor
   itself, then those members can clean up after themselves when they are destructed
 
 Classes that implement RAII are able to clean up after themselves
 
 -----------------------------------------------------------------------------------------------------------
 EXCEPTION CLASSES:
 
 Using the basic data types as exception types are inherently vague, bigger problem is disambiguation of
 what an exception means when there are multiple statements or function calls within a try block
 
 Exception class: a normal class designed specifically to be thrown as an exception, we can have the
 exception return a description of the problem that occurred, which provides the context for what went wrong
 exception handlers should catch class exception objects by reference instead of value, this prevents the
 compiler from making a copy of the exception at the point where it is caught, which can be expensive if
 the exception is a class object, this also prevents object slicing when dealing with the derived exception
 classes
 
 Catching exceptions by pointer should generally be avoided unless there is a specific reason to do so
 
 -----------------------------------------------------------------------------------------------------------
 EXCEPTION AND INHERITANCE:
 
 What happens when we use inherited classes as exceptions?
 Exception handlers will not only match classes of a specific type, they'll also match classes derived from
 that specific type as well
 
 Derived class type exceptions will be caught by the Base class type catch handlers, because a Derived is a
 Base(is-a relationship) and (a Base is not a Derived, in case of Base exceptions)
 
 C++, when attempts to find a handler for a raised exceptions, it does so sequentially
 
 RULE: handlers for derived classes should be listed before the handlers for base classes
 
 -----------------------------------------------------------------------------------------------------------
 std::exception - many of the classes and operators in the STD lib throw exception classes on failure
 
 operator new: throws std::bad_alloc if it is unable to allocate enough memory
 
 a failed dynamic_cast: throws std::bad_cast
 
 std::exception - is a class, defined in the <exception> header, all of the exception classes that can be
 thrown are derived from this class
 
 std::exception - is a small interface class, designed to serve as a base class to any exception thrown by
 the STD library
 
 We can setup an exception handler to catch exceptions of type std::exception and we'll end up catching
 std::exception and all of the derived exceptions together in one place
 
 std::exception - has a virtual member named what(), it returns a C-style string description of the
 exception, most derived classes from std::exception override the what() function to change the message,
 these inheritance hierarchies allow us to use specific handlers to target specific derived exception
 classes, or to use base handlers to catch the whole hierarchy of exceptions
 
 -----------------------------------------------------------------------------------------------------------
 USING THE STANDARD EXCEPTIONS DIRECTLY: You should feel free to throw the other standard exception classes
 in the standard library if they adequately represent your needs
 
 -----------------------------------------------------------------------------------------------------------
 DERIVING YOUR OWN CLASSES FROM std::exception OR std::runtime_error -
 
 we can also derive our own classes from std::exception and override the virtual const member function
 what()
 
 noexcept - is a specifier, it means that function promises not to throw any exceptions by itself, so our
 override should also have noexcept specifier
 
 std::runtime_error - has string handling capabilities, it is also a popular base class for derived
 exception classes, it can take c-style string and std::string parameter
 
 its up to you whether create your own standalone exception classes, use the standard lib. exception classes
 or derive own exception classes from std::exception or std::runtime_error
 
 -----------------------------------------------------------------------------------------------------------
 EXCEPTION CLASSES SHOULD BE COPYABLE:
 
 When an exception is thrown: the object being thrown is typically a temporary or local variable that has
 been allocated on the stack, the process of exception handling may unwind the function, causing all
 variables local to the function to be destroyed
 
 When a exception is thrown: the compiler makes a copy of the exception object to some piece of unspecified
 memory, outside of the call stack, reserved for handling exceptions, this way the exception object is
 persisted regardless of how may times the stack is unwound
 
 this means that objects being thrown generally need to be copyable, smart compilers maybe able to perform
 a move instead or elide the copy altogether in specific circumstances
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstddef>
#include <exception>            /// exception interface class
#include <limits>
#include <stdexcept>            /// for std::runtime_error

class Foo
{
private:
    /// in this case Foo will handle the allocation and deallocation
    int* int_ptr;
    
    /// in this case:
    /// if the Foo's constructor were to fail after ptr has allocated its dynamic memory
    /// ptr's destructor would execute and return that memory to the system
    /// Foo doesn't do the explicit cleanup when resource handling is delegated to RAII compliant members
    std::unique_ptr<int> ptr{};
};

class Member
{
public:
    Member()
    {
        std::cerr << "Member allocated some resources\n";
    }
    
    ~Member()
    {
        std::cerr << "Member cleaned up\n";
    }
};

class A
{
private:
    int m_x{};
    Member m_member{};
    
public:
    A(int x) : m_x{ x }
    {
        if (x <= 0)
            throw 1;
    }
    
    ~A()
    {
        std::cerr << "~A called\n";
    }
};

/// exception class returns a description of the problem that occurred
/// deriving our ArrayException class from std::exception
class ArrayException : public std::exception
{
private:
    std::string m_error{};
    
public:
    ArrayException(std::string_view error) : m_error{ error }
    {
    }
    
    const std::string& get_error() const { return m_error; }
    
    /// overriding the virtual member what() from std::exception
    /// it return a const char*, so we must return a const char* as well
    /// noexcept - a specifier, it means that function promises not to throw exceptions itself
    /// so our override(what()) should also have noexcept specifier
    const char* what() const noexcept override { return m_error.c_str(); }
};

class IntArray
{
private:
    int m_data[3]{};
    
public:
    IntArray(){}
    
    int get_length() { return 3; }
    
    int& operator[](const int index)
    {
        if (index < 0 || index >= get_length())
            throw ArrayException{ "Invalid Index passed" };
        return m_data[index];
    }
};

class Base
{
public:
    Base() {}
};

class Derived : public Base
{
public:
    Derived() {}
};

/// exception class ArrayException2 inheriting the runtime_error exception class
class ArrayException2 : public std::runtime_error
{
public:
    ArrayException2(const std::string& error) : std::runtime_error{ error }
    {
    }
    
    /// this class uses runtime_error's what member
};

class IntArray2
{
private:
    int m_data[3]{};
    
public:
    IntArray2(){}
    
    int get_length() { return 3; }
    
    int& operator[](const int index)
    {
        if (index < 0 || index >= get_length())
            throw ArrayException2{ "Invalid Index passed" };
        return m_data[index];
    }
};

class BaseCopyable
{
public:
    BaseCopyable() {}
};

class DerivedCopyable : public BaseCopyable
{
public:
    DerivedCopyable() {}
    
    /// this class should be copyable
    DerivedCopyable(const DerivedCopyable&) = delete;
};

int main()
{
    try
    {
        /// class A throws an exception, all of the members of A are destructed
        /// m_member's destructor is called, providing the opportunity to clean up any resources that is allocated
        A a{ 0 };
    }
    catch(int)
    {
        std::cerr << "Oops!\n";
    }
    
    IntArray array;
    
    try
    {
        /// out of range subscript provided, IntArray throws an exception of ArrayException type
        int value{ array[3] };
    }
    /// exception handler catch block handles the exception of type ArrayException
    /// exception class's object should be caught by reference
    catch(const ArrayException& exception)
    {
        /// Exception class's object can use its member function to get the error
        std::cerr << "An array exception occurred (" << exception.get_error() << ")\n";
    }
    
    try
    {
        throw Derived();
    }
    /// this catch block will execute
    /// because Derived is a base also
    /// the first in order is Base handler, so this will be used to handle the Derived exception
    catch(const Base& base)
    {
        std::cerr << "Caught Base\n";
    }
    catch(const Derived& derived)
    {
        std::cerr << "Caught Derived\n";
    }
    
    try
    {
        throw Derived();
    }
    /// this works as expected, Derived handler will be used, because it is first in order
    /// and also it matches with the type of exception being thrown from the try block
    catch(const Derived& derived)
    {
        std::cerr << "Caught Derived\n";
    }
    /// In case of a base exception, this catch handler will execute, because a base is not a derived but derived is a base
    catch(const Base& base)
    {
        std::cerr << "Caught Base\n";
    }
    
    try
    {
        std::string s;
        s.resize(std::numeric_limits<std::size_t>::max());
    }
    /// this handler will catch the exception of type std::exception and all the derived exceptions too
    catch(const std::exception& exception)
    {
        std::cerr << "Standard exception: " << exception.what() << '\n';
    }
    
    try
    {
        std::string s;
        s.resize(std::numeric_limits<std::size_t>::max());
    }
    /// handle the exception of type std::length_error here and any of the exceptions that are derived from it
    catch (const std::length_error& exception)
    {
        std::cerr << "You ran out of memory: " << exception.what() << '\n';
    }
    /// this will handle the exceptions of type std::exception and any exception derived from it that fall through here
    catch (const std::exception& exception)
    {
        std::cerr << "Standard exception: " << exception.what() << '\n';
    }
    
    try
    {
        /// feel free to throw the other standard exception classes
        /// in the standard library if they adequately represent your needs
        /// throw an exception of type std::runtime_error, it has a generic name and its
        /// constructor takes a customisable message
        throw std::runtime_error("Bad things happened\n");
    }
    /// this handler will catch the std::exception and all the derived exception also
    catch(const std::exception& exception)
    {
        std::cerr << "Standard exception: " << exception.what();
    }
    
    IntArray my_array;
    
    try
    {
        int value{ my_array[6] };
    }
    catch(const ArrayException& exception)
    {
        std::cerr << "Array exception occurred: " << exception.what() << '\n';
    }
    catch(const std::exception& exception)
    {
        std::cerr << "Some other std::exception occurred: " << exception.what() << '\n';
    }
    
    IntArray2 my_array2;
    
    try
    {
        int value{ my_array2[22] };
    }
    /// derived catch block executes first
    catch(const ArrayException2& exception)
    {
        std::cerr << "An array exception occurred: " << exception.what() << '\n';
    }
    catch(const std::exception& exception)
    {
        std::cerr << "Some other std::exception occurred: " << exception.what() << '\n';
    }
    
    DerivedCopyable d{};
    
    try
    {
        /// throwing a DerivedCopyable exception
        /// the copy constructor for DerivedCopyable was deleted, no copy can be performed
        /// no copy is made of object d to handle the exception
        /// the DerivedCopyable should be copyable
        /*throw d;*/
    }
    catch (const DerivedCopyable& derived)
    {
        std::cerr << "Caught derived\n";
    }
    catch (const BaseCopyable& base)
    {
        std::cerr << "Caught base\n";
    }
    
    return 0;
}
