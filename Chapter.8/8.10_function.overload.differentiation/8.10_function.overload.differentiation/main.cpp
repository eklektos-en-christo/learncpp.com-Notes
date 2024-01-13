//
//  main.cpp
//  8.10_function.overload.differentiation
//
//  Created by εκλεγμένοι εν Χριστώ on 2/16/23.
//

/*
 Overloaded functions that are not properly differentiated : cause compiler error
 
 How overloaded functions are differentiated?
 
 –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
 function property      Used for differentiation            Notes
 –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
 No. of parameters      YES
 Type of parameters     YES                                 excludes typedefs, type aliases
                                                            const qualifier on value
                                                            parameters, includes ellipses
 Return type            NO
 –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
 
 function's return type : not used to differentiate overloaded functions
 
 For member functions, additional function-level qualifiers are also considered:
 Function-level qualifier    Used for overloading
    -const or volatile              Yes
    -Ref-qualifiers                 Yes
 
 Overloading based on number of parameters:
 overloaded function is differentiated so long as each overloaded function has a different
 no. of parameters
 
 Overloading based on type of parameters:
 function can also be differentiated so long as each overloaded function's list of
 parameter types is distinct
 
 type aliases/ typedefs : are not distinct types, overloaded functions using type aliases
 are not distinct from the overloads using the aliased type
 
 parameters passed by value : the const qualifier is also not considered
 
 ellipsis parameters : are considered to be a unique type of parameters
 
 Type signature/signature : parts of a function header that are used for function
 differentiation
 -parts include : function name, no. of params, param type, function level qualifiers, it
 notably doesn't include the return type
 
 Name mangling : at the compilation of a function, compiled name of the function is altered
 based on various criteria, such as no. and type of parameters, so that the linker has
 unique names to work with
 example- int fcn() might compile to name __fcn_v
          int fcn(int) might compile to name ___fcn_i
 so in compiled code, names are actually unique
 
 different compilers : produce different mangled names
 */

#include <iostream>

/// function call with 2 parameters will go to this function
int add(int x, int y)
{
    return x + y;
}

/// function call with 3 parameters will go to this function
int add(int x, int y, int z)
{
    return x + y + z;
}

/// overloading based on type of parameters
/// all the below function overloads are different from each other based on parameter types
double add(double x, double y);
double add(int x, double y);
double add(double x, int y);

typedef int Height;
using Age = int;

/// all 3 functions are not differentiated below
/// compiler error
void print(int i)
{
    std::cout << i << '\n';
}

/// compiler error
//void print(Height h)
//{
//    std::cout << h << '\n';
//}
//
///// compiler error
//void print(Age a)
//{
//    std::cout << a << '\n';
//}

void sub(int a, int b)
{
    std::cout << a - b << '\n';
}

/// error : redefinition of previous function
/// const is not considered when parameters are passed by value
//void sub(int a, const int b)
//{
//    std::cout << a - b << '\n';
//}

void ellipsis(int x, int y)
{
    std::cout << x * y << '\n';
}

/// different from the previous function
void ellipsis(int x, ...)
{
    std::cout << x << '\n';
}

/// return type of the function : not considered when differentiating overloaded functions
int get_random();
//double get_random();
int get_random_int();
double get_random_double();     /// way to address this : use different function names

int main()
{
    std::cout << add(2, 2) << '\n';
    std::cout << add(2, 2, 2) << '\n';
    print(22);
    
    return 0;
}
