//
//  main.cpp
//  25.1_pointers.and.references.to.the.base.class.of.derived.objects
//
//  Created by Εκλεκτός εν Χριστώ on 10/29/23.
//

/*
 Derived class: is composed of multiple parts, one part of each inherited class and a part for itself.
 
 -----------------------------------------------------------------------------------------------------------
 POINTERS, REFERENCES AND DERIVED CLASSES:
 
 We can set derived pointers and references to derived object - Intuitive
 
 C++: will also let us set a Base pointer or reference to a Derived object
 
 Base pointer/reference: can't see the derived members
 
 -----------------------------------------------------------------------------------------------------------
 USE FOR POINTERS AND REFERENCES TO BASE CLASSES:
 
 The pointer or reference to the base class calls the base version of the function rather than the derived
 version
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <string_view>
#include <string>

class Base
{
protected:
    int m_value{};
    
public:
    Base(int value) : m_value{ value }
    {
    }
    
    std::string_view get_name() const { return "Base"; };
    int get_value() const { return m_value; }
};

class Derived: public Base
{
public:
    Derived(int value) : Base{ value }
    {
    }
    
    std::string_view get_name() const { return "Derived"; }
    int get_value_doubled() const { return m_value * 2; }
};

class Animal
{
protected:
    std::string m_name{};
    
    Animal(std::string_view name) : m_name{ name }
    {
    }
    
    Animal(const Animal&) = default;
    Animal& operator=(const Animal&) = default;
    
public:
    std::string_view get_name() const { return m_name; }
    std::string_view speak() const { return "???"; }
};

class Cat: public Animal
{
public:
    Cat(std::string_view name) : Animal{ name }
    {
    }
    
    std::string_view speak() const { return "meow"; }
};

class Dog: public Animal
{
public:
    Dog(std::string_view name) : Animal{ name }
    {
    }
    
    std::string_view speak() const { return "Woof"; }
};

int main()
{
    /// an object of the derived class
    Derived d{ 2 };
    std::cout << "d is a " << d.get_name() << " with value " << d.get_value() << '\n';
    
    /// setting a derived reference to a derived object
    Derived& r_derived{ d };
    std::cout << "r_derived is a " << r_derived.get_name() << " with value " << r_derived.get_value() << '\n';
    
    /// setting a derived pointer to a derived object
    Derived* p_derived{ &d };
    std::cout << "p_derived is a " << p_derived->get_name() << " with value " << p_derived->get_value() << '\n';
    
    /// setting Base reference and pointer to a derived object
    Base& r_base{ d };
    
    /// reference r_base can't see the members of Derived, it call only see its own members and the members which it inherits from other classes
    /// base pointer/reference can't see Derived::get_name(), Derived pointer/reference can see Derived::get_name()
    std::cout << "r_base is a " << r_base.get_name() << " with value " << r_base.get_value() << '\n';
    Base* p_base{ &d };
    
    /// base members are being accessed, because Base pointer/reference can't see the Derived members
    /// pointer p_base can't see the members of Derived, it can only see own members and the members which it inherits from other classes
    std::cout << "p_base is a " << p_base->get_name() << " with value " << p_base->get_value() << '\n';
    
    
    
    const Cat cat{ "Fred" };
    std::cout << "cat is named " << cat.get_name() << " and it says " << cat.speak() << '\n';
    
    const Dog dog{ "Garbo" };
    std::cout << "dog is named " << dog.get_name() << " and it says " << dog.speak() << '\n';
    
    /// p_animal can only see the Animal portion of the class and not the Cat and Dog portion
    const Animal* p_animal{ &cat };
    std::cout << "animal is named " << p_animal->get_name() << "and it says " << p_animal->speak() << '\n';
    
    /// p_animal can only see the Animal portion of the class and not the Cat and Dog portion
    p_animal = &dog;
    std::cout << "animal is named " << p_animal->get_name() << " and it says " << p_animal->speak() << '\n';
    
    return 0;
}
