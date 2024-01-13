//
//  main.cpp
//  7.20_summary.and.quiz
//
//  Created by εκλεγμένοι εν Χριστώ on 2/7/23.
//

/*
 straight line program : takes the same path every time it is run
 
 branch : when control flow statement causes program to begin executing some non-sequential
 instruction sequence

 conditional statement : specifies whether some associated statement should be executed or
 not
 
 null statement : that consists of just a semicolon
 
 fallthrough : when execution flows from a statement underneath a label into statements
 underneath a subsequent label
 
 loop variable/counter : integer variable used to count how many times a loop has executed
 
 iteration : each execution of a loop
 
 off by one error : when the loop iterates one too many or one too few times
 
 halts : terminate the program
 
 std::exit() : automatically called at the end of main()
 
 std::exit() : does not cleanup any local variables or unwind the call stack
 
 std::abort() : can be called for an abnormal termination
 
 scope creep : when a project's capabilities grow beyond what was originally intended at the
 start of the project or project phase
 
 software verification : process of testing whether or not the software works as expected in
 all cases
 
 unit test : test designed to test small portion of the code(typically function or call) in
 isolation to ensure a particular behavior occurs as expected
 
 unit test frameworks : help organize unit tests
 
 integration testing : tests the integration of bunch of units together to ensure they
 work properly
 
 code coverage : how much of the source code is executed while testing
 
 statement coverage : percentage of statements in program that have been exercised by
 testing routines
 
 branch coverage : percentage of branches that have been executed by testing routines
 
 loop coverage/0, 1, 2 test : if you have a loop, you should ensure it works properly when
 it iterates 0 times, 1 times and 2 times
 
 happy path : path of execution that occurs where there are no errors encountered
 
 sad path : where an error or failure state occurs
 
 non-recoverable/fatal error : severe enough that program can't continue running
 
 robust program : that handle error cases well
 
 buffer : temporary storage area for data while the it is moved from one place to another
 
 input validation : process of checking whether user input conforms to what the program is
 expecting
 
 std::cerr - output stream, designed to use for error messages
 
 precondition : condition that must always be true prior to the execution of some segment of
 code
 
 invariant : condition that must be true while some component is executing
 
 postcondition : any condition that must always be true after the execution of some code
 
 assertion : an expression, will be true unless there is a bug in the program
 
 runtime assertions : typically implemented using the assert preprocessor macro
 
 assertions : turned off in non-debug code
 
 static_assert : assertion, that evaluates at compile-time
 
 Assertions : should be used to document cases that should be logically impossible.
 
 Error handling : should be used to handle cases that are possible.
 
 algorithm : finite sequence of instructions that can be followed to solve some problem or
 produce some useful result
 
 stateful algorithm : if it retains some information across(one call to another) calls
 
 stateless algorithm : does not store any information, must be given all the information it
 needs to work with when it is called
 
 state : refers to the current values held in stateful variables
 
 deterministic algorithm : if for a given input(start value) it will always produce the same
 output sequence
 
 PRNG : algorithm that generates a sequence of numbers whose properties simulate a sequence
 of random numbers
 
 seed/random seed : an initial value of set of values used to instantiate the PRNG, this
 initializes the state of the PRNG
 
 seeded prng : when prng has been initialized
 
 size of seed : can be smaller than the size of the state of the prng
 
 under-seeded prng : when size of seed is smaller than the size of the state
 
 period : length of the sequence before a prng begins to repeat itself
 
 random number distribution : converts the output of prng into some other distribution of
 numbers
 
 uniform distribution : random number distribution, produces outputs between two numbers x
 and y(inclusive) with equal probability
 ––––––––––––––––––––––––
 
 prime number : natural number, greater than 1, evenly divisible only by 1 and itself
 evenly divisible : no remainder
 
 
 */

#include <iostream>
#include <cassert>
#include <cmath>
#include <random>
#include "constants.h"

double calculate_height(double init_height, int seconds)
{
    double distance_fallen{my_constants::gravity * seconds * seconds / 2};
    double height_now{init_height - distance_fallen};
    
    if (height_now < 0.0)
        return 0.0;
    else
        return height_now;
}

bool calculate_print_height(double init_height, int time)
{
    double current_height{calculate_height(init_height, time)};
    
    std::cout << "At " << time << " seconds, the ball is at height: ";
    std::cout << current_height << '\n';
    
    return (current_height == 0.0);
}

bool is_prime(int x)
{
    /// if x is negative, 0 or 1, then number is not prime
    if (x <= 1)
        return false;
    
    /// if x is 2 or higher, we need to see if we can find a divisor
    /// we only need to test the numbers between 2 and sqrt(x)
    /// non-prime number must have at least one divisor less than or equal to its square root
    ///
    /// computing the maximum numbers to test
    int max_test{static_cast<int>(std::sqrt(x))};
    
    for (int test{2}; test <= max_test; ++test)
    {
        /// if x is divisible evenly, then it's not prime
        if (x % test == 0)
            return false;
    }
    
    /// x must be prime, if there are no divisors
    return true;
}

bool play_game(int guesses, int number)
{
    for (int count{1}; count <= guesses; ++count)
    {
        std::cout << "Guess #" << count << ": ";
        
        int guess{};
        std::cin >> guess;
        
        if (guess > number)
            std::cout << "Guess is too high.\n";
        else if (guess < number)
            std::cout << "Guess is too low.\n";
        else
            return true;
    }
    
    return false;
}

bool play_again()
{
    while (true)
    {
        char ch{};
        std::cout << "Play again? (y/n): ";
        std::cin >> ch;
        
        switch (ch)
        {
            case 'y': return true;
            case 'n' : return false;
        }
    }
}

int main()
{
    std::cout << "Enter the initial height of the towers in meters: ";
    double init_height{};
    std::cin >> init_height;

    int seconds{0};
    
    while (!calculate_print_height(init_height, seconds))
        ++seconds;
    
    assert(!is_prime(0));
    assert(!is_prime(1));
    assert(is_prime(2));
    assert(is_prime(3));
    assert(!is_prime(4));
    assert(is_prime(5));
    assert(is_prime(7));
    assert(!is_prime(9));
    assert(is_prime(11));
    assert(is_prime(13));
    assert(!is_prime(15));
    assert(!is_prime(16));
    assert(is_prime(17));
    assert(is_prime(19));
    assert(is_prime(97));
    assert(!is_prime(99));
    assert(is_prime(13417));
    
    std::cout << "Success!\n";
    
    std::random_device rd;
    std::seed_seq seq{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
    std::mt19937 mt{seq};
    std::uniform_int_distribution die{1, 100};
    
    constexpr int guesses{7};
    
    do
    {
        int number{die(mt)};
        
        std::cout << "Let's play a game. I'm thinking of a number between 1 and 100. You have ";
        std::cout << guesses << " tries to guess what it is.\n";
        
        bool won{play_game(guesses, number)};
        
        if (won)
            std::cout << "Correct, you win!\n";
        else
            std::cout << "Sorry, you lose, The correct number was " << number << '\n';
    } while (play_again());
    
    std::cout << "Thank you for playing.\n";
    
    return 0;
}
