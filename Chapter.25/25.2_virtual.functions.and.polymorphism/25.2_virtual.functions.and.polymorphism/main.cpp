//
//  main.cpp
//  25.2_virtual.functions.and.polymorphism
//
//  Created by Εκλεκτός εν Χριστώ on 10/30/23.
//

/*
 Base pointer or reference: is only able to call the base version of a function, not a derived version
 
 -----------------------------------------------------------------------------------------------------------
 VIRTUAL FUNCTIONS: special type of a member function that, when called resolves to the most-derived version
 of the function for the actual type of the object being referenced or pointed to, the derived version will
 be called based on the actual type of the object
 
 Derived function: is considered a match if it has the same signature, (name, parameter types and whether it
 is const) and return type as the base version of the function
 
 Overrides: base and derived functions that have same signature and return type
 
 To make a function virtual: simply put the "virtual" keyword before the function declaration
 
 KEY INSIGHT:
 Virtual function resolution: only works when a virtual member function is called through a pointer or a
 reference to a class type object
 
 Compiler: can differentiate between the type of the pointer/reference and the type of the object being
 pointed/referenced to
 
 If a function is marked as virtual, all the matching overrides in derived classes are also implicitly
 considered virtual, even if they are not explicitly marked as virtual(this works from top to bottom)
 
 Rule:
 If a function is virtual, all matching overrides in derived classes are implicitly virtual.
 
 A virtual override in a derived class does not implicitly make the base class function virtual
 
 -----------------------------------------------------------------------------------------------------------
 POLYMORPHISM("many forms"): ability of an entity to have multiple forms
 
 Compile-time polymorphism: forms of polymorphism that are resolved by the compiler, this include function
 overload resolution, as well as template resolution
 
 Runtime polymorphism: forms of polymorphism that are resolved at runtime, this includes virtual function
 resolution
 
 -----------------------------------------------------------------------------------------------------------
 RETURN TYPES OF VIRTUAL FUNCTIONS:
 
 Under normal circumstances, the return type of a virtual function and its override must match
 
 Base - virtual int getValue() const { return 5; }
 Derived - virtual double getValue() const { return 6.78; }       // won't work, return type is different
 
 -----------------------------------------------------------------------------------------------------------
 DO NOT CALL VIRTUAL FUNCTIONS FROM CONSTRUCTORS OR DESTRUCTORS:
 
 When a derived class is created: the base portion is created first
 
 If calling a virtual function from the base constructor: if the derived portion haven't even been created
 yet, then it would be unable to call the derived version of the function because there's no derived object
 for the derived function to work on, in this case the base version will be called
 
 If calling a virtual function in a base class destructor: it will always resolve to the base class version
 of the function, because the derived portion of the class will already have been destroyed
 
 BEST PRACTICE:
 never call virtual functions from constructors and destructors
 
 -----------------------------------------------------------------------------------------------------------
 DOWNSIDE OF VIRTUAL FUNCTIONS:
 
 Resolving a virtual function call takes longer than resolving a regular function call, compiler also has
 to allocate an extra pointer for each class object that has one or more virtual functions
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <string_view>

/// the identifier is same but return type and parameter types are different - polymorphism
int add(int, int);
double add(double, double);

/*--------------------------------------------------------------------------------------------------------*/
class Base
{
public:
    /// making the base version a virtual function, so now  through Base pointer or reference the derived version will be called
    virtual std::string_view get_name() const { return "Base version"; }
};

class Derived: public Base
{
public:
    virtual std::string_view get_name() const { return "Derived version"; }
};
/*--------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------*/
class A
{
public:
    virtual std::string_view get_name() const { return "A"; }
};

class B: public A
{
public:
    virtual std::string_view get_name() const { return "B"; }
};

class C: public B
{
public:
    virtual std::string_view get_name() const { return "C"; }
};

class D: public C
{
public:
    virtual std::string_view get_name() const { return "D"; }
};
/*--------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------*/
class Animal
{
protected:
    std::string m_name{};
    
    Animal(std::string_view name) : m_name{ name }
    {
    }
    
public:
    const std::string& get_name() const { return m_name; }
    virtual std::string_view speak() const { return "?????"; }
};

class Cat: public Animal
{
public:
    Cat(std::string_view name) : Animal{ name }
    {
    }
    
    virtual std::string_view speak() const { return "Meow"; }
};

class Dog: public Animal
{
public:
    Dog(std::string_view name) : Animal{ name }
    {
    }
    
    virtual std::string_view speak() const { return "Woof"; }
};

void report(const Animal& animal)
{
    /// when animal.speak() is evaluated:
    /// program notes that Animal::speak() is virtual
    /// the program then looks to see if there are more same derived functions between the classes Animal and Cat
    std::cout << animal.get_name() << " says " << animal.speak() << '\n';
}
/*--------------------------------------------------------------------------------------------------------*/

int main()
{
    /// a derived object
    Derived d{};
    
    /// Base reference and base pointer to derived object
    Base& r_b{ d };
    Base* p_b{ &d };
    
    /// working as expected, through the base reference/pointer, the derived version is being called - polymorphism
    /// r_b.get_name would normally resolve to Base::get_name but because Base::get_name is virtual
    /// program will look for more derived versions of the get_name available for a derived object
    /// and hence the call will resolve to Derived::get_name
    std::cout << "r_b is a " << r_b.get_name() << '\n';
    std::cout << "p_b is a " << p_b->get_name() << '\n';
    
    /// class C object instantiated
    C c{};
    
    /// base class A reference set to reference the A portion of the C object
    /// r_base.get_name evaluates to A::get_name but A::get_name is virtual
    /// so compiler will call the most derived match between class A and C
    /// Most derived version of the get_name is in class C, so C::get_name will be called
    /// the original object is C, not a D, only functions between A and C are considered
    A& r_base{ c };
    std::cout << r_base.get_name() << '\n';
    
    /// calling a virtual member function directly on an object (not through a pointer or reference) will always invoke the member
    /// function belonging to the same type of that object
    std::cout << c.get_name() << '\n';
    
    Cat cat{ "Freddy" };
    Dog dog{ "Jack" };
    
    report(cat);        /// program looks all the classes from Animal and Cat
    report(dog);        /// program looks all the classes from  Animal and dog
    
    Cat fred{ "Fred" };
    Cat misty{ "Misty" };
    Cat zeke{ "Zeke" };

    Dog garbo{ "Garbo" };
    Dog pooky{ "Pooky" };
    Dog truffle{ "Truffle" };
    
    /// Set up an array of pointers to animals, and set those pointers to our Cat and Dog objects
    Animal* animals[]{ &fred, &garbo, &misty, &pooky, &truffle, &zeke };
    
    for (const auto* animal : animals)
        std::cout << animal->get_name() << " says " << animal->speak() << '\n';
    
    return 0;
}
