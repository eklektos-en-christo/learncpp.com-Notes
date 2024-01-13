//
//  main.cpp
//  7.13_code.coverage
//
//  Created by εκλεγμένοι εν Χριστώ on 1/17/23.
//

/*
 Code coverage : term is used to describe how much of the source code of a program is
 executed while testing.
 
 –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
 Some popular metrics used for code coverage are below:
 
 Statement coverage : percentage of the statements in the code that have been exercised by
 the testing routines, while aiming for 100% statement coverage is good, but it is not
 enough to ensure correctness
 
 –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
 Branch coverage : percentage of the branches that have been executed, each possible branch
 counted separately
 
 Best practice :
 Aim for 100% branch coverage of the code
 
 –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
 Loop coverage(formally)/0,1,2 test(informally) : if there is a loop in the code, then there
 is necessity to ensure it works properly when it iterates 0 time, 1 time and 2 times.
 if it works correctly for the 2nd iteration case, then it should work correctly for all
 iterations greater then 2.
 0,1,2 tests : cover all possibilities, and a loop can't execute a negative no. of times.
 then there would be 4 tests from 0-4
 
 best practice :
 use the 0, 1, 2 test to ensure the loops work correctly with different number of iterations
 
 –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
 Testing different categories of input : category means a set of input that have similar
 characteristics, when writing functions that accept parameters or accept user input,
 consider what happens with different categories of input
 
 example : if there a function written to produce the square root of an integer

 guidelines for category testing :
 For integers : make sure how the function handles -ve, zero and +ve values, also check for
 overflow if that's relevant
 
 For floating point : make sure how the function handles values that have precision issues,
 values that are slightly larger or smaller than expected
 
 For double : good double type values to test with are 0.1 and -0.1, to test numbers that
 are slightly larger than expected and 0.6 and -0.6, to test numbers that are slightly
 smaller than expected
 
 For strings : make sure how the function handles an empty string, normal valid string,
 strings that have whitespaces, strings that are all whitespace
 
 For pointer : don't forget to test the nullptr as well
 
 Best practice:
 test different categories of input values to make sure the unit handles them properly
 –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
 */

#include <iostream>

/// statement coverage :
/// calling this function as foo(2, 1) will give the complete statement coverage for this function
/// because every statement in the function will execute
/// there is a possibility to not to reach all the statements in one function call, so this won't ensure correctness
int foo(int x, int y)
{
    int z{y};
    if (x > y)
        z = x;
    return z;
}

/// branch coverage :
/// in this function, IF statement has two branches, a branch that executes on true and another that executes on false
/// IF statement has two branches, even if there is no corresponding else statement to execute
/// a switch statement can have many branches
/// calling this function as foo2(1,0) gives the 100% statement coverage, but 50% branch coverage
/// we need one more function call to test where the if statement does not execute i.e. when else executes
int foo2(int x, int y)
{
    int z{y};
    if (x > y)
        z = x;
    return z;
}

/// branch coverage :
/// two calls will be needed to give 100% branch coverage
/// 1st call : to test the first cases
/// 2nd call : to test the default case
/// multiple cases that feed into the same body doesn't need to be tested separately, if one works, then all works
bool is_lower_vowel(char c)
{
    switch (c)
    {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
        default:
            return false;
    }
}

/// branch coverage :
/// 3 calls are needed to get 100% branch coverage
/// 1st call : compare(1,0)
/// 2nd call : compare(0,1)
/// 3rd call : compare(0,0)
/// After three calls : we can say that this function reliably tested with 3 calls
void compare(int x, int y)
{
    if (x > y)
        std::cout << x << " is greater than " << y << '\n';
    else if (x < y)
        std::cout << x << " is less than " << y << '\n';
    else
        std::cout << x << " is equal to " << y << '\n';
}

/// loop coverage :
/// 3 times function call needed for 100% loop coverage
/// 1st call : spam(0), to test 0-iteration case
/// 2nd call : spam(1), to test 1-iteration case
/// 3rd call : spam(2), to test 2-iteration case
/// if spam(2) works, then spam(n) should work, where n>2
void spam(int times_to_print)
{
    for (int count{0}; count < times_to_print; ++count)
        std::cout << "SPAM!" << '\n';
}

int main()
{
    
    return 0;
}
