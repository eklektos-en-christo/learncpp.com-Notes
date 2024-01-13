//
//  main.cpp
//  9.6_intro.to.pointers
//
//  Created by εκλεγμένοι εν Χριστώ on 2/21/23.
//

/*
 & - when used with type(e.g. char&), it means lvalue reference
 
 compiler : takes care of the addressing, we just refer to variable by it's name/identifier
 
 ___________________________________________________________________________________________
 memory address used by variables : aren't exposed to us by default
 
 Address-of operator(&) : returns the memory address of its operand
 
 memory addresses : typically printed as hexadecimal values, often without the 0x prefix
 
 objects that use more than one byte of memory : & will return the memory address of the
 first byte used by the object
 
 ___________________________________________________________________________________________
 TIP:
 int& : when following a typename, & denotes an lvalue reference
 &x, &y : when used in unary context in an expression, & is the address of operator
 x & y : when used in binary context in an expression, & is the bitwise AND operator
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Most useful thing to do with an address : access the value stored at that address
 
 Dereference operator/indirection operator(*) : returns the value at a given memory address
 as an lvalue.
 
 dereference operator : is unary operator, multiplication operator is binary
 
 dereferencing : dereferencing the address
 
 Key insight:
 if memory address is given - we can use * operator to get the value at that address as an
 lvalue
 
 Address of & vs. dereference * - they both work as opposites
 address of & :gets the address of an object
 dereference *:gets the object at an address
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Pointer : is an object
 Pointer : holds a memory address as its value, typically of another variable
 
 this allows us to store the address of some object and use it later
 
 Pointers : sometime called raw pointers/dumb pointers to differentiate them from smart
 pointers
 
 to create a pointer variable - simply define a variable with a pointer type:
 int* ptr;       // a pointer to an integer
 
 best practice:
 when declaring a pointer type, place the asterisk next to the type name
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Pointer initialization:
 Pointers : are not initialized by default
 Wild pointer : uninitialized pointer
 Wild pointers : contain a garbage address
 Dereferencing a wild pointer : results in undefined behavior
 
 best practice : always initialize the pointer to a known value
 
 pointers : holds addresses, value has to be an address which we can get using the
 address of operator &
 
 dereference operator * : once the pointer is initialized with an address of an object
 , * can be used to access the value at that address, which means always dereference those
 pointers which are initialized with a known address
 
 pointer nomenclature : X pointer
 X - some type
 X* - pointer to an X
 int* - integer pointer, we really mean "a pointer to an integer"
 
 type of a reference : has to match the type of the object being referred to
 type of a pointer : also has to match the type of the object being pointed to
 
 initializing a pointer with a literal value : disallowed
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Pointers and assignment: we can use assignment with pointers in two ways
 1-to change what the pointer is pointing at : by assigning the pointer a new address
 2-to change the value being pointed at : by assigning dereferenced pointer a new value
 
 *ptr - returns an lvalue
 
 key insight:
 pointer without dereference - ptr : returns address held by the pointer
 pointer with dereference - *ptr : returns the object being pointed at
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Pointers behave much like lvalue references:
 both pointers and references - provide a way to indirectly access another object
 
 Pointers       vs          References
 
 pointers - we need to explicitly get the address to point at
 pointers - we have to explicitly dereference the pointer to get the value
 pointers - are not required to be initialized
 pointers - are objects
 pointers - can change what they are pointing at
 pointers - can point to nothing
 pointers - are dangerous
 
 references - the address-of happens implicitly
 references - the dereference happens implicitly
 references - required to be initialized
 references - are not objects
 references - cannot be changed to reference something else
 references - must be bound to an object
 references - are safe, except dangling references
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 The address-of operator & : returns a pointer, not an address of its operand as a literal,
 it returns a pointer containing the address of the operand, type of the pointer is derived
 from the argument
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 The size of pointers:
 size of a pointers - depends upon the architecture the executable is compiled for
 32bit executable : used 32bit memory addresses, so pointer will be of 32bits
 64bit executable : pointer will be of 64 bits
 
 size of the pointer : is always the same
 pointer : is just a memory address
 no. of bits required to access a memory address : is constant
 
 Note : this is true regardless the size of the object being pointed to by the pointer
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Dangling pointers:
 a pointer that is holding the address of an object that is no longer valid, e.g. object
 has been destroyed
 
 dereferencing a dangling pointer - will lead to undefined behavior, any other use of an
 invalid pointer is implementation-defined
 you can assign an invalid pointer a new value, such as nullptr (because this doesn’t use the invalid pointer’s value), but other operations such as copying or incrementing an invalid pointer will yield implementation-defined behavior.
 */

#include <iostream>

int main()
{
    /// when binary generated from this code is executed : a piece of memory from RAM will be assigned to object c
    /// assume : c is assigned memory address 299
    /// whenever we use c : program will go to memory address 299 to access the value 'a'
    char c{'a'};
    
    /// ref_c : alias for c
    /// whenever we use ref_c : program will go to memory address 299 to access the value
    /// compiler : takes care of the addressing
    char& ref_c{c};
    std::cout << c << ' ' << ++ref_c << ' ' << c << '\n';
    
    int x{22};
    
    /// prints the value of x
    std::cout << x << '\n';
    
    /// prints the memory address of x
    /// & : operator used to retrieve the address assigned to variable x
    std::cout << &x << '\n';
    
    /// prints the value at memory address of variable x
    /// &x : returns the memory address of x
    /// * : returns the value at the memory address returned by &x
    std::cout << *(&x) << '\n';
    
    /// normal int variable
    int p;
    /// lvalue reference to an int value
    int& p_ref{p};
    /// pointer to an int value, holds the address of an integer value
    int* ptr;
    
    /// incorrect
    /// q1 : pointer to an int
    /// q2 : just a plain text
    int* q1, q2;
    
    /// correct
    /// r1 : pointer to an int
    /// r2 : pointer to an int
    int* r1, * r2;
    
    int i_ptr{2200};
    
    /// pointer initialization
    ///
    /// uninitialized pointer - holds garbage address
    int* ptr1;
    /// null pointer
    int* ptr2{};
    /// initialized pointer with the address of variable i_ptr
    int* ptr3{&i_ptr};
    
    std::cout << i_ptr << '\n';
    /// using the * operator to access the value at the address which ptr3 is holding
    /// ptr3 : returns the address and * uses that address to return the value
    /// we say: ptr3 is pointing to i_ptr
    std::cout << *ptr3 << '\n';
    
    double d{2.222};
    
    /// error : d_ptr is pointer to an int object
//    int* d_ptr{&d};
    
    /// correct : d_ptr2 is pointer to a double object
    double* d_ptr2{&d};
    
    /// not allowed : literal is treated as an integer below
//    int* my_ptr{0x0012FF7C};f
    
    int obj1{400};
    /// obj_ptr pointing at obj1
    int* obj_ptr{&obj1};
    std::cout << *obj_ptr << '\n';
    
    int obj2{300};
    /// changing : obj_ptr is pointing at obj2 now
    /// using operator=, assignment operator to change the address
    obj_ptr = &obj2;
    std::cout << *obj_ptr << '\n';
    
    /// obj_ptr is dereferenced here and the object obj2 is assigned the value 1000
    /// = operator is used to assign the new value to obj2
    /// this is possible because *obj_ptr returns an lvalue which can be used on the left hand of expression
    *obj_ptr = 1000;
    std::cout << *obj_ptr << '\n';
    
    int ref_and_ptr{1};
    
    int& reference{ref_and_ptr};
    int* pointer{&ref_and_ptr};
    
    std::cout << reference << '\n';
    std::cout << *pointer << '\n';
    
    /// using the lvalue reference to change the value of ref_and_ptr
    ++reference;
    
    std::cout << reference << '\n';
    std::cout << *pointer << '\n';
    
    /// using the pointer dereference to change the value of ref_and_ptr
    ++*pointer;
    
    std::cout << reference << '\n';
    std::cout << *pointer << '\n';
    
    int A{91};
    /// this prints Pi as the type of &A, which means address-of operator returns a pointer
    std::cout << typeid(&A).name() << '\n';
    
    char* ch_ptr{};
    int* int_ptr{};
    long double* ld_ptr{};
    
    /// the size of the pointer is 8 bytes on this machine, 64bit machine
    /// the size of the object doesn't matter
    std::cout << sizeof(ch_ptr) << '\n';
    std::cout << sizeof(int_ptr) << '\n';
    std::cout << sizeof(ld_ptr) << '\n';
    
    int dangling{30};
    
    int* dang_ptr{&dangling};
    /// valid
    std::cout << *dang_ptr << '\n';
    
    {
        int dangling{40};
        dang_ptr = &dangling;
        std::cout << *dang_ptr << '\n';
    }/// dang_ptr is dangling here, dangling{40} is destroyed here
    
    /// invalid : undefined behavior from dereferencing a dangling pointer
    std::cout << *dang_ptr << '\n';
    
    return 0;
}
