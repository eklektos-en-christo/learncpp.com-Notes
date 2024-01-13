//
//  main.cpp
//  2.9_naming.collisions.and.into.to.namespaces
//
//  Created by εκλεγμένοι εν Χριστώ on 9/7/22.
//

/*
 naming collision/naming conflict: ambiguous identifiers,
 same identifiers, compiler/linker unable to distinguish them
 
 cases of naming collisions:
 two definitions for a function/global variable in separate
 files compiled into the same program : linker error
 two definitions for a function/global variable in the same
 file : compiler error
 
 local scope: doesn't work for function names as it works for
 local variables inside the function block
 
 Namespace: region that allows to declare names inside of it
 for the purpose of disambiguation.
 namespace: solves name conflict
 namespace: provides a scope region to the names
 namespace scope: scope region for variables
 so names in one namespace are different from the identical
 names in another scope
 
 Key insight

 A name declared in a namespace won’t be mistaken for an identical name declared in another scope.
 
 within a namespace: all names must be unique, otherwise
 name conflict
 
 namespaces: often used to group related identifiers in large
 project to ensure they don't accidentally collide with other
 identifiers
 example: putting all math functions in a namespace called
 math, so then math functions won't collide with other similar
 math functions outside of the math namespace
 
 Global namespace/global scope: any name that is not defined
 inside a class, function or a namespace
 implicit defined namespace: global namespace
 
 only declarations and definitions can appear in the global
 namespace
 
 avoid: defining variables in global namespace
 
 other type of statements like the expression statements:
 can't be place in the global namespace except the initializer
 for global variables
 
 Key insight

 When you use an identifier that is defined inside a namespace (such as the std namespace), you have to tell the compiler that the identifier lives inside the namespace.
 
 Best practice

 Use explicit namespace prefixes to access identifiers defined in a namespace.
 
 qualified name: When an identifier includes a namespace
 prefix
 
 using directive: allows to access the names in a namespace
 without using a namespace prefix
 
 Warning

 Avoid using-directives (such as using namespace std;) at the top of your program or in header files. They violate the reason why namespaces were added in the first place.
 */

#include <iostream>
using namespace std;        /// bad practice

/// OKAY: forward declaration
void foo();

/// OKAY but discouraged: uninitialized also
int x;

/// OKAY but discouraged: initialized also
int y{2};

/// error: executable statements not allowed
//x = 22;

int main()
{
    /// :: - scope resolution operator
    /// std:: - std is the namespace
    /// std::cout - cout is the name contained in the std namespace
    /// :: - if no name on left, then it means global namespace
    /// std::cout - cout lives in std namespace
    /// cout is a qualified name because of std prefix on its left
    std::cout << "hello" <<'\n';
    
    /// using directive : bad practice, name conflict may occur
    cout << "using directive" << '\n';
    
    ::foo();
}

/// OKAY: forward declaration
int goo();

void foo()
{
    std::cout << "I'm foo() from global namespace" << '\n';
}
