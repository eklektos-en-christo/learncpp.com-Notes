//
//  main.cpp
//  16.6_container.classes
//
//  Created by Εκλεκτός εν Χριστώ on 7/29/23.
//

/*
 -------------------------------------------------------------------------------------------
 CONTAINER CLASS: a class designed to hold and organize multiple instances of another type,
 either another class or fundamental type.
 
 Most commonly used container: std::array and std::vector, because of the additional
 benefits they provide, they are safer too, provide dynamic resizing, remember their size
 when passed to functions, do bounds checking.
 
 Standardized minimal set of functionality which the container classes provide are:
 
 - create an empty container, via a constructor
 - insert a new object into the container
 - remove an object from the container
 - report the number of objects currently in the container
 - empty the container of all objects
 - provide access to the stored objects
 - sort the elements, optional
 
 Container classes: implement a "member-of" relationship.
 
 -------------------------------------------------------------------------------------------
 TYPES OF CONTAINERS:
 
 - Value containers
 - Reference containers
 
 Value containers: are compositions that store copies of the object that they are holding
 and thus responsible for creating and destroying those copies.
 
 Reference containers: are aggregations that store pointers or references to other objects
 and thus are not responsible for creation or destruction of those objects.
 
 Containers: typically hold only one type of data.
 
 It's better to use Standard library classes if they meet our needs rather than creating our
 own classes.
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>
#include "IntArray.h"

int main()
{
    /// Declare an array with 10 elements
        IntArray array(10);array.

    /// Fill the array with numbers 1 through 10
    for (int i{ 0 }; i<10; ++i)
        array[i] = i+1;

    /// Resize the array to 8 elements
    array.resize(8);

    /// Insert the number 20 before element with index 5
    array.insert_before(20, 5);

    /// Remove the element with index 3
    array.remove(3);

    /// Add 30 and 40 to the end and beginning
    array.insert_at_end(30);
    array.insert_at_beginning(40);

    /// A few more tests to ensure copy constructing / assigning arrays
    /// doesn't break things
    {
        IntArray b{ array };
        b = array;
        b = b;
        array = array;
    }

    /// Print out all the numbers
    for (int i{ 0 }; i<array.get_length(); ++i)
        std::cout << array[i] << ' ';

    std::cout << '\n';
    
    return 0;
}
