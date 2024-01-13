//
//  main.cpp
//  11.4_sorting.an.array.using.selection.sort
//
//  Created by Εκλεκτός εν Χριστώ on 3/20/23.
//

/*
 Sorting an array - process of arranging all of the elements in the array in a particular
 order
 
 Sorting an array - can make searching an array more efficient
 
 How sorting works?
 
 Sorting - generally performed by repeatedly comparing pairs of array elements and swapping
 them if they meet some predefined criteria
 
 comparison order of elements - depends upon which sorting algorithm is used
 
 criteria - depends on how the list will be sorted e.g. in ascending or descending order
 
 -------------------------------------------------------------------------------------------
 SELECTION SORT - easiest to understand, one of the slower sorts
 
 this sort performs the following steps to sort an array from smallest to largest:
 1 - starting at index 0, search the entire array to find the smallest value
 2 - swap the smallest value found in the array with the value at index 0
 3 - repeat steps 1 and 2 starting from the next index
 
 example of selection sort algorithm working on 5 elements:
 
 sample array - {30, 50, 20, 10, 40}
 
 find the smallest element, starting from index 0: 10
 swap 10 with the element at index 0: { 10, 50, 20, 30, 40 }
 
 find the smallest element, starting from index 1: 20
 swap 20 with the element at index 1: { 10, 20, 50, 30, 40 }
 
 find the smallest element, starting from index 2: 30
 swap 30 with the element at index 3: { 10, 20, 30, 50, 40 }
 
 find the smallest element, starting from index 3: 40
 swap 40 with the element at index 4: { 10, 20, 30, 40, 50 }
 
 finally, find the smallest element, starting from index 4: 50
 swap 50 with the element at index 4: { 10, 20, 30, 40, 50 }, nothing happens
 
 Done! we can stop actually 1 element before the end of the array because the last
 comparison will always be with itself, which is redundant
 
 -------------------------------------------------------------------------------------------
 SELECTION SORT IN C++:
 
 confusing part is the loop inside of another loop - nested loop
 
 outside loop - iterates through each element one by one
 
 inside loop - for each iteration of the outer loop, the inner loop is used to find the
 smallest element in the remaining array
 
 smallest index variable - keeps track of the index of the smallest element found by the
 inner loop
 
 smallest index variable - then swapped with start index
 
 outer loop advances one element, and process is repeated
 
 -------------------------------------------------------------------------------------------
 std::sort - a sorting function in <algorithm> header
 
 std::sort - by default, sorts in ascending order using operator< to compare pairs of
 elements and swapping them if necessary
 
 -------------------------------------------------------------------------------------------
 BUBBLE SORT - works by comparing adjacent pairs of elements and swapping them if the
 criteria is met, so that elements bubble to the end of the array
 
 Unoptimized bubble sort performs the following steps:
 A) Compare array element 0 with array element 1. If element 0 is larger, swap it with element 1.
 B) Now do the same for elements 1 and 2, and every subsequent pair of elements until you
 hit the end of the array. At this point, the last element in the array will be sorted.
 
 C) Repeat the first two steps again until the array is sorted.
 */

#include <iostream>
#include <utility>          /// for std::swap function
#include <algorithm>        /// for std::sort
#include <iterator>         /// for std::size

int main()
{
    int x{3};
    int y{2};
    std::cout << "Before swap: " << x << ' ' << y << '\n';
    std::swap(x, y);        /// std::swap( ) from utility header, to swap the values of x and y
    std::cout << "After swap: " << x << ' ' << y << '\n';
    
    /// SELECTION SORT IN C++~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int array[]{30, 50, 20, 10, 40};
    constexpr int length{static_cast<int>(std::size(array))};
    
    std::cout << "BEFORE SORT: ";
    
    /// printing before sorting the array
    for (int index{0}; index < length; ++index)
        std::cout << array[index] << ' ';
    
    std::cout << '\n';
    
    /// step through each element of the array
    /// except the last one, last one will already be sorted by the time we get there
    for (int start_index{0}; start_index < length - 1; ++start_index)
    {
        
        /// smallest_index - index of the smallest element we've encountered this iteration
        /// assuming that smallest element is the first element of this iteration
        int smallest_index{start_index};
        
        /// looking for smaller element in the rest of the array
        for (int current_index{start_index + 1}; current_index < length; ++current_index)
        {
            
            /// if smaller element is found, that is smaller than the previously found smallest
            if (array[current_index] < array[smallest_index])
                
                /// then keep track of it
                smallest_index = current_index;
        }
        
        /// smallest_index - is now the smallest element in the remaining array
        /// swap the start element with the smallest element
        std::swap(array[start_index], array[smallest_index]);
    }
    
    std::cout << "AFTER  SORT: ";
    
    /// printing after sorting the array
    for (int index{0}; index < length; ++index)
        std::cout << array[index] << ' ';
    
    std::cout << '\n';
    
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    int array2[]{30, 50, 20, 10, 40};
    
    /// before sorting - printing
    for (int i{0}; i < static_cast<int>(std::size(array2)); ++i)
        std::cout << array2[i] << ' ';
    
    std::cout << '\n';
    
    /// invoking std::sort function on array2
    std::sort(std::begin(array2), std::end(array2));
    
    /// after sorting - printing
    for (int i{0}; i < static_cast<int>(std::size(array2)); ++i)
        std::cout << array2[i] << ' ';
    
    std::cout << '\n';
    
    /// BUBBLE SORT - UNOPTIMIZED~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int bubble_array[]{6, 3, 2, 9, 7, 1, 5, 4, 8};
    constexpr int length_bubble{static_cast<int>(std::size(bubble_array))};
    
    std::cout << "BEFORE SORT: ";
    
    for (int index{0}; index < length_bubble; ++index)
        std::cout  << bubble_array[index] << ' ';
    
    std::cout << '\n';
    
    for (int iteration{0}; iteration < length_bubble - 1; ++iteration)
    {
        for (int current_index{0}; current_index < length_bubble - 1; ++current_index)
        {
            if (bubble_array[current_index] > bubble_array[current_index+1])
                std::swap(bubble_array[current_index], bubble_array[current_index+1]);
        }
    }
    
    std::cout << "AFTER  SORT: ";
    
    for (int index{0}; index < length_bubble; ++index)
        std::cout  << bubble_array[index] << ' ';
    
    std::cout << '\n';
    
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    /// BUBBLE SORT - OPTIMIZED !~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    int array[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };
//        constexpr int length{ static_cast<int>(std::size(array)) }; // C++17
//    //  constexpr int length{ sizeof(array) / sizeof(array[0]) }; // use instead if not C++17 capable
//
//        // Step through each element of the array except the last
//        for (int iteration{ 0 }; iteration < length-1; ++iteration)
//        {
//            // Account for the fact that the last element is already sorted with each subsequent iteration
//            // so our array "ends" one element sooner
//            int endOfArrayIndex{ length - iteration };
//
//            bool swapped{ false }; // Keep track of whether any elements were swapped this iteration
//
//            // Search through all elements up to the end of the array - 1
//            // The last element has no pair to compare against
//            for (int currentIndex{ 0 }; currentIndex < endOfArrayIndex - 1; ++currentIndex)
//            {
//                // If the current element is larger than the element after it
//                if (array[currentIndex] > array[currentIndex + 1])
//                {
//                    // Swap them
//                    std::swap(array[currentIndex], array[currentIndex + 1]);
//                    swapped = true;
//                }
//            }
//
//            // If we haven't swapped any elements this iteration, we're done early
//            if (!swapped)
//            {
//                // iteration is 0 based, but counting iterations is 1-based.  So add 1 here to adjust.
//                std::cout << "Early termination on iteration: " << iteration+1 << '\n';
//                break;
//            }
//        }
//
//        // Now print our sorted array as proof it works
//        for (int index{ 0 }; index < length; ++index)
//            std::cout << array[index] << ' ';
//
//        std::cout << '\n';
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    return 0;
}
