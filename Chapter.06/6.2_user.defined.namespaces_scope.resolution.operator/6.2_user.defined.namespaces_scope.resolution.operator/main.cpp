//
//  main.cpp
//  6.2_user.defined.namespaces_scope.resolution.operator
//
//  Created by εκλεγμένοι εν Χριστώ on 11/1/22.
//

/*
 user defined namespaces: namespaces created for own declarations.
 
 namespaces provided by CPP : are not user defined namespaces
 
 namespace identifiers: typically non-capitalized
 
 scope resolution operator :: - tells the compiler that identifier
 specified by the right-hand operand should be looked for in the scope
 of left-hand operand
 
 identifier resolution from within a namespace : if an identifier is used and
 no scope resolution is provided, then compiler will first try to find the
 matching declaration in the same namespace, if no matching identifier is found
 then compiler will check each namespace in a sequence to see if match if found,
 if not found then it will check in global namespace.
 
 multiple namespace blocks : are allowed, legal to declare namespace blocks in
 multiple files/multiple places within the same file
 
 all declaration in a namespace : are considered part of the namespace
 
 Warning
 Do not add custom functionality to the std namespace.
 
 When you separate your code into multiple files, you’ll have to use a
 namespace in the header and source file.
 
 nested namespaces: namespaces inside namespaces
 
 namespace aliases: allow to temporarily shorten a long sequence of namespaces
 into something shorter
 example: namespace test = foo::goo;
 
 in general : avoid deeply nested namespaces.
 
 
 When you should use namespaces

 In applications, namespaces can be used to separate application-specific code from code that might be reusable later (e.g. math functions). For example, physical and math functions could go into one namespace (e.g. math::). Language and localization functions in another (e.g. lang::).

 When you write a library or code that you want to distribute to others, always place your code inside a namespace. The code your library is used in may not follow best practices -- in such a case, if your library’s declarations aren’t in a namespace, there’s an elevated chance for naming conflicts to occur. As an additional advantage, placing library code inside a namespace also allows the user to see the contents of your library by using their editor’s auto-complete and suggestion feature.
 */

#include "growth.h"
#include "circle.h"
#include "add.h"

#include <iostream>

/// this do_something lives in the global namespace
int do_something(int x, int y)
{
    return x * y;
}

/// created namespace foo
namespace foo
{
int do_something(int x, int y)
{
    return x + y;
}

void print()
{
    /// calls do_something from foo namespace
    std::cout << "foo: " << do_something(2, 2) << '\n';
    
    /// explicitly calls do_something from global namespace using :: operator
    std::cout << "foo: " << ::do_something(22, 3) << '\n';
}
}

/// created namespace goo
namespace goo
{
int do_something(int x, int y)
{
    return x - y;
}
}

/// nested namespaces
/// loo is inside moo namespace
namespace moo
{
    namespace loo
    {
        int do_something(int x, int y)
        {
            return x / y;
        }
    }
}

/// C++ 17 way of declaring nested namespaces
/// too is inside soo namespace
namespace soo::too
{
    int do_something(int x, int y)
    {
        return x * y;
    }
}

namespace koo::qoo
{
    int do_something(int x, int y)
    {
        return x + y;
    }
}

int main()
{
    /// using the do_something that exists in foo namespace with the help of ::
    std::cout << foo::do_something(2, 2) << '\n';
    
    /// using the do_something that exists in goo namespace with the help of ::
    std::cout << goo::do_something(2, 2) << '\n';
    
    /// using :: operator with no name prefix
    /// in this case the identifier do_something is looked for in the global namespace
    std::cout << ::do_something(3, 3) << '\n';
    
    foo::print();
    
    /// pi from math namespace from circle.h header
    std::cout << math::pi << '\n';
    
    /// e from math namespace from growth.h header
    std::cout << math::e << '\n';
    
    /// add( ) from add.h and add.cpp, declared in add.h, defined in add.cpp
    std::cout << basic_math::add(2, 20) << '\n';
    
    /// do_something( ) from loo namespace which is inside the moo namespace
    /// accessing using :: operator
    std::cout << moo::loo::do_something(20, 10) << '\n';
    
    /// nested namespaces, accessing using :: operator
    /// C++ 17 style declaration above the main( )
    std::cout << soo::too::do_something(40, 40) << '\n';
    
    /// namespace alias for moo::loo
    /// active refers to moo::loo
    namespace active = moo::loo;
    
    std::cout << active::do_something(20, 20) << '\n';
    
    return 0;
}
