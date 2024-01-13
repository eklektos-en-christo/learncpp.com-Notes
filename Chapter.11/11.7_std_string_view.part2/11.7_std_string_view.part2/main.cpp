//
//  main.cpp
//  11.7_std_string_view.part2
//
//  Created by Εκλεκτός εν Χριστώ on 3/26/23.
//

/*
 C-style strings - are fast but not as easy as to use and as safe as std::string
 
 std::string - has its own downsides, particularly when it comes to const strings
 
 std::string - provides some useful guarantees about the string data it manages:
 -string data will be valid for as long as the string object is alive
 -string data is cleaned up when the string object dies
 -string's value can only be modified by the string object
 -string's value can be modified without affecting other objects(for non-const strings)
 
 std::string object -
 -has no control over what king of string is used to initialize it(caller's responsibility)
 -the caller could destroy or modify the initialization string immediately after the
  std::string is initialized
 -post initialization, the string object can't rely on the initializer in any way, otherwise
  above guarantees could be violated
 
 by making copy of the initialization string(that only it has access to) - string object
 can ensure that the value and lifetime of the string data is independent from other objects
 (including the initialization string).
 
 const std::string objects - which can't modify their value
 
 A case - where we know that a std::string won't live longer than it's initialization string
 and that initialization string won't be modified, in such cases we're paying a high cost
 of making a copy of the initialization string for benefits we don't need i.e. independence
 from the initialization string
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::string_view - live in <string_view> header, C++17
 
 std::string - keeps its own copy of the string
 std::string_view - provides a view of a string that is defined elsewhere
 
 When we copy a std::string_view, the new std::string_view observes the same string as the
 copied-from std::string_view is observing
 
 std::string_view - not only fast, but has many of the functions that we know from std::
 string
 
 std::string_view - doesn't create a copy of the string, if we change the viewed string, the
 changes are reflected in the std::string_view
 
 when using std::string_view - best to avoid modifications to the underlying string for the
 remainder of the std::string_view's life to prevent confusion and errors
 
 Best practice:
 prefer std::string_view over std::string and c-style strings - when there is only a need
 of read-only access to a string
 
 if the string being viewed won't stay alive for the lifetime of the std::string_view, in
 that case prefer std::string
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 View modification functions:
 
 string_view - contains functions that let us manipulate the view of the string, this allows
 to change the view without modifying the viewed string
 
 functions for this are - remove_prefix, remove_suffix
 remove_prefix : removes characters from the left side of the view
 remove_suffix : removes characters from the right side of the view
 
 std::string_view - can't be opened back up, once you shrink the area, the only way to
 re-widen it is to reset the view by reassigning the source string to it again
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::string_view works with non-null-terminated strings
 
 C-style strings and std::string - use null terminators to mark the end of the string
 
 std::string_view - doesn't use null terminators to mark the end of the string
 std::string_view - knows where the string ends because it keeps track of its length
 
 std::cout - knows how to print std::string_view
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Converting std::string_view to a c-style string:
 
 some old functions like strlen - still expect c-style strings
 
 To convert std::string_view to a c-style string - we can do so by first converting to a
 std::string
 
 creating a std::string every time we want to pass a string_view as a c-style string is
 expensive, so this should be avoided if possible
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Prefer std:string_view function parameters over const std::string& -
 When writing a function that has a string parameter - in most cases type of the parameter
 should be std::string_view, better choice, it can handle wider range of argument types
 efficiently
 
 void some_fun(const std::string&);
 void some_fun(std::string_view);           /// prefer in most cases
 
 few cases where using a const std::string& may be more appropriate:
 -if you're using C++14 or older
 -if the function calling some other function that takes a c-style string or std::string
 
 std::string_view - not guaranteed to be null-terminated and does not efficiently convert
 back to a std::string
 
 best practice:
 -prefer passing strings using std::string_view by value instead of const std::string&
 -prefer passing strings using const std::string& if the function calls other functions that
 require c-style strings or std::string parameters
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Why std::string_view parameters are more efficient than const std::string&?
 
 A string argument in C++ : typically be a std::string, a std::string_view or a C-style
 string/string literal
 
 this happens when we try to pass each type:
 
 +-----------------------------------------------------------------------------------------+
 Argument type          std::string_view parameter          const std::string& parameter
 +-----------------------------------------------------------------------------------------+
 std::string            inexpensive conversion              inexpensive reference binding
 std::string_view       inexpensive copy                    won't implicitly convert
                                                            expensive explicit conversion to
                                                            std::string
 c-style string/literal inexpensive conversion              expensive conversion
 +-----------------------------------------------------------------------------------------+
 
 with a std::string_view value parameter- std::string_view handles all cases inexpensively
 
 -if std::string argument passed, compiler will convert std::string to std::string_view,
  this is inexpensive, so this is fine
 -if std::string_view argument passed, compiler will copy the argument into the parameter
  this is inexpensive, so this is fine
 -if c-style string or string literal passed, compiler will convert these to a std::string_
  view, this is inexpensive, so this is fine
 
 with const std::string& reference parameter- it only handles std::string args inexpensively
 
 -if std::string passed, parameter will reference bind to the argument, this is inexpensive,
  this is fine
 -if std::string_view passed, compiler will refuse to do an implicit conversion and produce
  a compilation error, static_cast can be used to do explicit conversion to std::string,
  since std::string will make a copy of the string being viewed, once conversion is done,
  the parameter will reference bind to the result, that is inexpensive, but we've made an
  expensive copy to do the conversion, this isn't great
 -if c-style string or string literal passed, compiler will implicitly convert this to a
  std::string, which is expensive, this isn't great also
 
 const std::string& - only handles the std::string argument inexpensively
 
 std::string_view - parameter is a normal object, can be accessed directly
 
 std::string& - accessing this parameter is more expensive, reference must be dereferenced
 to get the object before the object can be accessed
 
 +-----------------------------------------------------------------------------------------+
 Ownership issues:
 
 std::string_view's lifetime - independent of the string it is viewing, string can be
 destroyed before the string_view's object's destruction
 
 when string being viewed is destroyed before the string_view - cause undefined behavior
 
 string being viewed by string_view - has to have been created somewhere else, it might be a
 string literal that lives as long as the program lives, it might be a std::string that
 lives until the std::string decides to destroy it or the std::string dies
 
 std::string_view - can't create any strings of its own, because it's just a view
 
 When we create a string_view from a std::string and then modify the std::string, which
 cause the std::string's internal string to die and be replaced with a new one in a
 different place, the string_view will still look at where the old string was, but it's not
 there anymore
 
 WARNING:
 always make sure the underlying string view with a string_view doesn't go out of scope and
 isn't modified while using the string_view
 
 +-----------------------------------------------------------------------------------------+
 data() function and non-null-terminated strings:
 
 string being viewed by string_view - can be accessed using the data() function
 
 data() - returns a c-style string, null terminated, which provides fast access to the
 string being viewed as a c-string
 
 should only be used where we know the string being viewed is null-terminated
 
 WARNING:
 only use std::string_view::data() - if the string_view's view hasn't been modified and
 string being viewed is null terminated
 
 using std::string_view::data() - of a non-null-terminated string cause undefined behavior
 
 converting string_view to std::string and calling std::string::data() - is guaranteed to be
 null terminated
 */

#include <cstring>
#include <string>
#include <iostream>
#include <iterator>
#include <string_view>

/// std::string_view - normal object, can be accessed directly
void print_sv(std::string_view sv)
{
    std::cout << sv << '\n';
}

/// std::string& - more expensive, reference must be dereferenced to get the object
void print_s(const std::string& s)
{
    std::cout << s << '\n';
}

/// this function has an ownership issue
std::string_view ask_for_name()
{
    std::cout << "What's your name?\n";
    
    /// using std::string, because std::cin needs to modify it
    std::string name{};
    std::cin >> name;
    
    /// switching to std::string_view for demonstration purpose
    /// if you already have a std::string, no reason to switch to a std::string_view
    std::string_view view{name};
    
    std::cout << "Hello, " << view << '\n';
    
    /// function returns a dangling std::string_view
    return view;
}   /// name string dies here, also the string dies here that name created

int main()
{
    /// 3 copies of "hello" were made, resulting in 4 copies
    ///
    /// literal, known at compile-time, stored in binary - "hello"
    /// 1st copy - when we create char[ ]
    /// 2nd copy - str object creates one copy
    /// 3rd copy - more object creates one copy
    char text[]{"hello"};
    std::string str{text};
    std::string more{str};
    
    std::cout << text << ' ' << str << ' ' << more << '\n';
    
    /// no more copies of the "hello" were created
    /// main_text - only a view onto the string "hello"
    /// neither str_view nor more_view create any copies of the string
    ///
    /// view of the literal "hello", stored in binary
    std::string_view main_text{"hello"};
    /// view of the same "hello"
    std::string_view str_view{main_text};
    /// view of the same "hello"
    std::string_view more_view{str_view};
    
    std::cout << main_text << ' ' << str_view << ' ' << more_view << '\n';
    
    std::string_view my_str{"Trains are fast!"};
    
    /// some std::string_view functions
    ///
    /// 16
    std::cout << my_str.length() << '\n';
    /// Trains
    std::cout << my_str.substr(0, my_str.find(' ')) << '\n';
    /// true
    std::cout << (my_str == "Trains are fast!") << '\n';
    
    /// C++20
    ///
    /// false
//    std::cout << my_str.starts_with("Buses") << '\n';
    /// true
//    std::cout << my_str.ends_with("fast!") << '\n';
    
    std::cout << my_str << '\n';
    
    /// arr and arr_view share their string
    char arr[]{"Gold"};
    std::string_view arr_view{arr};
    
    std::cout << arr_view << '\n';
    
    /// viewed string changed to "Good" from "Gold"
    arr[2] = 'o';
    
    /// changes in viewed string reflected in std::string_view
    std::cout << arr_view << '\n';
    
    std::string_view str1{"GOATS"};
    std::cout << str1 << '\n';
    
    /// ignoring the first character from the left side of the view
    str1.remove_prefix(1);
    std::cout << str1 << '\n';
    
    /// ignoring the last 3 characters from the right side of the view
    str1.remove_suffix(3);
    std::cout << str1 << '\n';
    
    /// resetting the view by reassigning the source string to it again
    str1 = "GOATS";
    std::cout << str1 << '\n';;
    
    /// No null terminator at the end
    char vowels[]{'a', 'e', 'i', 'o', 'u'};
    
    /// passing the length manually because vowels is not null-terminated
    /// std::size used to get the length of vowels because vowels is an array
    std::string_view str2{vowels, std::size(vowels)};
    
    std::cout << str2 << '\n';
    
    /// creating a string_view
    std::string_view sv{"Honeypot"};
    sv.remove_suffix(3);
    
    /// creating a std::string from the std::string_view
    std::string str3{sv};
    
    /// getting the c-style null terminated string
    auto str_null_terminated{str3.c_str()};
    
    /// passing the null terminated string to the function that we want to use
    std::cout << str3 << " has " << std::strlen(str_null_terminated) << " letters!" << '\n';
    
    std::string s1{"hello world"};
    std::string_view sv1{s1};
    
    /// passing to std::string_view parameter
    ///
    /// conversion from std::string to std::string_view, inexpensive
    print_sv(s1);
    /// copy of std::string_view, inexpensive
    print_sv(sv1);
    /// conversion of c-style string literal to std::string_view, inexpensive
    print_sv("hello world");
    
    /// passing to std::string parameter
    ///
    /// bind to std::string argument, inexpensive
    print_s(s1);
    /// error - no implicit conversion from std::string_view to std::string, compiler error
//    print_s(sv1);
    /// temporary creation of std::string, expensive
    print_s(static_cast<std::string>(sv1));
    /// temporary creation of std::string, expensive
    print_s("hello world");
    
    std::string_view view{ask_for_name()};
    
    /// undefined behavior - string already died and view is observing that string
    std::cout << "Your name is " << view << '\n';
    
    std::string_view str4{"balloon"};
    std::cout << str4 << '\n';
    
    /// std::strlen needs a null terminated string, so passing str4.data() to it
    /// using data() - we haven't modified the view and string is null terminated
    std::cout << std::strlen(str4.data()) << '\n';
    
    /// std::string_view modified, no longer it is viewing a null terminated string
    /// this only changes the region that str is observing, doesn't modify the string
    ///
    /// remove the prefix 'b'
    /// str4 is viewing substring "alloon"
    /// substring "alloon" is still null terminated
    str4.remove_prefix(1);
    /// remove the suffix "oon"
    /// str4 is now viewing substring "all"
    /// substring "all" is no longer null-terminated
    str4.remove_suffix(3);
    
    /// data() - returns pointer to the first char in substring being viewed, which is c-style string  "alloon"
    std::cout << str4 << " has " << std::strlen(str4.data()) << " letter(s)" << '\n';
    std::cout << "str4 is " << str4 << '\n';
    std::cout << "str4.data() is " << str4.data() << '\n';
    
    return 0;
}
