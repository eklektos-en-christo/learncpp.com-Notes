//
//  main.cpp
//  12.6_ellipsis_and.why.to.avoid.them
//
//  Created by Εκλεκτός εν Χριστώ on 6/21/23.
//

/*
 ___________________________________________________________________________________________
 Number of parameters a function will take must be known in advance even if they have
 default values
 
 To be able to pass a variable number of parameters to a function: ellipsis can be used
 
 Ellipsis: also known as "..."
 
 Syntax:
                return_type func_name(argument_list, ...
 
 argument_list: is one or more normal function parameters
 
 Functions that use ellipsis: must have at least one non-ellipsis parameter
 
 argument_list: any arguments passed to the function must match the argument_list parameters
                first.
 Ellipsis: must always be the last parameter in the function
 Ellipsis: capture any additional arguments
 
 Conceptually: think of ellipsis as an array to hold any additional parameters beyond in the
               argument_list
 
 ___________________________________________________________________________________________
 <cstdarg>   : needed to use ellipsis
 
 std::va_list : to access the ellipsis
 std::va_start : to initialize the va_list, arguments it takes are the va_list & last non-
                 ellipsis parameter
 std::va_arg  : to get the values out of the ellipsis, arguments are the va_list & type of
                the value
 std::va_end  : to cleanup the va_list when we are done
 
 va_list, va_arg, va_start, va_end: are macros, needed to access the parameters that are
                                    part of the ellipsis
 
 Ellipsis parameter: has no name
 
 va_list: is a special type to access the values in the ellipsis
 
 Once va_start() has been called, va_list points to the first parameter in the ellipsis.
 
 va_arg(): also moves the va_list to the next parameter in the ellipsis
 
 va_start(): can be called again any time we want to reset the va_list to point to the 1st
 parameter in the ellipsis again
 
 ___________________________________________________________________________________________
 WHY ELLIPSIS ARE DANGEROUS: type checking is suspended
 
 With regular function parameters: compiler uses type checking to ensure the types of the
 function arguments match the type of the function parameters or compiler might do the
 implicit conversion to make them match
 
 Ellipsis parameters: have no type declarations
 
 Compiler: completely suspends type checking for ellipsis parameters
 
 Ellipsis: can take any type of arguments, that leave quite a bit of room for errors
 
 especially if the caller wasn't the one who wrote the function
 
 Computer: stores all data as a sequence of bits
 Type    : tells computer how to translate that sequence of bits into a meaningful value
 ellipsis: throw away the variable's type
 va_arg  : used to tell what the expected type of the next parameter is
 va_arg  : when actual parameter type doesn't match the expected parameter type, bad things
           usually happens
 
 GIGO    : GARBAGE IN, GARBAGE OUT
 
 ___________________________________________________________________________________________
 WHY ELLIPSIS ARE DANGEROUS: ellipsis don't know how many parameters were passed
 
 Three ways to keep track of the total parameters passed to an ellipsis:
 
 Method 1: pass a length parameter
 but if we provide arguments more or less than the length then we'd run into trouble
 
 Method 2: use a sentinel value
 Sentinel: special value or condition used to terminate a loop when it is encountered
 With ellipsis: the sentinel is typically passed in as the last parameter
 if the user forgets to pass in the sentinel value or passed the wrong value, function will
 loop continuously until it runs into garbage that matches the sentinel or crashes
 Sentinel values: only work well if there is a value that falls outside the valid set of
 values for the problem you are trying to solve
 
 Method 3: use a decoder string, this involves passing a decoder string that tells the
 program how to interpret the parameters
 the string encodes both the number of optional variables and their types, this lets us deal
 with different type of parameters
 the decoder string can be a bit cryptic and if the number of types of the optional
 parameters don't match the decoder string precisely, bad things can happen
 
 In C: printf used decoder string
 
 ___________________________________________________________________________________________
 RECOMMENDATIONS FOR SAFER USE OF ELLIPSIS:
 if possible: don't use ellipsis at all
 
 if using: better to pass all the values to ellipsis parameter which are of same type
 
 Intermixing different types: increases the possibility of the caller accidentally passing
 in the wrong type and va_arg() producing a garbage result
 
 count parameter or decoder string: is safer than using a sentinel value, This forces the
 user to pick an appropriate value for the count/decoder parameter, which ensures the
 ellipsis loop will terminate after a reasonable number of iterations even if it
 produces a garbage value.
 
 parameter packs and variadic templates: offers functionality similar to ellipsis with
 strong type checking
 
 ___________________________________________________________________________________________
 */

#include <iostream>
#include <cstdarg>
#include <string_view>

/// this function: takes a variable number of parameters
/// count: total number of argument we are passing
double find_avg(int count, ...)
{
    int sum{ 0 };
    
    /// va_list: to access the ellipsis we use it
    /// declared the va_list list
    std::va_list list;
    
    /// va_start: used to initialize the va_list
    /// first argument: the list to initialize
    /// 2nd argument: the last non-ellipsis parameter
    va_start(list, count);
    
    for (int arg{ 0 }; arg < count; ++arg)
        /// va_arg: to get the values out of the ellipsis
        /// first argument: va_list we are using, list in this case
        /// 2nd argument: is the type of the value
        sum += va_arg(list, int);
    
    /// va_end: to clean up the va_list when we are done
    va_end(list);
    
    return static_cast<double>(sum) / count;
}

/// no longer need to pass the length as the first parameter
/// we pass a sentinel value as the last parameter when function is called
double find_avg_sentinel(int first, ...)
{
    int sum{ first };
    
    std::va_list list;
    
    va_start(list, first);
    
    int count{ 1 };
    
    while (true)
    {
        int arg{ va_arg(list, int) };
        
        /// if the current parameter is the sentinel value, stop the loop
        if (arg == -1)
            break;
        
        sum += arg;
        ++count;
    }
    
    va_end(list);
    
    return static_cast<double>(sum) / count;
}

/// the string parameter encodes the number of optional variables and their types
/// this lets us deal with the parameters of different types
double find_avg_decoder(std::string_view decoder, ...)
{
    double sum{ 0 };
    
    std::va_list list;
    
    va_start(list, decoder);
    
    for (auto code_type: decoder)
    {
        switch (code_type)
        {
            case 'i':
                sum += va_arg(list, int);
                break;
                
            case 'd':
                sum += va_arg(list, double);
                break;
        }
    }
    
    va_end(list);
    
    return sum / std::size(decoder);
}

int main()
{
    std::cout << find_avg(5, 1, 2, 3, 4, 5) << '\n';
    
    std::cout << find_avg(10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << '\n';
    
    /// Note: the first ellipsis argument is a double instead of an integer
    /// va_arg expects integers but get double and then translates next sequence of bits as an integer
    /// double is: 8 bytes, va_arg will only return first 4 bytes of the double in first call
    /// 2nd call to va_arg: will return the next 4 bytes of the double
    /// this results in getting garbage values
    std::cout << find_avg(5, 1.1, 2, 3, 4, 5) << '\n';
    
    /// type checking is suspended, compiler won't complain about the below arguments passed in
    /// the line compiles fine but produces ridiculous results
    std::cout << find_avg(5, 1.8, 'c', "hello", 4, &find_avg) << '\n';
    
    /// specified 5 arguments but passed only 4 arguments, results in garbage values
    std::cout << find_avg(5, 10, 20, 30, 40) << '\n';
    
    /// specified 3 arguments but passed 5 arguments, result is what was expected but these kind of mistakes can be very
    /// hard to catch
    std::cout << find_avg(3, 1, 22, 18, 40, 60) << '\n';
    
    /// using -1 as the sentinel value which will indicate the end of the list to the function
    std::cout << find_avg_sentinel(1, 40, 22, 11, -1) << '\n';
    
    /// using decoder string to encode the number of optional variables and their types
    /// number of types of the optional parameter don't match the decoder string precisely, bad things can happen
    std::cout << find_avg_decoder("iiiddi", 2, 2, 1.1, 2.1, 6.8, 8) << '\n';
    
    return 0;
}
