//
//  main.cpp
//  10.12_summary.and.quiz
//
//  Created by Εκλεκτός εν Χριστώ on 3/15/23.
//

/*
 program-defined/user-defined type - custom type that we can create for use in our own
 programs
 
 enumerated types and class types - allow for creation of program-defined types
 
 program-defined types - must be defined before they can be used
 
 type definition - definition of a program-defined type
 
 type definitions - exempt from one definition rule
 
 enumeration/enum - compound data type where every possible value is defined as a symbolic
 constant called an enumerator
 
 enumerators - distinct types, compiler can differentiate it from other types(unlike type
 aliases)
 
 Unscoped enumerations - they put their enumerator names into the same scope as the
 enumeration definition itself as opposed to creating a new scope region like a namespace
 does
 
 Unscoped enumerations - provide a named scope region for their enumerators
 
 Unscoped enumerations - will implicitly convert to integral values
 
 Scoped enumerations - similar to unscoped enumerations but are strongly typed(no implicit
 conversion to integers) and strongly scoped(enumerators are placed only into the scope
 region of the enumeration)
 
 Struct/structure - program-defined type, allows us to bundle multiple variables together
 into a single type
 
 Data members/member variables - variables that are part of the struct/class
 
 Member selection operator. - to access a specific member variable(for normal structs and
 references to structs)
 
 Member selection from pointer operator-> - for pointers to structs
 
 Aggregate/aggregate data type - any type that can contain multiple data members
 
 Aggregates - in cpp, arrays and structs with only data members
 
 Aggregate initialization - a form of initialization that aggregates use, it allows to
 directly initialize the members of aggregates
 
 Initializer list - a list of comma-separated values used to initialize an aggregate
 
 Member-wise initialization - each member in the struct is initialized in the order of
 declaration
 
 Designated initializers - allow to explicitly define which initialization values map to
 which members, the members must be initialized in the order in which they are declared in
 the struct, otherwise an error will result
 
 Non-static member initialization/default member initializer - when we define a struct/class
 type, we can provide a default initialization value for each member as part of the type
 definition
 
 Padding - for performance reasons, compiler sometimes add gaps into structures, so the size
 of the structure may be larger than the sum of the size of its members
 
 Class template - template definition for instantiating class types
 
 CTAD(class template argument deduction) - C++17 feature that allows the compiler to deduce
 the template type arguments from an initializer
 
 
 */

#include <iostream>

enum class Monstertype
{
    ogre,
    dragon,
    orc,
    giant_spider,
    slime,
};

struct Monster
{
    Monstertype type{};
    std::string name{};
    int health{};
};

constexpr std::string_view get_monstertype_string(Monstertype type)
{
    switch (type)
    {
        case Monstertype::ogre:         return "Ogre";
        case Monstertype::dragon:       return "Dragon";
        case Monstertype::orc:          return "Orc";
        case Monstertype::giant_spider: return "Giant Spider";
        case Monstertype::slime:        return "Slime";
    }
    
    return "Unknown";
}

void print_monster(const Monster& monster)
{
    std::cout << "This " << get_monstertype_string(monster.type) << " is named " << monster.name << " and has " << monster.health << " health.\n";
}

template <typename T>
struct Triad
{
    T first{};
    T second{};
    T third{};
};

/// deduction guide
/// Triad with three arguments of same type T should deduce to a Triad<T>
template <typename T>
Triad(T, T, T) -> Triad<T>;

template <typename T>
void print(const Triad<T>& triad)
{
    std::cout << '[' << triad.first << ", ";
    std::cout << triad.second << ", ";
    std::cout << triad.third << ']' << '\n';
}

int main()
{
    Monster ogre{Monstertype::ogre, "Torg", 144};
    Monster slime{Monstertype::slime, "Blurp", 22};
    
    print_monster(ogre);
    print_monster(slime);
    
    Triad t1{1, 2, 3};
    print(t1);
    
    Triad t2{1.1, 2.22, 3.1};
    print(t2);
    
    return 0;
}
