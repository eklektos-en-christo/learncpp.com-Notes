//
//  main.cpp
//  11.2_arrays.part.2
//
//  Created by Εκλεκτός εν Χριστώ on 3/17/23.
//

/*
 Initializing fixed arrays:
 Array elements - treated like normal variables, so they are not initialized when created
 
 only way to initialize an array - to do it element by element and this is a pain
 especially when array gets larger, it's not initialization but assignment
 
 Assignments - don't work on const arrays
 
 convenient way to initialize entire arrays - via use of an initializer list
 
 initializer list - if there are more initializers in the list than the array can hold, then
 compiler will generate an error
 
 Zero initialization - if there are less initializers in the list than the array can hold,
 the remaining elements are initialized to 0 or whatever value 0 converts to for a
 fundamental non-integral type, like 0.0 for double
 
 to initialize all the elements of an array to 0 - use empty initializer list
 
 When initializer list is omitted - elements are uninitialized, unless they are a class type
 that self initializes
 
 Best practice -
 explicitly initialize the arrays, even when the element type is self-initializing
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Omitted length:
 when initializing a fixed array of elements using an initializer list - compiler can figure
 out the length of the array and explicit declaration of the array length can be omitted
 
 this save typing as well as there is not need to update the length if later the elements
 are removed or new elements added to the array
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Arrays and enums:
 Integer indices - don't provide any information to the programmer about the meaning of the
 index
 
 this can be solved by setting up an enumeration where one enumerator maps to each of the
 possible array indices,
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Arrays and enum classes:
 enum classes - don't have an implicit conversion to integer
 explicit static cast can be used to solve that problem
 but this is a pain,
 
 it might be better to use a standard enum inside a namespace
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Passing arrays to functions:
 C++ treats arrays differently when passing them to functions
 
 when normal variable is passed by value - argument is copied into the function parameter,
 now parameter is a copy, any changes to the parameter won't affect the original argument
 
 Copying large arrays - can be very expensive
 
 C++ - doesn't copy an array when it is passed into a function, instead the actual array is
 passed
 
 that means any changes made to the array will affect the actual array elements
 
 if you want to ensure the function doesn't modify the array elements, make the array const
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Determining the length of an array:
 std::size() - function, from <iterator> header, can be used to determine the length of
 arrays
 
 std::size - doesn't work for arrays that have been passed to functions
 
 std::size - works with other kind of objects like std::array and std::vector
 
 std::size - causes compiler error if you use it on a fixed array that has been passed to a
 function
 
 std::size - returns an unsigned value, to get the signed value, cast can be used
 
 C++20 - use std::ssize() to get the signed value, ssize means "signed size"
 
 ON OLD COMPILERS-------------
 you can use sizeof operator
 sizeof - isn't easy as std::size()
 
 sizeof - operator, can be used on arrays, it will return the total size of the array
 size will be - total array length/single element's size
 
 neat trick - we can determine the length of a fixed array by dividing the size of the
 entire array with the size of an array element, this trick works only on fixed length array
 and when you are doing this trick in the same function that array is declared in
 
 array size = array length * element size
 array size = sizeof(array) * sizeof(array[0])
 -element 0 is typically used for the element size, it's the only element guaranteed to
 exist no matter what the array length is
 
 be careful about using sizeof() on arrays

 array size and array length - most often used to refer to the array's length
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Indexing an array out of range:
 An array of length N - has elements 0 through N-1
 
 if try to access an array with a subscript out of that range - this could overwrite
  the value of another variable or cause a program crash, undefined behavior
 
 C++ - does not do any checking to make sure that indices are valid for the length of the
 array
 
 C++ - also let you use a negative index, results may be undesirable
 
 Rule - always ensure that indices are valid for the range of the array
 */

#include <iostream>
#include <iterator>     /// for std::size

/// setting up an enumeration
/// each enumerator maps to each of the possible array indices
/// last enumerator can be used to declare the array length
/// Array will be automatically resized if another enumerator is added
/// this works only if you don't change the enumerator values manually
enum Student_names
{
    /// 0 - 4 : can be used as array indices
    /// 5 : can be used to declare the array length
    kenny,          /// 0
    kyle,           /// 1
    stan,           /// 2
    butters,        /// 3
    cartman,        /// 4
    max_students,   /// 5
};

/// no implicit conversion to int
enum class Student_name_enum_class
{
    kenny,
    kyle,
    stan,
    butters,
    cartman,
    max_students,
};

/// better to use a standard enum inside of namespace
namespace Student_names_namespace
{
    enum Student_names
    {
        kenny,          /// 0
        kyle,           /// 1
        stan,           /// 2
        butters,        /// 3
        cartman,        /// 4
        max_students,   /// 5
    };
}

/// changing the value won't affect the original value passed
void pass_value(int value)
{
    value = 1000;
}

/// array prime[5] is the actual array passed and not a copy of prime[5] is passed
/// making array const - to ensure that function doesn't modify the array elements passed into it
void pass_array(/*const*/ int prime[5])
{
    /// changes made here will reflect in the original array
    prime[0] = 11;
    prime[1] = 7;
    prime[2] = 5;
    prime[3] = 3;
    prime[4] = 2;
}

/// std::size - doesn't work for arrays that have been passed to functions
void print_array_size(int array[])
{
    /// error
//    std::cout << std::size(array) << '\n';
    /// array - pointer
    /// array[0] - int
    std::cout << sizeof(array)/sizeof(array[0]) << '\n';
}

namespace animals
{
    /// name Animals - can be omitted, because it isn't used anywhere
    enum Animals
    {
        chicken,
        dog,
        cat,
        elephant,
        duck,
        snake,
        max_animals,
    };
}



int main()
{
    /// initializing a fixed array - with an initializer list
    /// {2, 3, 5, 7, 11} - initializer list
    int prime[5]{2, 3, 5, 7, 11};
    
    /// first five elements initialized, rest are initialized to 0
    int array[7]{1, 2, 3, 4, 5};
    
    /// element 6 and 7 are 0
    std::cout << array[0] << '\n';
    std::cout << array[1] << '\n';
    std::cout << array[2] << '\n';
    std::cout << array[3] << '\n';
    std::cout << array[4] << '\n';
    std::cout << array[5] << '\n';
    std::cout << array[6] << '\n' << '\n';
    
    /// initializing all elements to zero
    int array_zero[3]{};
    
    std::cout << array_zero[0] << '\n';
    std::cout << array_zero[1] << '\n';
    std::cout << array_zero[2] << '\n' << '\n';
    
    /// element uninitialized when initializer list omitted
    /// int - doesn't self initialize
    int array_omit[5];
    
    std::cout << array_omit[0] << '\n';
    std::cout << array_omit[1] << '\n';
    std::cout << array_omit[2] << '\n';
    std::cout << array_omit[3] << '\n';
    std::cout << array_omit[4] << '\n';
    
    /// double - doesn't self-initialize
    int array_omit_double[3];
    
    std::cout << array_omit_double[0] << '\n';
    std::cout << array_omit_double[1] << '\n';
    std::cout << array_omit_double[2] << '\n';
    
    /// std::string - class type, so all elements initialized to an empty string
    std::string str[3];
    
    std::cout << str[0] << '\n';
    std::cout << str[1] << '\n';
    std::cout << str[2] << '\n';
    
    /// explicit defining the length of the array - 3
    int dont_omit_length[3]{1, 2, 3};
    std::cout << sizeof(dont_omit_length) << '\n';
    /// length is figured out by the compiler using initializer list
    int omit_length[]{4, 8};
    std::cout << sizeof(omit_length) << '\n';
    
    /// extra enumerator used to ensure the array has proper length
    int test_scores[max_students]{};
    /// using enum as array index for better documentation to the programmer
    /// it's much clearer what each of the array elements represents
    test_scores[butters] = 66;
    
    /// with enum classes - implicit conversion to int won't work
//    int test_scores_enum_class[Student_name_enum_class::max_students]{};
//    test_scores_enum_class[Student_name_enum_class::kenny] = 22;
    
    /// can be solved with explicit static cast to integer
    /// but doing this is somewhat of a pain
    int test_scores_enum_class[static_cast<int>(Student_name_enum_class::max_students)]{};
    test_scores_enum_class[static_cast<int>(Student_name_enum_class::stan)] = 41;
    std::cout << test_scores_enum_class[static_cast<int>(Student_name_enum_class::stan)] << '\n';
    
    /// better to use a standard enum inside of namespace
    int test_scores_namespace[Student_names_namespace::max_students]{};
    test_scores_namespace[Student_names_namespace::cartman] = 89;
    std::cout << test_scores_namespace[Student_names_namespace::cartman] << '\n';
    
    /// pass by value - no change to the actual argument
    int value{1};
    std::cout << "Before pass: " << value << '\n';
    pass_value(value);
    std::cout << "After pass: " << value << '\n';
    
    int prime_changeable[5]{2, 3, 5, 7, 11};
    std::cout << "Before pass: " << prime_changeable[0] << '\n';
    pass_array(prime_changeable);
    std::cout << "After pass: " << prime_changeable[0] << '\n';
    
    int array_size[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    /// using std::size to determine the size of the array_size array
    std::cout << "Array has: " << std::size(array_size) << " elements." << '\n';
    
    std::cout << sizeof(array_size) << '\n';
    std::cout << sizeof(int) << '\n';
    /// neat trick - get the length of the array
    std::cout << "length: " << sizeof(array_size)/sizeof(array_size[0]) << '\n';
    
    /// in the function definition-
    /// array_size is the pointer
    print_array_size(array_size);
    
    int out_of_range[3]{};
    /// indexing an array out of range - undefined behavior
    std::cout << out_of_range[3] << '\n';
    
    /// assume 365 days in a year
    /// array with a value of 0.0 for each day
    /// hold the high temperature
    double temperature[365]{};
    
    int legs[animals::max_animals]{2, 4, 4, 4, 2, 0};
    
    std::cout << "Elephant has " << legs[animals::elephant] << " legs" << '\n';
    std::cout << "Snake has " << legs[animals::snake] << " legs" << '\n';
    
    return 0;
}
