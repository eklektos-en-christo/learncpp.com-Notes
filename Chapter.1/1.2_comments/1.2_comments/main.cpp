//
//  main.cpp
//  1.2_comments
//
//  Created by Judah's Leon on 7/14/22.
//

/*
 comments : programmer readable note inserted into the source code
 directly, they document the code in some way
 
 two styles of comments : single line and multiline
 
 Having comments to the right of a line can make both the code and the comment hard to read, particularly if the line is long. If the lines are fairly short, the comments can simply be aligned (usually to a tab stop)
 However, if the lines are long, placing comments to the right can make your lines really long. In that case, single-line comments are often placed above the line it is commenting
 
 snippets of code aren’t full programs, they aren’t able to be compiled by themselves
 
 Warning
 Don’t use multi-line comments inside other multi-line comments. Wrapping single-line comments inside a multi-line comment is okay.
 
 Best practice
 Comment your code liberally, and write your comments as if speaking to someone who has no idea what the code does. Don’t assume you’ll remember why you made specific choices.
 
 Summary

     At the library, program, or function level, use comments to describe what.
     Inside the library, program, or function, use comments to describe how.
     At the statement level, use comments to describe why.


 */

#include <iostream>

int main()
{
    // single line comments
    std::cout << "Hello world!\n";                 // std::cout lives in the iostream library
    std::cout << "It is very nice to meet you!\n"; // this is much easier to read
    std::cout << "Yeah!\n";                        // don't you think so?
    
    // This is a comment : single line and it won't execute
    std::cout<<"Hello\n";
    
    
    // multiline comments below
    
    /* This is a
       multiline comment
       It won't
       execute*/
    
    /*
     *
     *  just beautifying the code
     *
     */
    return 0;
}
