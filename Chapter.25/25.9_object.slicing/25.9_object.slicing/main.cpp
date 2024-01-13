//
//  main.cpp
//  25.9_object.slicing
//
//  Created by Εκλεκτός εν Χριστώ on 11/4/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 Through the use of virtual functions: we can access the most-derived version of a function
 
 What if instead of setting a Base reference or a pointer to a derived object, we simply assign a Derived
 object to a base object?
 
 When we assign a derived object to a base object, only the Base portion of the derived object is copied,
 the derived portion is not.
 
 OBJECT SLICING: On assigning a derived object to a base object, only the base portion of the derived
 object is copied and the derived portion is sliced off, so object slicing is the assigning of a derived
 object to a base object
 
 -----------------------------------------------------------------------------------------------------------
 Some few cases where slicing can cause unexpected results:
 
 SLICING AND FUNCTIONS:
 
 When derived object is passed by value, the derived portion is sliced off and only the base part of the
 derived object is copied into the base parameter, making the function parameter a reference instead of a
 pass by value is the solution, this is the another reason to pass the classes by reference and not by value
 
 SLICING VECTORS:
 
 the derived objects when added to the vector, they are sliced if the vector is declared to be a vector of
 type Base, solution is to create a vector of pointers(the object are pushed using & in front of object
 names or use std::reference_wrapper which is class that mimics an reassignable reference(the object are
 pushed just by name, no &, no *)
 
 FRANKENOBJECT: composed of parts of multiple objects
 
 Case where the derived object still exists
 
 -----------------------------------------------------------------------------------------------------------
 CONCLUSION: avoid slicing, make sure the function parameters are references or pointers, try to avoid any
 kind of pass by value when it comes to derived classes
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <string_view>
#include <vector>
#include <functional>       /// for std::reference_wrapper

class Base
{
protected:
    int m_value{};
    
public:
    Base(int value) : m_value{ value }
    {
    }
    
    virtual std::string_view get_name() const { return "Base"; }
    int get_value() const { return m_value; }
};

class Derived: public Base
{
public:
    Derived(int value) : Base{ value }
    {
    }
    
    std::string_view get_name() const override { return "Derived"; }
};

/// base passed by value, not by reference
void print_name(const Base base)
{
    std::cout << "I'm a " << base.get_name() << '\n';
}

int main()
{
    Derived derived{ 2 };
    std::cout << "derived is a " << derived.get_name() << " and has value " << derived.get_value() << '\n';
    
    Base& r_base{ derived };
    std::cout << "r_base is a " << r_base.get_name() << " and has value " << r_base.get_value() << '\n';
    
    Base* p_base{ &derived };
    std::cout << "p_base is a " << p_base->get_name() << " and has value " << p_base->get_value() << '\n';
    
    /// assigning a derived object to a base object
    /// the base part of the derived is copied to base
    /// the derived part of the derived is sliced off
    /// Base's virtual pointer still points to Base
    Base base{ derived };
    std::cout << "base is a " << base.get_name() << " and has value " << base.get_value() << '\n';
    
    Derived d1{ 8 };
    
    /// base is a value parameter in the actual definition
    /// so d1 is sliced and only the Base portion is copied into the base parameter
    /// when base.get_name() executes in print_name, the call resolves to base::get_name, even though it is virtualised
    /// because there no derived portion available, it was sliced off
    print_name(d1);
    
    /// vector v is declared to a vector of type Base
    std::vector<Base> v{};
    
    /// adding a base object to the vector v
    v.push_back(Base{ 22 });
    
    /// adding a derived object to the vector v
    /// when adding the Derived(29) to vector, the derived part is sliced
    v.push_back(Derived{ 29 });
    
    /// printing out all of the elements in the vector
    /// unexpected output - because vector v is declared to be a vector of type Base
    for (const auto& element : v)
        std::cout << "I'm a " << element.get_name() << " with value " << element.get_value() << '\n';
    
    Base b1{ 32439 };
    
    /// one way to address the issue of slicing is making a vector of pointers
    /// and object should not be temporary objects
    std::vector<Base*> v1{};
    v1.push_back(&b1);
    v1.push_back(&d1);
    
    /// no slicing is happening
    for (const auto* element : v1)
        std::cout << "I'm a " << element->get_name() << " with name " << element->get_value() << '\n';
    
    
    /// another way to address the issue of slicing is to use reference_wrapper
    /// a vector of reassignable reference to Base
    std::vector<std::reference_wrapper<Base>> v2{};
    
    Base b2{ 2393 };
    Derived d2{ 9978 };
    
    /// adding base and derived object to vector v2
    v2.push_back(b2);
    v2.push_back(d2);
    
    /// use .get() to get out all the elements from std::reference_wrapper
    for (const auto& element : v2)
        std::cout << "I'm a " << element.get().get_name() << " with value " << element.get().get_value() << '\n';
    
    Derived d3{ 98708 };
    Derived d4{ 56832 };
    Base& b3{ d4 };
    
    /// b3 points at d4, we're assigning d3 to b3
    /// b3 is a base, operator= provided by C++ for classes isn't virtual by default
    /// assignment operator that copies a Base is invoked and only the Base portion of d3 is copied into d4
    /// consequently, d4 now has the base portion of d3 and the derived portion of d4 - it becomes a frankenobject
    /// avoid assignment like this as much as possible
    b3 = d3;
    
    return 0;
}
