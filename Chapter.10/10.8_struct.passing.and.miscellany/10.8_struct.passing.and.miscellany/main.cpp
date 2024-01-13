//
//  main.cpp
//  10.8_struct.passing.and.miscellany
//
//  Created by Εκλεκτός εν Χριστώ on 3/9/23.
//

/*
 Passing structs by reference:
 we can pass the entire struct object to a function that needs to work with members
 
 structs - generally passed by const reference to avoid making copies
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Returning structs:
 functions - return only one value
 common way to return multiple values from a function - return a struct
 
 structs: are usually returned by value, so as not to return a dangling reference
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Returning unnamed structs:
 we can make the function slightly better by returning a temporary/unnamed object instead.
 In this case - a temporary object is constructed, copied back to caller and then destroyed
 at the end of the expression
 In case where function has an explicit return type - instead of using type deduction(an
 auto return type), we can even omit the type in the return statement
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Structs with program-defined members:
 In cpp-
 structs and classes - can have members that are other program-defined types
 
 two ways to have members of another program-defined types in the structs/classes:
 
 -first : we can define one program-defined type in global scope and then use it as a
 member of another program-defined type
 
 -second : types can also be nested inside other types, so if one type only existed as part
 of another type, then that existing type could be nested inside the another type
 
 nested initialization list - used to initialize the nested type
 e.g. - {outer-type{inner-type}};
 
 member selection operator twice - to access the members of nested type
 e.g. - outer-type.inner-type.inner-type-member;
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Struct size and data structure alignment :
 size of the struct - typically is the sum of all the size of all its members,but not always
 
 we can only say that - the size of a struct will be at least as large the size of all the
 variables it contains, but it could be larger
 
 Padding - the compiler will sometimes add gaps into structures, which is called padding
 
 padding - this can actually have a pretty significant impact on the size of the struct,
 size also depends on the order in which members are declared inside the struct, compare
 Foo and Foo2 definitions
 */

#include <iostream>

/// program defined type - in global scope
struct Employee
{
    int id{};
    int age{};
    double wage{};
};

/// Employee type inside the Company type
/// Employee - member of Company type
struct Company
{
    int num_of_emp{};
    Employee CEO{};
};

/// passing an entire struct object by const reference
/// const - to avoid the modifications to struct
/// no matter how many members  the struct object has
/// we only need to pass the object
void print_employee(const Employee& employee)
{
    std::cout << "ID: " << employee.id << '\n';
    std::cout << "Age: " << employee.age << '\n';
    std::cout << "Wage: " << employee.wage << '\n';
}

struct Point_3d
{
    double x{0.0};
    double y{0.0};
    double z{0.0};
};

/// function returning a struct object by value
Point_3d get_zero_points()
{
    /// creating a Point_3d variable and returning it by value
    /// returning by value - to avoid returning a dangling reference
    /// temp doesn't really provide any documentation value here
    /// improved in the next function definition - get_zero_points_unnamed()
    Point_3d temp{0.0, 0.0, 0.0};
    return temp;
}

/// function returning an unnamed/anonymous Point_3d object
/// improved return statements inside
Point_3d get_zero_points_unnamed()
{
    /// anonymous/unnamed/temporary object
    /// temp. object created, copied back to caller, then destroyed at the end of the expression
//    return Point_3d{0.0, 0.0, 0.0};
    /// better than the previous one
    /// return type already specified at the function declaration
    /// so we don't need to do here again
//    return {0.0, 0.0, 0.0};
    /// more better than the previous one
    /// we're returning all zero values, we can use empty braces to return a value-initialized object
    /// all members are value-initialized, curly braces used
    return {};
}

/// Employee2 exists only as part of Company2 -
/// so Employee2 is nested inside the Company2
struct Company2
{
    /// Employee2 - can be accessed via Company2::Employee2
    struct Employee2
    {
        int id{};
        int age{};
        double wage{};
    };
    
    int num_of_emp{};
    /// Employee2 - nested type as well as a member of Company2
    Employee2 CEO{};
};

/// expected size of struct Foo - 2+4+8 = 14
/// But size if 16 - reason is padding done by the compiler
/// compiler - added 2 extra bytes after the member s, making the size 16 bytes instead of 14
struct Foo
{
    short s{};
    int i{};
    double d{};
};

/// size is 24 instead of 16
/// this is because the order in which members are declared
struct Foo2
{
    int i{};
    double d{};
    short s{};
};

struct Advertising
{
    int ads_shown{};
    double ads_clicked_percentage{};
    double avg_earn_per_click{};
};

Advertising get_advertising()
{
    Advertising temp;
    std::cout << "How many ads were shown today? ";
    std::cin >> temp.ads_shown;
    std::cout << "What percentage of ads were clicked on by users? ";
    std::cin >> temp.ads_clicked_percentage;
    std::cout << "What was the average earnings per click? ";
    std::cin >> temp.avg_earn_per_click;
    return temp;
}

void print_advertising(const Advertising& ad)
{
    std::cout << "Number of ads shown: " << ad.ads_shown << '\n';
    std::cout << "Click through rate: " << ad.ads_clicked_percentage << '\n';
    std::cout << "Average earnings per click: $" << ad.avg_earn_per_click << '\n';
    
    std::cout << "Total Earnings: $" << (ad.ads_shown * ad.ads_clicked_percentage / 100 * ad.avg_earn_per_click) << '\n';
}

struct Fraction
{
    int numerator{};
    int denominator{1};
};

Fraction get_fraction()
{
    Fraction temp{};
    std::cout << "Enter numerator: ";
    std::cin >> temp.numerator;
    std::cout << "Enter denominator: ";
    std::cin >> temp.denominator;
    
    return temp;
}

Fraction multiply(const Fraction& f1, const Fraction& f2)
{
    return {f1.numerator * f2.numerator, f1.denominator * f2.denominator};
}

void print_fraction(const Fraction& f)
{
    std::cout << f.numerator << '/' << f.denominator << '\n';
}

int main()
{
    Employee joe{1, 40, 20.11};
    Employee lin{2, 30, 44.18};
    
    print_employee(joe);
    print_employee(lin);
    
    Point_3d zero{get_zero_points()};
    
    if (zero.x == 0.0 && zero.y == 0.0 && zero.y == 0.0)
        std::cout << "Point is zero.\n";
    else
        std::cout << "Point is not zero.\n";
    
    Point_3d zero2{get_zero_points_unnamed()};
    
    std::cout << (zero2.x == 0.0 && zero2.y == 0.0 && zero2.z == 0.0) << '\n';
    
    /// nested initialization list - to initialize Employee
    Company my_company{10, {1, 32, 44000.0}};
    
    /// accessing CEO's wage by using the member selection operator twice
    std::cout << my_company.CEO.wage << '\n';
    
    /// nested initialization list - to initialize Employee2
    Company2 my_company2{3, {11, 40, 44143.2}};
    
    /// CEO's wage by using member selection operator twice
    std::cout << my_company2.CEO.wage << '\n';
    
    /// size of Foo - 16 instead of 14
    std::cout << sizeof(Foo) << '\n';
    
    /// size of Foo2 - 24 instead of 16
    /// this is because of the declaration order in Foo2's definition
    std::cout << sizeof(Foo2) << '\n';
    
    Advertising ad{get_advertising()};
    print_advertising(ad);
    
    Fraction f1{get_fraction()};
    Fraction f2{get_fraction()};
    
    std::cout << "Fractions multiplied: ";
    print_fraction(multiply(f1, f2));
    
    return 0;
}
