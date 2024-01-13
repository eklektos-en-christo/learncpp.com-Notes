//
//  main.cpp
//  7.12_intro.to.testing.the.code
//
//  Created by εκλεγμένοι εν Χριστώ on 1/16/23.
//

/*
 Software testing/validation : process of determining whether or not the software actually
 works as expected.
 
 PRACTICAL THINGS:
 
 Test the code in small pieces - Analogy below:
 a) Build and test each car component individually before installing it
 b) Build a car out of all of the components all in one go, test the whole thing for the
    first time at the end
 
 OPTION : a) is better choice, risk is minimized by all the prior testing, reduces time
 spent in debugging the code, better to write small functions/classes and then compiling
 and testing them immediately
 
 Unit testing : testing a small piece of code in isolation to ensure that "unit" of code is
 correct
 Unit test : each unit test is designed to ensure that a particular behavior of the unit is
 correct
 
 Best practice
 write the program in small, well defined units (functions/classes), compile often, and test
 the code as you go.
 If the program is short and accepts user input, trying a variety of user inputs might be
 sufficient, but as programs get longer and longer this becomes less sufficient and There
 is more value in testing individual functions/classes before integrating them into the
 rest of the program
 
 Informal testing : after writing a unit of code(function,class or some discrete package of
 code), you can write some code to test the unit that was just added and then erase the test
 once the test passes
 
 Preserving the tests : Instead of erasing the temporary test code, you could move the tests
 into a tests() function
 
 Automating the test functions : we can do better by writing a test function that contains
 both the tests AND the expected answers and compare them, so there will be no need to
 manually compare the actual results to the expected results, this is useful when going back
 and modifying the old code to ensure you haven't accidentally broken anything.
 
 Unit testing frameworks : there exist entire frameworks that are designed to help simplify
 the process of writing, maintaining and executing the unit tests
 
 Integration testing : once each of the units has been tested in isolation, they can be
 integrated into the program and retested to make sure they were integrated properly
 
 ___________________________________________________________s
 Question: When should you start testing your code?
 Answer  : As soon as you’ve written a non-trivial function.
 */

#include <iostream>

/// we want to test the following function/unit
bool is_lower_vowel(char c)
{
    switch (c)
    {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
        default:
            return false;
    }
}

/// this function preserves the tests
void test_lower_vowel()
{
    /// moved the tests in main( ) to this function
    /// will be helpful in retesting things later
    /// if the function is modified to add new capability, then also
    /// this will be useful
    /// as more and more tests are created, you can simply add them
    /// to this test function to preserve the tests
    std::cout << is_lower_vowel('b') << '\n';
    std::cout << is_lower_vowel('a') << '\n';
}

/// automating the test functions
/// this returns the number of tests that failed
/// this returns 0 is all the tests passed
/// the test routine will do all the work
/// returning either an "all good" signal i.e. return value 0 or the test number that didn't pass
int tests_vowel()
{
    if (!is_lower_vowel('a')) return 1;
    if (is_lower_vowel('b')) return 2;
    
    return 0;
}

int main()
{
    /// -----------------INFORMAL TESTING-----------------
    /// temporarily testing the function to validate its working
    ///
    /// it's working as expected, i can erase the temporary test code and continue
    /// programming another units
//    std::cout << is_lower_vowel('b') << '\n';
//    std::cout << is_lower_vowel('a') << '\n';
    
    std::cout << tests_vowel() << '\n';
    
    return 0;
}
