//
//  main.cpp
//  8.14_function.template.instantiation
//
//  Created by εκλεγμένοι εν Χριστώ on 2/19/23.
//

/*
 Using a function template:
 function templates : aren't actually functions, their code isn't compiled directly
 function templates : generate functions, that are compiled and executed
 
 syntax to use function template-
 max<actual_type>(arguments);
 
 template argument : <actual_type> in the syntax, it specifies the actual type that will be
 used in place of template type T
 
 function template instantiation/instantiation : process of creating functions from function
 templates
 
 implicit instantiation : when instantiation happens due to a function call
 
 function instance/instance/template function : instantiated function
 
 function instances : are normal functions in all regards
 
 compiler : clones the function,
 replaces the template type(T) with the actual type specified inside <>
 
 function template : is only instantiated first time a function call is made in each
 translation unit, further calls to the function are routed to the already instantiated
 function
 
 if no function call is made to function template : function template wont' be instantiated
 in the translation unit
 
 Template argument deduction:
 compiler deduce the actual type that should be used from the argument types in the function
 call, where the type of the arguments match the actual type we want, we don't need to
 specify the actual type
 
 how the compiler resolves the function call from a set of overloaded functions?
 -(with the empty angled brackets), the compiler will only consider max<int> template
 function overloads when determining which overloaded function to call.
 -(with no angled brackets), the compiler will consider both max<int> template function
 overloads and max non-template function overloads.
 
 Best practice
 Favor the normal function call syntax when using function templates.
 
 Function templates with non-template parameters:
 possible to create function templates that have both template parameters and non-template
 parameters, type template parameters can be matched to any type, non-template parameters
 work like the parameters of normal functions
 
 Instantiated functions : may not always compile, refer to add_one()
 
 Using function templates in multiple files:
 If add.cpp had instantiated those functions, the program would have compiled and linked just fine. But such solutions are fragile and should be avoided: if the code in add.cpp was later changed so those functions are no longer instantiated, the program would again fail to link. Or if main.cpp called a different version of add (such as add<float>) that was not instantiated in add.cpp, we run into the same problem.
 solution :put all the template code in a header instead of a source file .cpp
 
 types, templates, inline functions, inline variables : allowed to have identical
 definitions in different files
 
 identical functions instantiated from templates in multiple files : are implicitly inline
 
 inline functions : can be defined in multiple files, as long as definition is identical
 
 Key insight
 Template definitions are exempt from the part of the one-definition rule that requires only one definition per program, so it is not a problem to have the same template definition #included into multiple source files. And functions instantiated from function templates are implicitly inline, so they can be defined in multiple files, so long as each definition is identical.
 
 Best practice
 Templates that are needed in multiple files should be defined in a header file, and then #included wherever needed. The allows the compiler to see the full template definition and instantiate the template when needed.
 
 Generic programming : programming with templates, lets us focus on logic of algorithms
 and design of data structures without having to worry so much about type information
 
 template types : sometimes called generic types
 
 good rule of thumb : create normal functions at first, then convert them into function
 templates
 
 function templates : can expand into a crazy amount of code, lead to code bloat and slow
 compile times
 
 function templates : tend to produce crazy looking borderline unreadable error messages,
 harder to decipher
 
 best practice : use function templates to write generic code that can work with a wide
 variety of types whenever there is a need
 */

#include "add.h"
#include <iostream>

template <typename T>
T max(T x, T y)
{
    std::cout << "Called: max<int>(int, int)\n";
    return (x > y) ? x : y;
}

int max(int x, int y)
{
    std::cout << "Called: int max(int, int)\n";
    return (x > y) ? x : y;
}

/// function template declaration
template <typename T>
T max2(T x, T y);

/// the function that gets instantiated looks something like this
///
/// the generated function by the compiler
template<>
int max2<int>(int x, int y)
{
    return (x > y) ? x : y;
}

/// function template with non-template parameters
/// double y : non-template parameter
/// T x : template parameter
template <typename T>
T some_func(T x, double y)
{
    return 2;
}

template <typename T>
T add_one(T x)
{
    return x + 1;
}

/// function template forward declaration
template <typename T>
T add(T x);

void foo();

int main()
{
    /// instantiates and calls function max<int>(int, int)
    std::cout << max<int>(2, 20) << '\n';
    
    /// calls already instantiated function max<int>(int, int)
    std::cout << max<int>(32, 20) << '\n';
    
    /// works
    std::cout << max2<int>(22, 20) << '\n';
    
    /// int arguments provided, arguments will be implicitly converted to double
    std::cout << max<double>(2.2, 3.3) << '\n';
    
    /// specified that we want to call max<int>
    std::cout << max<int>(1, 9) << '\n';
    
    /// haven't provided actual type,  compiler will attempt to deduce
    /// an actual type from the function arguments
    /// compiler will deduce that actual type int allows to instantiate function max<int>(int, int)
    /// where the type of both template parameters matches the type of the provided arguments
    std::cout << max<>(1, 9) << '\n';
    
    /// compiler will consider both max<int> template function overloads and max non-template function overloads
    std::cout << max(1, 9) << '\n';
    
    /// matches some_func(int, double)
    std::cout << some_func(1, 2.2) << '\n';
    /// matches some_func(int, double) - float promoted to double
    std::cout << some_func(1, 2.2f) << '\n';
    /// matches some_func(double, double)
    std::cout << some_func(1.1, 2.2) << '\n';
    /// matches some_func(float, double)
    std::cout << some_func(1.1f, 2.2) << '\n';
    /// matches some_func(float, double) - float promoted to double
    std::cout << some_func(1.1f, 2.2f) << '\n';
    
    std::cout << add_one(11) << '\n';
    std::cout << add_one(11.1) << '\n';
    
    /// solution here is simply not to call add_one() with std::string type argument
    std::string hello{"hello"};
    /// error : string + int doesn't make sense
//    std::cout << add_one(hello) << '\n';
    
    /// linker error : this function was never instantiated in add.cpp
    ///
    /// works now : put all the template code in add.h header
    std::cout << add<int>(2) << '\n';
    /// main.cpp and add.cpp include add.h
    /// both files can make use of the add<T> function template
    foo();
    
    return 0;
}
