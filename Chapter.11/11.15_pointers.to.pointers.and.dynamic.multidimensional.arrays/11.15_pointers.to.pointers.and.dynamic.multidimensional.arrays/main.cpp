//
//  main.cpp
//  11.15_pointers.to.pointers.and.dynamic.multidimensional.arrays
//
//  Created by Εκλεκτός εν Χριστώ on 4/21/23.
//

/*
 POINTER TO A POINTER : A POINTER THAT HOLDS THE ADDRESS OF ANOTHER POINTER
 
 Normal pointer - declared using a single asterisk
 
 POINTER TO A POINTER : is declared using two asterisks
 
 POINTER TO A POINTER : works just like a normal pointer
 
 POINTER TO A POINTER : we can dereference to retrieve the value pointed to
 
 POINTER TO A POINTER : retrieved value itself is a pointer, we can dereference it again to
 get the underlying value
 
 double dereference - can be done consecutively
 
 Setting pointer to a pointer directly to a value : not valid
 
 operator& : requires an lvalue but &value is an rvalue
 
 POINTER TO A POINTER : can be set to null
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ARRAYS OF POINTERS : most common use is to dynamically allocate an array of pointers
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 2D dynamically allocated arrays :
 
 another common use for pointers to pointers : to facilitate dynamically allocated
 multidimensional arrays
 
 two possible ways to allocate 2D arrays dynamically:
 -if right most array dimension is constexpr, we can do this:
        int (*array)[5] { new int[x][5] };
                    or
        auto array { new int[x][5] };
 
 -or we allocate an array of pointers first, then we iterate through all array of pointers
  and allocate a dynamic array for each array element
 
 Deallocating the 2D dynamically allocated arrays - requires loop
 
 Flattening the array - two dimensional array into a one dimensional array of size x * y,
 simple math can be used to convert a row and column index for a rectangular 2D array into a
 single index for 1D array
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Passing a pointer by address:
 
 Pointer parameter - can be used to change actual value of the underlying argument passed in
 
 We can pass - a pointer to a pointer to a function and use that pointer to change the value
 of the pointer it points to
 
 If we want a function to be able to modify what a pointer argument points to - this is
 generally better done using a reference to a pointer instead
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Pointer to a pointer to a pointer... - possible
 
 useful in allocating 3D dynamic arrays
 
 this requires a loop inside a loop
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Pointer to a pointer to a pointer to a pointer - possible
 
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 CONCLUSION:
 
 avoid pointers to pointers - unless no other options available

 they are potentially dangerous
 
 easy - to dereference a null or dangling pointer with normal pointers
 
 doubly easy - with a pointer to a pointer, double dereferencing required to get the value
 
 all this becomes complicated to use
 */

#include <iostream>

int get_single_index(int row, int col, int num_cols_in_array)
{
    return (row * num_cols_in_array) + col;
}

int main()
{
    /// normal pointer - int pointer declared using single asterisk(*)
    [[maybe_unused]]int* normal_ptr;
    
    /// pointer to a pointer to an int - declared using two asterisks
    [[maybe_unused]]int** ptr_to_ptr;
    
    int value{40};
    
    /// dereference the pointer to get the int value
    int* ptr{&value};
    std::cout << *ptr << '\n';
    
    /// dereference the pointer to get the pointer
    /// again dereference the pointer to get the int value
    int** ptr_ptr{&ptr};
    std::cout << **ptr_ptr << '\n';
    
    /// not valid
    /// operator& - requires an lvalue
    /// &value - is an rvalue
//    int** ptrptr{&&value};
    
    /// valid - pointer to a pointer can be set to null
    int** ptrptr{nullptr};
    
    /// an array of 10 int pointers
    /// array elements - are of type "pointer to integer" instead of integer
//    int** ptr_array{new int*[10]};
    
    /// fixed 2D array can be declared like this
    int fixed_2d_array[10][10];
    
    /// won't work
    /// dynamically allocating a 2d array is little more challenging
//    int** dynamic_2d_array{new int[10][10]};
    
    int x{7};
//    int (*array)[5]{new int[x][5]};
    /// rightmost dimension must be a compile-time constant
    auto array{new int[x][5]};
    
    /// 2D dynamic array below: dynamic 1D array of dynamic 1D arrays
    ///
    /// if the rightmost dimension isn't a compile time constant then:
    /// allocate an array of pointers first as below
    int** ptr_array{new int*[10]};
    /// then iterate through the array of pointers and allocate a dynamic array for each array element
    /// each array column is dynamically allocated independently
    for (int count{0}; count < 10; ++count)
        ptr_array[count] = new int[5];
    
    /// accessing array as usual
    ptr_array[9][2] = 2;
    
    
    
    int** ptr_array_triangular{new int*[10]};
    
    /// triangle shaped array - possible because each array column is dynamically allocated independently
    /// dynamically allocated 2D array
    for (int count{0}; count < 10; ++count)
        /// count+1 - to increment the length on every iteration, results in triangular shaped array
        ptr_array_triangular[count] = new int[count+1];
    
    /// deallocating dynamically allocated 2D arrays
    /// this method requires loop
    for (int count{0}; count < 10; ++count)
    {
        delete[] ptr_array[count];
        delete[] ptr_array_triangular[count];
    }
    delete[] ptr_array;
    delete[] ptr_array_triangular;
    
    /// flattening the above ptr_array into a single dimensional array of size 10x5
    /// 10x5 array - flattened into a single dimensional array
    int* flattened_array{new int[50]};
    
    /// setting the index using flattened array
    flattened_array[get_single_index(9, 4, 5)] = 3;
    
    /// possible
    /// useful in 3D array allocation dynamically
    /// this would also require a loop inside a loop
    int*** ptr_ptr_ptr;
    
    /// possible
    int**** ptr_ptr_ptr_ptr;
    
    return 0;
}
