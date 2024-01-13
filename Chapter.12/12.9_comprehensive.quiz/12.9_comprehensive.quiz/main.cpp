//
//  main.cpp
//  12.9_comprehensive.quiz
//
//  Created by Εκλεκτός εν Χριστώ on 7/3/23.
//

/*
 Chapter review:
 
 Functions arguments: can be passed by value, reference or address
 
 Pass by value: use it for fundamental data types and enumerators
 
 Pass by reference: use it for structs, classes or when need the function to modify the
 argument
 
 Pass by address: use it for passing pointers or built-in arrays
 
 Const: make pass by reference and and pass by address const whenever possible
 
 Values: can be returned by value, reference, address
 
 Return by reference or address: can be useful when working with dynamically allocated data
 structs or classes
 
 If returning by address or reference: make sure don't return something what will go out of
 scope
 
 Function pointers: allow to pass a function to another function, allows the caller to
 customize the behavior of a function
 
 Dynamic memory: is allocated on the heap
 
 Call stack: keeps track of all the active functions from start to the current point of
 execution
 
 Local variables: allocated on the stack
 
 Stack: has a limited size
 
 std::vector - can be used to implement stack like behavior
 
 Recursive function: a function that calls itself
 
 All recursive functions: need a termination condition
 
 Command line arguments: allow users/other programs pass data into our program at startup
 
 Command line arguments: are always C-style strings, need to be converted to numbers if
 numeric values are desired
 
 Ellipsis: allow to pass a variable number of arguments to a function
 
 Ellipsis arguments: suspend type checking
 
 Ellipsis: don't know how many arguments are passed, up to the program to keep track of
 these details
 
 Lambda functions: that can be nested inside other functions
 
 Lambda functions: don't need a name
 
 Lambda functions: useful in combination with algorithms library
 
 The best algorithm for determining whether a value exists in a sorted array is called
 binary search.

 std::binary_search returns true if a value exists in a sorted list.
 
 std::equal_range returns the iterators to the first and last element with a given value.
 
 */

#include <iostream>

int main()
{
    return 0;
}
