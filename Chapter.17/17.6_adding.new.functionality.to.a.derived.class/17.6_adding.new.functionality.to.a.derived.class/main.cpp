//
//  main.cpp
//  17.6_adding.new.functionality.to.a.derived.class
//
//  Created by Εκλεκτός εν Χριστώ on 8/10/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 Benefits of using derived classes: ability to reuse the already written code
 
 Some points to remember:
 - base class functionality can be inherited in derived classes
 - new functionality can be added to derived classes
 - existing functionality can be modified
 - some functionality can be hidden if its not needed
 
 -----------------------------------------------------------------------------------------------------------
 Adding new functionality to the base class: can be risky and time consuming. It may not be even possible to
 modify the base class.
 
 Solution: is to derive own class and add the functionality which is desired in the derived class
 
 To add new functionality to the derived class: simply declare that functionality in the derived class like
 normal
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>

/// Base does't have access to anything in the Derived
class Base
{
protected:
    int m_value{};
    
public:
    Base(int value) : m_value{ value }
    {
    }
    
    void identify() const { std::cout << "I'm Base!\n"; }
};

/// Derived has access to the stuff in Base
class Derived : public Base
{
public:
    Derived(int value) : Base{ value }
    {
    }
    
    /// we don't base class to be modified, so adding the additional functionality
    /// to the derived class, m_value is protected in Base, so Derived can access it directly
    /// public can access m_value from an object of Derived class
    int get_value() const { return m_value; }
};

int main()
{
    Derived derived{ 20 };
    std::cout << derived.get_value() << '\n';
    
    /// Base has no access to the get_value() member, because get_value is Derived's member function
    Base base{ 22 };
    /*std::cout << base.get_value() << '\n';*/
    
    return 0;
}
