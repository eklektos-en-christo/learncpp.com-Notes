//
//  main.cpp
//  25.11_printing.inherited.classes.using.operator<<
//
//  Created by Εκλεκτός εν Χριστώ on 11/11/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 CHALLENGES WITH operator<<:
 
 when a base pointer or reference to a derived object is used to call operator<<, the base's operator<< will
 be called rather than derived's
 
 -----------------------------------------------------------------------------------------------------------
 Can we make operator<< virtual?
 
 We can't make operator<< virtual
 
 Reasons:
 - only member functions can be made virtual because only classes can inherit from other classes and there
   is no way to override a function that lives outside of a class
 - non-member functions can be overloaded but can't be overridden
 - operator<< is typically implemented as a friend of the class, friends aren't considered member functions
 - so a friend function can't be virtualized
 - if we could virtualize the operator<<, there's still a problem, the function parameters for base's
   operator<< and derived's operator<< would differ, the base version takes a base object and derived
   version takes a derived object
 - so derived version wouldn't be considered as an override of the base's version and virtual function
   resolution would not be possible
 
 -----------------------------------------------------------------------------------------------------------
 One solution:
 
 we can set up operator<< as a friend in our base class and rather than have operator<< determine what to
 print, we can instead have it call a normal member function that can be virtualized, this virtual function
 will do the work of determining what to print for each class
 
 this solution has two potential downsides:
 - it makes the assumption that desired output can be represented as a single std::string
 - identify() member function does not have access to the stream object
 
 -----------------------------------------------------------------------------------------------------------
 A more flexible solution:
 
 In this solution, base::operator<< doesn't do anything, it just calls the virtual member function print()
 and passes the stream object, the print() function then uses this stream object to do its own printing
 
 base::print() uses the stream object to print base
 
 Derived::print() uses the stream object to print both derived and call employee::operator<< to print the
 value of member m_e
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>

class Base
{
public:
    virtual void print() const { std::cout << "Base"; }
    
    /// solution number 1
    /// operator<< defined as a friend of the base class
    /// operator<< doesn't determine what to print
    friend std::ostream& operator<<(std::ostream& out, const Base& b)
    {
        /// relying on the normal member function, which can be virtualized
        out << b.identify();
        return out;
    }

    /*friend std::ostream& operator<<(std::ostream& out, const Base& b)
    {
        out << "Base";
        return out;
    }*/
    
    /// because it is a normal member function and not a friend, it can be virtualized
    virtual std::string identify() const
    {
        return "Base";
    }
};

class Derived : public Base
{
public:
    void print() const override { std::cout << "Derived"; }
    
    /// no need to define an operator<< for the derived class
    /// base version will handle the derived objects also
    /*friend std::ostream& operator<<(std::ostream& out, const Derived& d)
    {
        out << "Derived";
        return out;
    }*/
    
    /// override for identify() in Base to handle the derived case
    std::string identify() const override
    {
        return "Derived";
    }
};

/*--------------------------------------------------------------------------------------------------------*/
class BaseFlexible
{
public:
    friend std::ostream& operator<<(std::ostream& out, const BaseFlexible& b)
    {
        /// printing responsibility is delegated to the virtual member function print()
        return b.print(out);
    }
    
    /// relying on the actual member function print() to do the actual printing
    /// print() is a normal function, it can be virtualized
    virtual std::ostream& print(std::ostream& out) const
    {
        out << "Base";
        return out;
    }
};

struct Employee
{
    std::string name{};
    int id{};
    
    friend std::ostream& operator<<(std::ostream& out, const Employee& e)
    {
        out << "Employee(" << e.name << ", " << e.id << ")";
        return out;
    }
};

class DerivedFlexible : public BaseFlexible
{
private:
    Employee m_e{};
    
public:
    DerivedFlexible(const Employee& e) : m_e{ e }
    {
    }
    
    /// overridden print() function to handle the derived case
    std::ostream& print(std::ostream& out) const override
    {
        out << "Derived: ";
        out << m_e;
        return out;
    }
};
/*--------------------------------------------------------------------------------------------------------*/

int main()
{
    Base b{};
    /// operator<< is called with parameter b referencing the base object
    /// virtual function call b.identify() will resolve to Base::identify()
    std::cout << b << '\n';
    
    Derived d{};
    /// compiler first looks to see if there's an operator<< that takes a derived object, there isn't
    /// next the compiler looks to see if there's an operator<< that takes a base object, there is
    /// so compiler upcasts the derived object to a Base& and calls the function
    /// the operator<<'s parameter b is referencing a derived object
    /// virtual function call b.identify will resolve to Derived::identify
    std::cout << d << '\n';
    
    /// unexpected output
    /// operator<< defined for Base objects is not virtual
    /// b_ref is a reference to derived object d
    /// so b_ref calls its own operator rather than derived's version of operator<<
    Base& b_ref{ d };
    /*std::cout << b_ref << '\n';*/
    
    /// works as expected -
    /// first the compiler matches variable b_ref with operator<< that takes a base reference
    /// because operator<<'s parameter b is referencing a derived object,
    /// b.identify() will resolved to derived::identify
    std::cout << b_ref << '\n';
    
    BaseFlexible b_f{};
    std::cout << b_f << '\n';
    
    DerivedFlexible d_f{ Employee{ "Leon", 2 } };
    std::cout << d_f << '\n';
    
    BaseFlexible& bf_ref{ d_f };
    std::cout << bf_ref << '\n';
    
    return 0;
}
