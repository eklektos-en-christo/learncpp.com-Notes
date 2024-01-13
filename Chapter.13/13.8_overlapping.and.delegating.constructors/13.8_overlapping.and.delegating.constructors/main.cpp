//
//  main.cpp
//  13.8_overlapping.and.delegating.constructors
//
//  Created by Εκλεκτός εν Χριστώ on 7/8/23.
//

/*
 -------------------------------------------------------------------------------------------
 When you instantiate a new object: the object's constructor called implicitly
 
 -------------------------------------------------------------------------------------------
 DELEGATING CONSTRUCTORS/CONSTRUCTOR CHAINING:
 
 Constructors: are allowed to call other constructors from the same class, this process is
 called delegating constructors
 
 To have one constructor call another constructor: simply call the constructor in the
 member initializer list, this is one case where calling another constructor directly is
 acceptable
 
 Few notes about delegating constructors:
 
 -a constructor that delegates to another constructor isn't allowed to do any member
 initialization itself
 
 -constructor can delegate or initialize but not both
 
 -it's possible for one constructor to delegate to another constructor, which delegates back
 to the first constructor, this forms an infinite loop and will cause the program to run out
 of stack space and crash, this can be avoided by ensuring that all of the constructors
 resolve to a non-delegating constructor
 
 infinite delegation below:
 1st constructor -> 2nd constructor -> 1st constructor = infinite loop, program crash
 
 BEST PRACTICE:
 if you have multiple constructors that have the same functionality, then use delegating
 constructors to avoid duplicate code
 
 -------------------------------------------------------------------------------------------
 USING A NORMAL MEMBER FUNCTION FOR SETUP:
 
 A constructor: can only initialize or delegate which leads to challenge if the default
 constructor does some common initialization
 
 Constructors: are allowed to call non-constructor member functions and non-member functions
 
 Better solution: use a normal member function to handle the common setup tasks
 
 -------------------------------------------------------------------------------------------
 RESETTING A CLASS OBJECT:
 
 If the class is assignable - meaning it has an accessible assignment operator
 
 If the class is assignable - we can create a new class object and then use assignment to
 overwrite the values in the object we want to reset, this prevents the violation of DRY
 principle when we would try to do the resetting in a reset function by assigning the
 default values again in reset function
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <string_view>

class Foo
{
public:
    Foo()
    {
        /// code to do A stuff
    }
    
    Foo(int value)
    {
        /// code to do A stuff
        /// Foo() - instantiates a new Foo object which is immediately discarded
        /// because it's not stored in a variable
        Foo();
        /// code to do B stuff
    }
};

class Foo2
{
public:
    Foo2()
    {
        /// code to do A stuff
    }
    
    /// calling the constructor from the member initializer list, not in the body of the constructor
    /// acceptable - calling another constructor directly
    Foo2(int value) : Foo2{}            /// code to do A stuff
    {
        /// code to do B stuff
    }
};

class Employee
{
private:
    int m_id {};
    std::string m_name {};

    /// Employee has 2 constructors
    /// one constructor delegates to Employee(int, std::string_view)
    /// the amount of redundant code is minimized
    /// we only have to write one constructor body instead of two
public:
    Employee(int id=0, std::string_view name="") : m_id{ id }, m_name{ name }
    {
    }
    
    /// this is a delegating constructor, it cannot initialize it's own members
    Employee(std::string_view name) : Employee{ 0, name }
    {
    }
};

class Foo3
{
private:
    const int m_value { 0 };
    
    /// using a normal member function for setup
    /// this is a private non-constructor member function
    /// every constructor is allowed to call it for initial setup
    /// only the members of this class can access it because it's private
    /// setup() - can't do things like bind a member reference or set a const value
    /// or assign values to members that don't support assignment
    void setup()
    {
        /// code to do some setup tasks
        std::cout << "SETTING THINGS UP...\n";
    }
    
public:
    /// default constructor can call setup() for common setup tasks
    /// like DB or file opening
    Foo3()
    {
        setup();
    }
    
    /// this constructor cannot initialize and delegate at the same time
    /// so this is initializing the const member variable
    /// it's necessary to initialize the const member variables
    Foo3(int value) : m_value{ value }
    {
        setup();
    }
};

class Reset
{
private:
    int m_a{ 1 };
    int m_b{ 2 };
    
public:
    Reset()
    {
    }
    
    Reset(int a, int b) : m_a{ a }, m_b{ b }
    {
    }
    
    void print()
    {
        std::cout << m_a << ' ' << m_b << '\n';
    }
    
    /// function resets the object to its original state
    /// Reset{} - creates a new default object with default values
    /// assignment - used to overwrite the implicit object
    /// here the *this refers to the object on which the reset function is called
    /// this performs a memberwise copy
    void reset()
    {
        *this = Reset{};
    }
};

int main()
{
    Reset r{ 11, 22 };
    r.print();
    
    r.reset();
    
    /// object is reset
    r.print();
    
    return 0;
}
