//
//  main.cpp
//  8.4_arithmetic.conversions
//
//  Created by εκλεγμένοι εν Χριστώ on 2/11/23.
//

/*
 In CPP : certain operators require that their operands be of the same type, if one of these
 operators is invoked with operand of different types, one or both the operands will be
 implicitly converted to matching types using a set of rules called the usual arithmetic
 conversions
 
 Operators the require operands of the same type:
 binary arithmetic operators : +, -, *, /, %
 binary relational operators : <, >, <=, >=, ==, !=
 binary bitwise arithmetic operators : &, ^, |
 conditional operator : ?:(condition excluded, condition is expected to be of type bool)
 
 Arithmetic conversion rules: pretty simple, compiler has a prioritized list of types that
 look something like this below-
 -long double(highest priority)
 -double
 -float
 -unsigned long long
 -long long
 -unsigned long
 -long
 -unsigned int
 -int(lowest priority)
 
 there are two rules only:
 -if type of at least one of the operands is on the priority list, operand with lower
 priority is converted to the type of the operand with higher priority
 -if type of neither operand is on the list, both operands are numerically promoted
 
 typeid : operator, included in <typeinfo> header, shows the resulting type of an expression
 typeid.name() : output is left up to the compiler
 
 prioritization hierarchy : can cause some problematic issues when mixing signed and
 unsigned values
 
 Avoid using unsigned integers mixed with signed integers in arithmetic
 expressions
 */

#include <iostream>
#include <typeinfo>

int main()
{
    std::cout << sizeof(long double) << '\n';
    std::cout << sizeof(double) << '\n';
    std::cout << sizeof(float) << '\n';
    std::cout << sizeof(unsigned long long) << '\n';
    std::cout << sizeof(long long) << '\n';
    std::cout << sizeof(unsigned long) << '\n';
    std::cout << sizeof(long) << '\n';
    std::cout << sizeof(unsigned int) << '\n';
    std::cout << sizeof(int) << '\n';
    
    int i{2};
    double d{3.2};
    /// this shows the type of i + d
    /// double operand d has the highest priority
    /// int is converted to double value 2.0, then added both which resulted in 5.2
    std::cout << typeid(i + d).name() << ' ' << i + d << '\n';
    
    short s_a{10};
    short s_b{20};
    /// neither operand appears on the priority list
    /// both short operands undergo integral promotion to type int
    std::cout << typeid(s_a + s_b).name() << ' ' << s_a + s_b << '\n';
    
    /// signed and unsigned issue below
    /// 5u : unsigned integer
    /// unsigned int : has higher priority
    /// so int is converted to an unsigned int
    /// -5 : is out of range of an unsigned int, so unexpected result
    std::cout << typeid(5u - 10).name() << 5u - 10 << '\n';
    
    /// 5 is greater than -3
    /// -3 is converted to large unsigned int which is larger than 5, so unexpected result
    /// that's why avoid using unsigned integers mixed with signed integers in arithmetic expressions
    /// compiler probably won't even issue a warning
    std::cout << std::boolalpha << (-3 < 5u) << '\n';
    
    std::cout << static_cast<unsigned int>(-3) << '\n';
    
    return 0;
}
