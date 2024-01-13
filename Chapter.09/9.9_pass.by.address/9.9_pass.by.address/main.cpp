//
//  main.cpp
//  9.9_pass.by.address
//
//  Created by Εκλεκτός εν Χριστώ on 2/28/23.
//

/*
 two different ways to pass an argument to a function:
 -pass by value
 -pass by reference
 
 third way to pass values to a function:
 -pass by address
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 PASS BY ADDRESS : instead of providing an object as an argument, the caller provides an
 object's address via a pointer, this pointer holds the address of the object is then copied
 into a pointer parameter of the called function, that pointer parameter also holds the
 object's address now, the function can then dereference the pointer to access the object
 whose address was passed
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 PASS BY ADDRESS : doesn't make a copy of the object being pointed to
 example - copying a std::string is expensive, which we want to avoid, when passing by
 address, there is not copy made, passing by address is fast, address is typically of 4 or 8
 bytes in size, pointer is only 4 or 8 bytes, we just copy the address of the actual object
 and not the object itself, copying a pointer is always fast
 
 pass by reference : fast
 pass by address : fast also
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 PASS BY ADDRESS : allows the function to modify the argument's value
 example - when passing an object by address, function receives the address of the passed
 object, that address can be accessed via dereferencing
 -if function parameter is a pointer to a non-const : function can modify the argument's
 value via the pointer parameter using dereferencing
 -if function is not supposed to modify the object being passed in : function parameter
 can be made a pointer to const
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 NULL CHECKING:
 when parameter is passed by address - care should be taken to ensure that pointer is not a
 null pointer before the dereferencing of the pointer, one way is to use conditional statement
 
 using conditional statement : this is fine in a simple function, in more complicated function
 this can result in redundant logic (like testing if pointer is not null multiple times) or
 nesting of the primary logic(if contained in a block), there is a repetition of null checking
 
 this is more effective : to test whether the function parameter is null as a precondition and
 handle the negative case immediately
 
 if a null pointer should never be passed to the function - an assert can be used instead/also
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Prefer pass by const reference :
 pass by reference - has same benefits as pass by address without the risk of accidentally
 dereferencing a null pointer
 
 pass by const reference : has a few other advantages over pass by address -
 
 first - object being passed by address must have an address, only lvalues can be passed by
 address, rvalues don't have addresses
 
 second - syntax for pass by reference is natural, we can just pass in literals or objects,
 but with pass by address, the code ends up littered with & and *
 
 pass by const reference : more flexible than pass by address, it can accept lvalues and
 rvalues
 
 follow this common maxim : pass by reference when you can, pass by address when you must
 
 best practice : prefer pass by const reference to pass by address unless you have a specific
 reason to use pass by address
 */

#include <iostream>
#include <cassert>

/// parameter value : is a copy of str
void pass_by_value(std::string value)
{
    std::cout << value << '\n';
}

/// parameter reference : is a reference that binds to str
void pass_by_reference(const std::string& reference)
{
    std::cout << reference << '\n';
}

/// parameter address : is a pointer that holds the address of the object str
/// we made function parameter a pointer named ptr
/// this function used ptr as read only
/// because ptr is a non-const pointer to a const value
void pass_by_address(const std::string* ptr)
{
    /// accessing the object via dereferencing the pointer, read only
    std::cout << *ptr << '\n';
    
    /// pointer is non-const
    ptr = nullptr;
}

/// ptr here : pointer to a non-const value
void change_value(int* ptr)
{
    /// changing the argument's value using dereferencing
    *ptr = 1000;
}

void null_checking(int* ptr)
{
    /// if ptr is not a null pointer then execute only the statements
    if (ptr)
    {
        std::cout << *ptr << '\n';
    }
}

void null_check_with_assert(const int* ptr)
{
    /// handling in debug mode
    assert(ptr);
    
    /// handling in production mode to avoid the crash
    if (!ptr)
        return;
    
    std::cout << *ptr << '\n';
}

void null_check_as_precondition(int* ptr)
{
    /// if ptr is null then early return, back to the caller
    /// if ptr is null, it returns false, ! makes false the true and return statement executes
    /// multiple times null checking : no more testing required
    if (!ptr)
        return;
    
    /// if the previous condition is false then only this statement executes
    /// this statement executes : which means ptr is valid
    std::cout << *ptr << '\n';
}

void print_by_value(int value)
{
    std::cout << value << '\n';
}

void print_by_reference(const int& value)
{
    std::cout << value << '\n';
}

void print_by_address(const int* ptr)
{
    std::cout << *ptr << '\n';
}

int main()
{
    std::string str{"HELLO!"};
    
    /// str is copied
    /// caller main( ) : is providing the actual argument
    pass_by_value(str);
    
    /// str is not copied
    /// caller main( ) : is providing the actual argument
    pass_by_reference(str);
    
    /// str is not copied, it's address copied to function's pointer parameter
    /// caller main( ) : is providing the actual argument
    /// & address of operator used to get the address of str in a pointer
    /// &str : will create a pointer holding the address of str
    /// this address is then copied into function parameter ptr
    /// ptr now holds the address of str
    /// when function dereferences ptr, it will get the value of str
    pass_by_address(&str);
    
    /// another pointer, holding the address of str
    std::string* ptr_to_str{&str};
    
    /// another way of passing : passing the pointer that holds the address of the object
    /// ptr_to_str : holds the address of str object
    /// that address is copied into the function parameter ptr
    pass_by_address(ptr_to_str);
    
    int changed_value{500};
    
    std::cout << changed_value << '\n';
    /// passing the address of the object to function call
    change_value(&changed_value);
    /// argument is changed and remain changed
    std::cout << changed_value << '\n';
    
    int x1{222};
    
    int* null_ptr{&x1};
    
    null_checking(null_ptr);
    
    /// better
    null_check_as_precondition(null_ptr);
    null_check_as_precondition(nullptr);
    
    /// null pointer passed : assert executes and stops the program
    null_check_with_assert(null_ptr);
    
    ++x1;
    
    /// x1 : copy is made
    print_by_value(x1);
    
    /// with const reference : can take the rvalues, lvalues
    /// const reference : more flexible than pass by address
    print_by_reference(28);
    
    /// with pointer parameter : can't take the address of an rvalue
    /// rvalues don't have addresses
    /// code is littered up with ampersands and asterisks
//    print_by_address(&28);
    
    return 0;
}
