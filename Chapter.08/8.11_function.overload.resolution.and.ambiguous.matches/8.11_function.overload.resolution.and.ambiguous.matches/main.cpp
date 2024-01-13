//
//  main.cpp
//  8.11_function.overload.resolution.and.ambiguous.matches
//
//  Created by εκλεγμένοι εν Χριστώ on 2/17/23.
//

/*
 When any function all is made : compiler must also ensure that a matching function
 declaration can be found
 
 with non-overloaded functions :
 -there is only one function that can match a function call, that function either matches
 or it doesn't
 
 with overloaded functions :
 -there can by many functions that can potentially match a function call
 -function call can only resolve to one of them, compiler has to determine which overloaded
 function is the best match
 - overload resolution : process of matching function calls to specific overloaded function
 
 Resolving overloaded function calls:
 compiler steps through a sequence of rules to determine which of the overloaded functions
 is the best match.
 at each step:
 -compiler applies a bunch of different type conversions to the arguments in the function
 call
 -for each conversion applied - compiler checks if any of the overloaded functions are now
 a match
 -after all different type conversions have applied and checked for matches, the step is
 done, result will be one of three possible outcomes:
 
 -no matching functions were found, compiler moves to the next step in the sequence
 -single matching function was found, considered to be the best match, matching process is
 now complete, subsequent steps are not executed
 -more than one matching function was found, compiler will issue an ambiguous match compile
 error
 
 if the compiler reaches the end of the entire sequence without finding a match, it will
 generate a compile error that no matching overloaded function could be found for the
 function call
 
 
 Argument matching sequence:
 –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
 STEP 1: compiler tries to find an exact match, this happens in two phases
 
 first - if there is an overloaded function where the type of the arguments in the function
 call exactly matches the type of the parameters in the overloaded function
 
 second - compiler will apply a number of trivial conversions to the arguments in the
 function call
 trivial conversions - set of specific conversion rules that will modify types with
 modifying the value for purposes of finding a match, example - a non-const type can be
 trivially converted to a const type as in main()
 
 trivial conversion : non reference type to reference type or vice versa
 
 matches made via trivial conversions : considered exact matches
 –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
 STEP 2:
 if no exact match is found: compiler tries to find a match by applying numeric promotion to
 the arguments, if after numeric promotions a match is found, the function call is resolved
 –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
 STEP 3:
 if not match is found via numeric promotion: compiler tries to find a match by applying
 numeric conversions to the arguments
 
 key insight : matches made by applying numeric promotions take precedence over any matches
 made by numeric conversions
 –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
 STEP 4:
 if no match is found via numeric conversion: compiler tries to find a match through any
 user defined conversions, like classes can define conversions to other types that can be
 implicitly invoked
 
 constructor of a class : also acts as a user defined conversion from other types to that
 class, can be used during this step to find matching functions
 –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
 STEP 5:
 if no match is found via user defined conversion: compiler will look for a matching
 functions that used ellipsis
 –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
 STEP 6:
 if no matches found by this point, compiler gives up and issue a compiler error about not
 being able to find a matching function
 –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
 
 Ambiguous matches:
 with non-overloaded functions - each function call will either resolve to a function or no
 match will be found and compiler will issue a compile error
 
 with overloaded functions - there is a third possible outcome, ambiguous match
 
 ambiguous match : compile time error
 ambiguous match : when compiler finds two or more functions that can be made to match in
 the same step, compiler stops matching and issue a compile error stating that it has found
 an ambiguous function call
 
 key insight : ambiguous function call - means no match from a given step is better than any
 other match from the same step
 
 Resolving Ambiguous matches:
 -often, best way is simply define a new overloaded function that takes parameters of
 exactly the type you are trying to call the function with
 -alternatively, explicitly cast the ambiguous arguments to match the type of the function
 you want to call
 
 Matching for functions with multiple arguments:
 if there are multiple arguments : compiler applies the matching rules to each argument in
 turn
 function chosen - must provide a better match than all the other candidate functions for at
 least one parameter, and no worse for all of the other parameters
 */

#include <iostream>

void print(int x)
{
    std::cout << x << '\n';
}

void print(double d)
{
    std::cout << d << '\n';
}

/// trivial conversion here : to match the arguments' type with parameters' type
void print2(const int x)
{
    std::cout << x << '\n';
}

void print2(double d)
{
    std::cout << d << '\n';
}

void print3(std::string s)
{
    std::cout << s << '\n';
}

void print3(double d)
{
    
    std::cout << d << typeid(d).name() << '\n';
}

class X
{
public:
    operator int(){return 0;}
};

void print4(int x)
{
    std::cout << x << '\n';
}

void print4(double d)
{
    std::cout << d << '\n';
}

void print5(unsigned int x)
{
    std::cout << x << '\n';
}

void print5(float f)
{
    std::cout << f << '\n';
}

/// this function matches the second parameter via promotion
/// this is unambiguously the best match
void print6(char c, int x)
{
    std::cout << "print6(char, int): best match" << '\n';
}

/// this function matches the second parameter via conversion
void print6(char c, double x)
{
    std::cout << 'b' << '\n';
}

/// this function matches the second parameter via conversion
void print6(char c, float x)
{
    std::cout << 'c' << '\n';
}

int main()
{
    /// exact match : type of the arguments passed exactly
    /// matches the type of the parameters in the overloaded functions
    print(2);
    print(2.2);
    
    /// x trivially converted to const int which then matches print2(const int)
    int x(2);
    print2(x);
    
    /// promoted to match print(int)
    print('a');
    /// promoted to match print(int)
    print(true);
    /// promoted to match print(int)
    print(false);
    /// promoted to match print(double)
    print(2.2f);
    
    /// numeric conversion : 'a' converted to double to match print3(double)
    print3('a');
    /// no numeric conversion
    print3("a");
    
    /// compiler : exact match > numeric promotion > numeric conversion > user defined conversion(happening below)
    /// xx is converted to int using the user defined conversion from X to int
    /// conversion : defined in class X above the main
    X xx;
    print(xx);
    
    /// 5l is of type long
    /// compiler : exact match > numeric promotion > numeric conversion(two potential matches)
    /// two potential matches in numeric conversion : numeric conversion to int or numeric conversion to double
    /// so function call is ambiguous
//    print(5L);
    
    /// 0 can be converted to unsigned int or a float
    /// so result is an ambiguous function call
//    print5(0);
    /// solving the ambiguity by using static cast, casting argument type to match the parameter type
    print5(static_cast<unsigned int>(2));
    /// using literal suffix to ensure the literal is interpreted as correct type, this becomes now an exact match
    print5(2u);
    
    /// 2.22 can be converted to unsigned int or a float
    /// so result is an ambiguous function call
//    print5(2.22);
    
    /// print(char, int) : best match
    print6('x', 'a');
    
    return 0;
}
