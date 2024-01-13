//
//  main.cpp
//  2.2_function.return.values
//
//  Created by Judah's Leon on 8/26/22.
//

/*
 return values : values returned back to the caller function
 for the use
 
 return type : type of the value returned to the caller
 
 void return type : no value returned to the caller
 
 return statement : used to indicate the the specific value
 being returned to the caller, this statement terminates the
 function immediately and return value is copied from the
 function to the caller
 
 return by value : process of copying the value from function
 to the caller
 
 main function : returns integer value, usually 0
 status code : return value of main
 exit code : tells whether the program successfully or not
 status code same as exit code
 if returned value by main is 0 then : program ran successfully
 
 3 status codes, c++ standard
 0, EXIT_SUCCESS = program executed successfully
 EXIT_FAILURE = didn't execute successfully
 
 void type function : function that doesn't return any value
 
 value returning function : function which returns a value, it must return a value
 otherwise it will produce an undefined behavior
 
 Best practice

 Make sure your functions with non-void return types return a value in all cases.

 Failure to return a value from a value-returning function will cause undefined behavior.
 
 main function : implicitly returns 0 if no return statement provided, but it is good
 practice to return 0 explicitly
 
 function can return only a single value:
 can be result of any valid expression, variable, or even call to another function
 which return a single value
 
 The function author can decide what the return value means:
 some function : use return value as status code about success or failure
 other functions : return calculated or selected value
 other function : returns nothing
 good idea : provide a comment which tells the meaning of return value
 
 
 DRY : don't repeat yourself, repeated code is bad
 Best practice
 Follow the DRY best practice: “don’t repeat yourself”. If you need to do something more than once, consider how to modify your code to remove as much redundancy as possible. Variables can be used to store the results of calculations that need to be used more than once (so we don’t have to repeat the calculation). Functions can be used to define a sequence of statements we want to execute more than once. And loops can be used to execute a statement more than once.
 The opposite of DRY is WET (“Write everything twice”).
 */

#include <iostream>

/// returning integer(type of the value) value, not specific value
int return_five()
{
    /// returning the specific value to the caller
    return 5;
}

/// returns integer type of value
int get_value_from_user()
{
    std::cout<<"Enter an integer: ";
    int input{};
    std::cin>>input;
    
    return input;   /// returning to the caller "main"
}

int main()
{
    std::cout<<return_five() + 2<<'\n';
    
    /// not used by main, so it is ignored
    /// return values will not be printed unless the caller sends them to the console via std::cout
    /// return value can be used in an expression or in a statement
    return_five();
    
    /// using the returned value
    int num{get_value_from_user()};
    
    std::cout<<num<<" doubled is: "<<num * 2<<'\n';
    
    /// c++ disallows calling the main function explicitly : but this can also used an infinite function
//    main();
    
    /// function reuse : DRY, save us from writing mutliple input statements    -   modular programming essence
    int a{get_value_from_user()};
    int b{get_value_from_user()};
    
    std::cout<<a<<" + "<<b<<" is "<<a + b<<'\n';
    
    /// for maximum portability, only use 0 or exit_success and exit_failure
    return EXIT_SUCCESS;
}
