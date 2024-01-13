//
//  main.cpp
//  7.5_switch.fallthrough.and.scoping
//
//  Created by εκλεγμένοι εν Χριστώ on 12/15/22.
//

/*
 Fallthrough : when execution flows from a statement underneath a label into
 statements underneath a subsequent label, mean - all subsequent cases execute
 
 warning : once the statements underneath a case or default label have started
 executing, they will overflow/fallthrough into subsequent cases
 
 break or return : statements are typically used to prevent the fallthrough
 
 Attributes in CPP : modern cpp feature that allows the programmer to provide the
 compiler with some additional data about the code,
 
 specifying the attribute : the attribute name is placed between double hard braces
 [[]]
 
 attributes : aren't statements, can be used anywhere where they are contextually
 relevant.
 
 (C++17)
 [[fallthrough]] attribute : modifies a null statement to indicate that fallthrough is
 intentional, then no warnings should be triggered by the compiler
 
 best practice : use the [[fallthrough]] attribute along with null statement to
 indicate intentional fallthrough
 
 sequential case labels :
 e.g. : using logical OR operator to combine multiple tests into a single statement,
 
 bool is_vowel(char c)
 {
    return (c=='a' || c=='e' || c=='i' || c=='o' || c=='u' ||
            c=='A' || c=='E' || c=='I' || c=='O' || c=='U');
 }
 
 similar can be done using switch statement by placing multiple case labels in sequence
 as below in the is_vowel function
 
 Switch case scoping :
 you can only have a single statement after the if condition, that statement is considered to be
 implicitly inside a block as below:
 if (x > 10)
    std::cout << x << " is greater" << '\n';    /// this line implicitly considered to be inside a
                                                /// block
 
 but in switch, the statements after the labels are all scoped to the switch block, which means no
 implicit blocks are created
 
 variable declaration and initialization inside the case statements:
 variable declaration/definition inside switch are allowed, both before and after the case labels
 
 best practice : if defining variables used in case statement, do so in a block inside the case.
 */

#include <iostream>

/// c was defined in case 1, it was used in case 2
/// all statements inside switch : considered to be part of the same scope
/// variable declared in one case : can be used in another later case, even if the case in which variable is defined is never executed
/// this is because the switch jumped over it
/// initialization of variables : require the definition to execute at runtime
/// initialization of variables : disallowed in any case that is not the last case, because initializer could be jumped over
/// this would leave the variable uninitialized
/// initialization of variables : disallowed before the first case, because those statements will never be executed
/// there is now way for the switch to reach them
void init_decl_def()
{
    switch (3)
    {
            int a;          /// definition allowed : OK
//            int b{5};       /// initialization not allowed before case labels : ILLEGAL
        case 1:
            int c;          /// definition allowed within the case : OK, but bad practice
            c = 10;         /// assignment allowed : OK
            std::cout << "CASE 1\n";
            break;
        case 2:
//            int d{15};      /// initialization not allowed, subsequent case 3 exists : ILLEGAL
            c = 11;         /// c is declared above but can be used here : OK
            std::cout << "CASE 2\n";
            break;
        case 3:
            std::cout << "CASE 3\n";
        {
            /// this case needs to define/initialize a variable
            /// so best practice is to do inside an explicit block underneath the case statement
            int x{2};
            std::cout << x << '\n';
            break;
        }
        default:
            std::cout << "DEFAULT CASE\n";
            break;
    }
}

/// example of fallthrough
/// all subsequent cases will execute starting from case 2
/// because no break or return statement provided
void fallthrough()
{
    switch (2)
    {
        case 1:     /// skipped, not matching
            std::cout << 1 << '\n';
        case 2:     /// execution starts here
            std::cout << 2 << '\n';
        case 3:     /// also executed
            std::cout << 3 << '\n';
        case 4:     /// also executed
            std::cout << 4 << '\n';
        default:    /// also executed
            std::cout << "DEFAULT EXECUTED" << '\n';
    }
}

void fallthrough_attribute()
{
    switch (2)
    {
        case 1:
            std::cout << 1 << '\n';
        case 2:
            std::cout << 2 << '\n';
            /// intentional fallthrough, semicolon at the end to indicate the null statement
            /// no warning should be triggered by the compiler now
            [[fallthrough]];
        case 3:
            std::cout << 3 << '\n';
        case 4:
            std::cout << 4 << '\n';
        default:
            std::cout << "DEFAULT EXECUTED" << '\n';
    }
}

/// sequential case labels
bool is_vowel(char c)
{
    switch (c)
    {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
            /// this is the first statement after the cases, if any of the case is true, then return true executes
            /// all cases share the same set of statements afterward
            /// this is not considered fallthrough behavior
            /// so [[fallthrough]] is not needed here
            return true;
        default:
            return false;
    }
}

/// in this example, the 2 statements between the case 1 and case 2 are scoped as part of the switch block
/// and not implicit block to case 1
void switch_scoping()
{
    switch (11)
    {
        case 1:     /// this case doesn't create an implicit block
            std::cout << "CASE 1" << '\n';  /// part of the switch scope, not implicit block to case 1
            break;  /// this is part of the switch scope, not an implicit block to case 1
        case 2:
            std::cout << "CASE 2" << '\n';
            break;
        default:
            std::cout << "DEFAULT CASE" << '\n';
            break;
    }
}

int calculate(int a, int b, char c)
{
    switch (c)
    {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '%':
            return a % b;
        default:
            std::cout << "INVALID OPERATOR\n";
            return 0;
    }
}

int main()
{
    fallthrough();
    
    fallthrough_attribute();
    
    std::cout << ((is_vowel('a')) ? "VOWEL" : "CONSONANT") << '\n';
    std::cout << ((is_vowel('e')) ? "VOWEL" : "CONSONANT") << '\n';
    std::cout << ((is_vowel('i')) ? "VOWEL" : "CONSONANT") << '\n';
    std::cout << ((is_vowel('o')) ? "VOWEL" : "CONSONANT") << '\n';
    std::cout << ((is_vowel('u')) ? "VOWEL" : "CONSONANT") << '\n';
    std::cout << ((is_vowel('A')) ? "VOWEL" : "CONSONANT") << '\n';
    std::cout << ((is_vowel('T')) ? "VOWEL" : "CONSONANT") << '\n';
    std::cout << ((is_vowel('I')) ? "VOWEL" : "CONSONANT") << '\n';
    std::cout << ((is_vowel('O')) ? "VOWEL" : "CONSONANT") << '\n';
    std::cout << ((is_vowel('U')) ? "VOWEL" : "CONSONANT") << '\n';
    
    switch_scoping();
    
    init_decl_def();
    
    std::cout << "ADD : " << calculate(2, 2, '+') << '\n';
    std::cout << "SUB : " << calculate(2, 2, '-') << '\n';
    std::cout << "MUL : " << calculate(2, 2, '*') << '\n';
    std::cout << "DIV : " << calculate(2, 2, '/') << '\n';
    std::cout << "MOD : " << calculate(2, 2, '%') << '\n';
    
    return 0;
}
