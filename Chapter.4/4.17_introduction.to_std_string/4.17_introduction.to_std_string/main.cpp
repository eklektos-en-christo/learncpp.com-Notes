//
//  main.cpp
//  4.17_introduction.to_std_string
//
//  Created by εκλεγμένοι εν Χριστώ on 10/10/22.
//

/*
 String: collection of sequential characters
 strings: used to represent text
 strings: placed inside double quotes ""
 std::string - type, lives in <string> header
 
 std::string - can be output using std::cout
 
 std::cin - breaks on whitespaces
 
 std::getline() - reads a full line of input into a string,
 takes two arguments, first - cin and second - string variable
 
 std::ws - input manipulator, ignores leading whitespaces
 before extraction, it alters the way input is accepted
 
 leading whitespace: any whitespace character, space, tab, new
 line that occur at the start of the string.
 
 best practice:
 If using std::getline() to read strings, use std::cin >>
 std::ws input manipulator to ignore leading whitespace.
 
 Key insight
 Using the extraction operator (>>) with std::cin ignores leading whitespace.
 std::getline() does not ignore leading whitespace unless you use input manipulator std::ws.
 
 string length - str.length() is a member function, it is
 nested within std::string. length( ) returns an unsigned
 integral value
 
 std::string is expensive to initialize and copy:
 when a std::string is initialized, a copy of the string that
 is used to initialize is made, when std::string is passed by
 value to a std::string parameter, another copy is made
 
 best practice:
 do not pass std::string by value, making copied of std::string
 is expensive, prefer std::string_view parameters
 
 "hello world" - C-style string literal, default
 "hello world"s - string literal with suffix s
 "hello world"sv - string_view literal with suffix sv
 
 s suffix - lives in std::literals::string_literals
 */

#include <iostream>
#include <string>

int main()
{
    /// ================================================
    /// test program: question
    std::cout << "Enter your full name: ";
    std::string n{};
    std::getline(std::cin >> std::ws, n);
    
    std::cout << "Enter your age: ";
    int a{};
    std::cin >> a;
    
    int l{static_cast<int>(n.length())};
    std::cout << "Your age + length of name is: "
    << l + a << '\n';
    
    /// ================================================
    
    /// a string object initialized with "hello" string literal
    std::string name{"leon"};
    
    /// string can hold numbers as well
    /// "22" is not same as integer 22
    /// "22" is treated as text and not as a number
    std::string roll_no{"22"};
    
    /// string output
    std::cout << "Name is " << name << '\n';
    
    /// string input
    /// doesn't work as expected
    /// std::cin breaks on whitespace
    /// operator >> - extracts a string from std::cin
    /// but, only >> only returns characters up to the first whitespace it
    /// encounters, any other characters inside std::cin are left inside for next
    /// extraction
    std::cout << "Enter your name: ";
    std::cin >> name;
    std::cout << "Enter your age: ";
    std::string age{};
    std::cin >> age;
    std::cout << "Name: " << name << ", Age: " << age << '\n';
    
    /// std::ws - input manipulator, ignores any leading whitespaces before
    /// extraction
    std::getline(std::cin >> std::ws, name);
    std::getline(std::cin >> std::ws, age);
    std::cout << "Name: " << name << ", Age: " << age << '\n';
    
    /// use of std::ws with std::getline to ignore leading whitespaces inside std::cin
    std::cout << "Pick 1 or 2: ";
    int choice{};
    std::cin >> choice;
    std::cout << "Now enter your name: ";
    std::getline(std::cin >> std::ws, name);
    std::cout << "hello, " << name << ", you picked " << choice << '\n';
    
    /// string length - .length( ) returns an unsigned integral value
    std::string my_str{"leon"};
    std::cout << my_str.length() << '\n';
    
    /// using static_cast to convert unsigned integral value to signed integral value
    int str_length{static_cast<int>(my_str.length())};
    
    /// using std::ssize to get the length of the string as a signed integer
    /// std::ssize is supported in C++20
    std::cout << std::size(my_str) << '\n';
    
    /// std::literals to access the s and sv suffixes
    using namespace std::literals;
    std::cout << "hello" << '\n';   /// C-style string literal
    std::cout << "hello"s << '\n';  /// std::string literal
    std::cout << "hello"sv << '\n'; /// std::string_view literal
    
    /// compiler error, not supported in C++17 or earlier
    /// little support in C++20
    /// for constexpr strings, string_view can be used
//    constexpr std::string str{"hello"};
    
    return 0;
}
