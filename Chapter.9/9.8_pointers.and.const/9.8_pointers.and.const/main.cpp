//
//  main.cpp
//  9.8_pointers.and.const
//
//  Created by Εκλεκτός εν Χριστώ on 2/28/23.
//

/*
 with non-const pointers :
 -we can change what the pointer is pointing at by assigning the new address to hold
 -we can change the value at the address being held by assigning new value to dereferenced
 pointer
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Pointer to const value/pointer to const: non const pointer that points to a constant value
 
 to declare pointer to a const value : use const keyword before the pointer's data type
 
 Because the data type being pointed to is const, the value being pointed to can’t be
 changed.
 
 pointer to const is not const itself: we can change what the pointer is pointing at by
 assigning the pointer a new address
 
 just like reference to const : a pointer to const can also point to non-const variables
 pointer to const : treats the value being pointed to as constant, regardless of whether the
 object at that address was initially defined as const or not
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Const pointers: a pointer whose address cannot be changed after first initialization
 
 to declare a const pointer : use const keyword after the asterisk in the pointer
 declaration
 
 a const pointer : must be initialized upon definition, and this value cannot be changed
 via assignment, if the value being pointed to is non-const then it is possible to change
 the value being pointed to via dereferencing the const pointer
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Const pointer to a const value:
 
 to declare a const pointer to a const value: use const before both before the type and
 after the asterisk in pointer declaration
 
 const pointer to a const value :
 -can't have its address changed
 -the value it is pointing to cannot be changed also through the pointer
 -can only be dereferenced to read/get the value it is pointing at
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 recap: 4 rules to remember
 -non const pointer : can be assigned another address what it is pointing at
 -const pointer : always points to the same address, address cannot be changed
 -pointer to non const value : can change the value it is pointing but cannot be point to a
 const value
 -pointer to a const value : treats the value as const when accessed through pointer, thus
 can't change the value it is pointing to, it can be pointed to const/non const lvalue but
 not rvalues which don't have an address
 
 the pointer's type : defines the type of the object being pointed at
 const in the type : means pointer is pointing at a const value
 const after asterisk : means pointer itself is const, it can't be assigned a new address
 */

#include <iostream>

int main()
{
    /// const variable x1
    const int x1{79};
    const int y1{90};
    
    /// compile error : can't convert from const int* to int*
    /// can't set a normal non const pointer to point at a const variable
    /// this violates the const-ness of variable x1 if non-const would be able to change the value of x1
//    int* ptr_x1{&x1};
    
    /// pointer is pointing to a const int variable x1
    const int* ptr_x1{&x1};
    
    /// ptr_x1 : points to a const int
    /// ptr_x1 : itself is not a const, it is just pointing to a const value
    /// which means: we can change what the pointer is pointing at by assigning to it a new address
    /// value being pointed to is const, so it cannot be changed
    /// x1 : is read only
//    *ptr_x1 = 88;
    
    /// ptr_x1 : is not const itself, so changing the address
    /// ptr_x1 pointing to y1 now
    ptr_x1 = &y1;
    
    int x2{33};
    const int* ptr_x2{&x2};
    
    /// error : x2 is read only variable
    /// pointer can access it but cannot modify it
    /// but the actual variable itself can change its own value
//    ++*ptr_x2;
    /// pointer can read only the value
    std::cout << *ptr_x2 << '\n';
    /// original variable only can change its own value
    /// the value is still non-const when accessed through non-const identifier x2
    std::cout << ++x2 << '\n';
    
    int x3{71};
    int y3{88};
    
    /// a const pointer to a non const value, not a pointer to const
    /// the address it holds now cannot be changed
    /// cnst_ptr : will always point to x3
    int* const cnst_ptr{&x3};
    
    /// once initialized, the const pointer can not be changed to point to another object
    /// error
//    cnst_ptr = &y3;
    
    /// dereferencing the const pointer to change the value
    /// the value itself it not const, the value itself is non const
    ++*cnst_ptr;
    
    /// const variable x4
    const int x4{482};
    const int y4{338};
    
    /// const pointer to const int value
    const int* const const_ptr_to_const_value{&x4};
    
    /// cannot change the const pointer's address once initialized
//    const_ptr_to_const_value = &y4;
    
    /// const int x4 : read only, so can't change the value via pointer
//    ++*const_ptr_to_const_value;
    
    /// const pointer to const value : can read the value only
    std::cout << *const_ptr_to_const_value << '\n';
    
    /// pointer to const value : cannot point to rvalue which don't have an address
//    int* ptr_to_const{22};
    
    int final_value{90112};
    
    /// ptr0 : points to an int, ptr0 is not const itself, normal pointer
    int* ptr0{&final_value};
    /// ptr1 : points to a const value, but not const itself, pointer to a const value
    const int* ptr1{&final_value};
    /// ptr2 : const pointer points to a non-const value, ptr2 is const itself
    int* const ptr2{&final_value};
    /// ptr3 : const pointer to a const value, ptr3 is const itself
    const int* const ptr3{&final_value};
    
    return 0;
}
