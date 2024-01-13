//
//  main.cpp
//  6.13_inline.functions
//
//  Created by εκλεγμένοι εν Χριστώ on 11/25/22.
//

/*
 in-place/inline code writing : writing the code as part of an existing function
 
 Each function call : there is a significant amount of overhead cost that is incurred
 with each function call
 
 large function with complex tasks : the overhead of the function call is typically
 insignificant compared to the amount of time it takes to run
 
 small function with simple tasks : the overhead cost can be larger than the time
 needed to actually execute the function's code
 
 cases where a small function is called often : using a function can result in a
 significant performance penalty over writing the same code in-place
 
 Inline expansion: compiler's trick that it can use to avoid overhead cost
 
 Inline expansion: procss where a function call is replaced by the code from the called
 function's definition.
 
 Inline expansion: allows to avoid the overhead of the calls, also preserves the results
 of the code
 
 example:
 consider this code below-
 ----------------------------------
 #include <iostream>
 
 int min(int x, int y)
 {
    return (x < y) ? x : y;
 }
 int main()
 {
    std::cout << min(2, 3) << '\n';
    std::cout << min(40, 30) << '\n';
 }
 ----------------------------------
 the inline expansion would look like this as the below code
 ----------------------------------
 #include <iostream>
 
 int main()
 {
    std::cout << ((2 < 3) ? 2 : 3) << '\n';
    std::cout << (40 < 30) ? 40 : 30 << '\n';
 }
 
 explanation: the two calls to min() have been replaced by the code in the body of min()
 function, value of the arguments substituted for the parameters, this will avoid the
 overhead of those calls, and will preserve the result of the code.
 ----------------------------------
 
 Performance of inline code:
 inline expansion allow the compiler to optimize the resulting code more efficiently,
 example-
 ((5 < 6) ? 5 : 6)  - this is now a compile time constant
 the compiler could further optimize the first statement in main() to std::cout<<5<<'\n';
 
 if the body of the function being expanded takes more instructions than the function
 call being replaced, then each inline expansion will cause the executable to grow larger
 
 larger executable: tend to be slower - due to not fitting as well in caches
 
 Inline expansion could result in :
 performance improvements
 preformance reductions or
 no change to performance at all
 
 inline expansion best suited to:
 simple, short functions, no more than few statements, cases where a single function call
 is executed more than once, example - like the function calls inside a loop
 
 When the inline expansion occurs?
 three categories where calls to the function:
 must be expanded
 may be expanded(dominant category)
 can't be expanded
 
 Inline function: that is eligible to have its function calls expanded
 
 Tip
 Modern optimizing compilers make the decision about when functions should be expanded
 inline.
 
 implicitly treated inline functions:
 functions defined a class, struct or union type definition
 constexpr/consteval functions
 
 inline keyword, historically: intended to be used as a hint to the compiler that a
 function would benefit from being expanded inline
 
 using inline to request inline expansion is a form of premature optimization and misuse
 could actually harm the performace
 
 the inline keyword is just a hint, the compiler is free to ignore it
 
 inline expansion is actually determined per function call, it may be beneficial to
 expand some function calls and detrimental to expand others, and there is not syntax
 to affect this
 
 BEST PRACTICE:
 don't use inline keyword to request inline expansion for your functions
 
 inline keyword, modernly: the inline concept has evolved to have a new meaning -
 multiple definitions are allowed in the program
 
 inline functions: typically defined in header files, where they can be included into any
 code file that needs to see the full defintion of the function
 
 Key insight
 The compiler needs to be able to see the full definition of an inline function wherever it is called.
 
 Best practice
 Avoid the use of the inline keyword for functions unless you have a specific, compelling reason to do so.
 */

#include <iostream>

int minimum(int x, int y)
{
    return (x < y) ? x : y;
}

/// hit to the compiler that it should do inline expansion of this function
inline int min(int x, int y)
{
    return (x < y) ? x : y;
}

int main()
{
    std::cout << minimum(2, 3) << '\n';
    std::cout << minimum(20, 3) << '\n';
    
    return 0;
}
