//
//  main.cpp
//  6.7_external.linkage_variable.forward.declarations
//
//  Created by εκλεγμένοι εν Χριστώ on 11/11/22.
//

/*
 external linkage : identifier with this linkage can be seen and used both from the
 file in which it is defined and from other code file(via a forward declaration), in
 this sense, identifiers with external linkage are truly global in that they can be
 used everywhere in the program
 
 functions : have external linkage by default
 
 forward declaration : satisfies the compiler
 
 external variables : global variables with external linkage
 
 extern keyword : to make a global variable external, thus accessible by other files
 
 non-constant globals : external by default, no need to use the extern with them
 
 const globals : can be defined as extern, this makes them external
 
 constexpr globals : can be defined as extern, this makes them external
 
 variable forward declaration via the extern keyword :
 To actually use an external global variable that has been defined in another file,
 you also must place a forward declaration for the global variable in any other
 files wishing to use the variable. For variables, creating a forward declaration
 is also done via the extern keyword (with no initialization value).
 
 extern : has different meanings in different contexts, in some "extern" means giving
 the variable external linkage, in some "extern" means the forward declaration for an
 external variable that is defined somewhere else
 
 Warning:
 If you want to define an uninitialized non-const global variable, do not use the
 extern keyword, otherwise C++ will think you’re trying to make a forward
 declaration for the variable.
 
 constexpr variables: can't be forward declared, because the compiler needs to know
 the value of the constexpr variable at compile time
 
 function forward declarations : don't need the extern keyword, the compiler is able
 to tell whether the function is defined as a new function or it is forward declared
 based on the supplying of function body or not
 
 variable forward declarations : do need the extern keyword, to differentiate variable
 definitions from variable forward declarations
 
 example :
 // non-constant
 int g_x;        // variable definition (can have initializer if desired)
 extern int g_x; // forward declaration (no initializer)

 // constant
 extern const int g_y { 1 }; // variable definition (const requires initializers)
 extern const int g_y;       // forward declaration (no initializer)
 
 file scope vs global scope:
 file scope : often applied to global variables with internal linkage
 global scope : often applied to global variables with external linkage, they can be
 used across the whole program, with appropriate forward declarations
 
 in cpp : all global variables have file scope
 
 
 */

#include <iostream>

/// forward declaration : tells the compiler about the existence of the function
void say_hello();

/// variable forward declarations, defined in a.cpp file, using those variable in this file via the extern forward declaration
/// without the initialization value
/// these foward declarations via the extern are necessary in order to use in this file
extern int g_x;
extern const int g_y;

/// g_a can be used in this file using the extern forward declaration without initialization value
/// g_a can be seen outside of a.cpp file via the extern keyword
/// g_a has the file scope in this file, it can be used from the point of declaration to the end of this file
extern int g_a;

int main()
{
    /// linker connects the function calls to the function definition in a.cpp file
    say_hello();
    
    /// variable from a.cpp file, used here because of extern forward declaration
    std::cout << g_x << '\n';
    std::cout << g_y << '\n';
    
    std::cout << g_a << '\n';
    
    return 0;
}
/// forward declaration for  g_a goes out of scope here
