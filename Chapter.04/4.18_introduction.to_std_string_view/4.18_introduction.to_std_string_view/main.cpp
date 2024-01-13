//
//  main.cpp
//  4.18_introduction.to_std_string_view
//
//  Created by εκλεγμένοι εν Χριστώ on 10/11/22.
//

/*
 std::string_view - introduced to address the issue with
 std::string being expensive to initialize or copy.
 
 std::string_view: live in <string_view> header
 
 std::string_view: provides a read only access to an existing
 string, cstyle string literal, a std::string or char array
 without making a copy.
 
 Best practice
 Prefer std::string_view over std::string when you need a
 read-only string, especially for function parameters.
 
 std::string_view: has full support for constexpr
 
 std::string to std::string_view - a std::string_view can be
 created using std::string, implicit conversion to
 std::string_view will take place
 
 std::string_view to std::string - std::string makes a copy of
 its initializer, so C++ won't allow implicit conversion of
 a std::string from a std::string_view. but, explicitly  a
 std::string can be created using std::string_view initializer
 also an existing std::string_view can be converted to std::
 string using static_cast
 
 string_view literals - can be created using sv suffix after
 the double quotes
 
 Do not return a std::string_view - returning a string_view
 from a function is usually a bad idea
 */

#include <iostream>
#include <string>
#include <string_view>

/// no copy of sv is made to initialize the s, sv is read only
void display_sview(std::string_view s)
{
    std::cout << s << '\n';
}

void display_s(std::string s)
{
    std::cout << s << '\n';
}

int main()
{
    /// no copy of the "leon" is made to initialize the sv, "leon" is read only
    std::string_view sv{"leon"};
    display_sview(sv);
    
    /// string_view has full support for constexpr
    /// s will be replaced with the "hello world" at compile-time
    constexpr std::string_view s{"Hello World!"};
    std::cout << s << '\n';
    
    /// initializing a string_view from a std::string
    std::string str{"World"};
    std::string_view str_init{str};
    
    /// implicit conversion of std::string to std::string_view below:
    display_sview(str);
    
    /// creating a std::string using std::string_view initializer
    /// sv is read only so str2 can be created
    std::string str2{sv};
    
    /// explicit: converting existing std::string_view to std::string using static_cast
    display_s(static_cast<std::string>(sv));
    
    /// using the entire namespace here is: OKAY
    /// sv lives in std::literals::string_view_literals
    using namespace std::literals;
    std::cout << "C-style string literal" << '\n';
    std::cout << "a std::string literal"s << '\n';
    std::cout << "a string_view literal"sv << '\n';
    
    return 0;
}
