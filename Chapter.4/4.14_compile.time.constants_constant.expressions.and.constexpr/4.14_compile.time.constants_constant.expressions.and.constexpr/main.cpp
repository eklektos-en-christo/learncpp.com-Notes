//
//  main.cpp
//  4.14_compile.time.constants_constant.expressions.and.constexpr
//
//  Created by εκλεγμένοι εν Χριστώ on 9/21/22.
//

/*
 Constant expression: expression that can be evaluated by
 the compiler at the compile time.
 
 constant expression: all values in constant expression must
 be known at compile time, all the called functions and
 operators must support compile time evaluation.
 
 compiler: replaces the constant expression with result of
 evaluated expression
 
 Compile time evaluation of constant expressions:
 -makes compilation longer
 -but expressions only need to be evaluated once
 -resulting executables are faster and use less memory
 
 Compile-time constants: constant whose value is known at
 compile-time. e.g. literals 1,2,3, "hello" are one type of
 compile-time constant
 
 const variables: may or may not be compile-time constants
 
 const variable: is a compile-time constant if its initializer
 is a constant expression
 
 compile-time const: initializer can be any constant
 expression
 
 Runtime const: whose initialization values aren't know until
 runtime. any const variable that is initialized with a non
 constant expression is a runtime constant
 
 constexpr: keyword, short for "constant expression",
 constexpr variable: can only be a compile-time constant, if
 it is not then the compiler will give error
 
 constexpr: mostly used for optimization purposes, in some
 cases C++ requires compile-time constants and not runtime
 constants
 
 compile-time constants: allow for better optimization
 typically: want to use compile-time constants wherever
 possible
 
 explanation: when a const variable is declared, compiler
 internally tracks whether it's a runtime/compile-time
 constant. it depends whether the initializer is a compile
 time expression or not. if we expect a compile time const
 then we can use constexpr. constexpr will make sure that we
 get a compile-time const and not runtime const.
 
 constexpr: keyword used instead of const keyword in
 variable's declaration.
 
 best practice:------
 
 variable: that is unmodifiable after its initialization and
 if it's initializer is known at compile-time, then it should
 be declared as constexpr
 
 variable: that is unmodifiable after its initialization and
 if it's initializer is unknown at runtime, then it should
 be declared as const and not constexpr.
 
 function parameters: can be const, but can't be constexpr
 
 C++ does support functions that can be evaluated at
 compile-time (and thus can be used in constant
 expressions)
 
 optimization process: called "constant folding"
 
 constexpr variables: ensures that variable that have values
 known at compile time, are eligible for constant folding
 when they are used in expressions(even in non-const
 expressions).
 */

#include <iostream>

int user_input()
{
    std::cout << "Enter the number: ";
    int num{};
    std::cin >> num;
    
    return num;
}

int ten()
{
    return 10;
}

int main()
{
    /// constant expression: 2+2, evaluated at compile time by the compiler
    /// std::cout - is not a constant expression, program can't output
    /// values to the console at compile-time, this expression will evaluate
    /// at runtime
    int a{2 + 2};
    std::cout << a << '\n';
    
    /// compile-time const, initializer is a constant expression
    const int x{2};
    /// compile-time const, initializer is a constant expression
    const int y{31};
    
    /// compile-time expression, compiler will replace x+y with 33
    const int z{x + y};
    std::cout << z << '\n';
    
    /// compile-time const variables: often used as symbolic constants
    const double gravity{9.8};
    
    /// compile time constant
    const int p{2};
    
    /// runtime constant q: it's value is unknown at compile time
    /// return value of user_input( ) is unknown until runtime
    const int q{user_input()};
    
    /// runtime constant r: value unknown at compile time
    /// p + q: runtime expression
    const int r{p + q};
    /// runtime expression below also
    std::cout << r << '\n';
    
    /// error: constexpr variable can only be a compile time constant
    /// initialization value of constexpr variable b is not a constant expression
    /// here, so this is an error
//    constexpr int b{user_input()};
    
    std::cout << "Enter the age: ";
    int age{};
    std::cin >> age;
    
    /// error: age is not a constant expression
//    constexpr my_age{age};
    
    /// error: return value of ten( ) is not a constant expression
//    constexpr int my_age{ten()};
    
    /// 3 + 4: not a constant expression,
    /// 3 + 4: constant subexpression, will still be optimized at compile time
    /// compilers: able to optimize constant subexpressions
    std::cout << 2 + 2 << '\n';
    
    return 0;
}
