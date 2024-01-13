//
//  main.cpp
//  17.2_basic.inheritance.in.CPP
//
//  Created by Εκλεκτός εν Χριστώ on 7/30/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 INHERITANCE in C++ :  TAKES PLACE BETWEEN CLASSES
 
 PARENT/BASE/SUPER CLASS: the class being inherited from
 
 CHILD/DERIVED/SUB CLASS: the class doing the inheriting
 
 A child class: inherits both behaviors/member functions and properties/member variables from the parent.
 These variables and functions become members of the derived class.
 
 Child classes: can also have their own members that are specific to that class.
 
 To make a class inherit from other class:
 
 - after the class declaration, use a colon and the word public and the name of the class we wish to inherit
 - this is a public inheritance
 
 -----------------------------------------------------------------------------------------------------------
 INHERITANCE CHAINS: it is possible to inherit from a class that is itself derived from other class
 
 This kind of inheritance is useful, we don't have to redefine the information from the base class in our
 derived class, if we ever update our base classes, the derived classes will automatically inherit the
 members and functions from the base classes.
 
 So the process of maintenance costs little. Creating new classes becomes easy and intuitive
 
 -----------------------------------------------------------------------------------------------------------
 CONCLUSION: inheritance allows us to reuse classes by having other classes inherit their members
 
 -----------------------------------------------------------------------------------------------------------
 DERIVATION CHART IN THIS FILE LOOKS LIKE THIS:
 
 
                                 ----Person---
                                |             |
                        Baseball Player    Employee
                                              |
                                           Supervisor
 
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <string_view>

/// a simple class to represent a generic person
class Person
{
public:
    /// members are made public for simplicity
    std::string m_name {};
    int m_age {};
    
    Person(std::string_view name = "", int age = 0) : m_name{ name }, m_age{ age }
    {
    }
    
    const std::string& get_name() const { return m_name; }
    int get_age() const { return m_age; }
};

/// baseball player class is inheriting from class Person publicly
/// now Baseball player has a name and age also
/// also the Baseball player acquires the member functions and variables from Person
/// batting average and homeruns are specific to baseball player and not to a person
/// so these two specific attributes should be inside baseball player class and not inside person
/// now this class has 4 variables: batting average, homeruns, name and age
class BaseballPlayer : public Person
{
public:
    double m_batting_average {};
    int m_homeruns {};
    
    BaseballPlayer(double batting_average = 0.0, int homeruns = 0)
    : m_batting_average{ batting_average }, m_homeruns{ homeruns }
    {
    }
};

/// an employee is a person, so it can inherit from Person, publicly inheriting from Person
class Employee : public Person
{
public:
    double m_hourly_salary {};
    long m_employeeID {};
    
    Employee(double hourly_salary = 0.0, long emp_id = 0)
    : m_hourly_salary{ hourly_salary }, m_employeeID{ emp_id }
    {
    }
    
    void print_name_and_salary()
    {
        /// this function uses one variable from Person and one its own
        std::cout << m_name << ": $" << m_hourly_salary << '\n';
    }
};

/// supervisor is an employee and employee is a person, this is called inheritance chain, top class is general and derived classes are more specific
/// at each level of inheritance
class Supervisor : public Employee
{
public:
    /// this supervisor can oversee a max of 5 employees, overseeing is specific to the supervisor and not to the person or employee
    long m_overseesIDs[5]{};
};

int main()
{
    BaseballPlayer leon{};
    
    /// m_name is publicly inherited from the class Person, so we can set it
    leon.m_name = "LEON";
    
    /// Person's member function is also acquired by the BaseballPlayer
    std::cout << leon.get_name() << '\n';
    
    Employee teddy{ 8.1, 103402746 };
    
    /// employee has a name, inherited publicly from Person
    teddy.m_name = "TEDDY";
    teddy.print_name_and_salary();
    
    return 0;
}
