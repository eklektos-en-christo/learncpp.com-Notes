//
//  main.cpp
//  17.4_constructors.and.initialization.of.derived.classes
//
//  Created by Εκλεκτός εν Χριστώ on 7/30/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 With non-derived classes: when object is created, the constructors only worry about their own members
 
 With derived classes: when object is created, the cases is slightly more complex, the main things is when
 the derived object is created, the (1) derived constructor is called, but before derived constructor do
 anything, the base constructor is called, control goes to the base constructor, when base constructor is
 finished constructing the the base portion, then control is returned back to the derived constructor, then
 derived constructor finish its work.
 
 So the constructor call order for derived classes is:
 
 derived, control goes to base > base does its work, control goes back to > derived, derived finishes work.
 
 -----------------------------------------------------------------------------------------------------------
 INITIALIZING THE BASE CLASS MEMBERS:
 
 What if we want to set the base class's member when we create the derived class's object?
 
 C++ : prevents classes from initializing inherited member variables in the member initializer list of a
 constructor. The value of a member variable can only be set in a member initializer list of a constructor
 that belongs to the same class as the member variable.
 
 This is because of const and reference variables, if the base class has const member variables, those
 variables must be initialized at the time of creation, base class constructor must set its value when the
 variable is created, if base class initializes its const member and then derived class tries to initialize
 that const variable, both classes would then have the opportunity to initialize that variable, it may
 change the value of that const variable, so C++ ensures that all the variables are initialized only once.
 
 Only non-inherited member variables can be initialized in the member initializer list of a derived class.
 
 Inherited variables: can still have their values changed in the body of derived class's constructor using
 assignment.
 
 How to properly initialize a base class's member when creating a derived class's object?
 
 C++ : gives us the ability to explicitly choose which base class constructor will be called, to do this
 simply add a call to base class's constructor in the member initializer list of the derived class
 
 Note: it doesn't matter where in the Derived constructor member list the Base constructor is called, it
 will always execute first.
 
 -----------------------------------------------------------------------------------------------------------
 Public members: can be accessed by anybody
 Private members: can only be accessed by member functions of the same class
 
 Derived class: cannot access private members of the base class directly but it can use base class's public
 access functions to access the private members of base class.
 
 -----------------------------------------------------------------------------------------------------------
 INHERITANCE CHAINS:
 
 Constructors: can only call constructors from their immediate parent/base class
 
 -----------------------------------------------------------------------------------------------------------
 DESTRUCTORS:
 
 When a derived class is destroyed, each destructor is called in the reverse order of construction
 
 WARNING: if the base class has virtual functions, the destructor should also be virtual, otherwise
 undefined behavior will result in certain cases
 
 -----------------------------------------------------------------------------------------------------------
 SUMMARY:
 
 When constructing a derived class, the derived class constructor is responsible for determining which base class constructor is called. If no base class constructor is specified, the default base class constructor will be used. In that case, if no default base class constructor can be found (or created by default), the compiler will display an error. The classes are then constructed in order from most base to most derived.
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <string_view>

/*--------------------------------------------------------------------------------------------------------*/
class Base
{
private:
    int m_id{};
    
public:
    Base(int id = 0) : m_id{ id }
    {
        /*std::cout << "Base constructor\n";*/
    }
    
    int get_id() const { return m_id; }
};

class Derived : public Base
{
private:
    double m_cost{};
    
public:
                                            /// call the base class's constructor to initialize the m_id with user specified value
                                            /// the order of base class constructor in the initializer list doesn't matter
                                            /// the Base{ int } will always execute first
    Derived(double cost = 0.0, int id = 0) : Base{ id }, m_cost{ cost }/*, Base{ id }*/
    {
        
        /// this works, m_id is inherited from Base, derived can change its value because its public, not private
        /// but if m_id is const or a reference, this won't work
        /*m_id = id;*/
        /*std::cout << "Derived constructor\n";*/
    }
    
    double get_cost() const { return m_cost; }
};
/*--------------------------------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------------------------------*/
class Person
{
private:
    std::string m_name {};
    int m_age {};
    
public:
    Person(const std::string_view name = "", int age = 0)
        : m_name{ name }, m_age{ age }
    {
    }
    
    const std::string& get_name() const { return m_name; }
    int get_age() const { return m_age; }
};

/// this class inheriting publicly from Person
class BaseballPlayer : public Person
{
private:
    double m_batting_average {};
    int m_homeruns {};
    
public:
    /// call Person's constructor explicitly to initialize the name and age of the Person
    BaseballPlayer(const std::string_view name = "", int age = 0, double batting_average = 0.0, int homeruns = 0)
        : Person{ name, age }, m_batting_average{ batting_average }, m_homeruns{ homeruns }
    {
    }
    
    double get_batting_average() const { return m_batting_average; }
    int get_homeruns() const { return m_homeruns; }
};
/*--------------------------------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------------------------------*/
///Inheritance chains: Class C cannot call the constructor of Class A or pass parameters to A directly, C can only call B and B calls the A
///Destructor of C called first, then B's and then A's destruction is called. Reverse order of construction
class A
{
public:
    A(int a)
    {
        std::cout << "A: " << a << '\n';
    }
};

class B : public A
{
public:
    B(int a, double b) : A{ a }
    {
        std::cout << "B: " << b << '\n';
    }
};

class C : public B
{
public:
    C(int a, double b, char c) : B{ a, b }
    {
        std::cout << "C: " << c << '\n';
    }
};
/*--------------------------------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------------------------------*/
class Fruit
{
private:
    std::string m_name{};
    std::string m_color{};
    
public:
    Fruit(std::string_view name = "", std::string_view color = "")
        : m_name{ name }, m_color{ color }
    {
    }
    
    const std::string& get_name() const { return m_name; }
    const std::string& get_color() const { return m_color; }
};

class Apple : public Fruit
{
private:
    double m_fiber{};
    
public:
    Apple(std::string_view name = "", std::string_view color = "", double fiber = 0.0)
    : Fruit{ name, color }, m_fiber{ fiber }
    {
    }
    
    double get_fiber() const { return m_fiber; }
};

std::ostream& operator<<(std::ostream& out, const Apple& a)
{
    out << "Apple(" << a.get_name() << ", " << a.get_color() << ", " << a.get_fiber() << ')';
    return out;
}

class Banana : public Fruit
{
public:
    Banana(std::string_view name = "", std::string_view color = "")
    : Fruit{ name, color }
    {
    }
};

std::ostream& operator<<(std::ostream& out, const Banana& b)
{
    out << "Banana(" << b.get_name() << ", " << b.get_color() << ')';
    return out;
}
/*--------------------------------------------------------------------------------------------------------*/



int main()
{
    /// this is a non derived class
    /// memory for Base is set aside
    /// the appropriate Base constructor is called - Base(int)
    /// member initializer list { 10 } initialized the variable
    /// the body of the constructor executes
    /// control is  returned to the caller - main()
    Base base{ 10 };
    
    /// this is a derived class
    /// memory for derived is set aside - enough for both base and derived portions
    /// the appropriate derived constructor is called
    /// the base object is constructed first using appropriate base constructor, if no base constructor preset, then use default base constructor
    /// member initializer list { 2.1 } initializes variables
    /// the body of the constructor executes
    /// control is returned to the caller - main()
    Derived derived{ 2.1 };
    
    /// memory for derived2 is allocated
    /// Derived(double, int) is called
    /// compiler sees the explicit call to Base(int) in Derived's constructor initializer list
    /// so Base(int) called to initialize m_id
    /// base constructor returns the control to derived
    /// derived class constructor initializes its members
    /// derived class constructor returns  - main()
    Derived derived2{ 2.1, 10 };
    std::cout << derived2.get_id() << '\n';
    std::cout << derived2.get_cost() << '\n';
    
    BaseballPlayer pedro{ "Pedro Salamanca", 22, 8.7, 40 };
    std::cout << pedro.get_name() << '\n';
    std::cout << pedro.get_age() << '\n';
    std::cout << pedro.get_batting_average() << '\n';
    std::cout << pedro.get_homeruns() << '\n';
    
    /// main() calls C(int, double, char)
    /// C constructor calls B(int, double)
    /// B constructor calls A(int)
    /// A is constructed, prints value 2
    /// control returns to B
    /// B is constructed, prints value 40.1
    /// control returns to C
    /// C is constructed, print vale 'C'
    /// control returns to main()
    /// program finishes
    C c{ 2, 40.1, 'C' };
    
    const Apple a{ "Red delicious", "Red", 4.2 };
    std::cout << a << '\n';
    
    const Banana b{ "Cavendish", "yellow" };
    std::cout << b << '\n';
    
    return 0;
}
