//
//  main.cpp
//  13.10_the.hidden_this_pointer
//
//  Created by Εκλεκτός εν Χριστώ on 7/10/23.
//

/*
 -------------------------------------------------------------------------------------------
 When a member function is called, how does C++ keep track of which object it was called
 on?
 
 Answer: C++ utilizes a hidden pointer named "this"
 
 -------------------------------------------------------------------------------------------
 THE HIDDEN *this POINTER:
 
            object_name.member_function(argument);      // object name as a prefix
 
 this member_function looks like it has only one argument, it actually has two
 
 Compiler: converts this syntax into the following
 
            member_function(&object_name, argument);    // object name as an argument
 
 When compiler compiles and non-static member function: it implicitly adds a new parameter
 to the function named "this"
 
 
 
 this pointer: is a hidden const pointer
 this pointer: holds the address of the object the member function was called on
 
 Any class members: also need to be updated so they refer to the object the function was
 called on
                
            member_function(&object_name, argument)
            {
                this->member = argument;    // addressofobject->object's member = value;
            }
 
 Only thing to remember: non-static member functions have a "this" pointer that refers to
 the object the function was called on
 
 -------------------------------------------------------------------------------------------
 this pointer: always refers to the object being operated on
 
 Each member function: has a "this" pointer parameter that is set to the address of the
 object being operated on
 
 Remember: this pointer isn't stored in the object, it is a pointer parameter
 
 this: is just a function parameter, it doesn't add any memory usage to the class
 
 -------------------------------------------------------------------------------------------
 Explicitly referencing "this":
 
 if you have a constructor that has a parameter with the same name as a member variable:
 then you can disambiguate them by using "this"
 
 usage:
            this->member_variable;
 
 "m_" prefix: is still a better solution by preventing duplicate names altogether
 
 this - make code less readable
 
 m_ prefix: is more readable way to differentiate member variables from non-member local
 variables
 
 -------------------------------------------------------------------------------------------
 CHAINING MEMBER FUNCTIONS:
 
 It is useful sometimes: to have a class member function returning the object it was working
 with as a return value
 
 Primary reason to do this: to allow a series of member function to be "chained" together,
 so several functions can be called on the same object
 
 EXAMPLE:
 ---------
 
            std::cout << "Hello, " << user_name;
 
 std::cout  - is an object
 operator<< - is a member function, it operates on the object
 
 above snippet is evaluated by the compiler like this:
 
            (std::cout << "Hello, ") << user_name;
 
 operator<< - uses std::cout and the string literal "Hello, " to print "Hello, " to the
              console
 
 operator<< - is part of a expression, so it returns a value or it returns void
 
 operator<< - returns *this, which is the std::cout object, so operator<< is evaluated, now
              we get:
 
            (std::cout) << user_name;
 
 it prints the user's name.
 
 So, in this way we only need to specify the object and each function call passes it on to
 the next function to work with, which allows us to chain multiple commands together
 
 -------------------------------------------------------------------------------------------
 SUMMARY:
 
 this: is a hidden parameter implicitly added to any non-static member function
 
 this: is a const pointer, it's value cannot be changed, which is the address of the object
 
 this: but it can be used to change the value of underlying object members
 
 Chainable functions: can be made by returning *this instead of returning void
 
 returning *this: most often used when overloading operators for the classes
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>

class Simple
{
private:
    int m_id{};
    
public:
    Simple(int id) : m_id{ id }
    {
    }
    
    /// function call set_id has an added argument:
    /// the function definition needs to be modified to accept and use the object argument as a parameter
    /// following member function set_id is converted by the converted by the compiler into this form:
    ///
    ///             void set_id(Simple* const this, int id) { this->m_id = id; }
    ///
    /// compiler adds a new parameter to the function named "this"
    /// so "this" holds the object's address on which the member function was called upon
    void set_id(int id) { m_id = id; }
    int get_id() { return m_id; }
};

class Something
{
private:
    /// m_ prefix is better though
    int data {};
    
public:
    Something(int data)
    {
        /// parameter data and member data : both are same names
        /// using this to disambiguate constructor parameter from the member variable
        this->data = data;
    }
};

class Calculate
{
private:
    int m_value{ 0 };
    
public:
    /// chaining functions, each function returns *this, which is a reference to the current object
    Calculate& add(int value) { m_value += value; return *this; }
    Calculate& sub(int value) { m_value -= value; return *this; }
    Calculate& mul(int value) { m_value *= value; return *this; }
    
    int get_value() { return m_value; }
};

int main()
{
    Simple s1{ 1 };
    
    /// compiler converts the following line into this:
    /// set_id(&s1, 200) - now this is just a standard function call
    /// s1 was prefix and now it is an object passed by address to the function set_id()
    s1.set_id(200);
    
    std::cout << s1.get_id() << '\n';
    
    /// chaining the member functions allow us to do this
    /// first: add(10) is called, adds 5 to m_value, returns a reference to c1
    /// c1 is the returned object by add(10) which can be used in the subsequent evaluation
    /// next: sub(5) evaluates,  subtracts 5 from m_value, and again returns a reference to c1
    /// next: mul(2) evaluates, multiplies m_value by 2, and returns reference to c1
    /// which isn't used further and thus ignored
    /// this way each function modified the c1 object, c1 is 10 now
    Calculate c1 {};
    c1.add(10).sub(5).mul(2);
    
    std::cout << c1.get_value() << '\n';
    
    return 0;
}
