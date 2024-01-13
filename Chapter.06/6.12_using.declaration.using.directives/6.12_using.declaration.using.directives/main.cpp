//
//  main.cpp
//  6.12_using.declaration.using.directives
//
//  Created by εκλεγμένοι εν Χριστώ on 11/22/22.
//

/*
 Qualified names: that include an associated scope, most often names are
 qualified with a namespace using the scope resolution operator ::, as
 below -
 std::cout      // cout is qualified by namespace std
 ::foo          // foo is qualified by the global namespace
 
 Advance:
 names can also be qualified by a class name using :: operator or by a
 class object using the . or -> (member selection operators)
 class C;
 C::s_member;   // s_member is qualified by class C
 obj.x;         // x is qualified by class object obj
 ptr->y;        // y is qualified by point to class object ptr
 
 Unqualified names: that do not include a scoping qualifier, as above -
 cout and x are unqualified because they don't include an associated
 scope
 
 Using declarations : allow us to use an unqualified name(without scope) as an alias
 for a qualified name
 
 for each name : a separate using declaration is needed
 using declaration : make code more readable
 
 Using directives : imports all of the identifiers from a namespace into the scope of
 using directive.
 
 advance reading:
 using directives do not actually import names into the current scope, instead the
 import the names into an outer scope, however these names are not accessible from
 the outer scope, they are only accessible via unqualified(non-prefixed) lookup from
 the scope of the using directive(or a nested scope), using directive behave as if the
 names had been imported into the current scope.
 
 Why avoid "using namespace std;"?
 this imports all the names from a namespace, the possibility for naming collisions
 increases significantly, especially if the namespace is std
 
 Scope of using declarations and using directives:
 
 using declaration/using directive when used within a block : names are applicable to
 just that block, it follows normal block scoping rules, it reduces the chances for
 naming collisions to occur to just within tha block
 
 using declaration/using directive when used in the global namespace : the names are
 applicable to the entire rest of the file, they have the file scope
 
 Cancelling/replacing a using statement :
 once a "using statement" is declared, there's no way to cancel/replace it with a
 different "using statement" within the scope in which it was declared
 
 Best Practice:
 prefer explicit namespaces over "using statements", avoid "using directives" whenever
 possible. "Using declarations" are okay to use inside blocks.
 */

#include "foolib.h"
#include <iostream>

namespace a
{
    int x{10};
}

namespace b
{
    int x{20};
}

int some_function(double)
{
    return 11;
}

int main()
{
    /// using declaration - this tells the compiler that cout should resolve to std::cout
    using std::cout;
    /// no std:: prefix needed now here
    cout << "HELLO" << '\n';
    
    /// this using directive tells the compiler to import all names from std namespace into the current namespace
    /// without qualification (without prefix)
    /// in this case the current scope is function main( )
    /// so, cout will resolve to the imported std::cout
    using namespace std;
    cout << "LEON" << '\n';
    
    using namespace a;
    using namespace b;
    /// the compiler is unable to determine from which namespace the x is being referred here, a or b
//    std::cout << x << '\n';
    
    /// the solution would be to remove one of the using statement or
    /// the solution would be to use a "using declaration"  or qualifty x with an explicit scope qualifier
    using a::x;
    std::cout << x << '\n';
    std::cout << b::x << '\n';
    
    using ::some_function;
    std::cout << some_function(2.2) << '\n';
    
    /// clearly a part of the foo library
    std::cout << foo::some_function(2) << '\n';
    /// likely a user-defined function
    std::cout << some_function(22.2) << '\n';
    
    /// intentionally limiting the scope of using statement from the outset using block scoping rules
    {
        using namespace foo;
        std::cout << "BLOCK: " << foo::some_function(2) << '\n';
    }   /// using namespace foo expires here
    
    /// useless example below 😂
    {
        using ::some_function;
        std::cout << "BLOCK: " << some_function(2.2) << '\n';
    }
    
    return 0;
}   /// using declaration expires here
