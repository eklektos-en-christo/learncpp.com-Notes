//
//  main.cpp
//  8.6_typedefs.and.type.aliases
//
//  Created by εκλεγμένοι εν Χριστώ on 2/12/23.
//

/*
 Type aliases:
 using - keyword, creates an alias for an existing data type
 
 syntax:
    using name_for_type_alias = existing_data_type
 
 Type aliases naming conventions: three common naming conventions
 -type aliases that end in a "_t" suffix,
 "_t" is short for type, this convention is used by
 standard library for globally scoped typed names like size_t and nullptr_t, this convention
 was inherited from C, POSIX reserves the "_t" suffix for globally scoped type names, so
 using this convention may cause type naming conflicts on POSIX systems
 
 -type aliases that end in a "_type" suffix,
 this convention is used by some standard
 library types like std::string to name nested type aliases, for example -
 std::string::size_type, many such nested type aliases do not use a suffix at all, like
 std::string::iterator, so this usage is inconsistent at best
 
 -type aliases that use no suffix
 in modern cpp, the convention is to name type aliases or any other type that you define
 yourself starting with a capital letter and using no suffix, capital letter helps
 differentiate the names of types from the names fo variables and functions, and prevents
 naming collision between the type and the name
 
 best practice :
 name the type aliases - starting with a capital letter, do no use a suffix unless there is
 a specific reason to do otherwise.
 
 Type aliases : are not distinct types
 
 an alias : doesn't actually define a new, distinct type
 an alias : introduces a new identifier for an existing type
 type alias : completely interchangeable with the aliased type
 -this allows us to do things that are syntactically valid but semantically meaningless
 -compiler doesn't prevent these kinds of semantic errors, we say aliases are not type safe
 
 warning:
 case must be taken - not to mix values of aliases that are intended to be semantically
 distinct
 
 strong typedef : some languages support this concept, in it the strong typedef actually
 creates a new type that has all the original properties of the original type but the
 compiler throws an error if you try to mix the values of the aliased type and the strong
 typedef
 
 enum classes : support strong typedefs,
 -quite few 3rd party cpp libraries that implement strong typedef-like behavior
 
 Scope of a type alias:
 scope : property of an identifier
 type alias : follow the same scoping rules as variable identifiers
 
 type alias defined inside a block : has block scope, usable only within that block
 type alias defined in global namespace : has file scope, usable to the end of the file
 
 if you need to use one or more type aliases across multiple files : they can be defined
 in a header file and included into any file that needs to use the definition
 
 ––––––––––––––––––––––––––––––––––––––––––––––
 Typedefs: still in cpp for backward compatibility reasons
 typedef : short for "type definition"
 typedef : older way of creating an alias for a type
 syntax : typedef existing_type type_alias;
 
 few syntactical issues with typedefs:
 -easy to forget whether the name of the typedef or the name of the type to alias comes
 first
 -syntax for typedefs can get more ugly with more complex types
 -typedef suggests that a new type is being defined, but it's not true, typedef is an alias
 
 best practice : prefer type aliases over typedefs
 
 –––––––––––––––––
 When to use type aliases?
 -for platform independent coding
 -to make complex types easier to read
 -for legibility
 -for easier code maintenance
 
 -for platform independent coding : type aliases can be used to hide platform specific
 details, for example- int is of 2 bytes on some platforms and 4 bytes on other platforms,
 using int to store more than 2 bytes can be potentially dangerous when writing platform
 independent code
 char, short, int and long : give no indication of their size
 fairly common for cross platform programs : to use type aliases to define aliases that
 include the type's size in bits, for example- int8_t would be an 8-bit signed integer,
 int16_t would be a 16-bit signed integer etc, type aliases of this kind are typically used
 in conjunction with preprocessor directives
 fixed width types : std::int16_t, std::uint32_t and size_t are actually just type aliases
 to various fundamental types
 
 -to make complex types easier to read : in advanced C++, types can be complicated and
 lengthy to manually enter on the keyboard, type aliases allow to take complex types and
 give them a simpler name which makes code easier to read and saves typing, this is probably
 the best use for type aliases
 
 -for legibility : type aliases also help with code documentation and comprehension, if you
 have multiple functions passing or returning the same type, creating a type alias might be
 worthwhile
 
 -for easier code maintenance : type aliases also allow to change the underlying type of an
 object without having to update lots of hardcoded types, for example - if we are using a
 short to hold a student's ID number, but later decided to use a long instead, we'd have to
 replace short with long everywhere the short was used, it will be difficult to figure out
 which objects of type short were being used to hold ID numbers and which are being used for
 another purposes, if we use type aliases, then changing types becomes simple as below-
 from using StudentID = short; to using StudentID = long;
 caution : whenever a type is changed, behavior of the program may also change, new type may
 have comparison or integer/float division issues, or other issues that the old type did not
 if you change an existing type to some other type, code should be thoroughly retested.
 –––––––––––––––––
 
 Downsides:
 they introduce another identifier into the code that needs to be understood, if this does
 not benefit to readability and comprehension then type alias is doing more harm than good,
 they are useful when they can be used in many places throughout the code, rather than in
 fewer places
 
 best practice :
 use type aliases judiciously, when they provide a clear benefit to code readability or
 code maintenance
 */

#include <iostream>
#include <vector>
/// using type aliases from the header below
#include "my_types.h"

/// creating a type alias
/// my_double is an alias for existing type double
using my_double = double;

using Distance = double;

/// Distance is defined type alias
/// Distance is type and distance is parameter name
void my_fun(Distance distance);

/// making VectPairSI an alias for this crazy type
using VectPairSI = std::vector<std::pair<std::string, int>>;

/// using VectPairSI in a function parameter
bool has_duplicates(VectPairSI pair_list)
{
    return false;
}

using Test_Score = int;

/// return type of Test_Score makes it a little more obvious that the
/// function is returning a type that represents a test score
Test_Score grade_test()
{
    return 0;
}

int main()
{
    /// using the created type alias to define a double variable
    /// my_double is equivalent of double type
    /// compiler will use the aliased type, which is double
    my_double d{2.222};
    std::cout << d << '\n';
    
    Distance d1{2.222};
    std::cout << d1 << '\n';
    
    using Miles = long;
    using Speed = long;
    
    Miles distance{5};
    Speed megahertz{3200};
    
    /// syntactically valid but semantically meaningless
    /// aliases are not type safe  in this case but are still useful
    distance = megahertz;
    std::cout << distance << ' ' << megahertz << '\n';
    
    /// type aliases included from a header file and have global scope
    Test_int test_int{2};
    Test_float test_float{2.2f};
    std::cout << test_int << '\n';
    std::cout << test_float << '\n';
    
    /// both following aliases are identical
    ///
    /// older way
    typedef int mytype_int_typedef;
    /// modern way
    using mytype_int_typealias = int;
    
    mytype_int_typedef int_typedef{2222};
    mytype_int_typealias int_typealias{222222};
    std::cout << int_typedef << '\n';
    std::cout << int_typealias << '\n';
    
    /// syntactical issue with typedefs
    ///
    /// test : unknown type
//    typedef test float;
    /// correct way of defining the typedef
    typedef float test;
    
    /// hard to read typedef
    typedef int (*FcnType)(double, char);
    /// easier to read type alias
    using FcnType = int(*)(double, char);
    
    /// variable x will be defined as a char type
    int8_t x{65};
    /// int8_t is actually a type alias for a char type, so output will be 'A'
    std::cout << x << '\n';
    
    /// instantiate a VectPairSI variable
    VectPairSI pairlist;
    
    grade_test();
    
    return 0;
}
