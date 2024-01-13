//
//  main.cpp
//  26.2_template.non.type.parameters
//
//  Created by Εκλεκτός εν Χριστώ on 11/16/23.
//

/*
 Template type parameter: is a placeholder type that is substituted for a type passed in as an argument
 
 Template non-type parameters: a template parameter where the type of the parameter is predefined and is
 substituted for a constexpr value passed in as an argument
 
 Non type parameter can be any of the following types:
 - an integral type
 - an enumeration type
 - a pointer or reference to a class object
 - a pointer or reference to a function
 - a pointer or reference to a class member function
 - std::nullptr_t
 - a floating type type
 
 If you try to instantiate a template non-type parameter with a non-constexpr value, it will not work
 non-type parameter must be a constexpr
 */

#include <iostream>
#include <array>

/// type parameter T controls the type of the static array
/// non-type parameter size controls the length of the array
template <class T, int size>
class StaticArray
{
private:
    T m_array[size] {};
    
public:
    T* get_array();
    
    T& operator[](int index)
    {
        return m_array[index];
    }
};

/// for for a class with a non-type parameter defined outside of the class
template <class T, int size>
T* StaticArray<T, size>::get_array()
{
    return m_array;
}

template <int size>
class Goo
{
};

int main()
{
    /// template type argument T passed - int here
    /// template non type argument size passed - 10 here, 10 is constexpr value passed in as an argument
    StaticArray<int, 10> int_array;
    
    /// filling up the array
    for (int count{ 0 }; count < 10; ++count)
        int_array[count] = count;
    
    /// printing the array
    for (int count{ 9 }; count >= 0; --count)
        std::cout << int_array[count] << ' ';
    std::cout << '\n';
    
    /// STD lib class array also used template type(double) and template non-type(10) parameters
    std::array<double, 10> std_array;
    
    /// filling
    for (int count{ 1 }; count <= 10; ++count)
        std_array[count] = count * 2343;
    
    /// printing
    for (int count{ 1 }; count <= 10; ++count)
        std::cout << std_array[count] << ' ';
    std::cout << '\n';
    
    /// won't work - a non-constexpr argument passed, x is non-constexpr
    int x{ 10 };
    /*Goo<x> f;*/
    
    /// works, y is a constexpr
    constexpr int y{ 10 };
    Goo<y> g;
    
    return 0;
}
