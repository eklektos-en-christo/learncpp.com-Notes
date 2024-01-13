//
//  main.cpp
//  8.15_function.templates.with.multiple.template.types
//
//  Created by εκλεγμένοι εν Χριστώ on 2/20/23.
//

/*
 type conversion : is done only when resolving function overloads, not when performing
 template argument deduction
 
 3 solutions to resolve the problem in calling max(int, double):
 -use static_cast to convert arguments to matching types : put burden on caller
 -provide an actual type : max<double>(double, double)
 -use templates with multiple template type parameters
 
 multiple template type parameters :
 each template type : resolves to its type independently
 a template with two type parameters T and U : T and U resolve to distinct types, or they
 could resolve to the same type.
 
 Abbreviated function templates Cpp2020:
 auto : when auto used as a parameter type in a normal function, compiler will automatically
 convert the function into a function template with each auto parameter becoming an
 independent template type parameter
 case : where you want each template type parameter to be an independent type, this form
 is preferred, the removal of template parameter declaration line makes the code more
 readable and concise.
 
 best practice : feel free to use abbreviated function templates with a single auto
 parameter, or where each auto parameter should be an independent type, cpp2020 should be
 the language standard or newer
 */

#include <iostream>

/// two template type parameters used : T and U
/// x will resolve to T, y will resolve to U
template <typename T, typename U>
T max_multiple(T x, U y)
{
    /// narrowing conversion problem here
    /// solution : use auto return type
    return (x > y) ? x : y;
}

template <typename T, typename U>
auto max_multiple_auto(T x, U y)
{
    return (x > y) ? x : y;
}

/// T : can only represent a single type
template <typename T>
T max(T x, T y)
{
    return (x > y) ? x : y;
}

/*

// there isn’t an easy abbreviated function template for something like this:
 
 template <typename T>
 auto max(T x, T y) // two parameters of the same type
 {
     return (x < y) ? y : x;
 }
 
/// abbreviated function template
auto max_auto_abbreviated(auto x, auto y)
{
    return (x > y) ? x : y;
}

/// same as above abbreviated function template
template <typename T, typename U>
auto max_auto_abbreviated(T x, U y)
{
    return (x > y) ? x : y;
}

*/

int main()
{
    /// error
    /// function call without using <> to specify actual type
    /// arguments of int and double type : no non-template match for max(int, double)
    /// they must resolve to the same actual type
//    std::cout << max(2, 2.2) << '\n';
    
    /// using static cast to convert int to double argument type
    std::cout << max(static_cast<double>(2), 2.2) << '\n';
    
    /// provided an actual type : double
    /// int converted to double : no template argument deduction
    std::cout << max<double>(2, 2.2) << '\n';
    
    /// double takes precedence over int, conditional operator will return double
    /// function is defined as returning a T, T resolves to int
    /// return value double will undergo a narrowing conversion to an int, possible loss of data
    std::cout << max_multiple(2, 2.2) << '\n';
    
    /// max now works fine with operands of different types
    std::cout << max_multiple_auto(2, 2.2) << '\n';
    
    
    
    return 0;
}
