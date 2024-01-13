//
//  main.cpp
//  7.19_generating.random.numbers.using.mersenne.twister
//
//  Created by εκλεγμένοι εν Χριστώ on 2/4/23.
//

/*
 two types of mersenne twister:
 
 mt19937 : generates 32-bit unsigned integers
 mt19937_64 : generates 64-bit unsigned integers
 
 32 bit PRNG : generate random numbers between 0 and 4,294,967,295
 
 PRNGs : can only generate numbers that use the full range
 
 Random number distribution : converts the output of a PRNG into some other distribution
 of numbers.
 
 random number distributions : use for statistical analysis
 
 extremely useful random number distribution : uniform distribution
 
 uniform distribution : a random number distribution that produces output between two
 numbers X and Y(inclusive) with equal probability.
 
 ------------------------------------------------------------------------------------------
 Seeding with the system clock : problem with this approach is if program is run several
 times in quick succession, the seeds generated for each run won't be that different, that
 will impact the quality of random results from a statistical standpoint, programs that
 require high quality, independent results, this method of seeding may be insufficient
 
 one thing that is different every-time a program is run - current time
 
 if the current time is used as our seed value : then program will produce a different set
 of random numbers each time it is run
 
 c/cpp : long history of prngs being seeded using the current time (std::time() function)
 
 ticks : very small unit of time, usually nanoseconds, could be milliseconds
 
 std::chrono::high_resolution_clock - is popular choice instead of std::chrono::steady_clock
 
 std::chrono::high_resolution_clock - used the most granular unit of time, but may use the
 system clock  for the current time, which can be changed or rolled back by users
 
 std::chrono::steady_clock - may have a less granular time, but is the only clock with a
 guarantee that users can't adjust it.
 
 ------------------------------------------------------------------------------------------
 Seeding with the random device : problem with std::random_device is that it isn't required
 to be non-deterministic, it could, on some systems produce the same sequence every time
 the program is run
 
 std::random_device - a type, implementation defined PRNG.
 std::random_device - asks the OS for a random number
 
 best practice :
 use std::random_device to seed the PRNGs, unless it is not implemented properly for the
 target compiler/architecture
 
 ------------------------------------------------------------------------------------------
 
 std::random_device{}() - std::random_device{} creates a value-initialized temporary object
 of type std::random_device, then () calls operator() on that temporary object which
 returns a randomized value, which we use as an initializer for our mersenne twister
 
 it is equivalent of the calling the below function:
 
 unsigned int get_random_device_value()
 {
    std::random_device rd{};    // creates value initialized std::random_device object
    return rd();                // return the result of operator() to the caller
 }
 
 std::random_device{}() - gives the same result without creating a named function of named
 variable, it's much more concise
 
 std::random_device - is better used to seed other prngs than as a prng itself.
 
 Only seed a PRNG once:
 PRNGs : can be reseeded after the initial seeding
 reseeding : re-initializes the state of the random number generator, causes it to generate
 results starting from the new seed state
 
 reseeding : should generally be avoided unless there is a specific reason to do so, it can
 cause the results to be less random or not random at all
 
 best practice : only seed a PRNG once, do no reseed it
 
 Random numbers across multiple functions:
 one way : create and seed the prng in main and then pass it everywhere we need it, but that
 is lot of passing, we may only use sporadically
 static local : we can create static local std::mt19937 variable in each function that needs
 it, it only gets seeded once, it's overkill to have every function that used random number
 generator define and seed its own local generator
 a better option in most cases : create a global random number generator(inside a namespace)
 
 Mersenne twister and under-seeding issues:
 Mersenne twister's internal state's size : 624 bytes
 seeding with clock/random_device : seed is only 32-bit integer
 this means : a 624 byte object with a 4-byte value, this is under-seeding the M. Twist PRNG
 random library : fill the remaining 620 bytes with "random" data
 under-seeded prng : can generate the results that are suboptimal for applications that need
 the highest quality results
 
 example- seeding std::mt19937 with single 32 bit value will never generate the number 42 as
 its first output
 
 std::seed_seq - seed sequence
 seed : can be either a single value or a set of values
 std::seed_seq - is a type
 std::seed_seq - performs two functions
 -first : it can hold multiple seed values, so PRNG can be seeded with more than one value
 -second : it will generate as many additional unbiased seed values as needed to initialize
 a PRNG's state
 
 std::seed_seq - if initialized with a 32 bit integer, like from std::random_device and then
 initialize a mersenne twister with std::seed_seq object
 std::seed_seq - will generate 620 bytes of additional seed data
 
 std::seed_seq - the more pieces of random data we can give to seed_seq, the better
 
 Why not give std::seed_seq 156 integers(624 bytes) from std::random_device?
 ans: we can, this may be slow, also there is risk of depleting the pool of random numbers
 that random_device uses
 
 std::seed_seq - "random" inputs can be used, like a value from the clock, can also use
 the current thread id, the address of particular functions, the user's id, the process id
 etc,
 
 alternate path : is to use a different prng with a smaller state
 many good prngs : use 64 or 128 bits of state
 
 Warming up a PRNG:
 "warmed up" : technique, where the first N results generated from the PRNG are discarded,
 this allows the internal state of PRNG to be mixed up such that the subsequent results
 should be of higher quality,
 typically - a few hundred to a few thousand initial results are discarded
 the longer the period of the PRNG : the more initial results should be discarded
 
 seed_seq initialization used by std::mt19337 - performs a warm up, so no need to warm up
 std::mt19337 objects.
 
 Programs that use random numbers : can be difficult to debug, when debugging, it's a useful
 technique to seed the prng with a specific value (e.g. 2) that causes the erroneous
 behavior to occur. 
 */

/// random header for randomization - using mersenne twister, random_device
#include <random>
/// chrono : gives access to the clock
#include <chrono>
#include <iostream>

/// used capital R in Random to avoid conflicts with functions named random()
namespace Random
{
    /// Random::mt - is a global variable and can be accessed from any function
    std::mt19937 mt{std::random_device{}()};
    
    /// easy way to get random number between min and max
    int get(int min, int max)
    {
        /// create distribution in any function that needs it
        /// std::uniform_int_distribution is typically cheap to create
        /// it's fine to create whenever needed
        std::uniform_int_distribution die{min, max};
        /// generate a random number from the global generator
        return die(mt);
    }
}

int get_card()
{
    /// this gets created and seeded everytime the function is called
    std::mt19937 mt{std::random_device{}()};
    
    std::uniform_int_distribution card{1, 52};
    
    return card(mt);
}

int main()
{
    /// -----------------------------------------------------------------------------------------------------------------------------------------------------
    /// 32 bit mersenne twister : instantiating
    std::mt19937 mt{};
    
    for (int count {1}; count <= 40; ++count)
    {
        /// mt( ) :
        /// mt is a variable
        /// what mt() means?
        /// for calling the function mt.operator()
        /// mt.operator() : function returns the next random result in the sequence
        ///
        std::cout << mt() << '\t';
        
        /// newline after 5 numbers
        if (count % 5 == 0)
            std::cout << '\n';
    }
    
    /// -----------------------------------------------------------------------------------------------------------------------------------------------------
    /// using a uniform distribution to simulate the roll of a 6 sided dice
    ///
    /// creating a reusable random number generator that generates uniform numbers between 1 and 6
    std::uniform_int_distribution die6{1, 6};
    
    for (int count{1}; count <= 40; ++count)
    {
        /// generating a roll of the die here
        /// calling die6(mt) to generate a value between 1 and 6
        std::cout << die6(mt) << '\t';
        
        /// start a new row after 10 numbers are printed
        if (count % 10 == 0)
            std::cout << '\n';
    }
    
    
    std::cout << '\n';
    
    
    /// -----------------------------------------------------------------------------------------------------------------------------------------------------
    /// seeding the mersenne twister using the current time
    std::mt19937 mt2{static_cast<unsigned int>
        (std::chrono::steady_clock::now().time_since_epoch().count())};
    
    /// creating reusable random number generator that generates uniform random numbers between 1 and 6
    std::uniform_int_distribution die6_2{1, 6};
    
    for (int count{1}; count <= 40; ++count)
    {
        /// generating a roll of die here
        std::cout << die6_2(mt2) << '\t';
        
        /// start new row after 10 numbers have printed
        if (count % 10 == 0)
            std::cout << '\n';
    }
    
    std::cout << '\n';
    
    /// -----------------------------------------------------------------------------------------------------------------------------------------------------
    /// seeding the mersenne twister with one random number generator from a temporary instance of std::random_device
    /// if run the program multiple times : it should produce different results each time
    std::mt19937 mt3{std::random_device{}()};
    
    /// creating reusable random number generator, generates uniform numbers between 1 and 6
    std::uniform_int_distribution die6_3{1, 6};
    
    for (int count{1}; count <= 40; ++count)
    {
        /// generate  a roll of die here
        std::cout << die6_3(mt3) << '\t';
        
        /// new row after 10 numbers
        if (count % 10 == 0)
            std::cout << '\n';
    }
    
    /// this is inefficient and will likely cause poor random results
    std::cout << get_card() << '\n';
    std::cout << get_card() << '\n';
    std::cout << get_card() << '\n';
    
    std::cout << Random::get(1, 6) << '\n';
    std::cout << Random::get(1, 10) << '\n';
    std::cout << Random::get(1, 20) << '\n';
    
    std::cout << '\n';
    
    /// using std::random_device to give std::seed_seq more data to work with
    std::random_device rd;
    /// giving 8 integers of random numbers from std::random_device for our seed
    std::seed_seq ss{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
    /// initializing mersenne twister with seed_seq
    std::mt19937 mt4{ss};
    /// creating reusable random number generator that generates uniform numbers between 1 and 6
    std::uniform_int_distribution die6_4{1, 6};
    
    for (int count{1}; count <= 40; ++count)
    {
        /// generating roll of the die
        std::cout << die6_4(mt4) << '\t';
        
        /// start a new row after 10 numbers
        if (count % 10 == 0)
            std::cout << '\n';
    }
    
    return 0;
}
