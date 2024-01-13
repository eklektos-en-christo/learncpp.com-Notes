//
//  main.cpp
//  12.4_recursion
//
//  Created by Εκλεκτός εν Χριστώ on 6/18/23.
//

/*
 RECURSIVE FUNCTION : A function that calls itself
 
 Stack overflow : if a recursive function calls itself infinitely then at some point the
 stack memory run out of its capacity and stack overflows, the program crashes or terminates
 
 ___________________________________________________________________________________________
 RECURSIVE TERMINATION CONDITIONS: a condition, when met, will cause the recursive function
 to stop calling itself
 
 General recursive termination condition: IF statement
 
 Recursive function calls : get subsequently popped off the stack until all the instances
 of that function have been removed
 
 Commenting: is good to understand the recursive code
 
 Operator--  has side effects, when variable that has a side effect applied more than once
 in a given expression will result in undefined behavior
 
 ___________________________________________________________________________________________
 RECURSIVE ALGORITHMS:
 
 BASE CASE: inputs for which an algorithm trivially produces an output is called a base case
 
 BASE CASE: acts as a termination condition for the algorithm
 
 ___________________________________________________________________________________________
 FIBONACCI NUMBERS: a fibonacci number in a sequence of numbers is that which is the sum of
 two preceding number in the sequence.
 
 Mathematically, fibonacci numbers are defined as:
                
                F(n)    =   0 if n = 0
                            1 if n = 1
                            
                            f(n-1) + f(n-2) if n > 1
 
 ___________________________________________________________________________________________
 MEMOIZATION ALGORITHMS:
 
 Memoization: technique, caches the results of expensive function calls so the result can be
 returned when the same input occurs again
 
 ___________________________________________________________________________________________
 RECURSIVE VS. ITERATIVE:
 
 For non-trivial problems: recursive approach is often much simpler to write and read
 
 Iterative functions: almost always more efficient than their recursive counterparts
 
 In recursion: every time a function is called, there is a some amount of overhead that
 takes place in pushing and popping stack frames
 
 In iteration: amount of overhead can be avoided
 
 Recursion is a good choice when:
 
 - recursive code is much simpler to implement
 
 - the recursion depth can be limited
 
 - the iterative version of the algorithm requires managing a stack of data
 
 - this isn't a performance-critical section of code
 
 BEST PRACTICE:
 Generally favor iteration over recursion, except when recursion really makes sense
 
 ___________________________________________________________________________________________
 */

#include <iostream>
#include <vector>

void infinite_recursion(int x)
{
    std::cout << x << '\n';
    infinite_recursion(x - 1);
}

int sum(int x)
{
    /// if the integer passed is 0 or less than 0, return 0 to the caller
    if (x <= 0)
    {
        std::cout << "Wrong input, pass a value greater than 0!\n";
        return 0;
    }
    
    /// termination condition, normal base case
    if (x == 1)
        return 1;
    
    /// operator-- is not used to decrement x: it has side effects
    return sum(x - 1) + x;
}

void recursive_func(int a)
{
    std::cout << "Push countdown: " << a << '\n';
    
    if (a > 1)
        recursive_func(a - 1);
    
    /// when condition above mets, then this print statement executes in reverse order
    std::cout << "Pop countdown: " << a << '\n';
}

int fibonacci(int x)
{
    /// base case - termination condition
    if (x == 0)
        return 0;
    
    /// base case - termination condition
    if (x == 1)
        return 1;
    
    return fibonacci(x - 1) + fibonacci(x - 2);
}

int fibonacci_memoized(int x)
{
    /// use a static std::vector to cache calculated results
    static std::vector results{ 0, 1 };
    
    /// If we've already seen this x, then use the cache'd result
    if (x < static_cast<int>(std::size(results)))
        return results[x];
    
    results.push_back(fibonacci_memoized(x - 1) + fibonacci_memoized(x - 2));
    
    return results[x];
}

int factorial(int x)
{
    if (x <= 0)
        return 1;
    
    return factorial(x - 1) * x;
}

int individual_digit_sum(int x)
{
    if (x < 10)
        return x;
    
    return individual_digit_sum(x / 10) + x % 10;
}

int dec_to_bin()
{
    std::cout << "Enter a +ve integer: ";
    int x{};
    std::cin >> x;
    
    return x;
}

void print_to_bin(unsigned int x)
{
    if (x == 0)
        return;
    
    print_to_bin(x / 2);
    
    std::cout << x % 2;
}

int main()
{
    /// infinite recursive function call, stack overflow
//    infinite_recursion(10);
    
    recursive_func(10);
    
    int x{ sum(5) };
    
    std::cout << "Sum: " << x << '\n';
    
    /// first 13 fibonacci numbers
    /// this calls fibonacci 1205 times
    for (int count{ 0 }; count < 13; ++count)
        std::cout << fibonacci(count) << ' ';
    std::cout << '\n';
    
    /// first 13 fibonacci numbers - memoized version
    /// this calls fibonacci 35 times
    for (int count{ 0 }; count < 13; ++count)
        std::cout << fibonacci(count) << ' ';
    std::cout << '\n';
    
    std::cout << factorial(7) << '\n';
    
    std::cout << individual_digit_sum(93427) << '\n';
    
    int y{ dec_to_bin() };
    
    print_to_bin(static_cast<unsigned int>(y));
    
    return 0;
}
