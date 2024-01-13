//
//  main.cpp
//  11.17_intro.to.std_vector
//
//  Created by Εκλεκτός εν Χριστώ on 5/5/23.
//

/*
 std::array - provides functionality of C++'s built-in fixed arrays
 
 std::vector - provides functionality of C++'s dynamic arrays
 
 std::vector - one of the most useful and versatile tools in C++'s toolkit
 
 std::vector - provides dynamic array functionality that handles its own memory management
 
 std::vector - can create arrays that have their length set at runtime
 
 std::vector - no need to explicitly allocate and deallocate memory using new and delete
 
 std::vector - lives in <vector> header
 
 Declaring a std::vector -
 -no need to specify the length at the declaration
 -initializer list can be used to initialize
 -uniform initialization can also be used
 -the type can be omitted since C++17, type deduction can handle that
 
 both initialized and uninitialized case - no need to include the array length at compile
 time
 
 Accessing the std::vector -
 -element access can be done via operator[]    - no bounds checking
 -element access can be done via at() function - bounds checking
 
 IF YOU REQUEST AN ELEMENT THAT IS OFF THE END OF THE ARRAY - VECTOR WILL NOT AUTOMATICALLY
 RESIZE
 
 C++11 - we can also assign values to a std::vector using an initializer list
 
 std::vector - self-resizes itself to match the number of elements provided
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Self cleanup prevents memory leaks:
 
 When a vector variable goes out of scope - it automatically deallocates the memory it
 controls if necessary, this prevents memory leaks
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Vectors - remember their length
 
 Built-in dynamic arrays - don't know the length of the array they are pointing to
 
 std::vector - keeps track of its length
 
 std::vector - length can be obtained via the size() function
 
 size() - returns a value of nested type size_type, which is an unsigned integer
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Resizing a vector:
 
 resizing a built-in dynamically allocated array is complicated
 
 std::vector - can be resized simply by calling the resize() function
 
 When the vector is resized - existing values are preserved, the new elements are
 initialized to the default value for the type
 
 VECTOR : MAYBE RESIZED TO BE SMALLER THAN THE CURRENT LENGTH
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Initializing a vector to a specific size:
 
 Resizing a vector - computationally expensive, so strive to minimize the number of times
 when resizing a vector
 
 If a vector is needed with a specific number of elements : use parentheses initialization
 
 using direct initialization - we can create a vector with specific size as below:
 std::vector<int> v(5);
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 KEY INSIGHT:
 
 Use brace initialization - when need to initialize the vector with specific values
 Use parentheses initialization - when need to initialize the vector to a specific size, the
 values will be value initialized
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 IF A TYPE IS SOME KIND OF LIST : USE DIRECT INITIALIZATION IF THERE IS NO NEED TO
 INITIALIZE THE OBJECT WITH A LIST OF VALUES
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Compacting bools:
 
 Special implementation for std::vector of type bool - that compacts 8 booleans into a byte
 
 this doesn't change how you use the std::vector
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 CONCLUSION:
 vectors:
 -prevent memory leaks
 -remember their length
 -can be easily resized
 
 - use them wherever dynamic arrays are needed
 */

#include <vector>
#include <iostream>

void memory_leak(bool early_exit)
{
    /// dynamically allocated memory
    int* array{new int[5] {1, 2, 3, 4, 5} };
    
    /// if condition evaluates to true then memory allocated before using new can't be deallocated
    /// memory will be leaked
    if (early_exit)
        return;
    
    /// this line never executes
    delete[] array;
}

void print_length(const std::vector<int>& vector)
{
    std::cout << "Length is: " << vector.size() << '\n';
}

int main()
{
    /// std::vector declaration - no need to specify the length
    std::vector<int> v1;
    
    /// using initializer list to initialize vector - before C++11
    std::vector<int> v2 = {9, 1, 4, 2, 3};
    
    /// using uniform initialization to initialize the vector
    std::vector<int> v3 {9, 1, 4, 2, 3};
    
    /// C++17 - the type can be omitted since C++17
    /// type deduction here - deduced to std::vector<int>
    std::vector v4 {9, 1, 4, 2, 3};
    
    /// [] - no bounds checking, undefined behavior
    std::cout << v4[5] << '\n';
    
    /// at() - does bounds checking, exception
//    std::cout << v4.at(5) << '\n';
    
    /// C++11 - can also assign values to a std::vector using an initializer list
    /// vector is resized now - length is 3 now
    v4 = {1, 2, 3};
    /// out of range error : vector was resized in previous statement
//    std::cout << v4.at(3);
    
    std::cout << "Sizes:" << '\n';
    std::cout << v1.size() << '\n';
    std::cout << v2.size() << '\n';
    std::cout << v3.size() << '\n';
    
    /// this statement is proof that vector auto resized itself
    std::cout << v4.size() << '\n';
    
    /// vector - remember its length
    print_length(v1);
    print_length(v2);
    print_length(v3);
    print_length(v4);
    
    std::vector v5 {0, 1};
    std::cout << v5.size() << '\n';
    
    /// vector resized - but existing values were preserved
    v5.resize(5);
    std::cout << v5.size() << '\n';
    
    /// #1 : existing values were preserved
    /// #2 : new elements were initialized to the default value for the type int
    for (int i : v5)
        std::cout << i << ' ';
    std::cout << '\n';
    
    std::vector v6 {1, 2, 3, 4, 5};
    std::cout << "Length: " << v6.size() << '\n';
    
    for (int i : v6)
        std::cout << i << ' ';
    std::cout << '\n';
    
    /// vector may be resized to be smaller
    /// current length 5, resized to 2
    v6.resize(2);
    std::cout << "Length: " << v6.size() << '\n';
    
    for (int i : v6)
        std::cout << i << ' ';
    std::cout << '\n';
    
    /// create a vector with 5 elements
    /// each element has value 0
    ///
    /// parentheses initialization to create a vector of specific size
    std::vector<int> v7(5);
    
    for (int i : v7)
        std::cout << i << ' ';
    std::cout << '\n';
    
    /// for remembrance
    std::vector a { 1, 2, 3 };      /// allocate 3 elements with values 1, 2, and 3
    std::vector b { 3 };            /// allocate 1 element with value 3
    std::vector<int> c ( 3 );       /// allocate 3 elements with values 0, 0, and 0
    std::vector<int> d ( 3, 4 );    /// allocate 3 elements with values 4, 4, and 4
    
    std::vector<bool> special_implementation {true, false, true, true};
    std::cout << "Length: " << special_implementation.size() << '\n';
    
    for (bool i : special_implementation)
        std::cout << i << ' ';
    std::cout << '\n';
    
    return 0;
}
