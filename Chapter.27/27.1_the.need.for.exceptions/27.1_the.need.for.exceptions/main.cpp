//
//  main.cpp
//  27.1_the.need.for.exceptions
//
//  Created by Εκλεκτός εν Χριστώ on 11/26/23.
//

/*
 ISSUES WITH RETURN CODES WHEN HANDLING ERRORS:
 
 - return values can be cryptic
 
 - functions can only return one value, returning both the error code and result is not possible, the fix is
   to pass either the result or the error handling back as a reference parameter, which makes for ugly code
   that is less convenient to use
 
 - In sequences of code where many things can go wrong, error codes have to be checked constantly, all of
   this error checking and returning values makes determining what the function is trying to do much harder
   to discern
 
 - return codes do not mix with constructors very well, constructors have no return type to pass back a
   status indicator and passing one back via a reference parameter is messy and must be explicitly checked
 
 - when an error code returned back to the caller, the caller may not always be equipped to handle the error

 -----------------------------------------------------------------------------------------------------------
 EXCEPTIONS: provide a mechanism to decouple/separate the handling of errors or other exceptional cases from
 the typical control flow of code, this allows more freedom to handle errors when and however is most useful
 for a given situation
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>

int main()
{
    return 0;
}
