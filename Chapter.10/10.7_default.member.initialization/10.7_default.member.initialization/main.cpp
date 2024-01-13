//
//  main.cpp
//  10.7_default.member.initialization
//
//  Created by Εκλεκτός εν Χριστώ on 3/8/23.
//

/*
 Non-static member initialization - when we define a struct or class type, we can provide
 a default initialization value for each member as part of the type definition
 
 default member initializer - initialization value in non-static member initialization
 
 default member initialization values - will be used if the user doesn't provide the
 explicit initialization values when instantiating an object of given type
 
 key insight:
 structs and classes can self-initialize even when no explicit initializers are provided
 using the default member initializers
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Explicit initialization values - take precedence over default values:
 explicit values in a list initializer - always take precedence over default member
 initialization values.
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Missing initializers in an initializer list when default values exist:
 if an aggregate is initialized but the no. of initialization values is fewer than the
 number of members, then all the remaining members will be value-initialized
 
 however, if a default member initializer is provided for a given member - that default
 member will be used instead
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Initialization possibilities:
 
 -if an aggregate is defined with an initialization list:
 •if an explicit initialization value exists, that explicit value is used
 •if an initializer is missing and a default member initializer exists, then default is used
 •if initializer is missing and no default ,, ,, ,, then value initialization occurs
 
 -if an aggregate is defined with no initialization list:
 •if a default member initializer exists, the default is used
 •if no default member initializer exists, the members remains uninitialized
 
 IMPORTANT-
 Members - are always initialized in order of declaration
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Always provide default values for the members:
 to avoid the possibility of uninitialized members - simply ensure that each member has
 a default value(either an explicit default value or an empty pair of braces), that way
 the members will be initialized with some value regardless of whether we provide an
 initializer list or not
 
 best practice : provide a default value for all members, this ensures that the members
 will be initialized even if the variable definition doesn't include an initializer list
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Default initialization vs value initialization for aggregates:
 
 value initialization - is safer because it will ensure that any members with no default
 values are value initialized, this protects against the case where default values are
 not provided
 
 one more benefit of value initialization - it's consistent with how we initialize objects
 of other types
 
 best practice : if no explicit initializer values will be provided for an aggregate, prefer
 value initialization(with an empty braces initializer) to default initialization(with no
 braces}
 
 value initialization - highly recommended
 
 it’s not uncommon for programmers to use default initialization instead of value initialization for class types. This is partly for historic reasons (as value initialization wasn’t introduced until C++11), and partly because there is a similar case (for non-aggregates) where default initialization can be more efficient
 */

#include <iostream>

struct Something
{
    /// no initialization value - bad
    /// x - has no default value
    int x;
    /// value initialized by default
    int y{};
    /// explicit default value
    int z{11};
};

struct Fraction
{
    int numerator{};
    int denominator{1};
};

int main()
{
    /// no explicit initialization values given, so default member initialization values are used
    Something s1;
    
    /// x - uninitialized, garbage value
    std::cout << s1.x << '\n';
    /// y - value initialized, so 0
    std::cout << s1.y << '\n';
    /// z - 11, default value given in definition of the Something
    std::cout << s1.z << '\n';
    
    /// defaults values - are not used when explicit initializers are provided
    /// so explicit initialization values - takes precedence over default member initialization values
    Something s2{1, 2, 3};
    std::cout << s2.x << ' ' << s2.y << ' ' << s2.z << ' ' << '\n';
    
    /// s3 - initialized with an empty list, all initializers are missing
    /// x - value initialized
    /// y - default value used from the definition
    /// z - default explicit value used
    Something s3{};
    std::cout << s3.x << ' ' << s3.y << ' ' << s3.z << ' ' << '\n';
    
    /// all initialization possibilities below:
    ///
    /// no initializer list -
    /// x - remains uninitialized
    /// y and z - use default values from the definition
    Something s4;
    /// explicit initializers
    /// x, y and z - use explicit values
    /// default values - not used
    Something s5{7, 8, 9};
    /// missing initializers
    /// x - value initialized
    /// y and z - use defaults
    Something s6{};
    
    /// in all the below cases - members are initialized with values, none left uninitialized
    ///
    /// numerator - value initialized to 0
    /// denominator - defaulted to 1
    Fraction f1;
    /// numerator - value initialized to 0
    /// denominator - defaulted to 1
    Fraction f2{};
    /// numerator - initialized to 2
    /// denominator - defaulted to 1
    Fraction f3{2};
    /// numerator - initialized to 8
    /// denominator - initialized to 4
    Fraction f4{8, 4};
    
    /// f5 - default initialized
    Fraction f5;
    /// f6 - value initialized
    /// this case is safer, because it will ensure
    /// that any member with no default values are value initialized
    Fraction f6{};
    
    return 0;
}
