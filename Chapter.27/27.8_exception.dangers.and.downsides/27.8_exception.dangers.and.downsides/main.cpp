//
//  main.cpp
//  27.8_exception.dangers.and.downsides
//
//  Created by Εκλεκτός εν Χριστώ on 12/4/23.
//

/*
 std::unique_ptr - template class that holds a pointer and deallocates it when it goes out of scope
 
 when using exceptions - issue of cleaning up resources can be solved by using a local variable of a class
 that knows how to cleanup itself when it goes out of scope e.g. std::unique_ptr
 
 example:
 
 #include <iostream>
 #include <memory> // for std::unique_ptr

 try
 {
     auto* john { new Person("John", 18, PERSON_MALE) };
     std::unique_ptr<Person> upJohn { john }; // upJohn now owns john

     ProcessPerson(john);

     // when upJohn goes out of scope, it will delete john
 }
 catch (const PersonException& exception)
 {
     std::cerr << "Failed to process person: " << exception.what() << '\n';
 }
 
 -----------------------------------------------------------------------------------------------------------
 Exceptions and destructors: exception should never be thrown in destructors
 
 when a exception is thrown from a destructor during the stack during the stack unwinding process, the
 compiler is put is a situation where it doesn't know whether to continue the stack unwinding process or
 handle the new exception, the end result is that program will be terminated immediately, write a message
 to a log file instead
 
 RULE: destructors should not throw exceptions
 
 -----------------------------------------------------------------------------------------------------------
 exceptions:
 
 - increase the size of the executable
 - may cause the executable to run slower, because of the checking that has to be performed
 - when exception is thrown, the stack must be unwound and an appropriate handler found, which is expensive
 
 Zero-cost exceptions: an exception model, supported on some modern computer architectures that has no
 additional runtime cost in the non-error case
 
 When to use exceptions?
 
 - the error being handled is likely to occur only infrequently
 - error is serious and execution could not continue otherwise
 - error can't be handled at the place where it occurs
 - there isn't a good alternative way to return an error code back to the caller
 
 CASE:
 
 consider the case where you’ve written a function that expects the user to pass in the name of a file on
 disk. Your function will open this file, read some data, close the file, and pass back some result to
 the caller. Now, let’s say the user passes in the name of a file that doesn’t exist, or a null string.
 Is this a good candidate for an exception?
 
 In this case, the first two bullets above are trivially met -- this isn’t something that’s going to happen
 often, and your function can’t calculate a result when it doesn’t have any data to work with. The
 function can’t handle the error either -- it’s not the job of the function to re-prompt the user for a
 new filename, and that might not even be appropriate, depending on how your program is designed. The
 fourth bullet is the key -- is there a good alternative way to return an error code back to the
 caller? It depends on the details of your program. If so (e.g. you can return a null pointer, or a
 status code to indicate failure), that’s probably the better choice. If not, then an exception would
 be reasonable.
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>



int main()
{
    
    
    return 0;
}
