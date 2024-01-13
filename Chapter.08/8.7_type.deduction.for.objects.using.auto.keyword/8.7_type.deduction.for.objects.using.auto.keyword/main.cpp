//
//  main.cpp
//  8.7_type.deduction.for.objects.using.auto.keyword
//
//  Created by εκλεγμένοι εν Χριστώ on 2/13/23.
//

/*
 cpp : strongly typed language, required to provide an explicit type for all objects
 
 cases : where we want variable and its initializer to have the same type, we're effectively
 providing the same type information twice
 
 Type deduction/ Type inference : feature that allows the compiler to deduce the type of an
 object from the object's initializer
 
 to use type deduction : auto keyword is used in place of the variable's type
 
 function calls : are valid expressions
 
 function calls : we can even use type deduction when the initializer is a function call
 
 type deduction :  will not work for objects that do not have initializers or empty initial-
 zers,
 
 auto : can save a lot of typing where types are complex and lengthy and cases where they
 are hard to figure out
 
 type deduction : drops const qualifiers from deduced types, if you want deduced type to be
 const, you must supply the const yourself, simply use the const keyword in conjunction with
 auto keyword
 
 string literals in CPP : have a strange type,
 "hello" - this string literal is of type const char* and not std::string
 if you want the type deduced from a string literal be to std::string or std::string_view,
 you'll need to use s or sv literal suffixes
 like this - "hello"s/"hello"sv
 
 Type deduction benefits:
 -if two or more variable defined on sequential lines, the names of the variables will be
 lined up by using auto, helping to increase readability
 -type deduction works only on variables that have initializers, it can help avoid
 unintentionally uninitialized variables
 -you are guaranteed that there will be no unintended performance impacting conversions
 
 Type deduction downsides:
 -it conceals an object's type information in the code
 -it is still bit easier to make type based mistakes when using type deduction
 -if the type of an initializer changes, the type of the variable using type deduction will
 also change, unexpectedly
 
 best practice :
 use type deduction for variables, unless there is a need to commit to specific type
 */

#include <iostream>

int add(int x, int y)
{
    return x + y;
}

int main()
{
    /// redundancy in the statement below
    ///
    /// variable d is of type double
    /// literal 7.1 is also of type double(implicitly determined via the format of the literal)
    ///
    /// variable and its initializer are of same type
    ///
    /// we are providing the type information twice
    double d{7.1};
    
    /// using the type deduction using "auto" keyword
    ///
    /// 2.2 is double, so d1 will be of type double
    auto d1{2.2};
    /// 2 * 2 evaluates to an int, so i1 will be of type int
    auto i1{2 * 2};
    /// i1 + 1 evaluates to an int, so i2 will be of type int too
    auto i2{i1 + 1};
    
    std::cout << d << '\n';
    std::cout << d1 << '\n';
    std::cout << i1 << '\n';
    std::cout << i2 << '\n';
    
    /// add( ) returns an int, so sum will be of type int, compiler will deduce that sum should have type int
    auto sum{add(2, 22)};
    
    std::cout << sum << '\n';
    
    /// invalid, type deduction will not work without initializer
//    auto x;
    /// invalid, type deduction will not work with empty initializer
//    auto y{};
    
    /// i3 will of type const int
    const int i3{20};
    /// i4 will of type int only, const will be dropped
    /// type deduction deduces the type as int, not const int
    auto i4{i3};
    /// i4 can be modified, because it isn't a const int
    /// it's just an int, const is dropped in type deduction
    i4 = 22;
    
    /// i5 is const int
    const int i5{200};
    /// i6 is also const int, we've re-added a const qualifier during the definition of i6
    const auto i6{i5};
    /// error : i6 is const int, because of const keyword
    /// used in conjunction with auto in previous statement at i6's definition
//    i6 = ++i6;
    std::cout << i5 << ' ' << i6 << '\n';
    
    /// s will be of type "const char*" and not std::string
    auto s{"Hello!"};
    
    /// to access s and sv literal suffixes
    using namespace std::literals;
    
    /// s1 will be deduced as a std::string because of s literal suffix
    auto s1{"choo"s};
    /// s2 will be deduced as a std::string_view because of sv literal suffix
    auto s2{"choo"sv};
    
    /// harder to read
    int var1{2};
    double var2{2.2};
    
    /// easier to read, variables names are lined up, increased the readability
    auto var3{2};
    auto var4{2.2};
    
    /// complier won't complain
    int var5;
    /// compiler will complain, type deduction works only variables with initializers
    /// this also avoid uninitialized variables
//    auto var6;
    
    /// implicit conversion from int to double
    double var6{2};
    /// no conversion : type deduced to int automatically
    auto var7{2};
    
    /// we wanted a double here, accidentally provided an int literal
    /// so it's a type based mistake even when using the type deduction
    auto var8{2};
    
    /// type based mistake even when using the type deduction
    auto var9{23};
    auto var10{2};
    
    /// we wanted floating point division here
    std::cout << var9 / var10 << '\n';
    
    /// sum2 changes from int to double if return type of add( ) or gravity changes from int to double
    auto sum2{add(2, 3) + 9.8};
    std::cout << sum2 << '\n';
    
    return 0;
}
