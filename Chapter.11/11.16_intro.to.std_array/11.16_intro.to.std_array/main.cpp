//
//  main.cpp
//  11.16_intro.to.std_array
//
//  Created by Εκλεκτός εν Χριστώ on 4/27/23.
//

/*
 Downsides of fixed and dynamic arrays:
 - fixed arrays : decay into pointers, losing the array length information
 - dynamic arrays : have messy deallocation issues, challenging to resize without errors
 
 To make array management easier, C++ std lib includes functionality:
 std::array
 std::vector
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::array : provides fixed array functionality, won't decay into a pointer when passed in
 to a function
 
 std::array : defined in <array> header, inside the std namespace
 
 To declare a std::array variable -
        std::array<int, 3> my_array;
 3 - length
 int - type
 my_array - name of the array
 
 length of std::array - must be known at compile time
 
 std::array - can be initialized using initializer lists or list initialization
 
 In built in fixed arrays - array length can be omitted when providing an initializer
 
 With std::array - length can't be omitted when providing an initializer
 
 C++17 - it is allowed to omit the type and size, but they can only be omitted together, not
 one or the other and array must be explicitly initialized
 
 C++20 - it is possible to specify the element type but omit the array length
 std::to_array - used to create an array with a specific type and deduced size
 
 std::to_array - more expensive than std::array when creating directly, because it copies
 all elements from a C-style array to a std::array
 
 std::to_array - should be avoided when the array is created many times e.g. in a loop
 
 values to the array : can also be assigned using an initializer list
 
 subscript operator : works the same as it works with built in fixed arrays
 
 subscript operator : does not do any bounds checking, if invalid index is provided, bad
 things will happen probably
 
 .at() function - std::array provides this function, it is a second form of array access, it
 also does the runtime bounds checking
 
 .at() - slower because it does bounds checking but it is safer than operator[]
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Size and Sorting on std::array -
 
 size() - function, can be used to retrieve the length of the std::array
 
 std::array - doesn't decay to a pointer when passed to a function, size() will work even
 if it is called within a function
 
 std lib size vs sizeof on a native fixed array:
 
 size - means array length, total elements in the array
 
 sizeof - actual size of the array in memory, the size of an element multiplied by the array
 length
 
 std::sort - lives in algorithm header, sorts the array in reverse or forward order
 
 BEST PRACTICE:
 always pass std::array by reference or const reference
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Range based for loops - work with std::array
 
 because the length is always known
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Passing std::array of different lengths to a function:
 
 std::array - it's type and length are part of the type information
 
 this limits the function to only handling arrays of specific type and length
 
 solution: templates
 
 C++ will use that template to create real functions with actual types as needed
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Manually indexing std::array via size_type :
 
 size() function and array index parameter to operator[] - use a type called size_type
 
 size_type - unsigned integral type
 
 size_type - isn't a global type
 
 size_type - defined inside the definition of std::array
 
 C++ - allows nested types
 
 size_type - when we want to use it, we have to prefix it with the full array type, assuming
 std::array will act like a namespace in this regard
 
 fully prefixed type of size_type is : std::array<int, 5>::size_type
 
 std::array::size_type - is just an alias for std::size_t, we can use std::size_t instead of
 std::array<int, 5>::size_type
 
 A better solution to manual indexing - use range based for loops or iterators
 
 UNSIGNED INTEGERS : wrap around/overflow when their limit is reached
 common mistake in wraparound : decrementing the index that is 0 already, this cause the
 wraparound to the maximum value
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Array of struct : every type that can be used in a regular array can be used in a
 std::array
 
 std::array - defined as a struct that contains a C-style array member whose name is
 implementation defined
 
 To initialize the struct std::array - we need to use extra set of braces, so that compiler
 may treat all the lists inside those braces as a whole list of elements
 
 std::array - when the element type requires a list of values, use extra set of braces
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 SUMMARY :
 
 std::array - great replacement for built in fixed arrays
 std::array - efficient, doesn't use any more memory than built in fixed arrays
 std::array - only one downside  : awkward syntax
 std::array - has signed/unsigned issues with size and indexing
 std::array - need explicit array length unless the type is omitted also, which isn't possible always
 
 RECOMMENDATION :
 Use std::array over built in fixed arrays for non-trivial array use
 */

#include <iostream>
#include <array>            /// for std::array
#include <algorithm>        /// for sort
#include <cstddef>          /// for std::size_t

/// std::array doesn't decay to a pointer when passed to a function
/// array passed by const reference - to avoid making a copy of the std::array
void print_length(const std::array<int, 5>& array)
{
    /// size( ) - works also within the function, std::array didn't decay to a pointer
    std::cout << "Length: " << array.size() << '\n';
}

/// range based for loop working with std::array
void print_array(const std::array<int, 5>& array)
{
    /// length of array is known
    /// so, range based for loop works with std::array
    for (int element : array)
        std::cout << element << ' ';
    std::cout << '\n';
}

void sort_array(std::array<int, 5>& array, bool order)
{
    /// sort the array forwards
    if (order)
        std::sort(array.begin(), array.end());
    /// sort the array backwards
    else
        std::sort(array.rbegin(), array.rend());
}

/// template function - handles std::array of different element types and lengths
template <typename T, std::size_t size>
void print_array_template(const std::array<T, size>& array)
{
    for (auto element : array)
        std::cout << element << ' ';
    std::cout << '\n';
}

struct House
{
    int number{};
    int stories{};
    int rooms_per_story{};
};

int main()
{
    /// declare an integer std::array with length 5
    /// length must be known at compile time
    std::array<int, 5> my_array1;
    
    /// std::array - can be initialized using list initialization
    std::array<int, 5> my_array2 {1, 2, 3, 4, 5};
    
    /// std::array - can be initialized using initializer list
    std::array<int, 5> my_array3 = {1, 2, 3, 4, 5};
    
    /// std::array - length can't be omitted when providing an initializer
//    std::array<int, > my_array4 {1, 2, 3, 4, 5};
//    std::array<int> my_array4 {1, 2, 3, 4, 5};
    
    /// C++17 - allowed to omit the type and size, both must be omitted together
    ///
    /// type deduced to std::array<int, 5>
    std::array my_array5 {1, 2, 3, 4, 5};
    /// type deduced to std::array<double, 2>
    std::array my_array6 {1.12, 3.5};
    
    /// C++20 feature
    ///
    /// type and size specified
//    auto my_array7 {std::to_array<int, 5>({1, 2, 3, 4, 5})};
    /// type specified, size deduced
//    auto my_array8 {std::to_array<int>({1, 2, 3, 4, 5})};
    /// type and size deduced both
//    auto my_array9 {std::to_array({1, 2, 3, 4, 5})};
    
    std::array<int, 5> my_array10;
    
    /// values to the array can also be assigned using an initializer list
    my_array10 = {1, 2, 3};         /// remaining elements are set to zero
    my_array10 = {9, 2, 3, 20};     /// last element set to zero
    my_array10 = {0};               /// all remaining elements set to zero
//    my_array10 = {1, 1, 1, 1, 1, 1};/// not allowed, too many elements in the initializer list
    
    /// subscript operator works the same as it works with built in fixed arrays
    std::cout << my_array10[0] << '\n';
    std::cout << my_array10[1] << '\n';
    std::cout << my_array10[2] << '\n';
    std::cout << my_array10[3] << '\n';
    std::cout << my_array10[4] << '\n';
    
    /// subscript doesn't do any bounds-checking, bad things can happen surely
    std::cout << my_array10[80] << '\n';
    
    /// at() function - it is a second form of array access, also does the runtime bounds checking
    my_array10.at(1) = 33;
    std::cout << my_array10.at(1) << '\n';
    
    /// runtime bounds checking - programs terminates, exception thrown
//    std::cout << my_array10.at(80) << '\n';
    
    /// size( ) function - can be used to retrieve the length of the std::array
    std::cout << my_array5.size() << '\n';
    
    ///
    print_length(my_array5);
    
    print_array(my_array5);
    
    std::array<int, 5> for_sort {7, 9, 1, 3, 2};
    std::cout << "Unsorted: ";
    print_array(for_sort);
    
    std::cout << "Ascending: ";
    sort_array(for_sort, true);
    print_array(for_sort);
    
    std::cout << "Descending: ";
    sort_array(for_sort, false);
    print_array(for_sort);
    
    std::array<int, 5> int_array {1, 2, 3, 4, 5};
    std::array<double, 5> double_array {1.1, 2.2, 3.3, 4.4, 5.5};
    
    print_array_template(int_array);
    print_array_template(double_array);
    
    /// manual indexing std::array via size_type, std::array::size_type just an alias for size_t
    for (std::size_t i{0}; i < int_array.size(); ++i)
        std::cout << int_array[i] << ' ';
    std::cout << '\n';
    
    /// infinite loop
    /// produces undefined behavior when i wraps around
    ///
    /// issue #1 : if int_array is empty i.e. size() returns 0 then int_array.size() - 1 wraps around
    /// issue #2 : i >= 0 is always true, because unsigned integers can't be less than zero, i is unsigned int here
//    for (auto i{int_array.size() - 1}; i >= 0; --i)
//        std::cout << int_array[i] << ' ';
//    std::cout << '\n';
    
    /// working example - reverse printing the array
    /// in first iteration i is 4 because i was decremented in the condition i-- > 0
    /// when i is 0 and about to wrap around, the condition is not longer true and loop stops
    /// i - wraps around when we do i-- for the last time but not used afterwards
    for (auto i{int_array.size()}; i-- > 0;)
        std::cout << int_array[i] << ' ';
    std::cout << '\n';
    
    /// std::array of struct
    std::array<House, 3> houses{};
    
    houses[0] = {1, 5, 10};
    houses[1] = {2, 3, 10};
    houses[2] = {3, 4, 20};
    
    for (const auto& house : houses)
    {
        std::cout << "House number: " << house.number;
        std::cout << " has " << (house.stories * house.rooms_per_story);
        std::cout << " rooms" << '\n';
    }
    
    /// this kind of initialization won't work
    /// compiler will interpret { 13, 4, 30 } as the initializer for the entire array
    ///
    /// reason : std::array is defined as a struct that contains a C-style array member
    /// this will initialize only the index 0 of houses array, rest will be zero-initialized
    ///
    /// { 14, 3, 10 }, { 15, 3, 40 } : will be treated as extraneous values and this will result in error
//    std::array<House, 3> houses2 {
//        { 13, 4, 30 },
//        { 14, 3, 10 },
//        { 15, 3, 40 }
//    };
    
    /// correct way of initializing std::array struct
    std::array<House, 3> houses3
    {
        /// initializer for houses3
        {   /// extra set of braces to initialize C-style array member inside std::array struct
            /// extra set of braces - required to initialize C-style array member
            /// within set of braces - we can then initialize each element individually
            ///
            /// each element - is initialized inside its own set of braces
            { 13, 4, 30 },      /// initializer for element 0
            { 14, 3, 10 },      /// initializer for element 1
            { 15, 3, 40 },      /// initializer for element 2
        }
    };
    
    return 0;
}
