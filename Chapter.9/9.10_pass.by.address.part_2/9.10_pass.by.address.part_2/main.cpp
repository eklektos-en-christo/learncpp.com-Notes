//
//  main.cpp
//  9.10_pass.by.address.part_2
//
//  Created by Εκλεκτός εν Χριστώ on 3/2/23.
//

/*
 Pass by address for "optional" arguments:
 more common uses for pass by address is to allow a function to accept an "optional"
 argument
 
 In many cases : function overloading is better alternative to achieve the same result
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Changing what a pointer parameter points at:
 when we pass an address to a function - that address is copied from the argument into
 the pointer parameter, if the pointer parameter is changed to point to another object, the
 argument pointer won't be affected, it points to the same address where it was pointing
 before
 
 so, how to allow a function to change what a pointer argument points to?
 
 PASS BY ADDRESS BY REFERENCE:
 normal variables : can be passed by reference
 pointers : can also be passed by reference
 reference to pointer : reference bounds to pointer argument, changes made to the reference
 are made to the pointer argument
 
 references to pointer : fairly uncommon
 it can be easy to mix up the syntax - int*& or int&*
 int&* - error : can't have a pointer to a reference
 
 pointers : must hold the address of an object, references aren't objects
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Why using 0 and NULL is no longer preferred?
 
 literal 0 : can be interpreted as integer literal or null pointer literal, it can be
 ambiguous which one we intend, so there are unintended consequences to the behavior of the
 program
 
 when using 0 and NULL in function overloading - they may cause problems.
 
 using nullptr : removes the ambiguity, nullptr will only match a pointer type
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 nullptr : can be differentiated from int values in function overloads, so it must be a
 different type
 
 What type is nullptr?
 nullptr : has type std::nullptr_t, defined in <cstddef>
 std::nullptr_t : holds only one value - nullptr
 
 usefulness of nullptr - if we want to write a function that accepts only a nullptr literal
 argument, we can make parameter a std::nullptr_t
 
 function overloading : matches on type, not values
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 THERE IS ONLY PASS BY VALUE : how?
 
 behind the scenes - pass by reference is essentially just a pass by address
 
 pass by address - just copies an address from the caller to the called function, which is
 passing an address by value
 
 CONCLUSION - CPP really passes everything by value
 
 the only difference : we can dereference the passed address to change the argument which we
 can't do with a normal pass by value parameter
 */

#include <iostream>
/// for NULL preprocessor macro
/// for std::nullptr_t also
#include <cstddef>

/// using pass by address : for optional argument
/// name : default parameter
void greet_optional(std::string* name=nullptr)
{
    std::cout << "Hello ";
    std::cout << (name ? *name : "Guest") << '\n';
}

void greet_overloaded()
{
    std::cout << "Hello Guest" << '\n';
}

void greet_overloaded(std::string_view name)
{
    std::cout << "Hello " << name << '\n';
}

/// ptr : receives a copy of the address held by argument ptr in main()
void nullify(int* ptr)
{
    /// this only affects the pointer parameter and not the argument ptr in main()
    ptr = nullptr;
}

/// refptr : is a reference to argument pointer ptr in main()
/// refptr : is bound to ptr in main()
/// any changes to refptr : are made to ptr in main()
void nullify_working(int*& refptr)
{
    /// this will also change the argument pointer to nullptr
    /// because refptr is reference to argument ptr in main()
    refptr = nullptr;
}

/// overloaded function
void print(int x)
{
    std::cout << "int x: " << x << '\n';
}

/// overloaded function
void print(int* ptr)
{
    std::cout << "int* ptr: " << (ptr ? "NON NULL" : "NULL") << '\n';
}

/// this function accepts only a nullptr literal
/// nullptr has type std::nullptr_t
void print(std::nullptr_t)
{
    std::cout << "std::nullptr_t called" << '\n';
}

int main()
{
    std::string leon{"Leon"};
    
    greet_optional();
    /// pass by address
    greet_optional(&leon);
    
    greet_overloaded();
    /// overloaded function
    /// we can pass string literals also
    /// no need to worry about null dereferences
    greet_overloaded("Leon");
    
    int x{50};
    int* ptr{&x};
    
    std::cout << (ptr ? "NOT NULL" : "NULL") << '\n';
    
    /// changing the address held by pointer parameter had no impact on the address held by argument
    /// ptr still points to x
    nullify(ptr);
    
    /// same output
    std::cout << (ptr ? "NOT NULL" : "NULL") << '\n';
    
    std::cout << (ptr ? "NOT NULL" : "NULL") << '\n';
    
    nullify_working(ptr);
    
    std::cout << (ptr ? "NOT NULL" : "NULL") << '\n';
    
    ptr = &x;
    
    /// always calls print(int*), because ptr is of type int*
    print(ptr);
    /// always calls print(int), because 0 is an integer literal
    print(0);
    /// ambiguous call : this call could call any of the print() overloaded functions
//    print(NULL);
    /// always calls print(std::nullptr_t)
    print(nullptr);
    
    /// ptr has type int* : so print(int*) called
    /// even when ptr holds nullptr, print(int*) will be called
    /// function overloading matches on types, not values
    ptr = nullptr;
    print(ptr);
    
    /// always calls print(std::nullptr_t)
    /// nullptr : has type std::nullptr_t
    print(nullptr);
    
    return 0;
}
