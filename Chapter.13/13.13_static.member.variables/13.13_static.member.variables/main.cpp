//
//  main.cpp
//  13.13_static.member.variables
//
//  Created by Εκλεκτός εν Χριστώ on 7/13/23.
//

/*
 -------------------------------------------------------------------------------------------
 Static variables: keep their values and are not destroyed even after they go out of scope
 
 Static keyword: when applied to global variables: it gives them internal linkage which
 restricts them from being seen/used outside of the file they are defined in
 
 -------------------------------------------------------------------------------------------
 STATIC MEMBER VARIABLES:
 
 static keyword use in classes: static member variables & static member functions
 
 When we instantiate a class object: each object gets its own copy of all normal member
 variables
 
 Static member variables: are shared by all objects of the class, each object accesses the
 single static member variable
 
 Static member: must be initialized in the global namespace, outside the class
 
 -------------------------------------------------------------------------------------------
 STATIC MEMBERS ARE NOT ASSOCIATED WITH CLASS OBJECTS:
 
 Static members: exist even if no objects of the class have been instantiated
 
 Static members: are much like the global variables, they are created when the program
 starts and destroyed when the program ends
 
 Static members: belong to the class itself not to the objects of the class
 
 Static members: can be accessed with the class name and the :: operator, this is the
 preferred method of access
 
 BEST PRACTICE:
 Access the static members using class name and :: operator
 
 -------------------------------------------------------------------------------------------
 DEFINING AND INITIALIZING STATIC MEMBER VARIABLES:
 
 When we declare a static member variable in a class: we're telling the compiler about the
 existence of a static member variable, but not actually defining it, it's much like a
 forward declaration
 
 Static members: must be explicitly defined outside the class in the global scope
 
 If no initialization value is provided: C++ initializes the value to 0
 
 Static member definition: is not subject to access controls, it can be defined and
 initialized even if it is declared as private or protected in the class
 
 If the class is defined in a .h file: static member definition is usually placed in
 the associated code file .cpp
 
 If the class is defined in .cpp file: static member definition is usually placed directly
 underneath the class
 
 Static member definition: don't put it in a header file, if the header file gets included
 more than once, it'll end up with multiple definitions, which will cause linker error
 
 -------------------------------------------------------------------------------------------
 INLINE INITIALIZATION OF STATIC MEMBER VARIABLES:
 
 When the static member is a const integral type(char,bool included) or a const enum: the
 static member can be initialized inside the class definition
 
 static constexpr member variables: can be initialized in the class directly
 
 C++17: we can also initialize non-const static members in the class definition by declaring
 them inline
 
 BEST PRACTICE:
 Static constexpr members: prefer to initialize them at the point of definition
 
 Static non-constexpr members: prefer to make them inline and initialize them at the point
 of definition
 
 -------------------------------------------------------------------------------------------
 WHY USE STATIC VARIABLES INSIDE THE CLASS?
 
 useful example is to assign a unique ID to every instance of the class
 
 Static member variables: also useful when the class needs to utilize an internal lookup
 table, by making lookup table static, only one copy exists for all objects, rather than
 making copy for each object instantiated, this saves substantial amounts of memory
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>

class Something
{
public:
    /// declaration of static member variable
    /// this is a static member variable, it is shared between all objects of the class
    static int s_value;
};

/// non-const static member variable must be defined outside of the class, in global namespace
/// this line instantiates and optionally initializes it with value 1
/// static member definition isn't subject to access controls
int Something::s_value{ 1 };

class Whatever
{
private:
    /// a static const int can be declared and initialized directly in the class definition
    static const int s_value{ 11 };
    /// static constexpr members can be initialized directly in the class definition
    static constexpr int s_value_exp{ 20 };
    /// non-const static member can also be initialized in the class directly by making them inline
    /// inline keyword
    static inline int s_value_inline{ 40 };
};

class ID_Generator
{
private:
    static inline int s_id_generator { 1 };
    int m_id { };
    
public:
    ID_Generator() : m_id{ s_id_generator++ } {}
    
    int get_id() const { return m_id; }
};

int main()
{
    Something first {};
    Something second {};
    
    first.s_value = 10;
    
    /// changing first object's value, changes the second object's value too
    /// which mean they both use the same member variable
    /// so static value can be accessed using anyone object
    std::cout << first.s_value << '\n';
    std::cout << second.s_value << '\n';
    
    /// we can access the static members using class name and :: operator
    /// preferred method for accessing static members
    Something::s_value = 2;
    
    std::cout << Something::s_value << '\n';
    
    ID_Generator id1 {};
    ID_Generator id2 {};
    ID_Generator id3 {};
    
    std::cout << id1.get_id() << '\n';
    std::cout << id2.get_id() << '\n';
    std::cout << id3.get_id() << '\n';
    
    return 0;
}
