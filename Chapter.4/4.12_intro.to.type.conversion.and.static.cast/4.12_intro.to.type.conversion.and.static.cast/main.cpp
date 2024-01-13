//
//  main.cpp
//  4.12_intro.to.type.conversion.and.static.cast
//
//  Created by εκλεγμένοι εν Χριστώ on 9/18/22.
//

/*
 type conversion: process of converting a value from one type
 to another type.
 
 implicit type conversion: when compiler performs type
 conversion with asking us explicitly
 
 type conversion produces a new value:
 Type conversion produces a new value of the target type from
 a value of a different type.
 
 int to double: safe to make
 double to int: unsafe, may result in value being changed
 during conversion
 
 brace initialization: unsafe implicit conversions will
 typically either generate a compiler warning/error in case of
 brace initialization.
 
 brace initialization: will ensure we don't try to initialize
 a variable with an initializer that will lose data when it
 is implicitly converted
 
 Explicit type conversion: allows programmer to explicitly
 tell the compiler to convert a value from one type to another
 type, and that we take full responsibility for the result
 of that conversion, if result is loss of data then it's our
 fault not compiler's.
 
 static_cast: operator
 syntax:
        static_cast<new_type>(expression)
 
 expression - as input, returns a value
 new_type - returned value will be converted to the type
 specified inside <>
 <> - between < > goes the type, that's how C++ deals with
 the code that needs a parameterized type.
 
 treat warnings an an error: shouldn't be disabled, we may
 overlook warning about more serious issues, explicit type
 conversion can be used in its place
 
 To convert an unsigned number to a signed number, you can
 also use the static_cast operator.
 
 Warning:
 The static_cast operator will produce undefined behavior if
 the value being converted doesn’t fit in range of the
 new type.
 
 std::int8_t and std::uint8_t likely behave like chars instead
 of integers
 */

#include <iostream>

void print(double x)
{
    std::cout << x << '\n';
}

void print_int(int x)
{
    std::cout << x << '\n';
}

int main()
{
    /// implicit type conversion, passed int literal
    /// 2 will be converted to 2.0 and then copied
    /// to the parameter
    print(2);
    
    /// implicit type conversion to int, passed double literal
    /// fractional component is dropped
    print_int(2.2);
    
    /// error: brace initialization will ensure we don't try to initialize a
    /// variable that will lose data when it is implicitly converted
    double d{2};        /// int to double: safe
//    int i{2.2};         /// double to int: unsafe
    
    /// unsafe: but handled with static cast, which converted
    /// the double value into an integer value
    /// compiler won't generate a warning or error here
    int i{static_cast<int>(4.1)};
    
    /// cout prints the char values as chars
    char c{66};
    std::cout << c << '\n';
    
    /// printing the char values as integers using static cast
    /// static_cast doesn't affect the original value,
    /// char is still a char
    /// so, argument to static_cast evaluates as an expression
    /// c is evaluated to produce its value, then converted to integer
    std::cout << static_cast<int>(c) << '\n';
    
    /// u means 22 as an unsigned int
    unsigned int ui{22u};
    /// unsigned ui to signed integer si
    int si{static_cast<int>(ui)};
    std::cout << si << '\n';
    
    /// static_cast: doesn't do range checking
    /// undefined behavior: if the value casted to a type whose
    /// range doesn't contain that value
//    int16_t i16{static_cast<int>(ui)};
    
    /// std::int8_t and std::uint8_t likely behave like chars instead of integers
    int8_t i8{65};
    std::cout << i8 << '\n';    /// prints 'A'
    /// solution: prints 65 instead of 'A'
    std::cout << static_cast<int>(i8) << '\n';
    
    
    /// In cases where std::int8_t is treated as a char, input from the console can
    /// also cause problems
    /// In contrast, the other fixed-width types will always print and input as
    /// integral values.
    std::cout << "Enter a number between 0-255: ";
    int8_t input{};
    std::cin >> input;
    
    std::cout << static_cast<int>(input) << '\n';
    
    std::cout << "Enter a single character: ";
    char single_char{};
    std::cin >> single_char;
    
    std::cout << "You entered " << single_char;
    std::cout << ", its ASCII value is ";
    std::cout << static_cast<int>(single_char) << '\n';
    
    int ascii{single_char};
    std::cout << "ascii: " << ascii << '\n';
    
    return 0;
}
