//
//  main.cpp
//  3.4_basic.debugging.tactics
//
//  Created by εκλεγμένοι εν Χριστώ on 9/10/22.
//

/*
 Debugging tactic #1: Commenting out your code
 
 Debugging tactic #2: Validating your code flow
 When printing information for debugging purposes, use
 std::cerr instead of std::cout
 std::cerr is unbuffered, which means anything you send to it
 will output immediately
 Tip:
 When adding temporary debug statements, it can be helpful to
 not indent them. This makes them easier to find for
 removal later.
 
 Debugging tactic #3: Printing values
 The third-party library dbg-macro can help make debugging
 using print statements easier. Check it out if this is
 something you find yourself doing a lot.
 
 
 
 Why using printing statements to debug isn’t great?
 -Debug statements clutter your code.
 -Debug statements clutter the output of your program.
 -Debug statements must be removed after you’re done with
 them, which makes them non-reusable.
 -Debug statements require modification of your code to both
 add and to remove, which can introduce new bugs.
 */
