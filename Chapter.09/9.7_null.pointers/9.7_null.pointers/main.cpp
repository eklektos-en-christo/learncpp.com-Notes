//
//  main.cpp
//  9.7_null.pointers
//
//  Created by εκλεγμένοι εν Χριστώ on 2/25/23.
//

/*
 pointers :
 objects that hold the address of another object, this address - can be dereferenced using
 (*) operator to get the value at that address
 
 besides a memory address, one another thing that a pointer can hold : a null value
 
 null value/null : special value, that means something has no value
 
 Null pointers: means the pointer is not pointing at anything, when it is holding a null
 value
 
 easiest way to create a null pointer : use value initialization
 
 pointer that is initially set to null : can be changed to point at a valid object using
 assignment
 
 best practice : value initialize the pointers(to be null pointers), if you are not
 initializing them with the address of a valid object
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 nullptr : keyword, represents a null pointer literal, just as the true/false literal for
 boolean values
 
 nullptr : we can use nullptr literal to explicitly initialize/assign a pointer a null value
 
 we can also pass nullptr to a function that has a pointer parameter(s)
 
 best practice : use nullptr when there is a need of a null pointer literal for
 initialization, assignment or passing a null pointer to a function
 
 Dereferencing a null pointer : results in undefined behavior, in most cases it crashes the
 application abnormally
 
 most common reason of cpp program crashing : accidental dereferencing of null and dangling
 pointers
 
 warning : be extra careful that the code isn't dereferencing null or dangling pointers
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Checking for null pointers:
 we can use a conditional to test if the pointer has the nullptr value or not
 
 pointers convert to boolean false if they are null and boolean true if they are not null
 boolean false : null
 boolean true : not null
 
 warning:
 conditionals : can only be used to differentiate null from non-null pointers, there is no
 convenient way to determine whether a non-null pointer is pointing to a valid object or to
 an invalid object(dangling)
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 use null pointers to avoid dangling pointers:
 dereferencing a null/dangling pointer : results in undefined behavior, to avoid this -
 we can use if conditional to ensure if the pointer in non-null before we try to dereference
 it
 
 dangling pointers : there is no way to detect if a pointer is pointing to a valid object
 or to an invalid object, to avoid this, we need to avoid having dangling pointers in the
 program in first place, to do that - set any pointer to nullptr if it is not pointing at a
 valid object
 -this way we only need to check if the pointer is null, if it is non-null then that means
 it is not a dangling pointer
 
 best practice :
 pointer : either hold the address of a valid object or be set to nullptr, in this way we
 can assume that any non-null pointer is valid, because if it is null then it holds nullptr
 
 PROGRAMMER'S RESPONSIBILITY : TO ENSURE THAT ALL THE POINTERS TO AN OBJECT THAT HAS
 JUST BEEN DESTROYED ARE PROPERLY SET TO NULLPTR BECAUSE SUCH POINTERS ARE NOT NULLED
 AUTOMATICALLY
 
 WARNING:
 WHEN AN OBJECT IS DESTROYED - POINTERS TO IT ARE LEFT DANGLING, THEY DON'T MAKE THEMSELVES
 NULL AUTOMATICALLY, IT IS PROGRAMMERS'S RESPONSIBILITY TO ENSURE THIS
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Legacy/old null pointer literals: 0 and NULL
 0 - specifies a null value in the context of pointers, 0 is the only integral literal
 that can be assigned to a pointer
 
 in modern architectures : address 0 is used to represent a null pointer
 some architectures : use other values
 literal 0 : when used in the context of a pointer will be translated into whatever address
 the architecture uses to represent a null pointer
 
 NULL : preprocessor macro, defined <cstddef> header, inherited from C, where it is commonly
 used to indicate a null pointer
 
 both 0 and NULL : should be avoided in modern CPP, use nullptr instead
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Favor references over pointers whenever possible:
 references : can't be bound to null, must be bound to a valid object upon creation so
 dangling references are harder to create
 ability of pointers to change whatever they are pointing at : can make creating dangling
 pointers easier
 
 best practice: favor references over pointers unless the additional capabilities provided
 by pointers are needed
 */

#include <cstddef>      /// for NULL preprocessor macro
#include <iostream>

int main()
{
    /// creating a null pointer using value initialization
    /// ptr : not holding an address
    int* ptr{};
    
    /// error : dereferencing a null pointer, will crash the program
//    std::cout << *ptr << '\n';
    
    int i{21};
    /// ptr : changed from pointing to null to a valid object i
    ptr = &i;
    
    /// valid : ptr is not a null pointer now
    std::cout << *ptr << '\n';
    
    /// using nullptr to initialize a pointer to be a null pointer
    int* null_pointer{nullptr};
//    std::cout << *null_pointer << '\n';
    
    /// we can also make a pointer null which was pointing on a valid object before
    /// ptr is pointing nowhere now
    /// using assignment to make the pointer a null pointer
    ptr = nullptr;
//    std::cout << *ptr << '\n';
    
    /// null pointer created
    int* deref_null_pointer{};
    /// error : dereferencing the null pointer - results in undefined behavior
//    std::cout << *deref_null_pointer << '\n';
    
    int* null_ptr{};
    /// checking if a pointer is null or not
    /// null_ptr == nullptr returns true
    std::cout << (null_ptr == nullptr ? "NULL" : "NOT NULL") << '\n';
    /// above line can also be written as:
    /// null_ptr : returns false
    std::cout << (null_ptr ? "NOT NULL" : "NULL") << '\n';
    
    /// implicit conversion to boolean
    /// null_ptr returns false, else block executes
    if (null_ptr)
        std::cout << "NOT NULL\n";
    else
        std::cout << "NULL\n";
    
    /// avoiding the dereferencing of null pointer with if conditional
    if (deref_null_pointer)
        std::cout << *deref_null_pointer << '\n';
    else
        std::cout << "ERROR: Can't dereference a null pointer!!\n";
    
    /// assigning 0 integer literal to create a null pointer
    float* f_ptr{0};
    std::cout << (f_ptr ? "not null\n" : "null\n");
    /// making a null pointer the non-null pointer
    float fl{22.11};
    f_ptr = &fl;
    std::cout << (f_ptr ? "not null\n" : "null\n");
    
    /// NULL preprocessor macro : to indicate that pointer is a null pointer
    f_ptr = NULL;
    std::cout << (f_ptr ? "not null\n" : "null\n");
    
    return 0;
}
