//
//  main.cpp
//  17.3_order.of.construction.of.derived.classes
//
//  Created by Εκλεκτός εν Χριστώ on 7/30/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 ORDER OF CONSTRUCTION WHEN A DERIVED CLASS IS INSTANTIATED:
 
 Members of a base class are not copied into the derived class, we can consider the derived class as a two
 part class:
 
 - part 1, derived
 - part 2, base
 
 When we instantiate a normal, non-derived, base class: C++ allocates memory for base class and then calls
 the default constructor for that base class.
 
 When we instantiate a derived class:
 
 - first, the most-base class at the top is constructed
 - then each child class is constructed in order
 - until the most-child class at bottom is constructed(last)
 
 - first, the base portion of derived class is constructed using the base's default constructor
 - then the derived portion is constructed using the derived default constructor
 
 -----------------------------------------------------------------------------------------------------------
 ORDER OF CONSTRUCTION FOR INHERITANCE CHAINS:
 
 C++ : always constructs the topmost base class first, then it walks through the inheritance tree in order
 and constructs each successive derived class
 
 CONCLUSION:
 
 C++ constructs derived classes in phases, it starts with topmost base class and finishing with the most-
 child class at the bottom. The appropriate constructor for each class is called to initialize the class.
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>

/*--------------------------------------------------------------------------------------------------------*/
class Base
{
public:
    int m_id{};
    
    Base(int id = 0) : m_id{ id }
    {
        std::cout << "Base portion is created!\n";
    }
    
    int get_id() const { return m_id; }
};

/// this class is derived from Base class
class Derived : public Base
{
public:
    double m_cost{};
    
    Derived(double cost = 0.0) : m_cost{ cost }
    {
        std::cout << "Derived portion is created!\n";
    }
    
    double get_cost() const { return m_cost; }
};
/*--------------------------------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------------------------------*/
class A
{
public:
    A()
    {
        std::cout << "A created\n";
    }
};

class B : public A
{
public:
    B()
    {
        std::cout << "B created\n";
    }
};

class C : public B
{
public:
    C()
    {
        std::cout << "C created\n";
    }
};

class D : public C
{
public:
    D()
    {
        std::cout << "D created\n";
    }
};
/*--------------------------------------------------------------------------------------------------------*/



int main()
{
    /// constructing the instance of only base class
    std::cout << "Instantiating Base!\n";
    Base base{};
    
    /// order of construction when a derived class is instantiated
    /// Base class constructor is called first
    /// Derived class constructor is called second
    std::cout << "Instantiating Derived\n";
    Derived derived{};
    
    /// order of construction for inheritance chains
    std::cout << "Constructing A: \n";
    A a {};
    
    std::cout << "Constructing B: \n";
    B b {};
    
    std::cout << "Constructing C: \n";
    C c {};
    
    std::cout << "Constructing D: \n";
    D d {};
    
    return 0;
}
