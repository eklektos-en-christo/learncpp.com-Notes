//
//  main.cpp
//  1.4_variable.assignment.and.initialization
//
//  Created by Judah's Leon on 7/14/22.
//

/*
 variable assignment : after the variable has been defined, we can give it a value in a
 separate statement using = operator
 this process is copy assignment or assignment
 Copy assignment is named such because it copies the value on the right-hand side of the = operator to the variable on the left-hand side of the operator. The = operator is called the assignment operator.
 
 Normal variables can only hold one value at a time.
 
 both are different
 = assignment operator
 == equality operator
 */

/*
 Initialization : instead of using two statement for definition and assignment we can combine
 both. this is called initialization. the value used to initialize a variable is initializer
 */

/*
 default initialization : when no initializer is given it is called default initialization
 it leaves variable with an indeterminate value
 
 */

/*
 copy initialization : when initializer is provided after an equals sign
 For simple types like int, copy initialization is efficient. However, when types get more complex, copy initialization can be inefficient.
 
 direct initialization : when initializer is provided inside parenthesis
 For simple data types (like int), copy and direct initialization are essentially the same. For more complicated types, direct initialization tends to be more efficient than copy initialization.
 
 brace initialization : direct initialization can't be used for all types of initialization
 so brace initialization is used. also it is uniform/list initialization
 Brace initialization has the added benefit of disallowing “narrowing” conversions.
 */


/*
 value initialization and zero initialization:
 When a variable is initialized with empty braces, value initialization takes place. In most cases, value initialization will initialize the variable to zero (or empty, if that’s more appropriate for a given type). In such cases where zeroing occurs, this is called zero initialization.
 */

/*
 Initialize your variables :
 Initialize your variables upon creation. You may eventually find cases where you want to ignore this advice for a specific reason (e.g. a performance critical section of code that uses a lot of variables), and that’s okay, as long the choice is made deliberately.
 */


#include<iostream>

int main()
{
    int width;      // definition
    width = 2;      // assignment or copy assignment
    width = 7;      // previous value is overwritten
    
    int length = 22;    // 22 : initializer, initial value at the time of definition
    std::cout<<length<<std::endl;
    
    
    // 4 ways to initialize variable in cpp are
    int a;          // no initializer
    int b = 2;      // initializer after assignment operator
    int c(22);      // initializer in parenthesis
    int d{33};      // initializer in braces
    
    int e = 22;     // copy initialization, copies 22 to e
    int f(22);      // direct initialization,
    
    // three forms of brace initialization
    int g{22};      // direct brace initialization - preferred
    int h = {22};   // copy brace initialization
    int i {};       // value initialization
    int j(2.2);     // would drop fractional part, so brace initialization is better
    int k = 2.2;    // would drop fractional part, ,,   ,,      ,,      ,,      ,,
    //int l{2.2};     // not allowed, give error, but better if some data is losing
    
    /*Best practice
    Favor initialization using braces whenever possible.*/
    /*
     C++ does not support a direct or brace assignment syntax.
     */
    
    int l{};        // value init. with zero or empty if that's more appropriate for given type
                    // initialization in which zero occurs is called zero initialization
    
    // cases: when to use {0} and {}
    // if you're using that value immediately then
    int m{0};
    std::cout<<m<<std::endl;
    
    // if the value is temporary and will change then
    int n{};
    std::cin>>n;
    
    
    /*
     Best practice

     Initialize your variables upon creation.
     */
    
    
    //Initializing multiple variables
    int o = 22, p = 22;
    int q, r = 22;      // bad practice
    int s(22), t(22);
    int u(22), v{22};   // preferred - brace initialization and direct are more clear
    
    
    // again : direct brace initialization is preferred
}

