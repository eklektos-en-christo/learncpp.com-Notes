//
//  main.cpp
//  1.7_keywords.and.naming.identifiers
//
//  Created by Judah's Leon on 8/24/22.
//

/*
 as of c++20 : cpp contains 92 reserved words for its own use
 each keyword(words) : has special meaning
 
 special identifiers : override, final, import, module  : not reserved but have  a
 special meaning when used in a certain context
 
 
 
 IDENTIFIER NAMING RULES :
 can't be a keyword
 can be composed of letters, number and underscore characters.
 must begin with a letter or underscore
 can't start with a number
 case sensitive, nvalue is not same as NVALUE/nValue
 
 variable names : lowercase letters
 function name : lowercase letters, as main() is also lowercase, also the cpp
 standard library functions
 capital letter names : structs, classes, enums
 multi-word variable or function name : snake_case or camelCase/intercapped
 whitespaces : not allowed
 
 
 Best practice

 When working in an existing program, use the conventions of that program (even if
 they don’t conform to modern best practices). Use modern best practices when
 you’re writing new programs.
 
 
 
 
 avoid : identifiers starting with _underscores
 _underscore names : reserved for OS, library or compiler use
 
 picking names : that make sense and convey what the variable is holding
 */

#include <iostream>

int main()
{
    // variable name should begin with a lowercase letter
    // if name is one word long, then whole name should be in lowercase letters
    int value;      // correct
    
    int Value;      // incorrect, should be in lowercase
    int VALUE;      // incorrect, ''    ''      ''
    int vaLuE;      // incorrect
    
    int my_variable;        // snake case
    int myVariable;         // camel case
    int my_function();      // snake case
    int myFunction();       // camel case
    
    
    
    // lengthy variable name : numberOfCharsIncludingWhitespacesAndPunctuation
    int numberOfCharsIncludingWhitespacesAndPunctuation;    // fix : next line
    
    // holds no. of chars - including whitespaces and punctuation
    int numberOfChars;  // comment is better than an lengthy name
}
