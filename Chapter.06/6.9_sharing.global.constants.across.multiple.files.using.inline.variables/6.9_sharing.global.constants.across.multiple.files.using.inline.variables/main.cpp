//
//  main.cpp
//  6.9_sharing.global.constants.across.multiple.files.using.inline.variables
//
//  Created by εκλεγμένοι εν Χριστώ on 11/14/22.
//

/*
 Term "optimizing away" - any process where compiler optimizes the performance of the
 program by removing things in a way that doesn't affect the output of the program.
 
 
 Global constants as internal variables:
 Prior to C++17, the following is the easiest and most common solution to share
 global constants across multiple files:

     Create a header file to hold these constants
     Inside this header file, define a namespace
     Add all your constants inside the namespace (make sure they’re constexpr)
     #include the header file wherever you need it
 
 
 Global constants as external variables:
 The above method has a few potential downsides.

 While this is simple (and fine for smaller programs), every time constants.h gets #included into a different code file, each of these variables is copied into the including code file. Therefore, if constants.h gets included into 20 different code files, each of these variables is duplicated 20 times. Header guards won’t stop this from happening, as they only prevent a header from being included more than once into a single including file, not from being included one time into multiple different code files. This introduces two challenges:

     Changing a single constant value would require recompiling every file that includes the constants header, which can lead to lengthy rebuild times for larger projects.
     If the constants are large in size and can’t be optimized away, this can use a lot of memory.
 
 NOTE:
 We use const instead of constexpr in this method because constexpr variables can’t be forward declared, even if they have external linkage.
 
 However, there are a couple of downsides to this method. First, these constants are now considered compile-time constants only within the file they are actually defined in (constants.cpp). In other files, the compiler will only see the forward declaration, which doesn’t define a constant value (and must be resolved by the linker). This means in other files, these are treated as runtime constant values, not compile-time constants. Thus outside of constants.cpp, these variables can’t be used anywhere that requires a compile-time constant. Second, because compile-time constants can typically be optimized more than runtime constants, the compiler may not be able to optimize these as much.


 Because the compiler compiles each source file individually, it can only see variable definitions that appear in the source file being compiled (which includes any included headers). For example, variable definitions in constants.cpp are not visible when the compiler compiles main.cpp. For this reason, constexpr variables cannot be separated into header and source file, they have to be defined in the header file.
 
 Key insight

 In order for variables to be usable in compile-time contexts, such as array sizes, the compiler has to see the variable’s definition (not just a forward declaration).
 
 Given the above downsides, prefer defining your constants in the header file. If you find that for some reason those constants are causing trouble, you can move some or all of them into a .cpp file as needed.


 
 Global constants as inline variables C++17:
 term "inline" in CPP: mean "multiple definitions are allowed"
 
 inline variable : that is allowed to be defined in multiple files without without
 the violation of ODR.
 
 inline global variables : have external linkage by default
 
 linker : consolidates all the inline definitons of a variable into a single variable
 definition
 
 two primary restrictions that inline variables must obey:
 - all definitions of inline variable must be identical, otherwise undefined behavior
 - the inline variable definition(not a forward declaration) must be present in any
 file that uses variable
 
 
 We can include constants.h into as many code files as we want, but these variables will only be instantiated once and shared across all code files.

 This method does retain the downside of requiring every file that includes the constants header to be recompiled if any constant value is changed. If you find yourself changing constants often (e.g. for tuning purposes) and this is leading to long recompile times, moving the changing constants into their own header (to reduce the number of #includes) may help.
 
 Best practice:
 If you need global constants and your compiler is C++17 capable, prefer defining inline constexpr global variables in a header file.
 
 reminder:
 Use std::string_view for constexpr strings.
 */

#include "constants.h"
#include <iostream>

int main()
{
    std::cout << "Enter the radius: ";
    int radius{};
    std::cin >> radius;
    
    /// global constants as internal variables
    std::cout << "The circumference is: " << 2.0 * radius * constants::cx_pi << '\n';
    /// global constants as external variables
    std::cout << "The circumference is: " << 2.0 * radius * constants::pi << '\n';
    /// global constants as inline variables
    std::cout << "The circumference is: " << 2.0 * radius * constants::in_pi << '\n';
    
    return 0;
}
