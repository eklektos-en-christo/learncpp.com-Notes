//
//  main.cpp
//  11.12_dynamically.allocating.arrays
//
//  Created by Εκλεκτός εν Χριστώ on 4/6/23.
//

/*
 single values - can be dynamically allocated
 
 arrays of variables - can also be dynamically allocated
 
 fixed array - array size must be fixed at compile time
 
 dynamically allocated array - allows us to choose the array length at runtime
 
 TO ALLOCATE AN ARRAY DYNAMICALLY: we use the array form of new and delete
 
 often called - new[] and delete[]
 
 length of dynamically allocated arrays - has to be a type that is convertible to
 std::size_t
 
 memory used for fixed arrays - is smaller than the memory used for dynamically allocated
 arrays
 
 programs that need to allocate a lot of memory - typically do so dynamically
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Dynamically deleting arrays:
 
 TO DELETE DYNAMICALLY ALLOCATED ARRAY - we use the array form of delete, which is delete[]
 
 [] - tells the cpu to clean up multiple variables instead of a single variable
 
 using scalar form of delete on array - result in undefined behavior, like data corruption,
 memory leaks or other problems
 
 OFTEN ASKED QUESTION - How does array delete know how many memory to delete?
 ANS- array new[] keeps track of how much memory was allocated to a variable
 
 delete[] - can delete the proper amount of memory, because new[] keeps track of how much
 memory was allocated to a variable
 
 size/length that new[] tracks of - not accessible to programmer
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Dynamic arrays vs. fixed arrays
 
 fixed array:
 -holds the memory address of the first element
 -can decay into a pointer that points to the first element
 -in decayed form, length of the fixed array is not available(nor size of the array via
  sizeof)
 
 dynamic array:
 -a pointer that points to the first element of the array
 -it doesn't know it's length or size
 -programmer is responsible for deallocating the dynamic array via delete[] keyword
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Initializing dynamically allocated arrays:
 
 if need to initialize a dynamically allocated array to 0, the syntax is below:
 
 int* array{new int[length]{}};
 
 auto can also be used in place of int* to avoid writing the type twice as below:
 
 auto* array{new int[length]{}};
 
 it is possible after C++11 - to initialize dynamic arrays using initializer lists
 
 fixed arrays - can also be initialized using uniform initialization/brace initialization
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Resizing arrays - no way to resize an array that has already been allocated, possible
 solution is to allocated a new array, copy the elements over and delete the old array, this
 is error prone especially when element type is a class
 
 recommended - avoid resizing the array
 
 better way to use resizable array - use std::vector
 */

#include <algorithm>
#include <iostream>
#include <string>

int name_count()
{
    std::cout << "How many names to enter? ";
    int length{};
    std::cin >> length;
    
    return length;
}

void get_names(std::string* names, int length)
{
    for (int i{0}; i < length; ++i)
    {
        std::cout << "Enter name #" << i + 1 << ": ";
        std::getline(std::cin >> std::ws, names[i]);
    }
}

void print_names(std::string* names, int length)
{
    std::cout << "Sorted list:\n";
    
    for (int i{0}; i < length; ++i)
        std::cout << "Name #" << i + 1 << ": " << names[i] << '\n';
}

int main()
{
    std::cout << "Enter a +ve integer: ";
    /// used int length, since int will convert to std::size_t
    int length{};
    std::cin >> length;
    
    /// dynamically allocating an array
    /// length - doesn't need to be constant
    /// new[] operator is called
    int* array{new int[length]{}};
    
    std::cout << "Array of length " << length << " allocated." << '\n';
    
    /// setting element 0 to 20
    array[0] = 20;
    
    /// deallocating the dynamically allocated array
    delete[] array;
    
    /// initializing a dynamic array with an initializer list
    /// syntax - has no = operator between the array's length and the initializer list
    /// size 5 - is optional here
    int* array_init_list{new int[5]{1, 2, 3, 4, 5}};
    delete[] array_init_list;
    
    /// this explicitly state that the size is optional to give
    int fixed_array[]{1, 2, 3};
    
    /// QUIZ
    int len{name_count()};
    
    auto* names{new std::string[len]{}};
    
    get_names(names, len);
    
    std::sort(names, names + len);
    
    print_names(names, len);
    
    delete[] names;
    
    return 0;
}
