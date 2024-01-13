//
//  main.cpp
//  10.6_struct.aggregate.initialization
//
//  Created by Εκλεκτός εν Χριστώ on 3/7/23.
//

/*
 much like normal variables - data members are not initialized by default
 
 Aggregate data type/aggregate - in general programming, any type that can contain multiple
 data members
 
 some type of aggregates - allow members to have different type, like in structs
 
 some type of aggregates - require that members must be of a single type, like in arrays
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 To be an aggregate in C++, a type must meet the following criteria:
 -type must be a class type(struct,class,union) or an array type(built-in or std::array)
 -type has no private or protected non-static data members
 -type has no user-declared or inherited constructors
 -type has no base classes
 -type has no virtual member functions
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 structs with only data members - are aggregates
 arrays - are also aggregates
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Aggregate initialization of a struct:
 when we define an object with a struct type, we need some way to initialize multiple
 members at initialization time
 
 Aggregate initialization - form of initialization, allows us to directly initialize the
 members of aggregates
 
 initializer list - used to directly initialize the members of aggregates, it is just a list
 of comma-separated initialization values
 
 normal variables - can be copy initialized, direct initialized or list initialized
 
 3 forms of aggregate initialization - copy, direct or list
 
 member wise initialization - each of the initialization forms does a member-wise
 initialization, which means each member in the struct is initialized in the order of
 declaration
 
 best practice:
 prefer the (non copy) braced list initialization when initializing aggregates
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Missing initializers in an initialization list:
 when an aggregate is initialized - if the number of initialization values are fewer than
 the number of members, then all remaining members will be value-initialized
 
 it means - we can use empty initialization list to value-initialize all members of the
 struct
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 const structs:
 variables of struct type can be const, they must be initialized as all the const variables
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Designated initializers : C++20
 when initializing a struct from a list of values - the initializer are applied to the
 members in order of declaration
 
 designated initializers - allow to explicitly define which initialization values map to
 which members, members must be initialized in same order in which they are declared in the
 struct, otherwise error will result, members not designated an initializer will be value
 initialized
 
 designated initializers - clutter up the initializer list significantly, it is good idea to
 avoid adding new members to the middle of an existing aggregate definition to avoid the
 risk of initializer shifting
 
 best practice:
 when adding a new member to an aggregate, it is safest to add it to the bottom of the
 definition list, so initializers for other members don't shift
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Assignment with an initializer list:
 similar to initializing a struct with an initializer list - we can also assign values to
 structs using an initializer list, which does member-wise assignment
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Assignment with designated initializers:
 designated initializers can also be used in a list assignment, any members that aren't
 designated in such an assignment will be assigned the value that would be used for value
 initialization
 */

#include <iostream>

struct Employee
{
    int id{};
    int age{};
    double wage{};
};

struct Rectangle
{
    double length{};
    double width{};
};

int main()
{
    /// each member in the struct is initialized in the order of declaration
    /// copy-list initialization using braced list
    Employee joe = {1, 28, 12000.0};
    
    /// each member in the struct is initialized in the order of declaration
    /// direct initialization using parenthesized list - C++20, commenting out
//    Employee frank(2, 33, 18000.0);
    
    /// each member in the struct is initialized in the order of declaration
    /// list initialization using braced list - preferred form of initialization
    Employee jack{3, 88, 40000.0};
    
    /// frank.wage is value-initialized to 0.0 - few initializers provided
    /// remaining member - value initialized
    Employee frank{4, 30};
    std::cout << frank.id << ' ' << frank.age << '\n';
    std::cout << frank.wage << '\n';
    
    /// empty initialization list - to value-initialize all the members of the struct
    Employee hank{};
    std::cout << hank.id << ' ' << hank.age << ' ' << hank.wage << '\n';
    
    /// const struct variables - can't be modified
    const Rectangle unit{1.0, 1.0};
    
    /// error : can't assign to a const variable
//    unit.length = 1.1;
    
    /// value initializing all members
    const Rectangle zero{};
    
    /// designated initializers
    /// tom.age - not designated an initializer, so value initialized
    Employee tom{.id{5}, .wage{4000.0}};
    
    /// error : initialization order does not match the order of declaration in the struct
//    Employee tom_new{.age{40}, .id{6}, .wage{30000.0}};

    /// initialization
    Employee tin{7, 35, 44000.0};
    /// assignment, not initialization
    /// assigning values to struct using an initializer list, member wise assignment
    /// don't want to change the id, so provided tin.id as a placeholder
    tin = {tin.id, 36, 45000.0};
    
    Employee lin{8, 70, 32000.0};
    
    std::cout << lin.id << '\n';
    std::cout << lin.age << '\n';
    std::cout << lin.wage << '\n';
    
    /// list assignment with designated initializers
    /// lin.age - haven't specified a designated initializer, so value initialized to 0
    lin = {.id = lin.id, .wage = 31000.0};
    
    std::cout << lin.id << '\n';
    std::cout << lin.age << '\n';
    std::cout << lin.wage << '\n';
    
    return 0;
}
