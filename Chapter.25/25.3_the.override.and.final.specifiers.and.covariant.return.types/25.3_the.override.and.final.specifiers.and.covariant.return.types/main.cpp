//
//  main.cpp
//  25.3_the.override.and.final.specifiers.and.covariant.return.types
//
//  Created by Εκλεκτός εν Χριστώ on 11/2/23.
//

/*
 C++ has two inheritance related identifiers: override & final, they are not keywords, they're normal words
 and have special meaning only when used in certain contexts, C++ standard calls them "identifiers with
 special meaning" but they are often referred to as "specifiers"
 
 -----------------------------------------------------------------------------------------------------------
 THE OVERRIDE SPECIFIER:
 
 A derived class' virtual function is only considered an override if its signature and return types match
 exactly, this can lead to inadvertent issue, where a function that was intended to be an override actually
 isn't an override.
 
 Override specifier: to help address the issue of functions that are meant to be overrides but aren't
 
 How to put override specifier: can be applied to any virtual function by placing the override specifier
 after the function signature(the same place a function-level const specifier goes)
 
 If the function doesn't not override a base class function or is applied to a non-virtual function, the
 compiler will flag the function as an error
 
 All virtual override functions should be tagged using the override specifier
 
 Override specifier implies virtual, there's no need to tag functions using the override specifier with the
 virtual keyword
 
 BEST PRACTICE:
 Use the virtual keyword on virtual functions in a base class
 Use the override specifier(but not the virtual keyword) on override functions in derived classes, this
 includes virtual destructors
 
 -----------------------------------------------------------------------------------------------------------
 THE FINAL SPECIFIER:
 
 Cases: where you don't want someone to be able to override a virtual function or inherit from a class
 
 final specifier: can be used to tell the compiler to enforce this, if the user tries to override a function
 or inherit from a class that has been specified as final, the compiler will give a compile error
 
 How to use final specifier: where we want to restrict the user from overriding a function, the final
 specifier is used in the same place the override specifier is
 
 In case where we want to prevent inheriting from a class: the final specifier is applied after the class
 name/identifier
 
 -----------------------------------------------------------------------------------------------------------
 COVARIANT RETURN TYPES:
 
 One special case: a derived class virtual function can have a different return type than the base class
 and still be considered a matching override, this is possible if the return type of a virtual function is
 a pointer or reference to some class, override functions can return a pointer or a reference to a derived
 class, these are called covariant return types
 
 Note: C++ can't dynamically select types, you'll always get the type that matches the actual version of the
 function being called
 
 Covariant return types: often used in cases where a virtual member function returns a pointer/reference to
 the class containing member function(e.g. base returns base* and derived returns derived*), covariant
 return can be used in any case where the return type of the override member function is derived from the
 return type of the base virtual member function(e.g. Derived's return type(Derived*) is derived from the
 Base's virtual member function return type(Base*)
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>

class A
{
public:
    virtual std::string_view get_name1(int x) { return "A"; }
    virtual std::string_view get_name2(int x) { return "A"; }
    virtual std::string_view get_name3(int x) { return "A"; }
};

class B: public A
{
public:
    /// the function below is not an override
//    std::string_view get_name1(short int x) override { return "B"; }
    
    /// the function below is not an override
//    std::string_view get_name2(int x) const override { return "B"; }
    
    /// using the override specifier - because the function is meant to be an override
    /// the function below is an override of A::get_name3
    /// no need to specify the "virtual" keyword, override specifier implies the virtual
    std::string_view get_name3(int x) override { return "B"; }
};

class Base
{
public:
    virtual std::string_view get_name() { return "Base"; }
};

class Derived1: public Base
{
    /// function is marked as final - it is no longer overridable
    std::string_view get_name() override final { return "Derived1"; }
};

class Derived2: public Derived1
{
public:
    /// function can't override Derived1::get_name because it is final
//    std::string_view get_name() override { return "Derived2"; }
};

/// class is marked as final, it cannot be inherited further
class Base1 /*final*/
{
};

class Derived1_1: public Base1
{
};

class Derived2_1: public Derived1_1
{
};


/*--------------------------------------------------------------------------------------------------------*/
class Base_covariant
{
public:
    /// base version is returning a pointer to a base_covariant class
    virtual Base_covariant* get_this() { std::cout << "called base's get_this()\n"; return this; }
    
    /// if the function below is a virtual function, then on calling this function through a base pointer would go into virtual function resolution
    /// and derived_covariant::print_type will be called
    void print_type() { std::cout << "returned a base\n"; }
};

class Derived_covariant: public Base_covariant
{
public:
    /// derived version returning a pointer to derived_covariant class
    Derived_covariant* get_this() override { std::cout << "called derived's get_this()\n"; return this; }
    void print_type() { std::cout << "returned a derived\n"; }
};
/*--------------------------------------------------------------------------------------------------------*/

int main()
{
    B b{};
    A& r_base{ b };
    
    std::cout << r_base.get_name1(2) << '\n';
    std::cout << r_base.get_name2(2) << '\n';
    std::cout << r_base.get_name3(2) << '\n';
    
    Derived_covariant d{};
    Base_covariant* p_base_covariant{ &d };
    
    /// calls Derived_covariant::get_this, which returns a this pointer to Derived_covariant
    /// pointer calls the Derived_covariant::print_type
    d.get_this()->print_type();
    
    /// calls Derived_covariant::get_this, which returns a Base_covariant pointer
    /// pointer calls the Base_covariant::print_type
    /// Base_covariant::get_this is virtual, so Derived_covariant::get_this is called
    /// which returns a Derived_covariant*, because Base version of the function returns a Base_covariant*
    /// the returned Derived_covariant* is upcast to Base_covariant*
    /// because Base_covariant::print_type is non-virtual, so it is called
    /// if Base_covariant::print_type is virtual then Derived_covariant::print_type will be called
    p_base_covariant->get_this()->print_type();
    
    return 0;
}
