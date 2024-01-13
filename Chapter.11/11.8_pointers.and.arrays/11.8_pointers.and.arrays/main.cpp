//
//  main.cpp
//  11.8_pointers.and.arrays
//
//  Created by Εκλεκτός εν Χριστώ on 3/30/23.
//

/*
 Pointer and arrays - intrinsically(essentially and naturally) related in cpp
 
 Array decay - when a fixed array is used in an expression, the fixed array will decay into
 a pointer that points to the first element of the array
 
 decay - be implicitly converted
 
 In C++, an array and a pointer to the array - not identical
 
 in main() - int array[5]{9, 7, 5, 3, 1};
 array : is of type int[5] and it's value is the array elements themselves
 
 pointer to the array - is of type int* and its value is the address of the first element of
 the array
 
 All elements of the array - can still be accessed through the pointer
 Information derived from the array's type(how long the array is) - can't be accessed from
 the pointer
 
 In most cases - fixed arrays and pointers can be treated identically effectively
 
 We can dereference the array - to get the value of the first element
 
 We can assign a pointer - to point at the array
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Pointers vs. Fixed arrays
 
 fixed array and pointer - are not the same, this can be checked using sizeof operator
 
 when sizeof used on a fixed array - sizeof returns the size of the entire array, i.e.
 array length * element size
 
 when sizeof used on a pointer - sizeof returns the size of the pointer in bytes
 
 fixed array - knows how long the array is
 pointer to array - doesn't know how long the array is
 
 address-of operator when used on pointer - returns the memory address of the pointer
 variable
 
 address-of operator when used on array - returns a pointer to the entire array, this
 pointer also points to the first element of the array, but the type information is
 different
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Passing fixed arrays to functions:
 a fixed array decays into a pointer, and the pointer is passed to the function
 
 even if the parameter is declared as a fixed array - array still decays to a pointer
 
 this means, following two declarations are identical:
 void print(int array[]);
 void print(int* array);
 
 some programmers prefer- [], pointer doesn't know how large the array is, so there is a
 need to pass the array size as a separate parameter anyway(strings being an exception, they
 are null terminated)
 
 recommended syntax: *
 it makes clear that parameter is being treated as a pointer not a fixed array and doing
 the sizeof will operate as if the parameter is a pointer
 
 BEST PRACTICE:
 favor the pointer syntax(*) over the array syntax([]) for array function parameters
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Pass by address:
 arrays - decay into a pointers when passed to a function
 
 that means changing an array in the function changes the actual array argument passed in
 
 NOTE: this phenomenon works with pointers to non-array values as well
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Arrays in structs and classes - don't decay
 
 array that are part of structs and classes - don't decay when the whole struct/class is
 passed to a function
 
 this is a useful way - if decay prevention is desired
 */

#include <iostream>

/// array decays to a pointer, treated as a pointer here
void print_size(int* array)
{
    /// so this prints the size of the pointer and not the size of the array
    std::cout << sizeof(array) << '\n';
}

/// Note: array parameter is declared as a fixed array but
/// CPP implicitly converted the array[ ] to *array
void print_size_fixed(int array[])
{
    /// array is treated a pointer and not as an array
    /// this prints the size of the pointer and not the size of the array
    std::cout << sizeof(array) << '\n';
}

/// ptr - contains a copy of the array's address
void change_array(int* ptr)
{
    /// changing the array element changes the actual array itself
    /// dereferencing the ptr will cause the ptr to point at the first element of the array
    *ptr = 2000;
}

int main()
{
    /// fixed array of 5 integers
    /// to us - below is an array of 5 integers
    /// to compiler - array is a variable of type int[5]
    int array[5]{9, 7, 5, 3, 1};
    
    /// fixed array used in an expression
    /// address of the array's first element
    std::cout << "Element 0 has address: " << &array[0] << '\n';
    
    /// fixed array used in an expression
    /// array decays to a pointer that holds the address of the first element
    std::cout << "The array decays to a pointer holding address: " << array << '\n';
    
    /// dereferencing the array returns the first element, element 0
    /// array is not actually dereferenced
    /// array - gets implicitly converted into a pointer of type int*
    /// pointer is being dereferenced here to get the value at the memory address the pointer is holding
    /// here pointer is holding the array's first element's address
    std::cout << *array << '\n';
    
    char name[]{"Donald"};
    
    /// c-style string also when dereferenced returns the first element
    std::cout << *name << '\n';
    
    /// array decays into a pointer of type int
    std::cout << "Same: " << *array << '\n';
    
    /// assigning a pointer to point at the array
    int* ptr_array{array};
    
    /// ptr_array is also of type int
    std::cout << "Same: " << *ptr_array << '\n';
    
    /// sizeof returning the size of the entire array i.e. sizeof(int) * array length
    /// array knows how long it is
    std::cout << "array: " << sizeof(array) << '\n';
    /// sizeof returning the size of a pointer
    /// pointer to the array doesn't know how long the array is
    std::cout << "pointer: " << sizeof(ptr_array) << '\n';
    
    /// type - int[5]
    std::cout << array << '\n';
    /// taking the address of the array, returns a pointer to the entire array
    /// this pointer points to the first element of the array
    /// type - int(*)[5]
    std::cout << &array << '\n';
    
    /// taking the address of a pointer, yields the memory address of the pointer variable
    /// type - int*
    std::cout << ptr_array << '\n';
    /// type - int**
    std::cout << &ptr_array << '\n';
    
    /// size of the array
    std::cout << sizeof(array) << '\n';
    /// size of the pointer, array argument decays into a pointer here
    print_size(array);
    
    /// array argument decays into a pointer here
    print_size_fixed(array);
    
    /// changing the array in the function reflected in the original array
    std::cout << "before: " << array[0] << '\n';
    /// array decays to a pointer to the array
    /// the value of that pointer is then copied into the ptr parameter of the function change_array(int* ptr)
    change_array(array);
    std::cout << "after: " << array[0] << '\n';
    
    return 0;
}
