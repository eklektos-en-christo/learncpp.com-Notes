//
//  main.cpp
//  10.3_unscoped.enumeration.input.and.output
//
//  Created by Εκλεκτός εν Χριστώ on 3/5/23.
//

/*
 Enumerators : are symbolic constants
 
 Enumerators : are integral symbolic constants
 
 Enumerated types : actually hold an integral value
 
 When we define an enumerator : each enumerator is automatically assigned an integer value
 based on its position in the enumerator list
 
 by default - first enumerator is assigned the integral value 0, each subsequent enumerator
 has a value one greater than the previous enumerator
 
 it is possible to explicitly - define the value of enumerators, these integral values can
 be negative or positive, and can share the same value as other enumerators
 
 any non-defined enumerators : are given a value one greater than the previous enumerator
 
 when enumerators share the same value - they become non-distinct, which means they are
 interchangeable,
 
 best practice : avoid assigning explicit values to the enumerators unless you have a
 compelling reason to do so
 
 unscoped enumerations : will implicitly convert to integral values
 
 When an enumerated type is used in a function call or with an operator:
 compiler will first try to find a function or operator that matches the enumerated type,
 if it doesn't find then it will implicitly convert an unscoped enumeration or enumerator
 to its corresponding integer value
 
 -------------------------------------------------------------------------------------------
 How to print enumerator names?
 typical way to do this is to write a function that takes an enumerated type as a parameter
 and then outputs the corresponding string, returns the string to the caller,
 typical way to do this is to test our enumeration against every possible enumerator
 
 using if-else for this is inefficient, it requires multiple comparison before a match is
 found, more efficient way is to use a switch statement
 
 but creating and returning a std::string is expensive
 
 a more efficient option is to replace std::string with std::string_view which allows us to
 return string literals in a way that is much less expensive to copy
 
 -------------------------------------------------------------------------------------------
 Teaching operator<< how to print an enumerator:
 
 we can actually teach << to print the value of a program-defined enumeration by using
 operator overloading, similar to function overloading
 
 -------------------------------------------------------------------------------------------
 Enumeration size and underlying type(base):
 
 enumerators of an enumeration : are integral constants
 
 underlying type or base : specific integral type used to represent enumerators
 
 most compilers : will use int as the underlying type, which means unscoped enumeration will
 be the same size as an integer, unless a larger type is required to store the enumerator
 values
 
 it is possible : to specify the different underlying type
 
 example - if you're working in some specific bandwidth-sensitive context like sending data
 over a network, you may want to specify a smaller type
 
 best practice : specify the base type of an enumeration only when necessary
 
 warning : std::int8_t and std::uint8_t - usually type aliases for char types, using either
 of these types as the enum base will most likely cause the enumerators to print as char
 values rather than int values
 
 -------------------------------------------------------------------------------------------
 Integer to unscoped enumerator conversion:
 
 compiler - will implicitly convert unscoped enumerators to an integer
 
 but compiler - will not implicitly convert an integer to an unscoped enumerator, compiler
 error
 
 there are two ways to work around this:
 first- force the compiler to convert an integer to an unscoped enumerator using static_cast
 second- if an unscoped enumeration has a specified base, then compiler will allow to
 initialize(but not assign) an unscoped enumeration using an integer value
 
 -------------------------------------------------------------------------------------------
 Unscoped enumerator input:
 if unscoped enumeration is program-defined type - the language doesn't know how to input
 an unscoped enumerator using std::cin
 
 to work around this:
 we can read in an integer and use static_cast to convert the integer to an enumerator of
 the appropriate enumerated type
 
 we can also teach operator>> how to input an enum type using operator overloading
 */

#include <iostream>
#include <string_view>      /// C++17

/// each enumerator : automatically assigned an integer value based on its position in the enumerator list
/// each subsequent enumerator has a value one greater than the  previous enumerator
enum Color
{
    red,            /// assigned 0
    black,          /// assigned 1
    yellow,         /// assigned 2
    white,          /// assigned 3
    blue,           /// assigned 4
    green,          /// assigned 5
};

/// every time function is called, std::string is created and returned, which is expensive, inefficient
std::string get_color(Color color)
{
    switch (color)
    {
        case red: return "red";
        case black: return "black";
        case yellow: return "yellow";
        case white: return "white";
        case blue: return "blue";
        case green: return "green";
        default: return "???";
    }
}

/// constexpr - to be executed at compile time or runtime
constexpr std::string_view get_color_less_expensive(Color color)
{
    switch (color)
    {
        case red: return "red";
        case black: return "black";
        case yellow: return "yellow";
        case white: return "white";
        case blue: return "blue";
        case green: return "green";
        default: return "???";
    }
}

/// teaching operator<< how to print a Color
/// std::ostream is the type of std::cout
/// return type and parameter type are references - to prevent copies from being made
std::ostream& operator<<(std::ostream& out, Color color)
{
    switch (color)
    {
        case red: out << "red";         break;
        case black: out << "black";     break;
        case yellow: out << "yellow";   break;
        case white: out << "white";     break;
        case blue: out << "blue";       break;
        case green: out << "green";     break;
        default: out << "???";          break;
    }
    
    return out;
}

/// explicitly defining the vale of enumerators
/// integral values can be positive or negative
/// enumerators can share the same values as other enumerators
/// non-defined enumerators are given a value one greater than the previous enumerator
enum Animal
{
    cat = -3,       /// explicitly defining the value of enumerator
    dog,            /// assigned value -2
    pig,            /// assigned value -1
    horse = 5,
    elephant = 5,   /// shares same value as horse
    giraffe,        /// assigned value 6
    chicken,        /// assigned value 7
};

/// using 8-bit integer as the enum underlying type
enum Color_small : std::int8_t
{
    black_small = 65,
    red_small,
    blue_small,
};

/// base is specified as int
enum Pet : int
{
    cow,        /// 0
    sheep,      /// 1
    goat,       /// 2
};

int main()
{
    /// this actually stores the integral value 2
    Color banana{yellow};
    
    std::cout << banana << '\n';
    
    Animal my_animal{horse};
    Animal my_animal1{elephant};
    Animal my_animal2{dog};
    Animal my_animal3{chicken};
    
    /// enumerations : implicitly convert to integral values
    /// compiler will first try to compile the std::cout
    /// compiler will first look to see if operator<< knows how to print an object of type Animal
    /// std::cout : can't do that
    ///
    /// if compiler can't find a match:
    /// compiler will then implicitly convert an unscoped enumeration or enumerator to its
    /// corresponding integer value and the printed as integer value
    std::cout << my_animal << '\n';
    std::cout << my_animal1 << '\n';
    std::cout << my_animal2 << '\n';
    std::cout << my_animal3 << '\n';
    
    Color shirt{blue};
    
    std::cout << "The shirt is " << get_color(shirt) << '\n';
    
    /// constexpr to be executed at compile time or runtime
    constexpr Color your_shirt{blue};
    
    std::cout << "Your shirt is " << get_color_less_expensive(your_shirt) << '\n';
    
    /// works now
    /// << operator is overloaded to print the enumerators of type Color
    std::cout << "Your shirt is " << your_shirt << '\n';
    /// underlying size - 4 bytes
    std::cout << sizeof(your_shirt) << '\n';
    
    Color_small my_color{black_small};
    /// size of 1 byte - underlying type
    std::cout << sizeof(my_color) << '\n';
    
    /// underlying type : int8_t
    /// causes the enumerators to print as char values rather than int values
    std::cout << my_color << '\n';
    
    /// force converting an integer to a Color
    /// integer to unscoped enumerator conversion : static_cast
    Color apple{static_cast<Color>(5)};
    std::cout << apple << '\n';
    std::cout << static_cast<int>(apple) << '\n';
    std::cout << (apple == Color::green ? "YES" : "NO") << '\n';
    
    /// okay : can initialize with an integer because base is specified as an int in the enumeration definition
    Pet my_pet{0};
    /// error : can't assign with an integer value
//    my_pet = 2;
    
    std::cout << my_pet << '\n';
    
    std::cout << "Enter a pet: 0=cow, 1=sheep, 2=goat : ";
    
    int input{};
    std::cin >> input;
    
    /// using static_cast - to convert the integer to an enumerator of the Pet type
    Pet your_pet{static_cast<Pet>(input)};
    std::cout << (your_pet == goat ? "You have a goat!" : "NO") << '\n';
    
    return 0;
}
