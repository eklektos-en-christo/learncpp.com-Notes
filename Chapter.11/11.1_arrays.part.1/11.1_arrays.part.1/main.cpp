//
//  main.cpp
//  11.1_arrays.part.1
//
//  Created by Εκλεκτός εν Χριστώ on 3/15/23.
//

/*
 struct - to aggregate many different data types into one identifier
 
 struct - great for the case where we want to model a single object that has many different
 properties
 
 Array - aggregate data type also, lets us access many variables of the same type through a
 single identifier
 
 Array variable declaration - we use square brackets [] to tell the compiler that this is an
 array variable as well as how many variable to allocate(that is called the array length)
 
 Array length - how many variables to allocate
 
 Fixed length/size array - an array where the length is known at compile time
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Array elements and subscripting:
 
 Element - each of the variables in an array
 
 elements - do have their own unique names
 
 To access the individual elements of an array - we use the array name, along with subscript
 operator[] and a parameter called subscript/index
 
 subscript operator - []
 subscript - parameter, passed into the [] operator
 
 subscript/index - tells the compiler which element we want to access
 
 subscripting/indexing - process, indexing or subscripting the array
 
 syntax to access the individual element:
 array_name[index/subscript];
 
 Key insight :
 in cpp - arrays always count starting from 0
 For an array of length N, the array elements are numbered 0 through N-1
 
 Array's range - 0 to N-1, last element is n-1 because first index is 0
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Array data types:
 Arrays - can be made from any data type
 
 arrays - can also be made from structs, to access a struct member of an array element,
 first pick which array element you want, then  use member selection operator to select the
 struct member you want
 type[index].member_name;
 
 Arrays - can even me made from arrays
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Array subscripts: must always be an integral type, this includes char, short, int long,
 long long etc, bool also(where false gives 0 and true gives index of 1)
 
 Array subscript - can be a literal value, a variable(const/non-const), an expression that
 evaluates to an integral type
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Fixed array declarations:
 when declaring a fixed array - length of the array between [] must be a compile-time
 constant, because length of a fixed array must be known at compile time
 
 non-const variables or runtime constants can't be used - to declare the fixed arrays
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Dynamic arrays -
 fixed arrays - have memory allocated at compile time
 
 two limitations with fixed arrays-
 -they can't have a length based on either user input or some other value calculated at
  runtime
 -their length is fixed and can't be changed
 
 Dynamic arrays - their length can be set at runtime, their length can be changed, they are
 little more complicated to instantiate
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Summary -
 Fixed arrays - provide easy way to allocate and use multiple variables of the same type
 so long as the length of the array is known at compile time
 */

#include <iostream>

struct Rectangle
{
    int length{};
    int width{};
};

/// constexpr symbolic constant
constexpr int days_per_week{7};

enum Days_of_week
{
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
    sunday,
    
    max_days_of_week,
};

#define DAYS_PER_WEEK 7

int main()
{
    /// fixed array named test_score
    /// length of test_score - 30
    /// length is known at compile time
    /// when test_score is instantiated - 30 integers will be allocated
    ///
    /// in the array below:
    /// first element in array is - test_score[0]
    /// no need to remember bunch of different related names
    int test_score[30];
    std::cout << test_score[0] << '\n';
    
    /// sample program that puts together the definition and indexing of an array
    int prime[5]{};
    
    prime[0] = 2;           /// first element
    prime[1] = 3;           /// second element and so on
    prime[2] = 5;
    prime[3] = 7;
    prime[4] = 11;          /// total element N=5, last element has index = N-1 i.e. 4
    
    std::cout << "Lowest prime number: " << prime[0] << '\n';
    std::cout << "Sum of first 5 primes: ";
    std::cout << prime[0] + prime[1] + prime[2] + prime[3] + prime[4] << '\n';
    
    /// allocate three doubles
    /// Array can be made from any data type
    /// below is the array of doubles
    double battery_life_in_hours[3]{};
    battery_life_in_hours[0] = 2.11;
    battery_life_in_hours[1] = 3.8;
    battery_life_in_hours[2] = 8.2;
    
    std::cout << "The average battery life is: ";
    std::cout << battery_life_in_hours[0] + battery_life_in_hours[1] + battery_life_in_hours[2] << " hours(s)" << '\n';
    
    /// array can also be made from structs
    Rectangle rectangles[5]{};
    
    /// accessing struct members of an array element
    /// first pick the array element then use (.) operator to select the members
    rectangles[0].length = 10;
    rectangles[0].width = 5;
    
    /// declared an array of length - 5
    int array[5]{};
    
    /// using an integer literal constant as the index
    array[1] = 22;
    
    /// using an enum constant as the index
    enum Animals
    {
        animal_cat = 2,
    };
    array[animal_cat] = 31;
    
    /// using a non-constant variable as the index
    int index{3};
    array[index] = 44;
    
    /// using an expression that evaluates to an integer value
    array[index + 1] = 8;
    
    /// ways to declare fixed arrays
    ///
    /// fixed array
    /// using a literal constant
    int num_lessons_per_day[7]{};
    
    /// fixed array
    /// using a constexpr symbolic constant
    int num_lessons_per_day2[days_per_week]{};

    /// fixed array
    /// using an enumerator
    int num_lessons_per_day3[max_days_of_week]{};
    
    /// fixed array
    /// using a macro - works, but don't do this, use a constexpr symbolic constant
    int num_lessons_per_day4[DAYS_PER_WEEK]{};
    
    /// fixed array
    /// using a non-const variable
    int days_per_week{};
    std::cin >> days_per_week;
    /// error - days_per_week isn't a compile time constant
//    int num_lessons_per_day5[days_per_week]{};
    
    /// fixed array
    /// using a runtime const variable
    int temp{5};
    /// days_per_week1 - a runtime constant, not a compile time constant
    const int days_per_week1{temp};
    /// error - value of days_per_week1 isn't known until runtime
//    int num_lessons_per_day6[days_per_week1]{};
    
    return 0;
}
