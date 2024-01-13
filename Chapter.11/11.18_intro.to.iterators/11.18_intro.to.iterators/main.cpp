//
//  main.cpp
//  11.18_intro.to.iterators
//
//  Created by Εκλεκτός εν Χριστώ on 5/11/23.
//

/*
 Different ways to iterate through an array or other structure of data:
 -with loops and an index(for and while loops)
 -pointers and pointer arithmetic
 -range based for loops
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Iterators:
 
 iterator - an object, designed to traverse through a container, providing access to each
 element along the way
 
 once appropriate type of iterator created, interface provided by the iterator - can be used
 to traverse and access elements without having to worry about what kind of traversal is
 being done or how the data is being stored in the container
 
 C++ iterators : typically use same interface for traversal and access the wide variety of
 different types of containers
 
 operator++ - to move to the next element
 operator*  - to access the current element
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Pointers as an iterator:
 
 simplest kind of iterator - pointer, uses pointer arithmetic, works for data stored
 sequentially in memory
 
 for arrays - the end marker is typically the place in memory where the last element would
 be if the container contained one more element
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Standard library iterators:
 
 all standard library container - offer direct support for iteration
 
 begin() and end() - functions to ask the container for the begin and end points
 
 <iterator> - this header also contains two generic functions std::begin and std::end that
 can be used
 
 include <iterator> when using std::begin and std::end with C-Style arrays
 
 All containers that support iterators - also include <iterator>, so need to explicitly
 include <iterator> when using begin and end with a container
 
 All we need is four things : begin point, end point, operator++ and operator*
 
 Types that have both begin() and end() member functions - are usable in range based for
 loops
 
 Dynamic C-Style arrays/decayed C-Style arrays - don't work with begin() and end(), there is
 no end function for them, the type information doesn't contain the array's length
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Iterator invalidation/dangling iterators :
 
 Iterators - can be left dangling if the elements being iterated over change address or are
 destroyed, we call it iterator is invalidated
 
 accessing an invalidated iterator - produces undefined behavior
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#include <array>            /// this header also includes <iterator> in itself
#include <vector>
#include <iostream>

int main()
{
    std::array data {1, 2, 3, 4, 5};
    std::size_t length{std::size(data)};
    
    std::size_t index{0};
    
    /// while loop to iterate through an array, index is explicit
    while (index < length)
    {
        std::cout << data[index] << ' ';
        ++index;
    }
    std::cout << '\n';
    
    /// for loop to iterate through an array, index is explicit
    for (int index{0}; index < length; ++index)
    {
        std::cout << data[index] << ' ';
    }
    std::cout << '\n';
    
    /// for loop with pointer and pointer arithmetic
    for (auto ptr{&data[0]}; ptr != (&data[0] + length); ++ptr)
    {
        std::cout << *ptr << ' ';
    }
    std::cout << '\n';
    
    /// range based for loop
    for (int i : data)
        std::cout << i << ' ';
    std::cout << '\n';
    
    /// begin : points to the beginning of the container
    auto begin{&data[0]};
    /// end : this points to  one spot beyond the last element
    auto end{begin + std::size(data)};
    
    /// Pointer as an iterator
    /// array traversal using pointer and pointer arithmetic
    ///
    /// operator++ - to move to the next element
    /// operator*   - to access the value of current element, indirection
    for (auto ptr{begin}; ptr != end; ++ptr)
        std::cout << *ptr + 1 << ' ';
    std::cout << '\n';
    
    /// using begin() and end() member functions for begin and end point of the array
    auto iter_begin{data.begin()};
    auto iter_end{data.end()};
    
    /// ++p - to move to the next element
    /// *p - to get the value of current element
    for (auto p{iter_begin}; p != iter_end; ++p)
        std::cout << *p + 10<< ' ';
    std::cout << '\n';
    
    /// std::array has begin and end member functions, so they can be used in range based for loop
    /// behind the scenes - this loop call begin() and end() of the type std::array to iterate over the array
    for (auto i : data)
        std::cout << i << ' ';
    std::cout << '\n';
    
    std::vector<int> v {1, 2, 3, 4};
    
    auto v_begin{v.begin()};
    
    /// moved to 2nd element
    ++v_begin;
    
    std::cout << *v_begin << '\n';
    
    /// erasing the element currently being iterated over
    /// erase() invalidates iterators to the erased element and subsequent elements
    /// iterator v_begin is now invalidated
    v.erase(v_begin);
    
    /// undefined behavior
    ++v_begin;
    std::cout << *v_begin << '\n';
    
    return 0;
}
