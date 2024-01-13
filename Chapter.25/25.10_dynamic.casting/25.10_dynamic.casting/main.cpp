//
//  main.cpp
//  25.10_dynamic.casting
//
//  Created by Εκλεκτός εν Χριστώ on 11/4/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 THE NEED FOR DYNAMIC CAST:
 
 When dealing with polymorphism, you'll often encounter cases where you have a pointer to a base class but
 you want to access some information that exists only in a derived class.
 
 One way is to add a virtual function to Base class and through the base pointer call the Derived function
 
 C++: will implicitly let you convert a Derived pointer into a Base pointer, this is called upcasting
 
 -----------------------------------------------------------------------------------------------------------
 dynamic_cast - it is a casting operator
 
 Downcasting: the process of converting base class pointers into derived class pointers
 
 -----------------------------------------------------------------------------------------------------------
 dynamic_cast FAILURE: when base pointer is pointing to the base object, casting the base pointer then to a
 derived pointer will result in a null pointer, dereferencing the null pointer will cause undefined
 behaviour or a crash
 
 RULE: always ensure the dynamic casts actually succeeded by checking for a null pointer result
 
 dynamic_cast: does incur a performance penalty because it does some consistency checking at runtime to
 ensure the conversion can be made
 
 Cases where downcasting using dynamic_cast will not work:
 - with protected or private inheritance
 - for classes that do not declare or inherit any virtual function and thus don't have a virtual table
 - in certain cases involving virtual base classes
 
 -----------------------------------------------------------------------------------------------------------
 DOWNCASTING WITH static_cast:
 
 static_cast: does no runtime type checking to ensure that what your're doing makes sense, casting the Base*
 to a Derived* will succeed even if the base pointer isn't pointing to the derived object, this will result
 in undefined behaviour
 
 if you're absolutely sure that the pointer downcasted will succeed, then static_cast is acceptable
 
 One way to ensure that you know what type of object you're pointing to is to use a virtual function
 
 -----------------------------------------------------------------------------------------------------------
 dynamic_cast AND REFERENCES:
 
 dynamic_cast: can also be used with references, this works analogously to how dynamic_cast works with
 pointers
 
 if the dynamic_cast fails in case of a reference, the std::bad_cast is thrown, since there is no thing like
 "null reference" in the C++, dynamic cast can't return a null reference
 
 -----------------------------------------------------------------------------------------------------------
 dynamic_cast vs static_cast:
 
 static_cast: use it when there no downcasting to do
 dynamic_cast: use it when there is a downcasting to do
 
 better consider avoiding the casting and use virtual functions
 
 -----------------------------------------------------------------------------------------------------------
 DOWNCASTING VS VIRTUAL FUNCTIONS:
 
 Using a virtual function should be preferred over downcasting, there are times when downcasting is the
 better choice, these times are:
 
 - when you cannot modify the base class to add a virtual function(maybe base class is part of standard lib)
 - when you need access to something that is specific to derived class, like access function that exists
   only in the derived class
 - when adding a virtual function to the base class doesn't make any sense, maybe there is no appropriate
   value for the base class to return, using a pure virtual function may be an option if you don't need to
   instantiate the base class
 
 -----------------------------------------------------------------------------------------------------------
 Dynamic cast and RTTI: Run time type information, a feature of C++ that exposes information about an
 object's data type at runtime, this capability is leveraged by dynamic_cast, compilers allow you to turn
 off RTTI as an optimisation because of the pretty significant space performance cost,
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <string_view>

/*--------------------------------------------------------------------------------------------------------*/
class Base
{
protected:
    int m_value{};
    
public:
    Base(int value) : m_value{ value }
    {
    }
    
    virtual ~Base() = default;
};

class Derived: public Base
{
protected:
    std::string m_name{};
    
public:
    Derived(int value, std::string_view name)
    : Base{ value }, m_name{ name }
    {
    }
    
    const std::string& get_name() const { return m_name; }
};

Base* get_object(bool return_derived)
{
    if (return_derived)
        return new Derived{ 2398, "Apple" };
    else
        return new Base{ 9880 };
}
/*--------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------*/
/// static_cast downcasting example
enum class ClassID
{
    base,
    derived
};

class BaseSC
{
protected:
    int m_value{};
    
public:
    BaseSC(int value) : m_value{ value }
    {
    }
    
    virtual ~BaseSC() = default;
    virtual ClassID get_classID() const { return ClassID::base; }
};

class DerivedSC : public BaseSC
{
protected:
    std::string m_name{};
    
public:
    DerivedSC(int value, std::string_view name)
    : BaseSC{ value }, m_name{ name }
    {
    }
    
    const std::string& get_name() const { return m_name; }
    virtual ClassID get_classID() const { return ClassID::derived; }
};

BaseSC* get_objectSC(bool b_return_derived)
{
    if (b_return_derived)
        return new DerivedSC{ 23987, "Apple" };
    else
        return new BaseSC{ 932798 };
}
/*--------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------*/
class BaseREF
{
protected:
    int m_value{};
    
public:
    BaseREF(int value) : m_value{ value } {}
    virtual ~BaseREF() = default;
};

class DerivedREF : public BaseREF
{
protected:
    std::string m_name{};
    
public:
    DerivedREF(int value, std::string_view name)
    : BaseREF{ value }, m_name{ name }
    {
    }
    
    const std::string& get_name() const { return m_name; }
};
/*--------------------------------------------------------------------------------------------------------*/

int main()
{
    Base* b{ get_object(true) };
    
    /// using the dynamic_cast to convert the base pointer b into a derived pointer d - downcasting
    /// Base class doesn't have the get_name function, so virtual function resolution is not possible
    /// so casting the base pointer into a derived pointer, derived pointer can access its member get_name directly
    /// b is actually pointing to the derived object, so cast is possible
    Derived* d{ dynamic_cast<Derived*>(b) };
    
    std::cout << "d is " << d->get_name() << '\n';
    
    /// if the base pointer is not pointing to a derived object, if it is pointing to a base object
    Base* b1{ get_object(false) };
    
    /// casting the base pointer to a derived pointer, base pointer is pointing to the base object currently
    /// dynamic_cast fails here and the result of the conversion will be a null pointer
    Derived* d2{ dynamic_cast<Derived*>(b1) };
    
    /// here d2 is trying to dereference a null pointer, results in undefined behaviour
    /*std::cout << "d2 is " << d2->get_name() << '\n';*/
    
    /// before accessing the derived pointer d2, make sure the pointer is non-null or not
    if (d2)
        std::cout << "d2 is " << d2->get_name() << '\n';
    
    delete b;
    
    BaseSC* b_sc{ get_objectSC(true) };
    
    /// check if the base pointer is pointing to a derived object
    if (b_sc->get_classID() == ClassID::derived)
    {
        /// using the static_cast for downcasting the Base* to a Derived*
        DerivedSC* d_sc{ static_cast<DerivedSC*>(b_sc) };
        std::cout << "The name of the d_sc is " << d_sc->get_name() << '\n';
    }
    
    DerivedREF apple{ 1, "Apple" };
    BaseREF& base_ref{ apple };
    /// casting the base reference to a derived reference using the dynamic_cast
    DerivedREF& derived_ref{ dynamic_cast<DerivedREF&>(base_ref) };
    
    /// accessing the the derived member through derived_ref
    std::cout << "The name of the derived_ref is " << derived_ref.get_name() << '\n';
    
    return 0;
}
