//
//  main.cpp
//  13.14_static.member.functions
//
//  Created by Εκλεκτός εν Χριστώ on 7/14/23.
//

/*
 -------------------------------------------------------------------------------------------
 If the static member variables are public: we can access them directly using class name
 and the scope resolution operator
 
 -------------------------------------------------------------------------------------------
 If the static member variables are private: using normal public function to return static
 member value would require us to instantiate an object of the class to use the function
 
 STATIC MEMBER FUNCTIONS: we can make member functions static too
 
 STATIC MEMBER FUNCTIONS: they are not attached to any particular object, this means they
 can be called directly using class name and :: operator
 
 STATIC MEMBER FUNCTIONS: can also be called through the class objects, but it's not
 recommended
 
 -------------------------------------------------------------------------------------------
 STATIC MEMBER FUNCTIONS HAVE NO "*this" POINTER:
 
 Static member functions have two quirks worth noting:
 
 FIRST:
 -they are't attached to an object, so they have no this pointer
 -static member functions don't work on object, so this pointer is not needed
 
 SECOND:
 -they can access directly the other static members/functions
 -they can't access non-static members
 -because non-static members must belong to the class object
 -static member functions have no object to work with, so they can't access static members
 
 STATIC MEMBER FUNCTIONS: can also be defined outside of class definition in same way as it
 works for the normal functions
 
 -------------------------------------------------------------------------------------------
 WARNING ABOUT THE CLASSES WITH ALL STATIC MEMBERS:
 
 PURE STATIC CLASSES/MONOSTATES: classes with all static members
 
 Downsides:
 -all static members are instantiated only once
 -there is no way to have multiple copies of a pure static class
 -if you needed two independent ID generator objects, this would't be possible
 -unless the class is cloned and renamed
 
 -all static members belong to the class and
 -class declarations usually have global scope
 -pure static class is essentially equivalent of declaring functions/global variables in a
 -globally accessible namespace
 -so pure static class has all the necessary downsides that global variables have
 -this mean any piece of code can change the value of the static members
 
 -------------------------------------------------------------------------------------------
 STATIC CONSTRUCTORS: NOT SUPPORTED BY C++
 
 If static variable can be directly initialized: then no need of a static constructor, they
 can be initialized at the point of definition
 
 If initializing the static variable requires executing some code: one way that works with
 all variables(static or not), is to use a lambda and call it immediately
 
 Another way is to use a nested class and do all the static member initialization in the
 constructor, all of the initialization code is kept hidden inside the original class with
 the static member
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <vector>

class StaticMemberFunction
{
private:
    /// s_value is private, can't be accessed directly in the main()
    static int s_value;
    
public:
    /// static member function
    /// accessor function for static member variable s_value
    /// with this we can access s_value in the main(), even though s_value is private
    /// this isn't attached to any particular object, it is attached to the class itself
    static int get_value() { return s_value;}
};

int StaticMemberFunction::s_value{ 1 };



/// all the data and functions are static in the class
/// we don't need to instantiate an object of the class to use it's functionality
class IDGenerator
{
private:
    /// declaring the static member variable
    static int s_next_id;
    
public:
    /// static member function declaration
    static int get_next_id();
};

/// defining the static member variables outside the class
/// start generating IDs from 1
int IDGenerator::s_next_id{ 1 };

/// static member function defined outside the class
/// no need to use static keyword here
/// every time the function is called, the s_next_id increments
int IDGenerator::get_next_id() { return s_next_id++; }



class AtoZ
{
public:
    static std::vector<char> s_chars;
};

/// static member definition requires executing some code
/// using the lambda and calling it immediately
std::vector<char> AtoZ::s_chars
{
    []
    {
        /// declaring a vector inside lambda and using a loop to fill it
        std::vector<char> v{};
        
        for (char ch{ 'a' }; ch <= 'z'; ++ch)
            v.push_back(ch);
        
        return v;
    }() /// () used here to call lambda immediately
};



class AtoZConstructorWay
{
public:
    static std::vector<char> s_chars;
    
    /// this is a nested class
    class init_static
    {
    public:
        /// it behaves like a regular constructor, initializes the static variable s_chars
        /// we can use this constructor to initialize any static member variables
        init_static()
        {
            for (char ch{ 'a' }; ch <= 'z'; ++ch)
                s_chars.push_back(ch);
        }
    };
    
private:
    /// creating object of init_static
    static init_static s_initializer;
};

/// defining the static member variable
std::vector<char> AtoZConstructorWay::s_chars{};

/// defining the static member initializer, this will call the constructor, that will initialize the s_chars
AtoZConstructorWay::init_static AtoZConstructorWay::s_initializer{};



int main()
{
    /// using the static member function accessor directly through class name and :: operator
    std::cout << StaticMemberFunction::get_value() << '\n';
    
    /// static member function can also be accessed through the object of the class
    /// not recommended
    StaticMemberFunction stat1 {};
    std::cout << stat1.get_value() << '\n';
    
    /// using the loop to print static member variable
    for (int count{ 0 }; count < 10; ++count)
        std::cout << "The next ID is : " << IDGenerator::get_next_id() << '\n';
    
    for (int i{ 0 }; i < AtoZ::s_chars.size(); ++i)
        std::cout << AtoZ::s_chars.at(i) << ' ';
    std::cout << '\n';
    
    return 0;
}
