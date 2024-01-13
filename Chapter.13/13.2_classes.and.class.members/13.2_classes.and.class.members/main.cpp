//
//  main.cpp
//  13.2_classes.and.class.members
//
//  Created by Εκλεκτός εν Χριστώ on 7/3/23.
//

/*
 Fundamental data types: often sufficient for solving relatively simple problems
 
 Complex problems: can be difficult to solve using the fundamental types
 
 -------------------------------------------------------------------------------------------
 CLASSES: a blueprint
 
 class - is a keyword, used to define a class, this defines a new program-defined type
 
 Class declaration: does not allocate memory, it only defines what the class looks like
 
 Class - requires semicolon at the end which is easy to forget
 
 Class - is like a blueprint, it describes what the resulting object will look like
 
 Class - does not actually create the object
 
 To create an object of the class: a variable of that class must be defined
 
 REMINDER again: initialize the member variables of a class at the point of declaration
 
 -------------------------------------------------------------------------------------------
 MEMBER FUNCTIONS or METHODS: functions defined inside a class
 
 Class: can also contain functions in addition to holding the data
 
 Member functions: can be defined inside or outside of the class
 
 Member variables and functions of a class: can be accessed using the member selection
 operator(.), this is same as we do with structs
 
 All member function calls: must be associated with an object of the class
 
 The associated object: is implicitly passed to the member function
 
 The associated object: is often called the implicit object
 
 With member functions: we can assume that we always have an implicit object of the class to
 work with
 
 m_prefix: using m_prefix for member variables help in distinguishing the member variables
 from function parameters or local variables inside member functions
 
 m_prefix: helps in recognizing that we are changing the member variable and not function
 parameter or a variable local to the member function
 
 m_prefix: this also helps in recognizing that m_prefix variables are member variables of
 the class
 
 BEST PRACTICE:
 Class: class name should begin with an upper case letter
 
 Non member functions: a function can't call a function that is defined below it, unless the
 forward declaration is there
 
 With classes: a member function can call another member function even if it is not defined
 before the calling function
 
 -------------------------------------------------------------------------------------------
 MEMBER TYPES: nested types inside the class, this includes type aliases as well
 
 In this case, the class name acts as a namespace for the nested types
 
 Inside the class: we can access all the nested types without a scope qualifier(::)
 
 Outside the class: we must access the nested types using the class name as a qualifier
 
 e.g. Classname::nested_type
 
 Nested types: can't be forward declared
 
 Classes: possible to nest the classes inside other classes
 
 -------------------------------------------------------------------------------------------
 struct keyword: use struct keyword for data-only structures, dont use structs for the
 objects that have member functions
 
 class keyword: use class keyword for defining objects that require both data and functions
 to be bundled together
 
 C++ standard library: is full of classes, you create the objects of these classes and call
 the member functions on the objects
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>

/// class names should begin with an upper-case letter
class Date
{
public:
    /// these are member variables of this class
    /// all member variables are prefixed with m to
    /// distinguish them from the member function parameters
    /// and local variables of the member functions
    int m_date {};
    int m_month {};
    int m_year {};
    
    /// this is a member function of this class
    /// member function is defined inside the class, can be defined outside
    void print()
    {
        /// date, month and year : they all refer to the associated object as determined by the caller
        std::cout << m_date << '/' << m_month << '/' << m_year;
    }
};

class Employee
{
public:
    std::string m_name {};
    int m_id {};
    double m_wage {};
    
    void print()
    {
        std::cout << "Name: " << m_name << '\t';
        std::cout << "ID: " << m_id << '\t';
        std::cout << "Wage: " << '$' << m_wage << '\n';
    }
};

class Mem_call
{
public:
    /// function y is called in the function x
    /// no need in classes to provide a forward declaration for y before the x
    /// y() is not yet defined but x() can call it
    void x(){ std::cout << "In x, "; y(); }
    void y(){ std::cout << "I'm y!\n"; }
};

/// struct name effectively acts as a namespace for the nested types
struct Employee_Struct
{
    /// a nested type inside the struct
    enum Contract
    {
        permanent,
        temporary,
        contractor,
    };
    
    /// a nested type alias inside the struct
    using ID_type = int;
    
    std::string name{};
    ID_type id{};
    double wage{};
    Contract contract{};
};

class Intpair
{
public:
    int m_first {};
    int m_second {};
    
    void set(int first, int second)
    {
        m_first = first;
        m_second = second;
    }
    
    void print()
    {
        std::cout << "Pair(" << m_first;
        std::cout << ", " << m_second << ")\n";
    }
};

int main()
{
    /// a variable of the class Date is defined and initialized
    Date today { 13, 02, 2020 };
    
    /// accessing the member variables using the member selection operator(.)
    std::cout << today.m_date << '\n';
    std::cout << today.m_month << '\n';
    std::cout << today.m_year << '\n';
    
    /// calling a member function using the member selection operator(.)
    /// this member function is associated with today object of the class Date
    today.print();
    
    std::cout << '\n';
    std::cout << '\n';
    
    
    Employee leon { "Leon", 2102, 20.31 };
    Employee keon { "Keon", 3122, 28.31 };
    Employee jeon { "Jeon", 2248, 33.17 };
    
    leon.print();
    keon.print();
    jeon.print();
    
    Mem_call m1{};
    
    m1.x();
    m1.y();
    
    Intpair pair1{};
    pair1.set(1, 1);
    
    Intpair pair2 { 2, 2 };
    
    pair1.print();
    pair2.print();
    
    return 0;
}
