//
//  main.cpp
//  2.8_programs.with.multiple.code.files
//
//  Created by εκλεγμένοι εν Χριστώ on 9/6/22.
//

/*
 Best practice

 When you add new code files to your project, give them a .cpp extension.
 
 As programs get larger, it is common to split them into multiple files for organizational or reusability purposes.
 
 When the compiler compiles a multi-file program, it may compile the files in any order. Additionally, it compiles each file individually, with no knowledge of what is in other files.
 
 Whenever you create a new code (.cpp) file, you will need to add it to your project so that it gets compiled.
 
 so, forward declaration can be used to link multiple files
 in the program
 */

#include <iostream>

/// forward declaration of multiply
/// definition of multiply is in another file, multiply.cpp
int multiply(int x, int y);

/// definition is in another file called add.cpp
int add(int x, int y);

int main()
{
    std::cout << "Multiply: " << multiply(2, 2) << '\n';
    std::cout << "Addition: " << add(2, 10) << '\n';
}
