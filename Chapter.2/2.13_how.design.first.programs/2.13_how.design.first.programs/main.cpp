//
//  main.cpp
//  2.13_how.design.first.programs
//
//  Created by εκλεγμένοι εν Χριστώ on 9/9/22.
//

/// most important thing to remember:
/// design your program before you start coding.
///
/// programming is like architecture
///
/// little up-front planning will save both time and frustration in the long run
///
///---------------------------------------------------------------------------------------------
/// Design step 1: Define your goal
/// -first need to define what your goal is
/// -you should be able to state this in a sentence or two
///
/// example:
/// Allow the user to organize a list of names and associated phone numbers.
/// Generate randomized dungeons that will produce interesting looking caverns.
/// Generate a list of stock recommendations for stocks that have high dividends.
/// Model how long it takes for a ball dropped off a tower to hit the ground.
///
/// Although this step seems obvious, it’s also highly important
///---------------------------------------------------------------------------------------------
/// Design step 2: Define requirements
/// Requirements is a fancy word for both the constraints that your solution needs
/// to abide by(e.g. budget, timeline, space, memory, etc…)
/// as well as the capabilities that the program must exhibit in order to meet the
/// users’ needs
/// requirements should similarly be focused on the “what”, not the “how”.
///
/// example:
/// Phone numbers should be saved, so they can be recalled later.
/// The randomized dungeon should always contain a way to get from the entrance
/// to an exit.
/// The stock recommendations should leverage historical pricing data.
/// The user should be able to enter the height of the tower.
/// We need a testable version within 7 days.
/// The program should produce results within 10 seconds of the user submitting
/// their request.
/// The program should crash in less than 0.1% of user sessions.
///
/// A single problem may yield many requirements,
/// the solution isn’t “done” until it satisfies all of them
///---------------------------------------------------------------------------------------------
/// Design step 3: Define your tools, targets, and backup plan
/// When you are an experienced programmer:
/// steps that typically would take place at this point-
///
/// -Defining what target architecture and/or OS your program will run on.
/// -Determining what set of tools you will be using.
/// -Determining whether you will write your program alone or as part of a team.
/// -Defining your testing/feedback/release strategy.
/// -Determining how you will back up your code.
///
/// as a new programmer:
/// writing a program for your own use, alone, on your own system
/// using an IDE you purchased or downloaded
/// code is probably not used by anybody but you
///
///  if you are going to work on anything of non-trivial complexity:
///  -you should have a plan to backup your code
///  -not enough to just zip or copy the directory to another location on your pc
///  -If your system crashes, you’ll lose everything
///  -good backup strategy involves getting a copy of the code off of your system
///  -lots of easy ways to do this:
///  -Zip it up and email it to yourself
///  -copy it to Dropbox or another cloud service
///  -FTP it to another machine
///  -copy it to another machine on your local network
///  -use a version control system residing on another machine or in the cloud
///
///  Version control systems have the added advantage:
///  -able to restore your files
///  -but also to roll them back to a previous version.
///---------------------------------------------------------------------------------------------
/// Design step 4: Break hard problems down into easy problems
/// example: we want to clean our house
///
/// let’s break it into subtasks:
/// -Vacuum the carpets
/// -Clean the bathrooms
/// -Clean the kitchen
///
/// we can break some of these down even further:
///
/// Clean the house:
/// -Vacuum the carpets
/// -Clean the bathrooms
/// -Scrub the toilet (yuck!)
/// -Wash the sink
///
/// Clean the kitchen:
/// -Clear the countertops
/// -Clean the countertops
/// -Scrub the sink
/// -Take out the trash
///
/// bottom up approach:  create a hierarchy of tasks
///
/// Get from bed to work
/// Bedroom things
///    Get out of bed
///    Pick out clothes
///    Get dressed
/// Bathroom things
///    Take a shower
///    Brush your teeth
/// Breakfast things
///    Prepare cereal
///    Eat cereal
/// Transportation things
///    Get on your bicycle
///    Travel to work
///
/// top level task: “Clean the house” or “Go to work” becomes main( )
/// it is the main problem you are trying to solve
/// The subitems become functions in the program.
///
/// task hierarchies are extremely useful in programming
/// task hierarchy: have essentially defined the structure of your overall program
///
/// one of the items (functions) is too difficult to implement, imply split that item
/// into multiple sub-items/sub-functions
/// you should reach a point where each function in your program is trivial to
/// implement.
///---------------------------------------------------------------------------------------------
/// Design step 5: Figure out the sequence of events
/// it’s time to determine how to link all the tasks together
/// first step is to determine the sequence of events that will be performed
///
/// example, when you get up in the morning, what order do you do the above
/// tasks?
///     Bedroom things
///     Bathroom things
///     Breakfast things
///     Transportation things
///
/// If we were writing a calculator, we might do things in this order:
///     Get first number from user
///     Get mathematical operation from user
///     Get second number from user
///     Calculate result
///     Print result
///
/// Don’t implement your entire program in one go
/// Work on it in steps
/// testing each step along the way before proceeding.
///
/// Words of advice when writing programs:
/// Keep your programs simple to start.
/// Add features over time.
/// Focus on one area at a time.
/// Test each piece of code as you go.
/// Don’t invest in perfecting early code.


#include <iostream>

/// Implementation step 2: implementing functions
/// Define the function prototype (inputs and outputs)
/// Write the function
/// Test the function
int get_input_from_user()
{
    std::cout << "Enter an integer: ";
    int input{};
    std::cin >> input;
    
    return input;
}

/// Implementation step 1: Outlining main function
int main()
{
    // Get first number from user
    int value{get_input_from_user()};
    
    // Get mathematical operation from user
//    get_mathematical_operation();
    // Get second number from user
//    get_input_from_user();
    // Calculate result
//    calculate_result();
    // Print result
//    print_result();
    return 0;
}
