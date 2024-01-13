//
//  main.cpp
//  11.3_arrays.and.loops
//
//  Created by Εκλεκτός εν Χριστώ on 3/20/23.
//

/*
 Array subscript - doesn't need to be a constant value, it can be a variable
 
 loop variable - can be used as an index to loop through all of the elements of our array
 and perform some calculations on them
 
 common thing - you will almost certainly find loops, wherever you find arrays
 
 iterating through the array - when a loop is used to access each array element in turn(one
 after another)
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Mixing loops and arrays:
 loops typically used with arrays to do one of three things-
 -calculate a value, e.g. average value, total value
 -search for a value, e.g. highest or lowest value
 -reorganize the array, e.g. ascending or descending order
 
 WHEN CALCULATING A VALUE: a variable is typically used to hold an intermediate result that
 is used to calculate the final value
 
 WHEN SEARCHING A VALUE: a variable is typically used to hold the best candidate value seen
 so far or the array index of the best candidate
 
 WHEN RE-ORGANIZING THE ARRAY: typically involves nested loops
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Arrays and off-by-one errors:
 trickiest parts of using loops with arrays - is making sure that loop iterates the proper
 number of times
 off-by-one errors - easy to make, trying the access an element that is larger than the
 length of the array can have dire consequences
 
 When using loops with arrays - always double check the loop conditions to make sure you do
 not introduce off-by-one errors
 */

#include <iostream>
#include <iterator>
#include <limits>

int main()
{
    constexpr int scores[]{81, 95, 71, 77, 80};
    constexpr int num_of_students{static_cast<int>(std::size(scores))};
    
    /// this variable - updated at every iteration
    int total_score{0};
    
    /// using a for loop to calculate total score
    /// solution is ideal in terms of readability and maintenance
    /// loop does - all element accesses, formulas adjust automatically to account for the no. of elements in the array
    for (int student{0}; student < num_of_students; ++student)
        total_score += scores[student];
    
    std::cout << "Average: " << static_cast<double>(total_score)/num_of_students << '\n';
    
    /// this variable - keep track of the largest score
    /// initialized to zero - to represent that we haven't seen any scores yet
    int max_score{0};
    
    /// using a for loop to search an array in order to determine the best score in the class
    for (int student{0}; student < num_of_students; ++student)
    {
        /// if there is a score that is higher than any we've seen before,
        /// then, set max_score to that higher value
        if (scores[student] > max_score)
            max_score = scores[student];
    }
    
    std::cout << "Max score was: " << max_score << '\n';
    
    /// condition student<=num_of_students is wrong
    /// scores[5] - results in garbage value
    for (int student{0}; student <= num_of_students; ++student)
    {
        if (scores[student] > max_score)
            max_score = scores[student];
    }
    
    std::cout << "Max score was: " << max_score << '\n';
    
    constexpr int array[]{4, 6, 7, 3, 8, 2, 1, 9, 5};
    
    for (int element{0}; element < static_cast<int>(std::size(array)); ++element)
        std::cout << array[element] << ' ';
    
    std::cout << '\n';
    
    /// --------------------------------------------------------------------------------------------------------------------------------------
    int number{};
    
    do
    {
        std::cout << "Enter a number between 1 and 9: ";
        std::cin >> number;
        
        /// if user entered an invalid character
        /// reset any error flags
        if (std::cin.fail())
            std::cin.clear();
        
        /// ignore any extra characters in input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
    } while (number < 1 || number > 9);
    
    /// print the array for the user
    for (int index{0}; index < static_cast<int>(std::size(array)); ++index)
        std::cout << array[index] << ' ';
    
    std::cout << '\n';
    
    /// search the array to find the index of the matching number, then print the index
    for (int index{0}; index < static_cast<int>(std::size(array)); ++index)
    {
        if (array[index] == number)
        {
            std::cout << "The number " << number << " has index " << index << '\n';
            /// each number in the array in unique, so need to search the rest of the array
            break;
        }
    }
    /// --------------------------------------------------------------------------------------------------------------------------------------
    
    return 0;
}
