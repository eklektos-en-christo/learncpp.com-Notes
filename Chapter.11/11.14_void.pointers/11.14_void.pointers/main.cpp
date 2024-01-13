//
//  main.cpp
//  11.14_void.pointers
//
//  Created by Εκλεκτός εν Χριστώ on 4/18/23.
//

/*
 VOID POINTER : generic pointer
 
 void pointer : special type of pointer
 
 void pointer : can be pointed at objects of any data type
 
 void pointer : declared like a normal pointer
 
 to declare - use void keyword as the pointer's type
 
 syntax:
 
        void* ptr;
 
 void pointer : doesn't know the what type of object it is pointing to
 
 void pointer : dereferencing a void pointer is illegal
 
 void pointer : must first be cast to another pointer type before the dereference can be
                performed
 
 if void pointer doesn't know what it's pointing to - how to know what to cast it to?
 sol - that is up to the programmer to keep track of
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 void pointer : can be set to a null value
 
 deleting a void pointer that points to dynamically allocated memory - should be avoided, it
 can result in undefined behavior
 
 void pointer : pointer arithmetic is not possible on void pointer because pointer
 arithmetic requires the pointer to know the size of the object it is pointing to, so it can
 increment or decrement the pointer appropriately
 
 void reference : no such thing, because it would be of type void& and wouldn't know what
 type of value it referenced
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Conclusion:
 it's a good idea - to avoid void pointers unless absolutely necessary, as they effectively
 allow to avoid type checking, this allows to accidentally to things that make no sense
 
 better way to do the type checking - using function overloading
 
 to handle multiple data types - templates are used now, they also offer strong type check
 
 before using void pointers - make sure there isn't a better safer way to do the same thing
 using other language mechanisms first
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 void pointer vs null pointer
 
 void pointer - the can point to any type of object but doesn't know what type of object it
 points to
 void pointer - must be explicitly cast into another type of pointer to perform indirection
 
 null pointer - that doesn't point to an address
 void pointer - can be a null pointer
 void pointer - refers to the type of the pointer
 null pointer - refers to the value(address) of the pointer
 */

#include <iostream>
#include <cassert>

struct Something
{
    int n;
    float f;
};

enum class Type
{
    t_int,
    t_float,
    t_cstring,
};

void print_value(void* ptr, Type type)
{
    switch (type)
    {
        case Type::t_int:
            /// cast to int pointer and perform indirection
            std::cout << *static_cast<int*>(ptr) << '\n';
            break;
        case Type::t_float:
            /// cast to float pointer and perform indirection
            std::cout << *static_cast<float*>(ptr) << '\n';
            break;
            /// cast to char pointer and no indirection
            /// std::cout - will treat the char* as c-style string
        case Type::t_cstring:
            std::cout << static_cast<char*>(ptr) << '\n';
            break;
            
        default:
            assert(false && "type not found");
            break;
    }
}

int main()
{
    void* generic_ptr;
    
    int n_value;
    int f_value;
    Something s_value;
    
    /// void pointer - can point to objects of any data type as below
    generic_ptr = &n_value;
    generic_ptr = &f_value;
    
    /// dereferencing void pointer is illegal
//    std::cout << *generic_ptr << '\n';
    
    generic_ptr = &s_value;
    
    int value{220};
    void* void_ptr{&value};
    
    /// illegal - dereference of void pointer
//    std::cout << *void_ptr << '\n';
    
    /// casting the void pointer to int pointer so the the dereference can be performed
    int* int_ptr{static_cast<int*>(void_ptr)};
    
    /// dereferencing the int_ptr now
    std::cout << *int_ptr << '\n';
    
    int nvalue{2};
    float fvalue{2.2f};
    char szvalue[]{"Lollie"};
    
    print_value(&nvalue, Type::t_int);
    print_value(&fvalue, Type::t_float);
    print_value(szvalue, Type::t_cstring);
    
    /// void ptr can also be set to a nullptr
    /// void_ptr_null : is a null pointer currently
    void* void_ptr_null{nullptr};
    
    /// who knows what the actual result would be!!!
    print_value(&nvalue, Type::t_cstring);
    
    return 0;
}
