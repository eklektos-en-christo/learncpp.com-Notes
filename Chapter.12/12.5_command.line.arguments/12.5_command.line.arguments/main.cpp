//
//  main.cpp
//  12.5_command.line.arguments
//
//  Created by Εκλεκτός εν Χριστώ on 6/18/23.
//

/*
 ___________________________________________________________________________________________
 Output of compiling and linking: an executable file
 
 NEED FOR COMMAND LINE ARGUMENTS:
 
 Command line arguments: optional string arguments, passed by the OS to the program when it
 is launched.
 
 Command line arguments: provide a way for people/programs to provide inputs to a program
 
 ___________________________________________________________________________________________
 Executable programs: can be run on the command line by invoking them by name
 
 Example: To run the executable file Notepad that is located in the current directory of a
          Windows machine, we could type:
 
          Notepad
 
          Equivalent command line on a Unix-based OS would be:
 
          ./Notepad
 
          Notepad - is the executable file, in order to pass command line arguments to it,
                    we simply list the command line arguments after the executable name:

          Notepad my_file.txt
 
          For multiple arguments - use arguments separated by spaces
 
          Notepad my_file.txt your_file.txt
 
 ___________________________________________________________________________________________
 USING COMMAND LINE ARGUMENTS:
 
 Below is the different form of main function -
 
            int main(int argc, char* argv[])        - preferred, easier to understand
 
                        OR
 
            int main(int argc, char** argv)
 
 argc: argument count, int param, count of the number of the arguments passed to the program
 argc: will always be at least 1, because first argument is always the program name itself
 argc: every command line argument the user passes, will cause the argc to increase by 1
 
 argv: argument values/argument vectors, where the actual argument values are stored
 argv: an array of char pointers, each pointer in it points to a C-style string
 argc: is the length of argv array
 
 Argument 0: is the path and name of the current program being run
 Argument 1: argument passed by the user/program
 Argument 2: next argument and so on it goes
 
 ___________________________________________________________________________________________
 DEALING WITH NUMERIC ARGUMENTS:
 
 Command line arguments: always passed as strings, even if the value provided is numeric
 
 To use command line argument as a number: convert it from a string to a number
 
 std::stringstream - works much like std::cin, operator>> can be used with std::stringstream
 
 ___________________________________________________________________________________________
 OS - parses the command line arguments first
 
 OSes - have special rules about how special characters like double quotes and backslashes
        are handled
 
 Strings: passed in double quotes are considered to be part of the same string
            
                    args "Hello world"
 
 String: each string considered a different string if not passed in double quotes
 
                    args Hello world
 
 To add a literal double quote to the string:
 include a literal double quote by backslashing the double quote
 
                    args \"Hello world\"
 
 Other characters: may also require backslashing/escaping depending on how the OS interprets
                   them
 
 ___________________________________________________________________________________________
 CONCLUSION:
 
 Command line arguments: provide a great way to people or programs to pass input data into
 a program at startup
 
 example: consider making any input data that a program requires when it starts to operate
 a command line parameter, if the command line isn't passed in then you can always detect
 that and ask the user for input, that way the program can operate either way.
 
 ___________________________________________________________________________________________
 */

#include <iostream>
#include <string>
#include <sstream>

/// argc - argument count
/// argv - argument vectors/values
int main(int argc, char* argv[])
{
    std::cout << "Total arguments: " << argc << '\n';
    
    /// looping through each argument and printing it
    for (int count = 0; count < argc; ++count)
        std::cout << count << ' ' << argv[count] << '\n';
    
    /*
    /// whether argv[0] is empty or not
    /// argv[0] - can end up as empty string instead of the program's name on some OSes
    if (argc <= 1)
    {
        if (argv[0])
            std::cout << "Usage: " << argv[0] << " <number>\n";
        else
            std::cout << "Usage: <program name> <number>" << '\n';
    }
    
    /// converting string command line argument to an integer
    std::stringstream convert{ argv[1] };
    
    int my_int{};
    /// if conversion fails: set my_int to a default value
    /// using >> to extract the value to an integer variable
    /// std::stringstream works much like std::cin
    if (!(convert >> my_int))
        my_int = 0;
    
    std::cout << "Got integer: " << my_int << '\n';
    */
    
    return 0;
}
