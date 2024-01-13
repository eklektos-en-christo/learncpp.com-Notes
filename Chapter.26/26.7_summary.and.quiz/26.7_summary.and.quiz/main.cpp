//
//  main.cpp
//  26.7_summary.and.quiz
//
//  Created by Εκλεκτός εν Χριστώ on 11/26/23.
//

/*
 Templates: allow us to write functions or classes using placeholder types, so that we can stencil out
 identical versions of the function or class using different types
 
 Function/class instance: a function/class that has been instantiated
 
 All template functions or classes must start with a template parameter declaration that tells the compiler
 that it is a template function or class
 
 Template type parameters: placeholder types, normally named T1, T2, T3 or other single letter names
 
 Expression parameters: usually integral types but can be pointer or reference to a function, class object
 or member function
 
 You can't put the class definition in a header and member function definitions in a .cpp file, it is best
 to keep all of them in a header file with the member function definitions under the class
 
 Template specialization: used when we want to override the default behaviour from the templated function or
 class for a specific type
 
 Full specialization: if all types are overridden
 
 Classes: can be partially specialized, where some of the templated parameters are specialized
 
 functions: cannot be partially specialized
 
 Templates: often used in implementing the container classes to make them to be used with any appropriate
 type
 
 */

#include <iostream>
#include <string>
#include <string_view>

/// a template class Pair1
template <typename T>
class Pair1
{
private:
    T m_first{};
    T m_second{};
    
public:
    Pair1(const T& first, const T& second)
    : m_first{ first }, m_second{ second }
    {
    }
    
    T& first() { return m_first; }
    T& second() { return m_second; }
    const T& first() const { return m_first; }
    const T& second() const { return m_second; }
};

/// class with two separate two template type parameters
template <typename T1, typename T2>
class Pair
{
private:
    T1 m_first{};
    T2 m_second{};
    
public:
    Pair(const T1& first, const T2& second)
    : m_first{ first }, m_second{ second }
    {
    }
    
    T1& first() { return m_first; }
    T2& second() { return m_second; }
    const T1& first() const { return m_first; }
    const T2& second() const { return m_second; }
};

/*
template<typename T2>
class Pair<std::string, T2>
{
private:
    std::string m_string{};
    T2 m_value{};

public:
    Pair(const std::string& string, const T2& value)
    : m_string{ string }, m_value{ value }
    {
    }

    std::string& first() { return m_string; }
    T2& second() { return m_value; }
    const std::string& first() const { return m_string; }
    const T2& second() const { return m_value; }
};
*/

template <typename T>
class StringValuePair : public Pair<std::string, T>
{
public:
    StringValuePair(const std::string_view string, const T& value)
    : Pair<std::string, T>{ static_cast<std::string>(string), value }
    {
    }
};

int main()
{
    /*
    Pair1<int> p1{ 5, 8 };
    std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
    
    const Pair1<double> p2{ 2.3, 4.5 };
    std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
    */
    
    Pair<int, double> p1 { 5, 6.7 };
    std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair<double, int> p2 { 2.3, 4 };
    std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
    
    StringValuePair<int> svp{ "Hello", 5 };
    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
    
    return 0;
}
