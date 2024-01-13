//
//  main.cpp
//  7.6_goto.statements
//
//  Created by εκλεγμένοι εν Χριστώ on 12/17/22.
//

/*
 Unconditional jump : causes execution to jump to another spot in the code
 
 "unconditional" : means the jump always happens, in if/switch statement, the jump
 happens only conditionally based on an expression's result
 
 C++ unconditional jumps : implemented via a goto statement and spot to jump to is
 identified using a statement label
 
 statement labels : have function scope
 
 function scope : label is visible throughout the function, even before it's point of
 declaration
 
 goto statement and corresponding statement label : must appear in same function
 
 goto statement : cannot only jump backwards but can jump forward also
 
 statement labels : must be associated with a statement, empty ; can be used, null
 statement can be used to associate the statement label with a statement
 
 statement labels : label a statement
 
 limitations to jumping :
 -you can jump only within the bounds of single function
 -you can't jump forward over the initialization of any variable that is still in
 scope at the location being jumped to
 
 Note : can jump backwards over a variable initialization, the variable will be
 re-initialized when the initialization is executed
 
 Avoid using goto :
 Spaghetti code : that has a path of execution that resembles a bowl of spaghetti,
 tangled and twisted, makes extremely difficult to follow the logic of such code
 
 best use of goto : when you need to exit a nested loop but not the entire function,
 in such case, a goto to just beyond the loops is the cleanest solution
 
 best practice : avoid goto statements, unless the alternatives significantly gives
 worse code readability
 */

#include <iostream>
#include <cmath>        /// for square root function

void print_dogs(bool skip)
{
    if (skip)
        goto end;   /// jumps forward, statement label 'end' is also visible here because of function scope
    
    std::cout << "DOGS\n";
end:                /// end is not declared yet, still the jump will work, because it has function scope
    ;               /// statement label must be associated with a statement, so null statement used here
    ///there is no statement at the end of the function, so null statement used
}

/// IF statement is better than goto
int back_and_forth()
{
    goto skip;
//    int x{3};   /// error : x remains uninitialized when skip: label executes
    
skip:
    return 3;
}

int main()
{
    double x{};
/// statement label
/// this is the spot to jump to, try_again: is used to identify the spot
try_again:
    std::cout << "Enter a non-negative integer: ";
    std::cin >> x;
    
    if (x < 0.0)
        /// this goto will jump back to try_again label if the IF condition is true
        goto try_again;
    
    std::cout << "SQRT. of " << x << " is: " << std::sqrt(x) << '\n';
    
    print_dogs(true);       /// jumps over the print statement, doesn't print anything
    print_dogs(false);      /// prints "DOGS"
    
    /// error : uninitialized x, return 3 would work
    std::cout << back_and_forth() << '\n';
    
    return 0;
}
