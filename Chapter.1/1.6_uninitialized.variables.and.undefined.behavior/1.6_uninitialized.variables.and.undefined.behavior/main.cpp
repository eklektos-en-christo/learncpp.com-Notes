//
//  main.cpp
//  1.6_uninitialized.variables.and.undefined.behavior
//
//  Created by Judah's Leon on 7/21/22.
//

/*
 Uninitialized variables:
            c/c++ doesn't initialize most variables if value not given
            so by default then garbage value is present in that location
            
            if the known value is not given then variable is called uninitialized
            variable
 */

/*
 Initialization : known value given at the point of definition
 Assignment : known value given after the point of definition
 Uninitialized : known value not yet given to the object.
 
 
 
 performance optimization : sometimes initialization is not done for performance
 optimization, it is inherited from C, back when computers were slow
 
 always initialize variables, it is negligible if is done so
 sometimes it is good to not initialize because of performance optimization
 */


/*
 Undefined behavior : UB, example below is the undefined behavior
                      it is the result of executing code whose behavior is not
                      well defined by the language
 
 in the below example, this behavior is not defined in the language that what to do
 if the variable is uninitialized used
 
 undefined behavior symptoms:
                            different results
                            consistent same incorrect results
                            sometimes correct, sometimes incorrect results
                            seems like working but produce wrong results later
                            program crashes, immediately/later
                            works on some compiler and on some not
                            works until you change some other seemingly unrelated code
 
 
 Rule

 Take care to avoid all situations that result in undefined behavior, such as using uninitialized variables.
 
 */

#include <iostream>


void donothing(int &){};    // used to remove the compile time warning, to trick
                          // the compiler that value is being used even
                          //uninitialized

int main()
{
    // uninitialized variable consequences, unknown value
    // some compilers give compile time warning for this
    int x;
    std::cout<<x;
    
    
    donothing(x);   // tricking compiler
}
