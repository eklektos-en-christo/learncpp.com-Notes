//
//  main.cpp
//  6.6_internal.linkage
//
//  Created by εκλεγμένοι εν Χριστώ on 11/10/22.
//

/*
 Internal linkage : identifiers that can be seen and used within a single file but
 not accessible from other files, not exposed to the linker, so two files having
 identically named identifiers with internal linkage will be treated as independent
 
 internal variables : global variables with internal linkage
 
 static keyword : used to make a  non-constant global variable internal
 
 const and constexpr global variables : have internal linkage by default, no need to
 use static keyword before them
 
 static keyword : is a storage class specifier, sets the name's linkage and its
 storage duration
 
 static, extern, mutable : most commonly used storage class specifiers
 
 one-definition rule : an object or function can't have more than one definition
 either within a file or a program
 
 internal objects and functions defined in different files : independent entities
 so there is no violation of ODR, each internal object has one definition within the
 file or a program
 
 linkage : property of an identifier, not of a variable
 
 function identifiers : have the same linkage property that variable identifiers do
 
 functions : default to external linkage, but can be set to internal linkage using
 static keyword
 
 SUMMARY:
 // Internal global variables definitions:
 static int g_x;          // defines non-initialized internal global variable (zero                       // initialized by default)
 static int g_x{ 1 };     // defines initialized internal global variable

 const int g_y { 2 };     // defines initialized internal global const variable
 constexpr int g_y { 3 }; // defines initialized internal global constexpr variable

 // Internal function definitions:
 static int foo() {};     // defines internal function
 */

#include <iostream>

/// non constant global variable, external linkage by default but now because of the static keyword
/// it has internal linkage
static int g_x;

/// const global variables have internal linkage by default
const int g_y{2};

/// constexpr global variables have internal linkage by default
constexpr int g_z{g_y * 3};

/// forward declaration for function my_fun( )
void my_fun();

int main()
{
    /// this variable has internal linkage, it doesn't refer to the same g_x in a.cpp file
    std::cout << g_x << '\n';
    
    /// this won't work, function definition for my_fun( ) is not accessible from a.cpp, my_fun( ) is static in a.cpp file
//    my_fun();
    
    return 0;
}
