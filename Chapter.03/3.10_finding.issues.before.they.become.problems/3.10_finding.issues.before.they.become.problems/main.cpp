//
//  main.cpp
//  3.10_finding.issues.before.they.become.problems
//
//  Created by εκλεγμένοι εν Χριστώ on 9/11/22.
//

/*
 Don’t make errors:
 Follow best practices
 Don’t program when tired
 Understand where the common pitfalls are in a language
 Keep your programs simple
 Don’t let your functions get too long
 Prefer using the standard library to writing your own code,
 when possible
 Comment your code liberally
 
 Refactoring your code: making structural changes to your
 code without changing its behavior, this makes code more
 organized, modular/performant
 
 functions less than ten lines are good
 Functions that are less than five lines are even better.
 
 Key insight

 When making changes to your code, make behavioral changes OR structural changes, and then retest for correctness. Making behavioral and structural changes at the same time tends to lead to more errors as well as errors that are harder to find.
 
 defensive programming: practice whereby the programmer tries to anticipate all of the ways the software could be misused, either by end-users, or by other developers (including the programmer themselves) using the code. These misuses can often be detected and then mitigated (e.g. by asking a user who entered bad input to try again).
 
 Finding errors fast: The best way to do this is to program a little bit at a time, and then test your code and make sure it works.
 
 testing functions: write testing functions to “exercise” the
 code you’ve written.
 
 unit testing: software testing method by which small units of source code are tested to determine whether they are correct.
 
 constraints: involve the addition of some extra code,
 to check that some set of assumptions or expectations are not violated.
 common method of doing this is via assert and static_assert

 static analysis tools/linters:
 programs that analyze your code to identify specific semantic issues (in this context, static means that these tools analyze the source code).
 
 Best practice

 Use a static analysis tool on your programs to help find areas where your code is non-compliant with best practices.
 */
