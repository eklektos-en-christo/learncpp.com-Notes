//
//  main.cpp
//  12.7_intro.to.lambdas_anonymous.functions
//
//  Created by Εκλεκτός εν Χριστώ on 6/23/23.
//

/*
 ___________________________________________________________________________________________
 LAMBDAS: anonymous functions
 
 LAMBDA EXPRESSION/LAMBDA/CLOSURE:  allows us to define an anonymous function inside another
                                    function
                                    The nesting is important:
                                    allows us both to avoid namespace naming pollution and
                                    to define the function as close to where it is used as
                                    as possible
                                    This means lambda function can be nested inside another
                                    function
 
 ___________________________________________________________________________________________
 SYNTAX FOR LAMBDAS: lambdas have no name, no need to provide one
 
                    [capture_clause] (parameters_list) -> return_type
                    {
                        statements;
                    }
 
 capture_clause : can be empty if not captures are needed
 parameters_list: can be empty if no parameters are required, can also be omitted entirely
                  if no return type is specified
 return_type    : optional, if omitted, auto return type will be assumed(type deduction)
                  in context of lambdas, type deduction is fine because of the triviality
 
 Lambda: requires () before the return type
 
 BEST PRACTICE: use a lambda expression when they are to be defined in a smallest scope and
                used only once, prefer them over normal functions when there is a need of
                a trivial, one-off function to pass as an argument to some other function
 
 FUNCTION LITERAL: when lambda is defined right where it is needed
 
 ___________________________________________________________________________________________
 TYPE OF A LAMBDA:
 
 Writing a lambda in the same line as it's used: sometimes make code harder to read
 
 We can: initialize a variable with a literal value or a function pointer for later use
 
 We can also: initialize a lambda variable with a lambda definition and then use it later
 
 Named lambda along with a good function name: make code easier to read
 
 // Bad: We have to read the lambda to understand what's happening.
 return std::all_of(array.begin(), array.end(), [](int i){ return ((i % 2) == 0); });
 
 // Good: store the lambda is a named variable and pass it to the function
 // return whether all of the elements in the array are even
 return std::all_of(array.begin(), array.end(), is_even);
 
 KEY INSIGHT:
 -storing the lambda in a variable: give it a useful name, makes the code more readable
 -also provides a way to use that lambda more than once
 
 Type of a lambda: they don't have a type that we can explicitly use
 
 compiler - generate a unique type just for the lambda that is not exposed to us
 
 LAMBDAS: aren't functions
 LAMBDAS: special kinds of objects called functors
 
 Functors: objects that contain an overloaded operator(), this makes them callable like a
           function.
 
 SEVERAL WAYS OF STORING A LAMBDA FOR USE POST-DEFINITION, when we don't know its type:
 
 - if the lambda has an empty capture clause: we can use a regular function pointer
 
 - if the lambda has non-empty capture clause: we can use std::function or type deduction
                                               via the auto keyword
 
 ONLY WAY OF USING THE LAMBDA'S ACTUAL TYPE IS: by means of auto keyword, auto has benefit
 of having no overhead compared to std::function
 
 Prior to C++20: we can't always use auto
 
 Cases where the actual lambda is unknown: e.g. when passing a lambda to a function as a
 parameter and the caller determines what lambda will be passed in, we can't use auto
 without compromises, in such cases std::function can be used instead.
 
 std::function works with regular functions and lambdas
 
 Functions with auto parameters: can't be separated into a header (declaration) and source
 file (definition)
 
 BEST PRACTICE:
 
 When storing a lambda in a variable: use auto as the variable's type
 
 when passing a lambda to a function:
 
 - if C++20 capable, use auto as the parameter's type
 - otherwise use std::function
 
 ___________________________________________________________________________________________
 GENERIC LAMBDAS: lambdas with one or more auto parameter, potentially work with wide
 variety of types
 
 lambda parameters: work by the same rules as regular function parameters for the most part
 
 Since C++14: we are allowed to use auto for parameters
 
 C++20: regular functions are able to use auto for parameters too
 
 When a lambda has one or more auto parameters: compiler infers parameter types from the
 calls to the lambda
 
 auto: when used in the context of lambda, it is a shorthand for a template parameter
 
 ___________________________________________________________________________________________
 GENERIC LAMBDAS AND STATIC VARIABLES:
 
 auto: a unique will be generated for each different type the auto resolves to
 
 ___________________________________________________________________________________________
 RETURN TYPE DEDUCTION AND TRAILING RETURN TYPES:
 
 If return type deduction is used: lambda's return type is deduced from the return
 statements inside the lambda body
 
 All return statements in the lambda: must return the same type, otherwise compiler wont'
 understand which one to prefer
 
 In case where we're returning different return type in a lambda: we have two options:
 -do explicit cast to make all return types match
 -explicit specify a return type for the lambda and let compiler do the conversions-(better)
 
 ___________________________________________________________________________________________
 STANDARD LIBRARY FUNCTION OBJECTS:
 
 For common operations: addition, negation or comparison: no need to write own lambdas
 
 std library: contains many basic callable objects that can be used instead
 
 <functional> : contains basic callable objects
 
 ___________________________________________________________________________________________
 CONCLUSION:
 
 Upgrading code that uses library functions is easier than upgrading the code that uses
 loops
 
 Prefer regular functions for non-trivial and reusable cases
 
 ___________________________________________________________________________________________
 */

#include <iostream>
#include <algorithm>
#include <array>
#include <string_view>
#include <functional>
#include <string>

/// passing a lambda to a function as a parameter
/// the caller determines what lambda will be passed in
/// we can't use auto, std::function can be used instead
///
/// if we had used auto for the type of fn
/// the caller wouldn't know what parameters and return type fn needs to have
void repeat(int repetitions, const std::function<void(int)>& fn)
{
    for (int i{ 0 }; i < repetitions; ++i)
    {
        fn(i);
    }
}

bool greater(int a, int b)
{
    return (a > b);
}

struct Student
{
    std::string name{};
    int points{};
};

struct Season
{
  std::string_view name{};
  double averageTemperature{};
};

int main()
{
    /// a trivial lambda definition looks like this
    /// lambda : with omitted return type, omitted parameters and no captures
    [] {};
    
    constexpr std::array<std::string_view, 4> A{ "apple", "mango", "banana", "lemon" };
    
    /// defining a lambda where it would be used
    /// lambda has  no capture clause, not required here
    /// no return type specified, type deduction will be used, operator!= returns a bool
    /// the lambda is defined right where it is needed, this use if also called a function literal
    const auto found{ std::find_if(A.begin(), A.end(), [] (std::string_view str) { return (str.find("ana") != std::string_view::npos); })};
    
    if (found == A.end())
        std::cout << "No \"ana\"\n";
    else
        std::cout << "Found " << *found << '\n';
    
    /// we can store the lambda in a named variable and pass it to the function, readability improved
    auto is_even
    {
        [](int i)
        {
            return ((i % 2) == 0);
        }
    };
    
    /// this is a regular function pointer storing the lambda for use post the lambda definition
    /// this only works with empty capture clause [ ]
    double (*add_numbers)(double, double)
    {
        [](double a, double b)
        {
            return (a + b);
        }
    };
    
    std::cout << add_numbers(2.2, 1.9) << '\n';
    
    /// using std::function to store the lambda for use post the lambda definition
    /// lambda could have a non-empty capture clause
    std::function add_numbers_2
    {
        [](double a, double b)
        {
            return (a + b);
        }
    };
    
    std::cout << add_numbers_2(2.2, 1.9) << '\n';
    
    /// storing lambda for use post definition using auto keyword
    /// this will store the lambda with its real type
    auto add_numbers_3
    {
        [](double a, double b)
        {
            return (a + b);
        }
    };
    
    std::cout << add_numbers_3(2.2, 1.9) << '\n';
    
    repeat(3, [](int i)
     {
         std::cout << i + 1 << '\n';
     });
    
    
    constexpr std::array months
    {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };
    
    /// search for two consecutive months that start with the same letter
    ///
    /// we use auto parameters to capture our strings by const reference
    /// all string types allow access to their individual characters via operator[ ]
    const auto same_letter
    {
        std::adjacent_find(months.begin(), months.end(),
                           [](const auto& a, const auto& b){return (a[0] == b[0]);}) };
    
    /// making sure that two months were found
    if (same_letter != months.end())
        /// std::next return the next iterator after the same_letter
        std::cout << *same_letter << " and " << *std::next(same_letter)
                  << " start with the same letter\n";
    
    /// using auto would infer a type of const char*
    /// so explicitly defined the parameter as a std::string_view
    const auto five_letter_months
    {
        std::count_if(months.begin(), months.end(),
                      [](std::string_view str) { return (str.length() == 5);}) };
    
    std::cout << "There are " << five_letter_months << " months with 5 letters\n";
    
    /// this will check how many times the print has been called
    auto print
    {
        [](auto value)
        {
            static int call_count{ 0 };
            std::cout << call_count++ << ": " << value << '\n';
        }
    };
    
    /// one generic lambda turn into two distinct lambdas
    /// different version of lambda is called
    /// static variable is different in these two calls not shared with next two integer literal calls
    print("Hello!");
    print("World!");
    
    /// one generic lambda turn into two distinct lambdas
    /// different version of lambda is called
    print(1);
    print(2);
    
    print("dog cat");
    
    /*
    /// no specified return type for the lambda
    auto divide
    {
        [](int x, int y, bool int_division)
        {
            if (int_division)
                /// returns an int
                return x / y;
            else
                /// returns a double, doesn't match with the previous return type
                return static_cast<double>(x / y);
        }
    };
    */
    
    /// explicitly specified the lambda's return type, now compiler will do the conversion if needed
    auto divide
    {
        [](int a, int b, bool int_division) -> double
        {
            if (int_division)
                /// compiler will do the implicit conversion to double
                return a / b;
            else
                return static_cast<double>(a / b);
        }
    };
    
    std::cout << divide(2, 2, true) << '\n';
    std::cout << divide(2, 2, false) << '\n';
    
    std::array B{ 13, 90, 99, 5, 40, 80 };
    
    /// std::greater - we can use std::greater instead of converting greater() into a lambda
    std::sort(B.begin(), B.end(), std::greater{});
    
    for (auto i : B)
        std::cout << i << ' ';
    std::cout << '\n';
    
    
    std::array<Student, 8> arr
    {
      { { "Albert", 3 },
        { "Ben", 5 },
        { "Christine", 2 },
        { "Dan", 8 }, // Dan has the most points (8).
        { "Enchilada", 4 },
        { "Francis", 1 },
        { "Greg", 3 },
        { "Hagrid", 5 } }
    };
    
    const auto most_points
    {
        std::max_element(arr.begin(), arr.end(),
                         [](const auto& a, const auto& b) { return (a.points < b.points); }) };
    
    std::cout << most_points->name << " is the best student\n";
    
    
    std::array<Season, 4> seasons{
        { { "Spring", 285.0 },
          { "Summer", 296.0 },
          { "Fall", 288.0 },
          { "Winter", 263.0 } }
      };
    
    std::sort(seasons.begin(), seasons.end(),
                [](const auto& a, const auto& b) {
                  return (a.averageTemperature < b.averageTemperature);
                });
    
    for (const auto& season : seasons)
      {
        std::cout << season.name << '\n';
      }
    
    return 0;
}
