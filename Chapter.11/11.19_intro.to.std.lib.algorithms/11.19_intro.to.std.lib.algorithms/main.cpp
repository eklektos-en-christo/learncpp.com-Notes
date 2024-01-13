//
//  main.cpp
//  11.19_intro.to.std.lib.algorithms
//
//  Created by Εκλεκτός εν Χριστώ on 5/30/23.
//

/*
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Functionality provided in algorithms library - generally fall into one of three categories
 
 Three categories:
 
 INSPECTORS   - Used to view only the data in a container, like searching and counting
 MUTATORS     - Used to modify the data in a container, like sorting and shuffling
 FACILITATORS - Used to generate a result based on the values of the data members, like
                objects that multiply values, or objects that determine what order pairs of
                elements should be sorted in.
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 <algorithm> -  library where all these algorithms live, all of these use iterators
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::find - to find an element by value
 std::find - searches for the first occurrence of a value in a container
 std::find - takes 3 parameters, start element, end element and value to search for
 std::find - returns an iterator pointing to the element if found or end of the container if
             not found
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::find_if - to find an element that matches some condition
 std::find_if - used to see if there is a value in a container that matches some condition
 std::find_if - example, a string that contains a specific substring rather than exact value
 std::find_if - instead of passing in a specific value to search for, we pass in a callable
                object, such as a function pointer or a lambda
                For each element being iterated over, find_if will call this function and
                the function can return true if a match is found, or false otherwise
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::count and std::count_if - search for all the occurrences of an element or an element
                                fulfilling a condition
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::sort - sort an array in in ascending order by default
 std::sort - there's a version of std::sort that takes a function as its third parameter
             this allows us to sort however we like
             function as a parameter takes 2 parameters to compare, returns true if the 1st
             argument should be ordered before the second
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 function pointer : When we use a function without parentheses, its not a function call
 std::sort - uses function pointer and calls the actual passed function with any 2 elements
 of the array
 
 std::greater - custom type provided by the C++, its not callable function, in order to use
 it, we need to instantiate an object of that type, curly braces instantiate an anonymous
 object of that type which then gets passed as an argument to std::sort
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::for_each - to do something to all the elements of a container
 std::for_each - takes as list as input and applies a custom function to every element
 std::for_each - can skip elements at the beginning or end of a container using std::next
 
 for skipping first element of container use this-
 std::for_each(std::next(arr.begin()), arr.end(), doubleNumber);
 
 std::for_each - can be parallelized to achieve faster processing, better suited for larger
 projects and big data than a range based for-loop
 
 Algorithms that guarantee sequential execution:
 std::for_each
 std::copy
 std::copy_backward
 std::move
 std::move_backward
 
 Ranges in C++20 : allows us to simply pass array name instead of explicitly passing
 begin() and end() to every algorithm
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 BEST PRACTICE:
 favor using the functions from algorithms library over writing own functions to do the same
 thing
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

/// returns true if the element matches
bool contains_og(std::string_view str)
{
    /// std::find - returns std::string_view::npos if it doesn't find the substring "og"
    /// npos is -1
    /// std::find - returns the index where the substring occurs in str
    return (str.find("og") != std::string_view::npos);
}

/// custom comparison function
/// function needs two arguments, but none passed in main()
bool greater(int a, int b)
{
    /// order a before b : if a is greater than b
    return (a > b);
}

void double_number(int& i)
{
    i *= 2;
}

int main()
{
    std::array A{ 2, 5, 1, 6, 3, 20 };
    
    std::cout << "Enter a value to search for: ";
    int search{};
    std::cin >> search;
    
    std::cout << "Enter a value to replace with: ";
    int replace{};
    std::cin >> replace;
    
    /// std::find - returns an iterator pointing to the element found
    auto found{ std::find(A.begin(), A.end(), search) };
    
    /// std::find - returns the end of the container if not found
    if (found == A.end())
        std::cout << "Couldn't find " << search << '\n';
    else
        /// replace the found element with new value
        *found = replace;
    
    for (int i : A)
        std::cout << i << ' ';
    std::cout << '\n';
    
    ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::array<std::string_view, 5> B{ "Apple", "Banana", "Cat", "Dog", "Elephant" };
    
    /// scan the array B to see if there is any element that contains "og" substring
    auto found_B{ std::find_if(B.begin(), B.end(), contains_og) };
    
    if (found_B == B.end())
        std::cout << "No dogs!\n";
    else
        std::cout << "Found " << *found_B << '\n';
    
    ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::array<std::string_view, 6> C{ "Apple", "Banana", "Cat", "Dog", "Elephant", "Fog" };
    
    /// count how many elements contain the substring "og"
    auto found_C{ std::count_if(C.begin(), C.end(), contains_og) };
    
    std::cout << "Counted " << found_C << " og(s)!" << '\n';
    
    ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::array D{ 12, 23, 10, 2, 7, 40};
    
    /// sort the array D in reverse order, pass greater as argument to std::sort
    std::sort(D.begin(), D.end(), greater);
    
    for (int i : D)
        std::cout << i << ' ';
    std::cout << '\n';
    
    ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::array E{ 1, 2, 3, 4, 5 };
    
    /// for each - taking the list as input and applying a custom function to every element of array E
    std::for_each(E.begin(), E.end(), double_number);
    
    for (int i : E)
        std::cout << i << ' ';
    std::cout << '\n';
    
    return 0;
}
