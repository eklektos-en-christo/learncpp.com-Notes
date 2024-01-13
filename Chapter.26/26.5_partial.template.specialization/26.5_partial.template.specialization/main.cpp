//
//  main.cpp
//  26.5_partial.template.specialization
//
//  Created by Εκλεκτός εν Χριστώ on 11/17/23.
//

/*
 Problem with full template specialization: all template parameters must be explicitly defined
 
 Full template specialization: is too restrictive
 
 -----------------------------------------------------------------------------------------------------------
 PARTIAL TEMPLATE SPECIALIZATION: allows us to specialize classes but not individual functions, where some
 but not all of the template parameters have been explicitly defined
 
 PARTIAL TEMPLATE SPECIALIZATION: can only be used with classes, not template functions, functions must be
 fully specialized
 
 -----------------------------------------------------------------------------------------------------------
 PARTIAL TEMPLATE SPECIALIZATION FOR MEMBER FUNCTIONS:
 
 Function can't be partially specialized, one way it to partially specialize the entire class
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>

/// T - template type parameter
/// size - expression parameter/non-type parameter
template <class T, int size>
class StaticArray
{
private:
    T m_array[size] {};
    
public:
    T* get_array() { return m_array; }
    
    T& operator[](int index)
    {
        return m_array[index];
    }
};

/// this will print the c-style string with spaces - not expected
template <class T, int size>
void print(StaticArray<T, size>& array)
{
    for (int count{ 0 }; count < size; ++count)
        std::cout << array[count] << ' ';
    std::cout << '\n';
}

/// this is an overridden version of the print function to print the chars without spaces
/// this solves the problem but if the user inputs the size as 20, 5, 10 and not 14 then?
/// in this full template specialization we have to explicitly define the length of the array this function will accept
template <>
void print(StaticArray<char, 14>& array)
{
    for (int count{ 0 }; count < 14; ++count)
        std::cout << array[count];
    std::cout << '\n';
}

/// partial template specialization
/// this function works, not because it is partially specialized, it is just an overloaded
/// function using a class parameter that's partially specialized
/// the size expression parameter is left templated
/// so any size will be acceptable, not just 14 as in the above print(staticarray<char, 14>)
template <int size>
void print(StaticArray<char, size>& array)
{
    for (int count{ 0 }; count < 14; ++count)
        std::cout << array[count];
    std::cout << '\n';
}

/*--------------------------------------------------------------------------------------------------------*/
/// a template class
template <class T, int size>
class StaticArrayMF
{
private:
    T m_array[size]{};
    
public:
    T* get_array() { return m_array; }
    
    T& operator[](int index)
    {
        return m_array[index];
    }
    
    void print();
};

template <class T, int size>
void StaticArrayMF<T, size>::print()
{
    for (int i{ 0 }; i < size; ++i)
        std::cout << m_array[i] << ' ';
    std::cout << '\n';
}

/// won't work - partially specializing a function is not allowed
/*
template <int size>
void StaticArrayMF<double, size>::print()
{
    for (int i{ 0 }; i < size; ++i)
        std::cout << std::scientific << m_array[i] << ' ';
    std::cout << '\n';
}
*/

/// because partial specializing of functions is not allowed, so partially specializing the whole class for double type
template <int size>
class StaticArrayMF<double, size>
{
private:
    double m_array[size]{};
    
public:
    double* get_array() { return m_array; }
    
    double& operator[](int index)
    {
        return m_array[index];
    }
    
    void print();
};

/// member function of the partially specialized class
/// StaticArrayMF<double, size>::print() - is no longer a partially specialized function
/// it is a non-specialized member of partially specialized class StaticArrayMF<double, size>
template <int size>
void StaticArrayMF<double, size>::print()
{
    for (int i{ 0 }; i < size; ++i)
        std::cout << std::scientific << m_array[i] << ' ';
    std::cout << '\n';
}

/*--------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------*/
/// reducing the duplicate code in above class by using the inheritance
/// using a common base class
template <class T, int size>
class StaticArray_Base
{
protected:
    T m_array[size]{};
    
public:
    T* get_array() { return m_array; };
    
    T& operator[](int index)
    {
        return m_array[index];
    }
    
    void print()
    {
        for (int i{ 0 }; i < size; ++i)
            std::cout << m_array[i] << ' ';
        std::cout << '\n';
    }
    
    virtual ~StaticArray_Base() = default;
};

template <class T, int size>
class StaticArray_Derived : public StaticArray_Base<T, size>
{
};

template <int size>
class StaticArray_Derived<double, size> : public StaticArray_Base<double, size>
{
public:
    void print()
    {
        for (int i{ 0 }; i < size; ++i)
            std::cout << std::scientific << this->m_array[i] << ' ';
        std::cout << '\n';
    }
};

/*--------------------------------------------------------------------------------------------------------*/

int main()
{
    StaticArray<int, 4> int4{};
    
    int4[0] = 0;
    int4[1] = 1;
    int4[2] = 2;
    int4[3] = 3;
    
    print(int4);
    
    StaticArray<char, 14> char14{};
    
    std::strcpy(char14.get_array(), "Hello, world!");
    
    /// unexpected output, spaces in the characters of a C-style string - print(StaticArray<T, size) was called
    /*print(char14);*/
    
    /// print(StaticArray<char, size> is called
    print(char14);
    
    /// print(StaticArray<char, 14> is taking the size as 19 here
    StaticArray<char, 19> char19{};
    
    std::strcpy(char19.get_array(), "Hello, world!");
    
    /// print(StaticArray<char, 14> is taking the size as 19 here, so print(StaticArray<T, size> will be called
    /// size 19 didn't match with size 14 - in the overridden print function
    /*print(char19);*/
    
    /// working as expected
    print(char19);
    
    StaticArrayMF<int, 6> int6{};
    
    for (int count{ 0 }; count < 6; ++count)
        int6[count] = count + 1;
    
    int6.print();
    
    StaticArrayMF<double, 4> double4{};
    
    for (int count{ 0 }; count < 4; ++count)
        double4[count] = 2.1 + count;
    
    double4.print();
    
    StaticArray_Derived<int, 6> int6_derived{};
    
    for  (int i{ 0 }; i < 6; ++i)
        int6_derived[i] = i + 1;
    
    int6_derived.print();
    
    StaticArray_Derived<double, 4> double4_derived{};
    
    for (int i{ 0 }; i < 4; ++i)
        double4_derived[i] = i + 1.0;
    
    double4_derived.print();
    
    return 0;
}
