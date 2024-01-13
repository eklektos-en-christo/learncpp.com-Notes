//
//  main.cpp
//  28.5_stream.states.and.input.validation
//
//  Created by Εκλεκτός εν Χριστώ on 12/11/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 State flags - are used to signal various conditions that may occur when using streams, ios_base contains
 several state flags, these flags live in ios_base, ios is derived from ios_base, ios is generally used to
 access these flags
 
 goodbit - flag, means everything is okay
 badbit - flag, some kind of fatal error occurred
 eofbit - flag, the stream has reached the end of file
 failbit - a non-fatal error occurred
 
 ios also provides a number of member functions in order to conveniently access the above states:
 
 good() - returns true if the goodbit is set, means the stream is OK
 bad() - returns true if the badbit is set, a fatal error occurred
 eof() - returns true if the eofbit is set, the stream is at the end of file
 fail() - returns true if the failbit is set, a non fatal error occurred
 clear() - clears all flags and restores the stream to goodbit state, means the streak is OK
 clear(state) - clears all flags and sets the state flag passed in
 rdstate() - returns the currently set flags
 setstate(state) - sets the state flag passed in
 
 If an error occurs and a stream is set to anything other than goodbit, then further stream operations on
 that stream will be ignored, this condition can be cleared by using clear() function
 
 -----------------------------------------------------------------------------------------------------------
 INPUT VALIDATION: process of checking if the user input meets some set of criteria, general types of
 input validation are: string and numeric
 
 string validation - we accept all user input as a string and then accept or reject it based on whether it
 is formatted appropriately
 
 numerical validation - we typically concerned with making sure the number the user enters is within a
 particular range, it is possible that users enter things that aren't numbers at all
 
 Some useful functions that we can use to determine whether specific characters are numbers or letters,
 following functions live in <cctype>:
 
 std::isalnum(int) - returns non-zero if the parameter is a letter or a digit
 std::isalpha(int) - returns non-zero if the parameter is a letter
 std::iscntrl(int) - returns non-zero if the parameter is a control character
 std::isdigit(int) - returns non-zero if the parameter is a digit
 std::isgraph(int) - returns non-zero if the parameter is printable character that is not whitespace
 std::isprint(int) - returns non-zero if the parameter is printable character including whitespace
 std::inpunct(int) - returns non-zero if the parameter is neither alphanumeric nor whitespace
 std::isspace(int) - returns non-zero if the parameter is whitespace
 std::isxdigit(int) - returns non-zero if parameter is a hex digit
 
 -----------------------------------------------------------------------------------------------------------
 String validation: best way to validate strings is to step through each character of the string and ensure
 it meets the validation criteria(besides using a regular expression)
 
 -----------------------------------------------------------------------------------------------------------
 Numeric validation: by checking the failbit in the input, we can tell whether the user entered a number or
 not
 
 -----------------------------------------------------------------------------------------------------------
 Numeric validation as a string: Another way to process numeric input is to read it in as a string, then
 try to convert it to a numeric type.
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <algorithm>
#include <cctype>
#include <map>
//#include <ranges>
#include <string>
#include <string_view>
#include <limits>
#include <charconv>
#include <optional>

bool is_valid_name(std::string_view name)
{
    /// C++20, ranges
    /*return std::ranges::all_of(name, [](char ch)
    {
        return (std::isalpha(ch) || std::isspace(ch));
    })*/
    
    /// before C++, without ranges
    return std::all_of(name.begin(), name.end(), [](char ch)
    {
        return (std::isalpha(ch) || std::isspace(ch));
    });
}

/*bool input_matches(std::string_view input, std::string_view pattern)
{
    if (input.length() != pattern.length())
    {
        return false;
    }
    
    static const std::map<char, int (*)(int)> validators
    {
        { '#', &std::isdigit },
        { '_', &std::isspace },
        { '@', &std::isalpha },
        { '?', [](int) { return 1; } }
    };
    
    return std::equal(input.begin(), input.end(), pattern.begin(), [](char ch, char mask) -> bool
    {
        if (auto found{ validators.find(mask) }; found != validators.end())
        {
            return (*found->second)(ch);
        }
        else
        {
            return (ch == mask);
        }
    });
}*/

std::optional<int> extract_age(std::string_view age)
{
  int result{};
  auto end{ age.data() + age.length() };

  // Try to parse an int from age
  if (std::from_chars(age.data(), end, result).ptr != end)
  {
    return {};
  }

  if (result <= 0) // make sure age is positive
  {
    return {};
  }

  return result;
}


int main()
{
    /// the input statement is expecting an integer
    /// if the user enters non-numeric data, then cin will be unable to extract anything to age
    /// the failbit will be set
    /*std::cout << "Enter your age: ";
    int age{};
    std::cin >> age;*/
    
    std::string name{};
    
//    do
//    {
//        std::cout << "Enter your name: ";
//        std::getline(std::cin, name);
//    } while (!is_valid_name(name));
    
    /*std::string phone_number{};
    
    do
    {
        std::cout << "Enter a phone number (###) ###-####: ";
        std::getline(std::cin, phone_number);
    } while (!input_matches(phone_number, "(###) ###-####"));
    
    std::cout << "You entered: " << phone_number << '\n';*/
    
    int age{};
    
    /*while (true)
    {
        std::cout << "Enter your age: ";
        std::cin >> age;
        
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (std::cin.gcount() > 1)
            continue;
        
        if (age <= 0)
            continue;
        
        break;
    }*/
    
    while (true)
      {
        std::cout << "Enter your age: ";
        std::string strAge{};
        std::getline(std::cin >> std::ws, strAge);

        if (auto extracted{ extract_age(strAge) })
        {
          age = *extracted;
          break;
        }
      }

    
    std::cout << "You entered: " << age << '\n';
    
    return 0;
}
