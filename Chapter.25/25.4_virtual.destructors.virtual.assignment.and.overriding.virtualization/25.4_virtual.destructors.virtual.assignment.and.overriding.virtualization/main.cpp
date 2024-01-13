//
//  main.cpp
//  25.4_virtual.destructors.virtual.assignment.and.overriding.virtualization
//
//  Created by Εκλεκτός εν Χριστώ on 11/2/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 VIRTUAL DESTRUCTORS:
 C++: provides a default constructor for the class if it is not provided by the programmer, when you will
 want to provide your own custom destructor(if needs to deallocate some memory), you should always make the
 destructors virtual if you're dealing with inheritance
 
 RULE:
 whenever you're dealing with inheritance, you should many any explicit destructors virtual
 
 if a base class function is virtual, all derived overrides will be considered virtual regardless of whether
 they are specified as such, it is not necessary to create an empty derived class destructor just to mark it
 as virtual
 
 If you want the base class to have a virtual destructor that is otherwise empty, you can define your
 destructor this way:
 virtual ~Base() = default;         // generate a virtual default destructor
 
 -----------------------------------------------------------------------------------------------------------
 VIRTUAL ASSIGNMENT:
 
 It is possible to make the assignment operator virtual, in destructor case, the virtualisation is a good
 idea, virtualising the assignment operator really opens up a bag full of worms
 
 -----------------------------------------------------------------------------------------------------------
 IGNORING VIRTUALIZATION:
 
 Very rarely you may want to ignore the virtualisation of a function, there may be cases where you want a
 Base pointer to a derived object to call the base's member function instead of derived's overridden
 member function, to do so, simply use the scope resolution operator
 
 -----------------------------------------------------------------------------------------------------------
 SHOULD WE MAKE ALL DESTRUCTORS VIRTUAL?
 
 If the base class's destructor isn't marked as virtual, then the program is at risk for leaking memory if
 a programmer later deletes a base class pointer that is pointing to a derived object
 
 there is a performance penalty in marking all the destructors as virtual, a virtual pointer added to every
 instance of your class, so you have to balance the cost as well as your intent
 
 Conventional wisdom (as initially put forth by Herb Sutter, a highly regarded C++ guru) has suggested
 avoiding the non-virtual destructor memory leak situation as follows, “A base class destructor should
 be either public and virtual, or protected and non-virtual.”
 
 A class with a protected destructor can't be deleted via a pointer, thus preventing the accidental deleting
 of a derived class through a base pointer when the base class has a non-virtual destructor, this means the
 base class can't be deleted through a base class pointer, which essentially means the class can't be
 dynamically allocated or deleted except by a derived class. This also precludes using smart pointers (such
 as std::unique_ptr and std::shared_ptr) for such classes, which limits the usefulness of that rule. It
 also means the base class can’t be allocated on the stack. That’s a pretty heavy set of penalties.
 
 * if you intend your class to be inherited from, make sure your destructor is virtual
 * if you don't intend your class to be inherited from, make your class as final, this will prevent other
   classes from inheriting from it in the first place, without imposing any other use restrictions on the
   class itself
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>

class Base
{
public:
    /// in order to call the derived destructor to deallocate the m_array, we need to make base class's destructor virtual
    /// the derived destructor will be called first then in turn, the base destructor will be called
    virtual ~Base()
    {
        std::cout << "Calling ~Base()\n";
    }
};

class Derived: public Base
{
private:
    int* m_array{};
    
public:
    Derived(int length) : m_array{ new int[length] }
    {
    }
    
    /// virtual keyword is not necessary, this override will be considered as virtual, because base destructor is marked as virtual
    /*virtual*/ ~Derived()
    {
        std::cout << "Calling ~Derived()\n";
        delete[] m_array;
    }
};

class Base1
{
public:
    virtual ~Base1() = default;
    virtual std::string_view getName() const { return "Base1"; }
};

class Derived1: public Base1
{
public:
    virtual std::string_view getName() const { return "Derived2"; }
};

int main()
{
    Derived* derived { new Derived(5) };
    
    /// base is a Base pointer, when base is deleted, the program looks to see if the Base destructor is virtual, it's not
    /// so it assumes it only needs to call the Base destructor
    Base* base { derived };
    
    delete base;
    
    Derived1 d1{};
    const Base1& r_b1{ d1 };
    
    /// this will call the derived's get_name, but we want to call the base's get_name even when base's get_name is virtual
    std::cout << r_b1.getName() << '\n';
    
    /// direct call to base's get_name, virtualised derived2::get_name is not called - ignored the virtualisation using :: operator
    std::cout << r_b1.Base1::getName() << '\n';
    
    return 0;
}
