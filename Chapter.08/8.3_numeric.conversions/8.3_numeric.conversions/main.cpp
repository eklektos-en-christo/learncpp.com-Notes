//
//  main.cpp
//  8.3_numeric.conversions
//
//  Created by εκλεγμένοι εν Χριστώ on 2/10/23.
//

/*
 ––––––––––––––––––––––––––––NUMERIC CONVERSIONS––––––––––––––––––––––––––––
 numeric conversions : type conversions that are not covered by numeric by numeric promotion
 rules
 
 types of numeric conversions : 5 basic types
 integral type                  >   any other integral type(excluding integral promotions)
 floating point                 >   any other floating type(excluding floating promotions)
 floating point                 >   any integral type
 integral type                  >   any floating type
 integral type/floating type    >   boolean type
 
 brace initialization : disallows some numeric conversions
 
 Narrowing conversions:
 numeric conversion - may or may not result in the loss of data or precision
 
 always safe numeric conversions:
 int > long
 int > double
 
 double > int : may result in the loss of data, depends upon value being converted or the
 range of the underlying types
 
 narrowing conversion : numeric conversions that may result in the loss of data, these are-
 -  floating point > integral type
 
 -  wider floating type > narrower floating type, unless the value is constexpr and is in
 the range of the destination type, even if the narrower type doesn't have the precision to
 store the whole number
 
 -  integral type > floating point, unless the value is constexpr and is in the range of the
 destination type and can be converted back into the original type without data loss
 
 -  wider integral type > narrower integral type, unless the value is constexpr and after
 integral promotion will fit into the destination type
 
 Warning:
 Compilers will often not warn when converting a signed int to an unsigned int, or vice-versa, even though these are narrowing conversions. Be extra careful of inadvertent conversions between these types (particularly when passing an argument to a function taking a parameter of the opposite sign).
 
 narrowing conversions : should be avoided in general, there are situational cases where
 there is a need to do one, in such cases implicit narrowing conversion should be made
 explicit by using static_cast
 
 best practice:
 avoid narrowing conversions whenever possible, if there is a need of narrow conversion then
 make it explicit to the compiler using static_cast
 
 Brace initialization : disallows narrowing conversions- that's why brace initialization is
 preferred and it's one of the primary reasons to use brace initialization
 
 In most cases:
 -converting a value into a type whose range doesn't support that value will probably lead
 to unexpected results
 -converting from a large integral/floating point to smaller type from the same family will
 generally work as long as the value fits in the range of smaller type
 -in case of floating point, some rounding may occur due to a loss of precision in the small
 type
 -converting from an integer to floating point works as long as the value fits in the range
 of floating point type
 -converting from floating point to an integer works as long as value fits in the range of
 integer, but fractional values are lost
 
 some signed/unsigned conversions excluded by the compiler otherwise compiler warns
 generally if you try to do something dangerous
 */

#include <iostream>
#include <iomanip>

void some_fcn(int i)
{
}

int main()
{
    /// integral type to any other integral type - integral promotions excluded
    short s = 3;                    /// int to short
    long l = 3;                     /// int to long
    char ch = s;                    /// short to char
    
    /// floating type to any other floating type - floating promotions excluded
    float f = 3.2;                  /// double to float
    long double ld = 3.2;           /// double to long double
    
    /// floating point to any integral type
    int i = 2.2;                    /// double to int
    
    /// integral type to any floating type
    double d = 2;                   /// int to double
    
    /// integral/floating type to boolean type
    bool b1 = 2;                    /// int to bool
    bool b2 = 2.2;                  /// double to bool
    
    /// narrowing conversion : may/may not result in loss of data
    int i1 = 5.1;                   /// 0.1 dropped : loss of data
    int i2 = 5.0;                   /// converted to 5, no loss of data
    
    double d1{1.1};
    
    some_fcn(d1);                   /// narrowing conversion : compiler warning
    some_fcn(static_cast<int>(d1)); /// good : explicitly telling the compiler that it is expected, no warning
    
    //int i3{2.2};                    /// compilation error : narrowing conversion in brace initialization
    
    /// assigned larger integer to char variable, this causes char to overflow
    int i4{30000};
    char c = i4;                    /// chars have range -128 to 127, char will overflow, unexpected result
    
    std::cout << static_cast<int>(c) << '\n';
    
    /// large integral to small integral type works as long as value fits in the smaller type's range
    int i5{2};
    short s1 = i5;                  /// from int to short
    std::cout << s1 << '\n';
    
    /// large floating point to small floating point works as long as value fits in the smaller type's range
    double d2{2.12112};
    float f1 = d2;                  /// from double to float
    std::cout << f1 << '\n';
    
    /// double has 9 significant digits, float can about 7
    float f2{0.123456789};          /// double to float, loss of precision, rounding occurs
    std::cout << f2 << '\n';
    /// loss of precision, float can't hold as much precision as a double
    std::cout << std::setprecision(9) << f2 << '\n';
    
    /// value fits in the range of floating point type, so this generally works
    int i6{10};
    float f3 = i6;                  /// int to float
    std::cout << f3 << '\n';
    
    /// float/double to int works as long as the value fits in int's range, but fractional part is lost
    int i7 = 2.2;
    std::cout << i7 << '\n';
    
    return 0;
}
