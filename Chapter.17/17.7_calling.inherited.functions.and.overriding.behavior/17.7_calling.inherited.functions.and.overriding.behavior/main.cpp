//
//  main.cpp
//  17.7_calling.inherited.functions.and.overriding.behavior
//
//  Created by Εκλεκτός εν Χριστώ on 8/12/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 BY DEFAULT: derived classes inherit all of the behaviors defined in a base class.
 
 -----------------------------------------------------------------------------------------------------------
 CALLING A BASE CLASS FUNCTION:
 
 When a member function is called with a derived class object: compiler first looks to see if that member
 exists in the derived class. If not then it begins walking up in the inheritance chain and checks if the
 members have been defined in any of the parent classes. It uses the first one it finds in the inheritance
 chain, it uses the most-derived version of the function that it can find.
 
 -----------------------------------------------------------------------------------------------------------
 REDEFINING BEHAVIORS:
 
 We can make functions work differently with our derived classes by redefining them in the derived class
 
 To modify the way a function defined in a base class works in the derived class: simply redefine the
 function in the derived class.
 
 When redefining the function in the derived class: the derived function does not inherit the access
 specifier of the function with same name in the base class. It uses whatever access specifier it is defined
 under in the derived class.
 
 A function that is defined as private in the base class can be redefined as public in the derived class
 or vice-versa.
 
 -----------------------------------------------------------------------------------------------------------
 ADDING TO EXISTING FUNCTIONALITY:
 
 Sometimes we don't want to completely replace a base class function but instead we want additional
 functionality to it. It is possible to have our derived function call the base version of the function of
 the same name(in order to reuse the code) and then add additional functionality to it.
 
 To have a derived function call a base function of the same name: simply do a normal function call, but
 prefix the function with the scope qualifier(the name of the base class and two colons).
 
 -----------------------------------------------------------------------------------------------------------
 When trying to call friend functions in base classes: friend functions aren't actually part of the base
 class, using the scope resolution qualifier won't work.
 
 Solution: is to make our derived class temporarily look like the base class so the the right version of the
 function can be called
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>

class Base
{
protected:
    int m_value{};
    
public:
    Base(int value) : m_value{ value } {}
    
    friend std::ostream& operator<<(std::ostream& out, const Base& b)
    {
        out << "I'm Base\n";
        out << b.m_value << '\n';
        return out;
    }
    
private:
    void identify() const { std::cout << "I'm Base\n"; }
    
protected:
    void identify2() const { std::cout << "I'm Base\n"; }
};

class Derived : public Base
{
public:
    Derived(int value) : Base{ value } {}
    
    /// redefining the behavior in the derived class, this will be called when derived object calls the function
    /// identify is private in Base but redefined as public in the Derived, it works
    /// so derived function doesn't inherit the access specifier of the function with the same name in the base class
    void identify() const { std::cout << "I'm Derived\n"; }
    
    /// adding to existing functionality
    /// first call the Base and do stuff
    /// then do additional stuff in the Derived
    void identify2() const
    {
        /// :: is necessary, otherwise identify2 will call itself and this would result in infinite recursion
        Base::identify2();
        std::cout << "I'm Derived\n";
    }
    
    /// we can't use :: to call the Base class's friend operator<< because it isn't a part of the Base class
    /// so making the Derived class temporarily look like the Base class so that the right version of the function can be called
    /// casting the Derived to a Base object, right version of operator<< of Base will be called
    /// Derived is a base
    friend std::ostream& operator<<(std::ostream& out, const Derived& d)
    {
        out << "I'm derived\n";
        out << static_cast<const Base&>(d);
        return out;
    }
};

int main()
{
    Base base{ 2 };
    /*base.identify();*/
    
    /// compiler looks first if the identify() has been defined in the Derived class, it isn't
    /// so it looks up in the parent class which is Base, Base has the identify function
    /// so it uses Base class's identify() member function
    /// Base::identify() was used because Derived didn't have the identify() function
    Derived derived{ 3 };
    derived.identify();
    
    Derived derived2{ 33 };
    derived2.identify();
    
    /// first, the call is made to base's identify2() function
    /// then the call returns and then the Derived's identify2() executes
    derived2.identify2();
    
    /// Derived is a Base, static cast converts Derived into a base, so Base class's appropriate version of operator<< is called
    std::cout << '\n' << base << '\n';
    std::cout << derived << '\n';
    std::cout << derived2 << '\n';
    
    return 0;
}
