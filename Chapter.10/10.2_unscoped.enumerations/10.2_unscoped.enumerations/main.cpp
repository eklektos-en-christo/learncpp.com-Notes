//
//  main.cpp
//  10.2_unscoped.enumerations
//
//  Created by Εκλεκτός εν Χριστώ on 3/5/23.
//

/*
 Enumeration/enumerated type/enum : compound data type, where every possible value is
 defined as a symbolic constant called an enumerator
 
 enumerations : program-defined type, each enumeration needs to be defined before its use
 to create objects using that enumerated type
 
 Two kinds of enumerations : unscoped and scoped
 
 -------------------------------------------------------------------------------------------
 Unscoped enumerations : defined via enum keyword
 enum - keyword
 
 to define an unscoped enumeration-
 use enum keyword followed by the name, inside a pair of curly braces we define the
 enumerators for the name type, these enumerators specify the set of possible values that
 objects of type name will be able to hold, each enumerator must be separated by a comma,not
 a semicolon, trailing comma after the last enumerator is optional but recommended for
 consistency, type definition must end with a semicolon
 
 initializer for an enumerated type : must be one of the defined enumerators for that type
 
 enumeration : program-defined type
 enumerator  : is a symbolic constant that is a possible value for a given enumeration
 
 -------------------------------------------------------------------------------------------
 Naming enumerations and enumerators:
 convention - name of the enumerated types start with a capital letter
 
 warning
 enumerations don't have to be named, but unnamed enumerations should be avoided in modern
 cpp
 
 Enumerators : must be given names
 common choices for enumerator names - start with lower case e.g. red
                                       start with caps e.g. Red
                                       all caps e.g. RED
                                       all caps with a prefix e.g. COLOR_RED
                                       prefixed with a "k" and inter-capped e.g. kColorRed
 
 all caps : may conflict with preprocessor macros
 avoid : all caps naming conventions
 avoid : all conventions starting with a capital letter, reserved for program-defined types
 
 best practice:
 name the enumerated types starting with a capital letter
 name the enumerators starting with a lower case letter
 
 -------------------------------------------------------------------------------------------
 Enumerated types : are distinct types
 
 each created enumerated type : is a distinct type, compiler can distinguish it from other
 types
 
 typedefs and type aliases : considered non-distinct from the types they are aliasing
 
 enumerators defined as part of one enumerated type : can't be used with the objects of
 another enumerated type
 
 -------------------------------------------------------------------------------------------
 Putting enumerations to use:
 
 enumerators are : descriptive
 enumerators : enhances code documentation and readability
 
 enumerated types : best used when you have a smallish set of related constants and objects
 only need to hold one of those values at a time
 
 commonly defined enumerations include : days of the week,  cardinal directions, suits in a
 deck of cards
 
 boolean : is essentially just an enumeration of 2 enumerators - false and true, but in C++
 true and false are defined as keywords instead of enumerators
 
 -------------------------------------------------------------------------------------------
 The scope of unscoped enumerations:
 
 unscoped enumerations : named such because they put their enumerator names into the same
 scope as the enumeration itself
 
 global enumerations : pollute the global scope and significantly raise the chances of
 naming collisions
 
 unscoped enumerations : also provide a named scope region for their enumerators, much like
 a namespace acts as a named scope region for the names declared within, this means we can
 access the enumerators of an unscoped enumeration as follows in main()
 
 most often : unscoped enumeration are accessed without using the scope resolution operator
 
 -------------------------------------------------------------------------------------------
 Avoiding enumerator naming collisions:
 few common ways to prevent unscoped enumerator naming collisions-
 -prefix each enumerator with the name of the enumeration itself : this still pollutes the
 namespace but reduces the change for naming collisions by making the names longer and more
 unique
 -put the enumerated type inside something that provides a separate scope region, like a
 namespace : we now have to prefix our enumeration and enumerator names with the name of
 the scoped region.
 
 classes : also provide a scope region, it's common to put enumerated typed related to class
 inside the scope region of the class
 
 best practice:
 -prefer putting enumerations inside a named scope region, such as a namespace or class, so
 the enumerators don't pollute the global namespace
 
 if the enumeration is only used within the single function - enumeration should be defined
 inside the function, this limits the scope of the enumeration and its enumerators to just
 that function, the enumerators of such enumeration will shadow/hides identically named
 enumerators defined in the global scope
 
 -------------------------------------------------------------------------------------------
 Comparing against enumerators:
 we can use the equality operators == and != to test whether an enumeration has the value of
 a particular enumerator or not.
 
 this way we can conditionalize the program's behavior based on what enumerator our
 enumeration is holding
 */

#include <iostream>

/// new unscoped enumeration named Color
/// this enum is defined in the global namespace
enum Color
{
    /// red, green and blue : enumerators
    /// red, green and blue : these symbolic constants define all the possible values this type can hold
    /// each enumerator : separated by a , and not by a ;
    /// red, green and blue  are put into the global scope because enumeration Color is in global namespace
    red,
    green,
    blue,       /// trailing comma : optional but recommended
};  /// definition : must end with a semicolon

enum Pet
{
    lion,
    tiger,
    whale,
    elephant,
};

enum Days_of_week
{
    sunday,
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
};

enum Cardinal_directions
{
    north,
    east,
    south,
    west,
};

enum Card_suits
{
    clubs,
    diamonds,
    hearts,
    spades,
};

enum File_read_result
{
    read_result_success,
    read_result_error_file_open,
    read_result_error_file_read,
    read_result_error_file_parse,
};

/// function returning a status code
File_read_result read_file_contents()
{
    return read_result_success;
}

/// Enumerated types can also be put to good use in games
enum Item_type
{
    sword,
    torch,
    potion,
};

enum Sort_order
{
    alphabetical,
    alphabetical_reverse,
    numerical,
};

/// when user needs to make a choice between two or more options
void sort_data(Sort_order order)
{
    if (order == alphabetical)
        std::cout << "Sorting in alphabetical order!\n";
    else if (order == alphabetical_reverse)
        std::cout << "Sorting in alphabetical reverse order!\n";
    else if (order == numerical)
        std::cout << "Sorting in numerical order!\n";
}

enum Feeling
{
    sad,
    happy,
    /// error : the name 'blue' conflicts with the another 'blue' enumerator in the global scope
//    blue,
};

/// fix one : prefixing each enumerator with the name of the enumeration itself
enum Feeling2
{
    Feeling2_sad,
    Feeling2_happy,
    Feeling2_blue,      /// blue no longer has a naming collision with Color::blue
};

/// fix two : putting the enumerated type inside a namespace to avoid naming conflict with global enumerations
namespace color
{
    enum Color
    {
        red,
        green,
        blue,
    };
}

/// fix two : putting the enumerated type inside a namespace to avoid naming conflict with global enumerations
namespace feeling
{
    enum Feeling
    {
        sad,
        happy,
        blue,   /// doesn't collide with global blue
    };
}

namespace monster
{
    enum Monster_type
    {
        orc,
        goblin,
        troll,
        ogre,
        skeleton,
    };
}

int main()
{
    /// few variables of enumerated type Color instantiated
    Color apple{red};
    Color shirt{green};
    Color cup{blue};
    
    /// error : white is not an enumerator of Color
    /// error : 20 is not an enumerator of Color
//    Color socks{white};
//    Color hats{20};
    
    /// error : green is not an enumerator of Pet
//    Pet my_pet{green};
    /// error : lion is not an enumerator of Color
//    Color my_color{lion};
    
    /// caller can test the function’s return value against the appropriate enumerator
    if (read_file_contents() == read_result_success)
    {
        std::cout << "File read success!" << '\n';
    }
    else
    {
        std::cout << "File read failed!" << '\n';
    }
    
    Item_type holding{torch};
    
    sort_data(numerical);
    
    /// error : blue is in both enumerations which are in global namespace
//    Feeling i_feel{blue};
    /// no naming collision with Color::blue
    Feeling2 why_feel{Feeling2_blue};
    
    /// accessing enumerator from global namespace
    Feeling u_feel{happy};
    /// accessing enumerator from the scope of Feeling
    Feeling i_feel{Feeling::sad};
    
    /// we have to prefix the enumeration and enumerator names with the name of the scoped region
    color::Color paint{color::red};
    feeling::Feeling my_feeling{feeling::happy};
    
    Days_of_week day{sunday};
    
    /// comparing against enumerator
    if (day == sunday)
        std::cout << ":) - Today is sunday!\n";
    else
        std::cout << ":( - Today is not sunday\n";
    
    monster::Monster_type my_monster{monster::troll};
    
    return 0;
}
