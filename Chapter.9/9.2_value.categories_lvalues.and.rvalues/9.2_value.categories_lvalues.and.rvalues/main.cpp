//
//  main.cpp
//  9.2_value.categories_lvalues.and.rvalues
//
//  Created by εκλεγμένοι εν Χριστώ on 2/20/23.
//

/*
 Expressions can do one more thing : evaluate to objects or functions
 
 Properties of an expression : they have two properties
 -a type category
 -a value category
 
 ___________________________
 Type of an expression: equivalent to the type of the value, object or function that results
 from the expression
 
 compiler : can use the type of an expression to determine whether an expression is valid in
 a given context
 
 Type of the expression: must be determinable at compile time
 Value of an expression: may be determined at either compile time(constexpr expression)
 or runtime(non-constexpr expression)
 ___________________________
 Value of an expression/sub-expression: indicates whether an expression resolves to a value,
 a function or an object of some kind
 ---------------------------
 
 Prior to cpp11, only two possible value categories : lvalue and rvalue
 In cpp11, 3 additional value categories : glvalue, prvalue and xvalue - to support move
 semantics
 
 ___________________________
 L-value and R-value expressions:
 
 L-value/left value/locator value/lvalue : an expression that evaluates to an identifiable
 object or function or bit field
 
 entity(such as an object or function) : that has an identity can be differentiated from
 other similar entities(typically by comparing the addresses of the entity)
 
 Entities with identities : can be accessed via an identifier, reference or pointer, their
 lifetime is typically longer than a single expression or statement
 
 L-values : come in two subtypes-
 -modifiable lvalue : whose value can be modified
 -non-modifiable lvalue : whose value can't be modified, lvalue is const or constexpr
 ___________________________
 R-value/right value/rvalue : an expression that is not an l-value
 
 commonly seen rvalues : literals(except c-style string literals), return value of functions
 and operators
 
 R-values : aren't identifiable, they have to be used immediately, only exist within the
 scope of the expression in which they are used
 
 an assignment operation : requires the left operand to be a modifiable lvalue expression
 and right operand to be a rvalue expression
 ___________________________
 L-value to R-value conversion :
 lvalues will implicitly convert to rvalues, so lvalue can be used whenever an rvalue is
 required
 
 Key insight:
 how identify lvalue and rvalue expressions?
 lvalue expressions : that evaluate to variables/identifiable objects, that persist beyond
 the end of the expression
 rvalue expressions : that evaluate to literals/returned values of functions and operators
 that are discarded at the end of the expression
 
 */

#include <iostream>

void print(int x)
{
    std::cout << x << '\n';
}

int return_five()
{
    return 5;
}

int main()
{
    /// int / int > int
    /// int : is the type of this expression
    auto v1{12 / 4};
    
    /// double / int > double
    /// double : is the type of this expression
    auto v2{12.0 / 4};
    
    /// type of this expression does not match
    /// no conversion can be found
    /// print(int) : expecting an int parameter
//    print("foo");
    print(2);
    
    int x{};
    /// valid
    x = 2;
    /// error : assigning the value of x to a literal
    /// fails : because 2 isn't an lvalue, its rvalue expression
    /// x : is a modifiable lvalue expression
//    2 = x;
    
    int a{8};
    
    /// a is an lvalue expression
    /// it evaluates to variable a which has an identifier
    int b{a};
    
    int i{};
    const double d{};
    
    /// i : modifiable lvalue expression
    int j{i};
    /// d : non-modifiable lvalue expression
    const double e{d};
    
    /// 2 : rvalue expression, temporary value
    int x1{2};
    /// 11.2 : rvalue expression, temporary value
    const double d1{11.2};
    /// x1 : modifiable lvalue expression
    int y2{x1};
    /// e2 : non-modifiable lvalue expression
    const double e2{d1};
    /// return_five() : rvalue expression, result is returned by value, temporary value
    int z{return_five()};
    /// x1 + 1 : rvalue expression, temporary value
    int w{x1 + 1};
    /// static casting d to an int : rvalue expression, temporary value
    int q{static_cast<int>(d)};
    
    int m{2};
    int n{3};
    
    /// legal
    /// n : modifiable lvalue, not an rvalue
    m = n;
    
    /// m is being used in two different contexts
    /// on left side, m : is modifiable lvalue expression, evaluates to 3
    /// on right side, m + 1 : is rvalue expression, evaluates to 4
    m = m + 1;
    std::cout << m << '\n';
    
    return 0;
}
