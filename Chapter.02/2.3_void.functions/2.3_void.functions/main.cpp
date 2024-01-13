//
//  main.cpp
//  2.3_void.functions
//
//  Created by Judah's Leon on 8/27/22.
//

/*
 void function : a function that does not return a value
 also called non-value returning function.
 
 void return values : to tell the compiler that a function
 does not return a value, a return type of void is used
 
 return statement : void function automatically return to the
 caller, no return statement needed
 return statement : can also be used in a void function, but
 it is redundant, it happens internally in void function
 
 Best practice
 Do not put a return statement at the end of a non-value
 returning function.
 
 void functions : can't be used in an expression that require
 a value
 
 Some statements require values to be provided, and others
 don’t.
 
 When we call a function by itself (e.g. the first printHi() in the above example), we’re calling a function for its behavior, not its return value. In this case, we can call either a non-value returning function, or we can call a value-returning function and just ignore the return value.
 
 When we call a function in a context that requires a value (e.g. std::cout), a value must be provided. In such a context, we can only call value-returning functions.
 
 Returning a value from a void function is a compile error
 
 early returns : return statement that is not the last
 statement in the function, this causes function to return to
 the caller. early return can be used in non void functions
 */

#include <iostream>

/// void : means function does not return a value to the caller
void print_hello()
{
    /// code below executes and control returns to main
    std::cout << "Hello!" << '\n';
    
    /// no return statement needed here in void's case
//	return 2;	/// error : void doesn't return value
}

void early_return()
{
	std::cout << "Early return!" << '\n';
	
	/// early return : will cause the function to return to the caller
	return;
	
	std::cout << "Early return!" << '\n';
}

int main()
{
    print_hello();
    
    /// error : cout requires a value and print_hello is a void function
//    std::cout << print_hello();
	
	early_return();
}
