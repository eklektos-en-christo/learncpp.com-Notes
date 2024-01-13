//
//  main.cpp
//  6.14_constexpr.and.consteval.functions
//
//  Created by εκλεγμένοι εν Χριστώ on 12/7/22.
//

/*
 constexpr keyword : used to create compile-time(symbolic) constants.
 
 constant expressions : expressions that can be evaluated at compile time rather than
 runtime
 
 constexpr function : whose return value may be computed at compile time
 
 making a function constexpr : simply use the constexpr keyword in front of the return
 type
 
 constexpr functions : can be evaluated at compile-time
 
 eligibility for compile-time evaluation :
 -function must have a constexpr return type
 -function must not call any non-constexpr functions
 -call to the function must have constexpr arguments(e.g. constexpr variables or
 literals)
 
 best practice:
 use a constexpr return type for functions that need to return a compile time constant
 
 constexpr functions are implicitly inline :
 which makes them exempt from the one definition rule (ODR)
 
 constexpr functions : often defined in header files, so they can be included into
 any .cpp file that requires full definition
 
 constexpr functions : can also be evaluated at runtime
 in this case they will return a non-constexpr result
 
 key insight:
 allowing the functions with constexpr return type to be evaluated at either compile
 time or runtime was alloed, so that a single function can serve both cases, otherwise
 two separate functions needed, one with constexpr and another with non constexpr
 return type, the code will be duplicated, also the different for both functions will
 be required
 
 When is a constexpr function evaluated at runtime?
 C++ standard: constexpr function that is eligible for compile time evaluation must
 be evaluated at compile time if the return value is used where a constant expression
 is required, otherwise compiler is free to evaluate the function at either compile
 time or runtime
 
 key insight:
 constexpr function that is eligible to be evaluated at compile time will only be
 evaluated at compile time if the return value is used where the a constant expression
 is required, otherwise, compile time evaluation is not guaranteed
 
 constexpr function : is better thought of as "can be used in a constant expression"
 and not "will be evaluated at compile-time".
 
 How to determine if the constexpr function call is evaluating at compile time or
 runtime?
 Sol:   std::is_constant_evaluated() - defined in <type_traits> header,
        return a bool, indicates whether the current function call is executing in
        a constant context, this can be combined with a conditional statement to
        allow a function to behave differently when evaluated at compile time vs
        runtime
 
 Forcing a constexpr function to be evaluated at compile-time:
 there is not way to tell the compiler that a constexpr function should prefer to
 evaluate at compile time, even in cases where the return value is used in a
 non-constant expression.
 the only way is to ensure that return value is used where a constant expression is
 required, this needs to be done on a per-call basis.
 most common way : is to use the return value to initialize a constexpr variable, this
 requires introducing a new variable to just ensure the compile time evaluation which
 is ugly and reduces readability
 
 Consteval: keyword, used to indicate that a function must evaluate at compile time,
 otherwise compiler error will result
 
 immediate functions : functions which must evaluate at compile time because of
 consteval keyword
 
 consteval functions : implicitly inline
 
 best practice:
 use consteval if the function must run/evaluate at compile time for some reason,
 for example - performance
 
 consteval functions : can't evaluate at runtime
 constexpr functions : can evaluate either at runtime or compile-time
 
 consteval functions : require constant expressions as arguments
 constexpr function  : must be evaluated at compile-time
 */

#include <type_traits>
#include <iostream>

consteval int compile_time(int value)
{
    return value;
}

/// constexpr function
/// this function definition and call to this function is eligible for compile-time evaluation
constexpr int greater(int x, int y)
{
    return (x > y ? x : y);
}

/// Determining if a constexpr function call is evaluating at compile-time or runtime
constexpr int test_constant_evaluated()
{
    if (std::is_constant_evaluated())
        return 1;
    else
        return 0;
}

consteval int greater_consteval(int x, int y)
{
//    if (std::is_constant_evaluated() && (x > y))
//        return x;
//    else
//        return y;
    
    return ((std::is_constant_evaluated() && (x > y)) ? x : y);
}

int main()
{
    constexpr int x{5};
    constexpr int y{40};
    
    /// this will be evaluated at compile time instead of runtime
    /// function call to greater( ) will be replaced by the result of the function call which is 40
    constexpr int g{greater(x, y)};
    
    std::cout << g << " is greater!" << '\n';
    
    /// a and b are not constexpr
    int a{5};
    int b{6};
    
    /// this will be evaluated at runtime, returning the expected value as a non-constexpr int
    /// the function will be resolved at runtime
    std::cout << greater(a, b) << " is greater!" << '\n';
    
    /// arguments to great are constexpr, so it is eligible to be evaluated at compile time
    /// the initializer of constexpr great is also a constant expression
    /// the return value is used in a context that requires a constant expression
    /// thus greater( ) must be evaluated at compile time
    constexpr int great{greater(5,60)};
    std::cout << great << " is greater!" << '\n';
    
    /// p is not constexpr
    int p{50};
    /// this will be evaluated at runtime, because one argument to greater( ) i.e. p is non-constexpr
    std::cout << greater(p, 6) << " is greater!" << '\n';
    
    /// may be evaluated at either compile time or runtime
    /// greater( ) is being called with constexpr arguments, so it is eligible for compile-time evaluation
    /// but the return value of greater( ) is not being used in a context that requires a constant expression
    /// because operator<<
    /// always executes at runtime, so compiler is free to choose whether the call to greater( ) will be evaluated at
    /// compile time or runtime
    std::cout << greater(5, 6) << " is greater!" << '\n';
    
    /// Determining if a constexpr function call is evaluating at compile-time or runtime
    /// test: checking compile time evaluation
    constexpr int test{test_constant_evaluated()};
    int test2{test_constant_evaluated()};
    std::cout << test << '\n';      /// compile-time evaluation
    std::cout << test2 << '\n';     /// runtime evaluation
    
    /// test: checking runtime evaluation
    std::cout << test_constant_evaluated() << '\n';
    
    /// this will evaluate at compile time
    constexpr int consteval_{greater_consteval(22, 20)};
    std::cout << consteval_ << " is greater!" << '\n';
    
    /// this will evaluate at compile time
    std::cout << greater_consteval(100, 10) << " is greater!" << '\n';
    
    /// error: consteval functions must evaluate at compile time
    /// consteval__ is not a constexpr, so error
    int consteval__{100};
//    std::cout << greater_consteval(consteval__, 200) << '\n';
    
    /// may or may not execute at compile-time
    std::cout << greater(10, 5) << " is greater!" << '\n';
    
    /// this will execute at compile time
    /// in compile-time context, the entire call to consteval function will simply
    /// be replaced with the calculated return value
    /// compiletime function call takes the return value of greater function call and simply returns it by value
    std::cout << compile_time(greater(5, 6)) << " is greater!" << '\n';
    
    /// calling the constexpr version at runtime
    int c{5};
    std::cout << greater(c, 6) << " is greater!" << '\n';
    
    return 0;
}
