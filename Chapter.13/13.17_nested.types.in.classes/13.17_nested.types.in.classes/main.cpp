//
//  main.cpp
//  13.17_nested.types.in.classes
//
//  Created by Εκλεκτός εν Χριστώ on 7/17/23.
//

/*
 Nesting types: types can also be defined/nested inside of a class, to do this simply define
 the type inside the class, under the appropriate access specifier
 
 Classes: essentially act as a namespace for any nested types
 
 Nested class in C++: doesn't have access to this pointer of the outer class
 
 Nested classes: can't directly access the members of the outer class
 
 Nested classes: are members of of the outer class, they can access any private members of
 the outer class that are in scope, e.g. an object of the outer class is passed as an
 argument to the nested class
 
 Nested types: they can't be forward declared
 */

#include <iostream>

class Fruit
{
public:
    /// FruitType type is defined inside the class
    /// defined it under the public access specifier
    /// so that the type definition can be accessed from outside the class
    /// enum classes: also act like namespaces, so used enum instead of enum classes
    enum FruitType
    {
        apple,
        banana,
        cherry,
    };
    
private:
    FruitType m_type {};
    int m_percentage_eaten { 0 };
    
public:
    Fruit(FruitType type) : m_type{ type } {}
    
    FruitType get_type() { return m_type; }
    int get_percentage_eaten() { return m_percentage_eaten; }
};

int main()
{
    /// we can access the FruitType via Fruit now using :: operator
    Fruit apple { Fruit::apple };
    
    if (apple.get_type() == Fruit::apple)
        std::cout << "I'm an apple.\n";
    else
        std::cout << "I'm not an apple.\n";
    
    return 0;
}
