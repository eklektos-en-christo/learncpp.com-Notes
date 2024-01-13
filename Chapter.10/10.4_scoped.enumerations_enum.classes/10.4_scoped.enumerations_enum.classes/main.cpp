//
//  main.cpp
//  10.4_scoped.enumerations_enum.classes
//
//  Created by Εκλεκτός εν Χριστώ on 3/6/23.
//

/*
 unscoped enumerations : distinct types but are not type safe, in some cases they will allow
 to do things that don't make sense
 
 
 Scoped enumerations/enum class - work similarly to unscoped enumerations but have two
 primary differences:
 -they are strongly typed : won't implicitly convert to integers
 -they are strongly scoped: enumerators are only placed into the scope region of the
 enumeration
 
 to use the scoped enumeration -
 we use the keywords : enum class
 rest of the definition is same as unscoped enumeration
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 As an aside-
 class keyword along with static keyword : is one of the most overloaded keywords in C++
 language and can have different meanings depending on context
 although : scoped enumeration use class keyword but scoped enumeration isn't considered to
 be a class type, class type is reserved for structs, classes and unions
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Scoped enumerations : define their own scope regions
 
 unscoped enumerations - place their enumerators in the same scope as the enumeration itself
 
 scoped enumerations - place their enumerators only in the scope region of the enumeration
 
 scoped enumerations : act like a namespace for their enumerators, this built in namespacing
 helps reduce global namespace pollution and the potential for name conflicts when scoped
 enumerations are used in the global scope
 
 to access a scoped enumerator : we do so just as if it was in a namespace having the same
 name as the scoped enumeration
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Scoped enumerations : don't implicitly convert to integers
 
 note : you can still compare enumerators from within the same scoped enumeration, because
 they are of same type
 
 there are cases occasionally - when it is useful to be able to treat a scoped enumerator
 as an integer, in these cases a scoped enumerator can be explicitly converted to an int
 by using static_cast
 
 you can also - convert an int to a scoped enumerator using static_cast which can be useful
 when inputting from the user
 
 As of C++17, you can initialize a scoped enumeration using an integral value without the
 static_cast (and unlike an unscoped enumeration, you don’t need to specify a base).
 
 best practice :
 favor scoped enumerations over unscoped enumerations unless there's a compelling reason to
 do otherwise
 
 unscoped enumerations : still commonly used in cpp, there are situations when we desire the
 implicit conversion to int, doing lots of static casting get annoying, and we don't need
 the extra namespacing
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Easing the conversion of scoped enumerators to integers:
 
 if we need to convert a scoped enumeration to integers often - static_cast can clutter the
 code significantly, a useful hack is to overload unary operator+ to perform this conversion
 
 this method prevents unintended implicit conversions to an integral value, but provides a
 convenient way to explicitly request such conversions as needed
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 using enum statements :
 using enum statement imports all of the enumerators from an enum into the current scope
 when used with an enum class type, this allows to access the enum class enumerators without
 having to prefix each with the name of the enum class
 
 this can be useful in cases where we would otherwise have many identical, repeated prefixes
 such as within a switch  statement
 */

#include <iostream>
#include <string_view>

enum class Animals
{
    chicken,
    dog,
    cat,
    elephant,
    duck,
    snake,
};

/// overloading the unary + operator to convert Animals to the underlying type
constexpr auto operator+(Animals a) noexcept
{
    return static_cast<std::underlying_type_t<Animals>>(a);
}

enum class Color
{
    black,
    red,
    blue,
};

///// C++20
///// this saves from having multiple, redundant, obvious prefixes inside switch statement
//constexpr std::string_view get_color(Color color)
//{
//    /// C++20 - standard
//    /// this brings all color enumerators into current scope
//    /// we can now access the enumerators of color without using a Color:: prefix
//    using enum Color;
//
//    switch (color)
//    {
//        case black: return "black";
//        case red: return "red";
//        case blue: return "blue";
//        default: return "????";
//    }
//}

enum class Animal
{
    pig,
    chicken,
    goat,
    cat,
    dog,
    duck,
};

constexpr std::string_view get_animal_name(Animal a)
{
    switch (a)
    {
        case Animal::pig: return "pig";
        case Animal::chicken: return "chicken";
        case Animal::goat: return "goat";
        case Animal::cat: return "cat";
        case Animal::dog: return "dog";
        case Animal::duck: return "duck";
        default: return "no such animal\n";
    }
}

void print_no_of_legs(Animal a)
{
    std::cout << "A " << get_animal_name(a) << " has ";
    
    switch (a)
    {
        case Animal::chicken:
        case Animal::duck:
            std::cout << 2;
            break;
        case Animal::pig:
        case Animal::goat:
        case Animal::cat:
        case Animal::dog:
            std::cout << 4;
            break;
        default:
            std::cout << "???";
            break;
    }
    
    std::cout << " legs.\n";
}

int main()
{
    /// scoped enumeration, not unscoped enumeration
    /// enum class : keyword defines a scoped enumeration
    enum class Color
    {
        /// red and blue are considered part of Color's scope region
        red,
        blue,
    };
    
    enum class Fruit
    {
        /// banana and orange are considered part of Fruit's scope region
        banana,
        orange,
    };
    
    /// red and banana are not directly accessible
    /// we have to use ::
    Color clr{Color::red};
    Fruit frt{Fruit::banana};
    
    /// compiler error : compiler doesn't know how to compare different types - Color and Fruit
    /// scoped enumeration : won't convert to any type that can be compared with another type
    /// no conversion here
//    if (clr == frt)
//        std::cout << "color and fruit are equal\n";
//    else
//        std::cout << "color and fruit are not equal\n";
//
    
    /// compiler error : orange is not defined in this scope region
    /// scoped enums : strongly scoped
//    std::cout << orange << '\n';
    
    /// compiler error : std::cout doesn't know how to print this
    /// no conversion from Fruit to int
    /// scoped enums : strongly typed
//    std::cout << Fruit::orange << '\n';
    
    /// scoped enums : strongly scoped
    Color color1{Color::blue};
    Fruit fruit1{Fruit::banana};
    
    /// this comparison is okay - comparing the enumerators from within the same scoped enumeration
    if (clr == Color::red)
        std::cout << "Your shirt is red!\n";
    else
        std::cout << "Your shirt is not red!\n";
    
    /// won't work - no implicit conversion to int - scoped enumeration
//    std::cout << fruit1 << '\n';
    
    /// will work - explicit conversion to int - scoped enumeration
    std::cout << static_cast<int>(fruit1) << '\n';
    
    std::cout << "Enter a Fruit 0=banana, 1=orange : ";
    
    int input{};
    std::cin >> input;
    
    /// static cast an integer to a Fruit
    Fruit fruit2{static_cast<Fruit>(input)};
    
    /// C++17 - scoped enumeration can be initialized using an integral value
    /// without static_cast, and also there is not need to specify a base as it is done in unscoped enumerations
    Fruit fruit3{input};
    
    /// Animals::snake to an integer using unary operator+
    std::cout << "underlying type: " << +Animals::snake << '\n';
    
    print_no_of_legs(Animal::cat);
    print_no_of_legs(Animal::duck);
    
    return 0;
}
