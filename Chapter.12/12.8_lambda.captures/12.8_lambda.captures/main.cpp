//
//  main.cpp
//  12.8_lambda.captures
//
//  Created by Εκλεκτός εν Χριστώ on 6/27/23.
//

/*
 ___________________________________________________________________________________________
 In nested blocks: any identifier defined in an outer block is accessible in the scope of
 the nested block
 
 LAMBDAS: can only access specific kinds of identifiers-
 -global identifiers
 -entities that are known at compile-time
 -entities with static storage duration
 
 ___________________________________________________________________________________________
 CAPTURE CLAUSE:
 
 used to indirectly give a lambda access to the variables available in the surrounding scope
 that it normally would not have access to
 
 To access the variables from the surrounding scope in the lambda: list the entities inside
 the capture clause
 
 ___________________________________________________________________________________________
 HOW DO LAMBDAS ACTUALLY WORK?
 
 When a lambda definition is executed:
 -for each variable that the lambda captures, a clone of that variable is made with an
  identical name inside the lambda
 -these cloned variables are initialized from the outer scope variables of the same name at
  this point
 -cloned variables may have the same name, they don't necessarily have the same type as the
  original variable
 
 KEY INSIGHT:
 captured variables inside the lambda are clones of the outer scope variables, they are not
 the actual variables
 
 ___________________________________________________________________________________________
 FUNCTORS: lambdas aren't functions, they are objects that can be called like functions
 
 When the compiler encounter a lambda definition:
 -it creates a custom object definition for the lambda
 -each captured variable becomes a data member of the object
 
 At runtime:
 -when the lambda definition is encountered, the lambda object is instantiated,
 -the members of the lambda are initialized at that point
 
 ___________________________________________________________________________________________
 LAMBDA CAPTURES DEFAULT TO CONST VALUE:
 
 By default:
 -variables are captured by const value
 -this means the lambda captures a constant copy of the outer scope variable
 -this means the lambda is not allowed to modify the constant copy
 
 ___________________________________________________________________________________________
 MUTABLE CAPTURE BY VALUE:
 
 To allow the modifications of variables that were captured by value:
 -we can mark the lambda as mutable
 -mutable(keyword), removes the const qualification from all variables captured by value
 
 WARNING:
 -captured variables are members of the lambda object
 -their values are persisted across multiple calls to the lambda
 
 ___________________________________________________________________________________________
 CAPTURE BY REFERENCE:
 
 Functions: can change the value of arguments passed by reference
 
 Variables captured by reference in lambda: allow the lambda to affect the actual values
 
 To capture a variable by reference:
 -prepend an & to the variable name in the capture
 -variable captured by reference is non-const, unless the variable itself is const
 
 Capture by reference: should be preferred over capture by value whenever you'd normally
 prefer passing an argument to a function by reference, e.g. for non-fundamental types
 
 ___________________________________________________________________________________________
 CAPTURING MULTIPLE VARIABLES:
 
 To capture multiple variable: separate them with comma, this can include a mix of captured
 by value or capture by reference
 
 ___________________________________________________________________________________________
 DEFAULT CAPTURES:
 
 To auto-generate a list of variables we need to capture: use default capture
 
 Default capture/capture default: captures all the variables that are used inside the lambda
 definition
 
 If variables are not mentioned/used inside the lambda definition: they won't be captured
 when default capture is used
 
 To capture all used/mentioned variables by value: use a capture value of =
 To capture all used/mentioned variables by reference: use a capture value of &
 
 DEFAULT CAPTURES: can be mixed with normal captures
 
 We can: capture some by reference and others by value, but each variable can only be
 captured once
 
 capture default (=) or (&): must be the first element in the capture clause and then the
 other variables
 
 ___________________________________________________________________________________________
 DEFINING NEW VARIABLE IN THE LAMBDA CAPTURE:
 
 To capture a variable with slight modification or define a new variable that is only
 visible in the scope of lambda:
 
 -define the variable in the lambda capture without specifying its type
 
 BEST PRACTICE:
 only initialize the variables in the capture if their value is short and their type is
 obvious
 
 ___________________________________________________________________________________________
 DANGLING CAPTURED VARIABLES:
 
 A variable captured by reference: when dies before the lambda, the lambda will be left
 holding a dangling reference
 
 A variable captured by value: when dies before the lambda, the lambda will be left
 holding a dangling reference
 
 WARNING:
 THE CAPTURED VARIABLES MUST OUTLIVE THE LAMBDA
 
 If we want the captured variable to be valid: capture it by value instead, either explicit
 way or using default capture by value
 
 ___________________________________________________________________________________________
 UNINTENDED COPIES OF MUTABLE LAMBDAS:
 
 Lambdas are objects: which means they can be copied
 
 If we need to pass a mutable lambda and want to avoid the possibility of accidental copies
 of lambda object being made, there are two options:
 
 -use a non-capturing lambda instead, we could remove the capture and track our state using
  a local static variable
 
 -prevent copies of our lambda object being made in the first place, <functional> header
  contains a type called std::reference_wrapper
  reference_wrapper: allows us to pass a normal type as if it was a reference
  reference_wrapper: contains a ref() function, can be used to create a reference_wrapper
  reference_wrapper: by wrapping the lambda in reference_wrapper, we can avoid making the
  copies of our lambda, it will make a copy of the reference instead of making a copy of the
  object, so a reference will be copied and not the actual object
 
 RULE:
 std lib functions may copy the lambda objects, to provide lambdas with mutable captured
 variables, pass them by reference using std::ref
 
 BEST PRACTICE:
 avoid mutable lambdas, non-mutable lambdas are easier to understand and don't suffer the
 issues like avoiding the copying of lambda objects
 
 ___________________________________________________________________________________________
 */

#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>
#include <string>
#include <vector>
#include <functional>

struct Car
{
    std::string make{};
    std::string model{};
};

auto make_walrus(const std::string& name)
{
    return [&](){ std::cout << "I'm walrus, my name is " << name << '\n'; };
}

/// std::function - internally makes a copy of the lambda object passed
void my_invoke(const std::function<void()>& func)
{
    /// func is actually being executed on the copy of the lambda object, not the actual lambda
    func();
}

int main()
{
    std::array<std::string_view, 4> A{ "apple", "banana", "walnut", "lemon" };
    
    std::cout << "Enter the string to search for: ";
    
    std::string search{};
    std::cin >> search;
    
    /// search identifier in the capture clause [ ]
    /// lambda now has the access to search variable
    /// Note: search variable inside the lambda is not the main's search variable
    /// it is a clone of main's search variable with a same name
    /// the value of main's search is used to initialize the cloned variable inside the lambda
    auto found
    {
        std::find_if(A.begin(), A.end(),
                     [search](std::string_view str)
                     { return (str.find(search) != std::string_view::npos); })
    };
    
    if (found == A.end())
        std::cout << "Not found!\n";
    else
        std::cout << "Found " << *found << '\n';
    
    
    int ammo{ 10 };
    
    /// lambda captures ammo variable as a const copy
    /// modification is not allowed to a const copy
    /// lambda is non-mutable
    ///
    /// this means, by default, the variables are captured by const value
    auto shoot
    {
        [ammo]()
        {
//            --ammo;
            std::cout << ammo << " shot(s) left!\n";
        }
    };
    
    shoot();
    
    /// mutable keyword: removes all the const qualifications from all variables captured by value
    /// ammo: is modifiable now
    /// logical error: ammo is a copy of the original ammo variable
    /// any modification to ammo: will not affect the original variable ammo
    auto shoot_again
    {
        [ammo]() mutable
        {
            --ammo;
            std::cout << ammo << " shot(s) left!\n";
        }
    };
    
    shoot_again();
    shoot_again();
    
    /// original variable still is unaffected by all the calls to lambda
    std::cout << ammo << " shot(s) left!\n";
    
    /// capturing ammo by reference
    /// any changes to the ammo will affect the original ammo in the main()
    /// no need of mutable keyword now
    auto shoot_working
    {
        [&ammo]()
        {
            --ammo;
            std::cout << ammo << " shot(s) left!\n";
        }
    };
    
    /// call to lambda object modifies the ammo variable
    shoot_working();
    
    
    std::array<Car, 3> cars
    {
        {
            { "Volkswagen", "Golf" },
            { "Toyota", "Corolla" },
            { "Honda", "Civic" }
        }
    };
    
    int comparisons{ 0 };
    
    /// capturing the comparisons variable by reference to modify it through the lambda
    /// sorting the cars by their make
    std::sort(cars.begin(), cars.end(),
              [&comparisons](const auto& a, const auto& b)
              { ++comparisons; return (a.make < b.make); });
    
    std::cout << "Comparisons made: " << comparisons << '\n';
    
    for (const auto& car : cars)
        std::cout << car.make << ' ' << car.model << '\n';
    std::cout << '\n';
    
    /// capturing multiple variables
    /// each variable is separated by a comma
    /// some are captured by value and some are captured by reference - MIX capture
    auto multiple_captures
    {
        /// search, ammo - capture by value
        /// comparisons - capture by reference
        [search, ammo, &comparisons](){}
    };
    
    
    std::array areas{ 100, 10, 201, 41, 38 };
    
    int width{};
    int height{};
    
    std::cout << "Enter width and height: ";
    std::cin >> width >> height;
    
    /// default capture - will capture the width and height variable by value
    /// width and height - both are mentioned/used inside the lambda definition
    /// all mentioned variables: will be captured by value
    auto area_found
    {
        std::find_if(areas.begin(), areas.end(),
                     [=](int known_area)
                     { return (width * height == known_area); })
    };
    
    if (area_found == areas.end())
        std::cout << "Don't know this area!\n";
    else
        std::cout << "Area found\n";
    
    int increment1{ 0 };
    int increment2{ 0 };
    int increment3{ 0 };
    
    /// default capture - capturing all the variables by reference
    /// all three increments are mentioned inside lambda, so they all can be captured by reference
    /// reference will affect the original variables
    auto default_capture_ref
    {
        [&]()
        {
            ++increment1;
            ++increment2;
            ++increment3;
            
            std::cout << increment1 + increment1 + increment1 << '\n';
        }
    };
    
    default_capture_ref();
    
    /// capturing by reference affected the original variables
    std::cout << increment1 << ' ' << increment2 << ' ' << increment3 << '\n';
    
    /// mixing the default capture with normal capture
    /// increment1, increment2: are captured by value(not modifiable)
    /// increment3 : captured by reference(modifiable)
    /// each variable can only be captured once
    auto mix_capture
    {
        [increment1, increment2, &increment3]()
        {
            std::cout << "By value: " << increment1 + increment1 << '\n';
            std::cout << "By reference: " << ++increment3 << '\n';
        }
    };
    
    mix_capture();
    
    /// increment3 modified by the lambda
    std::cout << increment1 << ' ' << increment2 << ' ' << increment3 << '\n';
    
    
    int health{ 33 };
    int armor{ 100 };
    
    std::vector<int> enemies{};
    
    /// health, armor : capture by value
    /// enemies : capture by reference
    [health, armor, &enemies](){};
    
    /// enemies : capture by reference
    /// others : by value
    [=, &enemies](){};
    
    /// armor : by value
    /// rest of them : reference
    [&, armor](){};
    
    /// all : capture by reference
    /// error : first & already says that capture all by reference
//    [&, &armor](){};
    
    /// capture all by value
    /// error : first = already says that capture all by value
//    [=, armor](){};
    
    /// error : armor is captured twice
//    [armor, health, &armor](){};
    
    /// error : capture default must be the first element in the capture group
//    [armor, &](){};
    
    
    /// user_area : defined inside the capture clause without any type specification
    /// user_area : will only be calculated once
    /// if lambda is mutable: the original value of variables will be overridden
    auto area_found_again
    {
        std::find_if(areas.begin(), areas.end(),
                     [user_area { width * height }](int known_area)
                     { return user_area == known_area;})
    };
    
    if (area_found_again == areas.end())
        std::cout << "Dont know this area!\n";
    else
        std::cout << "Area found\n";
    
    /// "LEON" is temporary string
    /// lambda captures the "LEON" by reference
    /// "LEON" dies when make_walrus returns
    /// but lambda still references the string "LEON"
    auto say_name{ make_walrus("LEON") };
    
    /// this is accessing the dangling reference to "LEON"
    /// undefined behavior
    say_name();
    
    
    int i{ 0 };
    
    /// lambda increments the variable i
    auto count
    {
        [i]() mutable
        {
            std::cout << "Current state copied: " << ++i << '\n';
        }
    };
    
    /// count's current state: i is 1 this time
    count();
    
    /// lamba object copied
    /// another copy of count is made
    /// when copy was made, the count current state was: i = 1
    /// current state of count is copied to another_count
    /// another_count also has 1 now
    /// another_count's i is different from the count's i
    auto another_count{ count };
    
    count();
    another_count();
    
    int j{ 0 };
    
    auto count_invoke
    {
        [j]() mutable
        {
            std::cout << "Local copy: " << ++j << '\n';
        }
    };
    
    /// local copy of i is incremented and printed every time
    my_invoke(count_invoke);
    my_invoke(count_invoke);
    my_invoke(count_invoke);
    
    int k{ 0 };
    
    auto count_invoke_ref
    {
        [k]() mutable
        {
            std::cout << "std::ref : " << ++k << '\n';
        }
    };
    
    /// std::ref - ensures that count_invoke_ref is treated like a reference
    /// the reference is copied if anything tries to copy the lambda object
    /// this ensures that only one count_invoke_ref exists
    my_invoke(std::ref(count_invoke_ref));
    my_invoke(std::ref(count_invoke_ref));
    my_invoke(std::ref(count_invoke_ref));
    my_invoke(std::ref(count_invoke_ref));
    my_invoke(std::ref(count_invoke_ref));
    
    return 0;
}
