//
//  main.cpp
//  1.8_whitespace.and.basic.formatting
//
//  Created by Judah's Leon on 8/24/22.
//

/*
 whitespace : characters used for formatting purposes.
 
 example : spaces, tabs and newlines
 
 compiler c++ : ignores whitespaces except when processing text literals
 
 
 formatting recommendations :
 fine : to use spaces or tabs for indentations
 function braces : {
                   }
 
 or
 
 function name{
 }
 
 
 BEST PRACTICE :
 lines should be no longer than 80 chars in length.
 
 some editors : support column guide, to see when the line getting too long
 */
#include <iostream>

int main()
{
    std::cout<<"hello world\n";
    
    // different than the previous, whitespaces considered by the compiler
    std::cout<<"hello       world\n";
    
//    std::cout<<"hello         // error : newlines not allowed in quoted text
//    world"
    
    
    /// concatenation of quoted texts
    std::cout<<"hello"
    "world"
    "hello\n";
    
    /*
    std::cout<<"hello world";       // single line
    comment, this line is not a part of the comment : error
     */
    
    // indentation for contnuation line
    std::cout<<"sdsajlsa sdfjsklaslkfjalsjs jas flkasjflkasjflkajfkdklj dkkdfkjfdkdkjdjfdjdfjdkdjfkdjflsdfsdflksfksdfjkfkjdfkf\n";
    
    // text aligned with previous line for continuation
    std::cout<<"sddkkdfkjfdkdkjdjfdjdfjdkdjfkdjflsdfsdflksfksdfjkfkjdfkfdfdfdfdfdfdfdf        dfdfdfdfdfdfdfkdsjfksdjfksfjskdj dkjfdkjfkdjfdkjfdkjkdjkdjfkdjjl\n";
    
    
    // operator at the beginning of new line, not at the end of previous line
    std::cout<<2+2
    +3<<std::endl;
    
    
    
    // harder to read
    int apple = 2;
    int boy = 3;
    int california = 4;
    
    // easier to read
    int apple2      = 2;
    int boy2        = 3;
    int california2 = 4;
    
    // harder to read
    std::cout<<"hello"; // a comment
    std::cout<<"hello world, c++ programming";  // a comment
    
    // easier to read
    std::cout<<"hellodf";                        // a comment
    std::cout<<"hello world, c++ programming";     // a comment
    std::cout<<"progtam";                        // a comment
    
    // harder to read
    // a comment
    std::cout<<"hello";
    // a comment
    std::cout<<"world";
    // a comment
    std::cout<<"hello";
    
    // easier to read
    // a comment
    std::cout<<"hello";
    
    // a comment
    std::cout<<"world";
    
    // a comment
    std::cout<<"hello";
    
    
    
    /*
     Best practice

     Using the automatic formatting feature is highly recommended to keep your code’s formatting style consistent.
     */
}
