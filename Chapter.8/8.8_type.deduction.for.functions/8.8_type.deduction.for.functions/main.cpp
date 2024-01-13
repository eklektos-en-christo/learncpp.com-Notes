//
//  main.cpp
//  8.8_type.deduction.for.functions
//
//  Created by εκλεγμένοι εν Χριστώ on 2/15/23.
//

/*
 in cpp14 : auto keyword was extended to do function return type deduction
 
 this works : by using auto keyword in place of function's return type
 
 compiler deduces return type from the return statement
 
 when using auto : all return statements within the function must return values of the same
 type, otherwise error, if such as case is desired - either explicitly specify the return
 type for the function(compiler will perform implicit conversion), or explicitly convert all
 return statements to the same type
 
 static_cast : can also be used for non-literal types
 
 major downside of function with auto return type : such functions must be fully defined
 before they can be used, a forward declaration is not sufficient, inability for such
 functions to be forward declared limits their usefulness in multi-file programs
 
 normal functions that return auto : are typically only callable from within the file in
 which they are defined
 
 best practice : favor explicit return type over function return type deduction for normal
 functions
 
 Trailing return type syntax:
 auto : where the return type is specified after the rest of the function prototype
 auto : doesn't perform any type deduction in this case, it is just part of the syntax
 use of trailing return type syntax : makes all function names line up
 
 Trailing return type syntax: also required for some advanced features of cpp, such as
 lambdas
 
 Type deduction: can't be used for function parameter types, function templates was
 designed to handle such cases
 */

#include <iostream>

auto add(int x, int y)
{
    /// type deduction : compiler will deduce the return type from this return statement
    return x + y;
}

/// trailing return syntax
/// auto : doesn't perform any type deduction
auto add2(int x, int y) -> int
{
    return x + y;
}

/// all return values must be of same type when auto is used as return type of the function
auto some_func(bool b)
{
    if (b)
        /// error : different type of the return value
//        return 2;
        return static_cast<double>(2);  /// solution
    else
        /// error : different type of the return value
        return 2.2;
}

/// this function with deduced return type cannot be used before it's definition
auto foo();

/// trailing return type syntax : making all the function names line up
auto add3(int x, int y) -> int;
auto mul(int x, int y) -> double;
auto div() -> void;

/// type deduction: doesn't work for function parameters
//void add_and_print(auto x, auto y)
//{
//    std::cout << x + y << '\n';
//}

int main()
{
    /// compiler has only seen the forward declaration at this point, so this won't work as expected
//    std::cout << foo() << '\n';
    
    return 0;
}

auto foo()
{
    return 2;
}
