//
//  main.cpp
//  11.13_for.each.loops
//
//  Created by Εκλεκτός εν Χριστώ on 4/11/23.
//

/*
 for loops - easy to mess up and prone to off-by-one errors
 
 for each loop/range based loop - simpler and safer, for cases where we want to iterate
 through every element in an array or other list-type structure
 
 for each loop syntax:
    
        for (element_declaration : array)
            statement;
 
 working - when the statement above is encountered, the loop will iterate through each
 element in array, assigning the value of the current array element to the variable
 declared in element_declaration
 
 for best results - element_declaration should have the same type as the array element
 otherwise type conversion will occur
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 for each loops and auto keyword:
 
 element_declaration - should have the same type as the array elements
 
 so - it's an ideal case to use the auto keyword and let C++ deduce the type of the array
 elements for us
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 for each loop and references:
 
 copying array elements - can be expensive
 
 to avoid copying and simply referring the original element - use references
 
 using reference in for each loop - any changes made to the element will get reflected in
 original array
 
 using const reference - use const reference if the intent is to use for read-only purpose
 
 BEST PRACTICE:
 in for each loops element declarations-
 for non-fundamental types : use references or const references for performance reasons
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 for each loops and non arrays :
 
 for each loops - work with fixed arrays
 
 for each loops - work with many kinds of list-like structures, such as vectors, linked list
 trees and maps
 
 so for each loops - provide flexible and generic way to iterate through more than just
 arrays
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 for each - doesn't work with pointers to an array
 
 dynamic arrays - won't work with for each loops for the same reason
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Can i get the index of the current array element?
 
 for each loops - don't provide a direct way to get the index of the current array element
 
 many structures that for-loops can be used with - are not directly indexable, like linked
 list
 
 C++20 - range based for loops can be used with an init-statement, same like init-statement
 in normal for loops
 
 init-statement - can be used to create a manual index counter without polluting the
 function in which for loop is placed
 
 init-statement - placed right before the loop variable
 
 syntax:
        for (init-statement; element:array)
            statement;
 
 init-statement : only executes one time when the loop starts
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Conclusion:
 for each loops - should be preferred over normal for loop when we need to access all of the
 array elements in forwards sequential order
 
 to prevent copies of each element - element declaration can be a reference
 */

#include <iostream>
#include <vector>
#include <string_view>

int sum_array(const int array[])
{
    int sum{0};
    
    /// error : array is treated as a pointer
    /// array - don't know its size, because it has decayed into a pointer
//    for (auto number : array)
//    {
//        sum += number;
//    }
    
    return sum;
}

int main()
{
    constexpr int fibonacci[]{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
    
    /// simple for each loop to print all the elements in array fibonacci
    ///
    /// access the array element for all iterations through variable current_number
    ///
    /// note - current_number is not an array index, it's assigned the value of the array element for the current loop iteration
    for (int current_number : fibonacci)
        std::cout << current_number << ' ';
    std::cout << '\n';
    
    /// above for each loop using auto keyword
    ///
    /// current_number - its type is deduced from the fibonacci array
    for (auto current_number : fibonacci)
        std::cout << current_number << ' ';
    std::cout << '\n';
    
    std::string array[]{"peter", "natalie", "monica", "leon"};
    
    /// in this for each loop:
    /// element - declaration is declared by value
    /// this means - each array element iterated over will be copied into variable element
    for (auto element : array)
    {
        std::cout << element << ' ';
    }
    
    std::cout << '\n';
    
    /// here:
    /// element - is a reference to the currently iterated array element
    /// this avoids copying
    /// any changes made to the array element - will reflect in the original array
    for (auto& element : array)
    {
        std::cout << element << ' ';
    }
    
    std::cout << '\n';
    
    /// here:
    /// element - const reference to the currently iterated array element
    /// read only - const used to read only the array elements, no modifications possible
    for (const auto& element : array)
    {
        std::cout << element << ' ';
    }
    
    std::cout << '\n';
    
    /// non-array
    /// for each loops also work with list-like structures, as one below
    std::vector<int> fibonacci_vector{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
    
    for (auto number : fibonacci_vector)
    {
        std::cout << number << ' ';
    }
    
    std::cout << '\n';
    
    /// fibonacci - decayed into a pointer here
    std::cout << sum_array(fibonacci) << '\n';
    
    /// these two arrays are correlated by index
    constexpr std::string_view names[]{"Alex", "Betty", "Caroline", "Dave", "Emily"};
    constexpr int scores[]{82, 81, 93, 74, 88};
    
    int max_score{0};
    
    /// i - init statement
    /// i - index of the current array element
    /// i - only executed at the starting of the loop
    for (int i{0}; auto score : scores)
    {
        if (score > max_score)
        {
            std::cout << names[i] << " beats the previous best score of ";
            std::cout << max_score << " by " << (score - max_score) << " points\n";
            max_score = score;
        }
        
        /// increment to the next index
        ++i;
    }
    
    std::cout << "Best score was " << max_score << '\n';
    
    
    /// QUIZ
    constexpr std::string_view fixed_names[]{"Alex", "Betty", "Caroline", "Dave", "Emily", "Fred", "Greg", "Holly"};
    
    std::cout << "Enter a name: ";
    std::string username{};
    std::cin >> username;
    
    bool found{false};
    
    for (std::string_view name : fixed_names)
    {
        if (name == username)
        {
            found = true;
            break;
        }
    }
    
    if (found)
        std::cout << username << " was found\n";
    else
        std::cout << username << " wasn't found\n";
    
    return 0;
}
