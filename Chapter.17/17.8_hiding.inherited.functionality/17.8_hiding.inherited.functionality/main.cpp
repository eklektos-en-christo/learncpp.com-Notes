//
//  main.cpp
//  17.8_hiding.inherited.functionality
//
//  Created by Εκλεκτός εν Χριστώ on 8/15/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 CHANGING AN INHERITED MEMBER'S ACCESS LEVEL:
 
 C++ : gives the ability to change an inherited member's access specifier in the derived class, this is done
 by using a using-declaration to identify the base class member that is having its access changed in the
 derived class, under the new specifier
 
 You can only change the access specifiers of base members the derived class would normally be able to
 access
 
 If the base class has a private member, it can't be changed from private to protected or from private to
 public, because derived classes don't have access to private members of the base class
 
 -----------------------------------------------------------------------------------------------------------
 HIDING FUNCTIONALITY:
 
 In C++ : it is not possible to remove or restrict functionality from a base class other than by modifying
 the source code
 
 But in derived class, it is possible to hide the functionality that exists in the base class, so that it
 can not be accessed through derived class, this can be done simply by changing the relevant access
 specifier
 
 -----------------------------------------------------------------------------------------------------------
 DELETING FUNCTIONS IN THE DERIVED CLASS:
 
 member functions can also be marked as deleted in the derived class, this ensures that they can't be called
 at all through a derived object
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>

class Base
{
private:
    int m_value {};
    
public:
    int m_value_pub {};
    Base(int value) : m_value{ value }, m_value_pub{ value }
    {
        
    }
    
    int get_value() { return m_value; }
    int get_value(int) { return m_value; }
    
    void deleted_in_derived() const { std::cout << "I'm deleted\n"; }
    
protected:
    /// print_value is declared as protected, so it is accessible only in this class and the derived class
    void print_value() const { std::cout << m_value << '\n'; }
};

class Derived : public Base
{
public:
    Derived(int value) : Base{ value }
    {
        
    }
    
    /// print_value is protected in Base
    /// print_value is inherited publicly in Derived
    /// print_value has protected access in the Derived class
    /// protected members can't be accessed publicly in the main
    /// changing below the protected access to public via a using declaration
    /// print_value has the public access, because it is made public under the public access specifier
    /// parentheses aren't required
    using Base::print_value;
    
    /// function from Base is marked as inaccessible in the Derived class
    void deleted_in_derived() = delete;
    
private:
    /// m_value_pub is public in Base
    /// In derived, the m_value_pub is private because of using-declaration
    using Base::m_value_pub;
    
    /// changing the get_value from public to private in the Derived class
    /// the access specifier for another same overloaded function(the one with int parameter) will also change
    using Base::get_value;
};

int main()
{
    /// print_value is not protected anymore, it is public
    /// so it can used called outside the base and derived class
    Derived d1{ 2 };
    d1.print_value();
    
    
    /// m_value_pub can't be accessed outside of the Derived
    /// because it is treated as private in the Derived class
    /*std::cout << d1.m_value_pub << '\n';*/
    
    /// accessible from the base class
    /// In Base, the m_value_pub is public
    Base& b1{ static_cast<Base&>(d1) };
    std::cout << b1.m_value_pub << '\n';
    
    /// get_value is Base's overloaded function
    /// get_value and get_value(int) both became private in Derived when changed the access specifier of one function i.e. get_value
    /// get_value(int) which is an overloaded function, also became private
    /*d1.get_value();
    d1.get_value(2);*/
    
    /// deleted function in the derived class, can't be accessed
    /*d1.deleted_in_derived();*/
    
    /// even though the deleted_in_derived is inaccessible from Derived object
    /// it can be called directly from the Base
    d1.Base::deleted_in_derived();
    
    /// we can cast the Derived to a Base reference and deleted_in_derived will resolve to Base::deleted_in_derived()
    /// cast to Base& was made to avoid making a copy of the Base portion of Derived
    static_cast<Base&>(d1).deleted_in_derived();
    
    return 0;
}
