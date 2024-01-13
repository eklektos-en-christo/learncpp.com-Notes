//
//  main.cpp
//  2.11_header.files
//
//  Created by εκλεγμένοι εν Χριστώ on 9/8/22.
//

/*
 header file: propagate declarations to code files
 extensions: .h, .hpp or no extension at all
 
 Key insight
 Header files allow us to put declarations in one location
 and then import them wherever we need them. This can save a
 lot of typing in multi-file programs.
 
 Key insight
 When you #include a file, the content of the included file
 is inserted at the point of inclusion. This provides a
 useful way to pull in declarations from another file.
 
 header files: typically only contain function and variable
 declarations and not their definitions(otherwise ODR)
 
 std::cout - forward declared in iostream.h header but
 defined as part of the C++ standard library
 it is automatically linked into the program during the linker
 phase
 
 Best practice
 Header files should generally not contain function and
 variable definitions, so as not to violate the one
 definition rule. An exception is made for symbolic constants
 
 header file consists two parts:
 header guard
 actual content - forward declarations for all identifiers
 
 Best practice
 Use a .h suffix when naming your header files.
 
 Header files are often paired with code files, with the
 header file providing forward declarations for the
 corresponding code file.
 
 Best practice
 If a header file is paired with a code file (e.g. add.h with
 add.cpp), they should both have the same base name (add).
 
 Best practice
 Source files should #include their paired header file (if
 one exists).
 
 Angled brackets vs double quotes:
 
 angled brackets: telling the preprocessor that this is a
 header file we didn’t write ourselves
 preprocessor will search for the header only in the
 directories specified by the include directories
 The include directories are configured as part of your
 project/IDE settings/compiler settings, and typically
 default to the directories containing the header files
 that come with your compiler and/or OS.
 preprocessor will not search for the header file in your
 project’s source code directory.
 
 double quotes: The preprocessor will first search for the
 header file in the current directory
 If it can’t find a matching header there, it will then
 search the include directories
 
 Rule

 Use double quotes to include header files that you’ve written or are expected to be found in the current directory. Use angled brackets to include headers that come with your compiler, OS, or third-party libraries you’ve installed elsewhere on your system.
 
 Why doesn’t iostream have a .h extension?
 iostream.h is a different header file than iostream
 
 Key insight:
 The header files with the *.h* extension define their names in the global namespace, and may optionally define them in the std namespace as well.
 The header files without the *.h* extension will define their names in the std namespace, and may optionally define them in the global namespace as well.
 
 Best practice

 When including a header file from the standard library, use the version without the .h extension if it exists. User-defined headers should still use a .h extension.
 
 transitive includes:
 When your code file #includes the first header file, you’ll also get any other header files that the first header file includes (and any header files those include, and so on).
 
 Best practice

 Each file should explicitly #include all of the header files it needs to compile. Do not rely on headers included transitively from other headers.
 
 Best practice

 To maximize the chance that missing includes will be flagged by compiler, order your #includes as follows:
     The paired header file
     Other headers from your project
     3rd party library headers
     Standard library headers
 The headers for each grouping should be sorted alphabetically.
 
 Header file best practices:
1 Always include header guards
2 Do not define variables and functions in header files
 (global constants are an exception)
3 Give a header file the same name as the source file it’s
 associated with
4 Each header file should have a specific job, and be as
 independent as possible.
5 Be mindful of which headers you need to explicitly
 include for the functionality that you are using in your code
 files
6 Every header you write should compile on its own (it should
 #include every dependency it needs)
7 Only #include what you need (don’t include everything just
 because you can).
8 Do not #include .cpp files
 */

/// including header add.h to use it in the main
/// "" needed, not <>
#include "add.h"
#include <iostream>

int main()
{
    /// std::cout - forward declared in "iostream" header file
    /// preprocessor: copies all of the content(including forward declaration for
    /// std::cout) from the iostream file into the source file
    std::cout << "Hello World!" << '\n';
    
    std::cout << "Add: " << add(10, 10) << '\n';
}
