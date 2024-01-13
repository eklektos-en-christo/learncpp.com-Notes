//
//  main.cpp
//  11.5_multidimensional.arrays
//
//  Created by Εκλεκτός εν Χριστώ on 3/22/23.
//

/*
 elements of an array - can be of any data type, including arrays
 
 Multidimensional Array - An array of arrays
 
 Where there are two subscripts [][] - that is a two dimensional array
 
 left subscript [][]- think of it as being the row
 right subscript [][] - think of it as being the column
 
 row major order - elements are arranged sequentially row by row, means filling all the
 index of first row and then moving on to the next row
 
 int array[3][5];
 
 above array is laid out as follows:
 
                3 rows-------------->
        +–––––––––––––––––––––––––––––––––––––––+
        |       |       |       |       |       |   1st row
        +–––––––––––––––––––––––––––––––––––––––+
        |       |       |       |       |       |   2nd row
        +–––––––––––––––––––––––––––––––––––––––+
        |       |       |       |       |       |   3rd row
        +–––––––––––––––––––––––––––––––––––––––+
5 columns   ^       ^       ^       ^       ^
          col1    col2    col3    col4    col5
 
 Accessing the 2D array - simply use two subscripts as below:
 array[2][0] = 5;   // 3rd row, first column
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Initializing 2D arrays:
 to initialize - use nested braces, each set of numbers represents a row
 
 some compilers - let you omit the inner braces, but include them anyway for readability
 and because of the way C++ will replace missing initializers with 0
 
 missing initializers - replaced with 0
 
 2D arrays with initializer lists - can omit only the leftmost length specification, means
 left subscript can be omitted during the definition of the 2d array
 
 removing right length specification - not allowed, compiler won't be able to figure out the
 length of the array
 
 like normal arrays, the Multidimensional array - can also be initialized to 0 using {}
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Accessing elements in a 2D array:
 
 to access all of the elements of a 2D array - requires two loops
 
 first loop - for the row
 2nd loop - for the column
 
 2D arrays - typically accessed row by row, row index is typically used as the outer loop
 
 example-
        for (int row{0}; row<num_rows; ++row)   /// step through the rows in array
        {
            for (int col{0}; col<num_cols; ++col/// step through each column in array
            {
                std::cout << array[row][col];
            }
        }
 
 for each loop, C++11 - can be used with multidimensional arrays
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Multidimensional arrays - may be larger than two dimensions
 
 int array[3][5][4];
 
 3D arrays - hard to initialize, typically better to initialize the array to 0 and
 explicitly assign values using nested loops
 
 accessing the elements of a 3D array - analogous to the 2D case
 
 std::cout << array[2][3][2];
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 2D arrays - commonly used in tile based games, where each array element represents a tile
 2D arrays - also used in 3D computer graphics as matrices in order to rotate, scale and
 reflect shapes
 */

#include <iostream>

int main()
{
    /// [ ] [ ] means - a two dimensional array
    /// an array of 3 elements, each element contain a five-element array
    /// a 3-element array of 5-element arrays
    int two_dim_array[3][5];
    
    /// initializing a 2D array, using nested braces
    ///
    int init_2d_array[3][5]
    {
        /// each set of numbers representing a row
        {1, 2, 3, 4, 5},        /// set 1 - row 1
        {6, 7, 8, 9, 10},       /// set 2 - row 2
        {11, 12, 13, 14, 15}    /// set 3 - row 3
    };
    
    /// missing initializers are replaced with 0
    int init_2d_array_miss[3][5]
    {
        {1, 2},                 /// row 1 - 1, 2, 0, 0, 0
        {6, 7},                 /// row 2 -  6, 7, 0, 0, 0
        {11}                    /// row 3 - 11, 0, 0, 0, 0
    };
    
    /// left subscript specification omitted
    /// compiler can do the math to figure out the array length - length is 3 based on the nested sets
    int omit_left_spec_array[][5]
    {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15}
    };
    
    /// not allowed - error, can't omit right length specification
//    int omit_left_right_spec_array[][]
//    {
//        {1, 2, 3, 4, 5},
//        {6, 7, 8, 9, 10},
//        {11, 12, 13, 14, 15}
//    };
    
    /// valid - can be initialized to 0 using empty {} braces
    int init_to_zero[3][5]{};
    
    /// practical example of a 2D array
    constexpr int num_rows{10};
    constexpr int num_cols{10};
    
    /// a 10x10 array with all 0 values
    int array_2D[num_rows][num_cols]{};
    
    /// calculating a multiplication table
    /// starting from 1, because row0 and col0 is always 0
    for (int row{1}; row < num_rows; ++row)
    {
        for (int col{1}; col < num_cols; ++ col)
        {
            array_2D[row][col] = row * col;
        }
    }
    
    /// printing the table
    for (int row{1}; row < num_rows; ++ row)
    {
        for (int col{1}; col < num_cols; ++col)
        {
            std::cout << array_2D[row][col] << '\t';
        }
        
        std::cout << '\n';
    }
    
    return 0;
}
