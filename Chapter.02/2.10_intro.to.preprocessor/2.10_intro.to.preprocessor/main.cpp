//
//  main.cpp
//  2.10_intro.to.preprocessor
//
//  Created by εκλεγμένοι εν Χριστώ on 9/7/22.
//

/*
 translation: happens before the compilation
 translation unit: code file with translations applied to it
 
 translation unit:
 an implementation file and all the headers that it includes
 directly or indirectly
 
 preprocessor: separate program that manipulates the text in
 each code file
 
 preprocessor: scans through the code file, top to bottom,
 looks for preprocessor directives
 
 preprocessor directives: instructions that start with # and
 end with a new line (not with semicolon)
 
 directives: tell the preprocessor to perform certain
 text manipulation tasks
 
 preprocessor: doesn't understand C++ syntax
 
 output of preprocessor: also goes through several more
 translation phases, then compiled
 
 all text changes made by the preprocessor happen either
 temporarily in-memory or using temporary files each
 time the code file is compiled
 
 using directives : are not preprocessor directives
 
 macro: rule that defines how input text is converted into
 replacement output text
 
 types of macros:
 object like macros
 function like macros
 
 object like macros: defined in two ways
 #define identifier
 #define identifier substitution_text
 identifier: traditionally type in capital letters, underscore
 used for spaces
 substitution_text: when further occurrence of the identifier
 is replaced by the substitution text
 
 function like macros: act like functions, their use is
 generally considered as dangerous
 
 conditional compilation: these directives allow to specify
 under what conditions something will/won't compile
 #if, #elif
 #else
 #ifndef, #ifdef, #endif
 // c++ style syntax below
 #ifdef = #if defined()
 #ifndef = #if !defined()
 
 #ifdef: allows the preprocessor to check whether
 an identifier has been previously defined, if so then code
 between ifdef and matching endif is compiled.
 #endif: necessary to specify the end of the ifdef or ifndef
 
 Object-like macros don’t affect other preprocessor directives
 
 output of the preprocessor: contains no directives at all
 compiler doesn't understand the directives,they are all
 resolved/stripped out before compilation
 
 Macros only cause text substitution for normal code.
 Other preprocessor commands are ignored
 
 preprocessor: doesn't understand functions
 generally: define the #define outside of functions
 directives: valid from point of definition to the end of the
 file in which they are defined
 directives: in one file don't not have impact on other code
 files in the same project
 */

/// include: is a directive
/// preprocessor: replaces the #include directive with
/// the contents of the included file, in this case it is iostream file
/// included contents: preprocessed along with the rest of the file, then compiled
/// #include: exclusively used to include header files
#include <iostream>

/// further occurrence of MY_NAME will be replaced by the "Leon"
/// object like macros: can be avoided, there are better ways to do it
#define MY_NAME "Leon"

/// object like macro: without substitution text
/// further occurrence of the USE_INR will be removed and replaced by nothing
/// this object like macro is considered acceptable to use
#define USE_INR

/// preprocessor: doesn't understand functions
void foo()
{
#define INSIDE_FUNCTION "Inside Function"
}

/// forward declaration, definition inside function.cpp
void print_something();

int main()
{
    std::cout << "Name is: " << MY_NAME << '\n';
 
    
    
#ifdef USE_INR
    std::cout << "INR" << '\n';
#endif
  
    
    
/// USE_USD is not defined, so this won't compile
#ifdef USE_USD
    std::cout << "USD" << '\n';
#endif
  
    
    
/// will compile: because ifndef mean - if not defined
#ifndef USE_USD
    std::cout << "USD not defined" << '\n';
#endif
 
    
    
/// c++ style syntax
#if defined(MY_NAME)
    std::cout << MY_NAME << '\n';
#endif
   
    
    
#if 0       /// used to exclude a block of code from being compiled,
           /// works like a comment
    std::cout << "Uncompiled code" << '\n';
#endif
   
    
/// convenient way to comment out code that contains multi-line comments
/// which can't be commented out using another multi-line comment due to
/// due to multi-line comments being non-nestable
#if 0
    std::cout << "Can't compile it " << '\n';
    /*
     this is
     a multi-line
     comment
     */
    std::cout << "Can't compile it " << '\n';
#endif
    
  
/// Object-like macros don’t affect other preprocessor directives
#define PRINT_HELLO "HELLO"
/// PRINT_HELLO in ifdef will not be replaced by the "HELLO", ignored
#ifdef PRINT_HELLO
    /// PRINT_HELLO will be replaced with "HELLO"
    /// because it is normal code and not a preprocessor directive
    std::cout << PRINT_HELLO << '\n';
#endif
    
    
    /// INSIDE_FUNCTION from the foo( ) function
    std::cout << INSIDE_FUNCTION << '\n';
    
/// even though PRINT is defined in this file
/// but it's scope is limited to this file only
/// so "not printing" will execute from function.cpp
#define PRINT
    print_something();
    
    return EXIT_SUCCESS;
}
