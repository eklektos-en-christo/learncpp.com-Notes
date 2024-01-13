//
//  main.cpp
//  25.7_pure.virtual.functions.abstract.base.classes.and.interface.classes
//
//  Created by Εκλεκτός εν Χριστώ on 11/3/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 PURE VIRTUAL(ABSTRACT) FUNCTIONS AND ABSTRACT BASE CLASSES:
 
 Pure virtual function/abstract function: is a special kind of virtual function that has no body at all, it
 simply acts as a placeholder that is meant to be redefined by the derived classes
 
 To create a pure virtual function: rather than defining the body, we simply assign the function the value 0
 
 A non-virtual function cannot be set to zero
 
 Abstract base class: any class with one or more pure virtual functions, this type of class can't be
 instantiated, any derived must define a body for this function, or that derived class will be considered an
 abstract class also
 
 Pure virtual function: is useful when we have a function that we want to put in the base class but only
 the derived classes know what it should return, pure virtual enforce the derived classes to implement the
 pure virtual function otherwise both the base and derived class becomes an abstract class, this helps
 ensure the derived class do not forget to redefine functions that the base class was expecting them to
 
 Pure virtual functions: can be called using a reference or pointer to a base class
 
 Any class with pure virtual functions should also have a virtual destructor
 
 -----------------------------------------------------------------------------------------------------------
 PURE VIRTUAL FUNCTIONS WITH DEFINITIONS: still considered an abstract class, can't be instantiated, derived
 classes must provide the implementation for it
 
 the definition must be a separate definition and not inline, like defining outside the class(as below)
 
 This paradigm is useful when you want your base class to provide a default implementation for a function,
 but still force any derived classes to provide their own implementation, however, if the derived class is
 happy with the default implementation by the base class, it can simply call the base class implementation
 directly
 
 A destructor can be made pure virtual but must be given a definition so that it can be called when a
 derived object is destructed
 
 -----------------------------------------------------------------------------------------------------------
 INTERFACE CLASSES: class that has no member variables, and where all of the functions are pure virtual
 
 Interfaces: are useful when you want to define the functionality that derived classes must implement, but
 leave the details of how the derived class implements that functionality entirely up to the derived class
 
 Interface class: are often named beginning with an I
 
 Don't forget to include a virtual destructor for the interface class, so that the proper derived destructor
 will be called if a pointer to the interface is deleted
 
 -----------------------------------------------------------------------------------------------------------
 PURE VIRTUAL FUNCTIONS AND THE VIRTUAL TABLE:
 
 Abstract classes still have virtual tables, these can still be used if you have a pointer or reference to
 the abstract class, the virtual table entry for a class with a pure virtual function will generally either
 contain a null pointer or point to a generic function that prints an error, sometimes this function is
 named __purecall
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <cmath>
#include <string>
#include <string_view>

class NonVirtualFunction
{
public:
    /// a normal non-virtual function
    std::string_view say_hi() const { return "Hi!"; }
    
    /// a normal virtual function
    virtual std::string_view get_name() const { return "Base"; }
    
    /// a pure virtual function
    /// it is up to the derived class to implement this function
    virtual int get_value() const = 0;
    
    /// non-virtual function can't be set to 0
    /*int do_something() = 0;*/
};

class DerivedAbstractAlso: public NonVirtualFunction
{
};

/*-------------------------------------------------------------------------------------------------------*/
/// this class is an abstract base class, because it contains one pure virtual function named speak()
class Animal
{
protected:
    std::string m_name{};
    
public:
    Animal(std::string_view name) : m_name{ name }
    {
    }
    
    const std::string& get_name() const { return m_name; }
    
    /// speak is a pure virtual function, it has to be implemented by the derived class
    virtual std::string_view speak() const = 0;
    
    virtual ~Animal() = default;
};

class Cow: public Animal
{
public:
    Cow(std::string_view name) : Animal(name)
    {
    }
    
    /// derived class implementing the pure virtual function from the Animal class
    std::string_view speak() const override { return "Moo"; }
};
/*-------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------*/
/// this is still an abstract base class, it can't be instantiated
/// any class inheriting from this class have to provide definitions for the pure virtual function
/// otherwise that derived class will be considered an abstract class
class AnimalPureVirtualDefined
{
protected:
    std::string m_name{};
    
public:
    AnimalPureVirtualDefined(std::string_view name)
    : m_name{ name }
    {
    }
    
    std::string get_name() { return m_name; }
    
    /// function is made pure virtual by assigning to zero
    virtual std::string_view speak() const = 0;
    
    virtual ~AnimalPureVirtualDefined() = default;
};

/// defining the pure virtual function here, but still it is considered a pure virtual function
std::string_view AnimalPureVirtualDefined::speak() const
{
    /// some default implementation
    return "buzz";
}

class DragonFly: public AnimalPureVirtualDefined
{
public:
    DragonFly(const std::string_view name)
    : AnimalPureVirtualDefined{ name }
    {
    }
    
    /// Dragonfly is no longer an abstract class because pure virtual function has been defined
    std::string_view speak() const override
    {
        /// using the default implementation provided by the base class AnimalPureVirtualDefined
        return AnimalPureVirtualDefined::speak();
    }
};
/*-----------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------*/
/// any class inheriting from this class must provide implementation for all three functions in order to be instantiated
class IErrorLog
{
public:
    virtual bool open_log(std::string_view filename) = 0;
    virtual bool close_log() = 0;
    virtual bool write_error(std::string_view error_message) = 0;
    
    /// making a virtual destructor in case we delete an IErrorLog pointer, so the proper derived destructor is called
    virtual ~IErrorLog()
    {
    }
};

/// using the object of IErrorLog class
/// now the caller can pass in any class that conforms to the IErrorLog interface
/// if they want the error to go to a file, they can pass in an instance of FileErrorLog
/// if they want it to go to the screen, they can pass in a instance of ScreenErrorLog
/// or if they want to do something which they haven't even thought of, such as sending an
/// email when there's an error, they can derive a new class from IErrorLog and use an instance of that
/// By using IErrorLog, the function becomes more independent and flexible
double my_sqrt(double value, IErrorLog& log)
{
    if (value < 0.0)
    {
        log.write_error("Tried to take square root of value less than 0");
        return 0.0;
    }
    else
    {
        return std::sqrt(value);
    }
}
/*-------------------------------------------------------------------------------------------------------*/

int main()
{
    /// can't instantiate an object of the NonVirtualFunction, because this class is an abstract class, it contains one pure virtual function
    /*NonVirtualFunction nvf{};*/
    
    /// derived class haven't implemented the base class's pure virtual function, so it is also an abstract class now
    /*DerivedAbstractAlso daa{};*/
    
    /// speak in the Animal  is overridden by the speak(implemented) in the Cow
    Cow cow{ "Joana" };
    std::cout << cow.get_name() << " says " << cow.speak() << '\n';
    
    /// calling the pure virtual function using a pointer to the base Animal class - virtual function resolution
    Animal* a{ &cow };
    std::cout << a->get_name() << " says " << a->speak() << '\n';
    
    /// can't create an object of an abstract class
    /*AnimalPureVirtualDefined apvd;*/
    
    /// default implementation provided by the base class has been used
    /// derived class DragonFly is happy with the default implementation,
    /// so it is calling the base's speak() which is defined outside the class
    DragonFly d_fly{ "Sally" };
    std::cout << d_fly.get_name() << " says " << d_fly.speak() << '\n';

    /// abstract class still have virtual table, it can be used if you have a pointer/reference to the abstract class
    AnimalPureVirtualDefined& apvd{ d_fly };
    std::cout << apvd.get_name() << " says " << apvd.speak() << '\n';
    
    return 0;
}
