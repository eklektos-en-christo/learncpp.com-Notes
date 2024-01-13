//
//  main.cpp
//  2.6_why.functions.are.useful.how.to.use.them.effectively
//
//  Created by εκλεγμένοι εν Χριστώ on 9/6/22.
//

/*
 Why use functions?
 useful in programs of non-trivial length and complexity
 
 Organization: reduces complexity
 
 Reusability: avoid duplicate code, minimizes errors, sharing
 code with other programs as functions reduce the amount of
 code to be written from scratch
 
 Testing: less code to test again and again once a function is
 tested, no need to test it again unless the changes are made
 to it
 
 Extensibility: functions allow us to change them, change in
 once place will take effect every time a function is called
 
 Abstraction: use a function requires its name, inputs,
 outputs, and place where it lives. no need of knowing the
 working of the function and its dependencies. lowers the
 amount of knowledge required to use other people's code.
 example - STD
 
 Effective use of functions:
 when to write functions?
 group of statements that appear more than once in a program
 should be made into a function, example - reading input
 multiple times from the user, outputting something in
 multiple places
 code that has a well defined set of inputs and inputs is
 a good candidate for a function,particularly it the code
 is complicated. example - code for sorting the unsorted list,
 code than simulates the roll of a 6-sided dice
 -----A function should perform only one task generally.
 when function becomes too long and complicated, it can be
 split into multiple sub functions, this is refactoring
 */
