//
//  main.cpp
//  14.17_overloading.operators.and.function.templates
//
//  Created by Εκλεκτός εν Χριστώ on 7/26/23.
//

/*
 -------------------------------------------------------------------------------------------
 Compiler: use function templates to instantiate function, which are then compiled
 
 If the code in the function template tries to perform some operation that the actual type
 doesn't support, then the functions may not compile
 
 -------------------------------------------------------------------------------------------
 OPERATORS, FUNCTION CALLS & FUNCTION TEMPLATES:
 
 Function templates when work with custom types, then they might not work with some
 operators which the class hasn't overloaded, to make the template function work, we have
 to define the operators inside the class
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>

class Cents
{
private:
    int m_cents{};
    
public:
    Cents(int cents) : m_cents{ cents } {}
    
    friend std::ostream& operator<<(std::ostream& out, const Cents& cents)
    {
        out << cents.m_cents;
        return out;
    }
    
    /// to make the max() function template work
    friend bool operator<(const Cents& c1, const Cents& c2)
    {
        return c1.m_cents < c2.m_cents;
    }
    
    /// to make the average() template function work with +=
    Cents& operator+=(const Cents& c)
    {
        m_cents += c.m_cents;
        return *this;
    }
    
    /// to make the average() template function work with /=
    Cents& operator/=(int x)
    {
        m_cents /= x;
        return *this;
    }
};

/// a template function
template <typename T>
const T& max(const T& x, const T& y)
{
    /// C++ doesn't know how to evaluate x < y when they are of type Cents
    /// to get around this problem, simply overload operator< for any class that we wish to use max() with
    /// operator< is called
    return (x < y) ? y : x;
}

/// function template calculates the average number of objects in an array
template <typename T>
T average(const T* my_array, int num_values)
{
    /// T is of type Cents when Cents object passed from the main()
    T sum{ 0 };
    
    /// C++ doesn't know how to work with += and /= when objects are of type Cents
    for (int i{ 0 }; i < num_values; ++i)
        sum += my_array[i];
    
    /// works because Cents has defined the overloaded operator /=
    sum /= num_values;
    return sum;
}

int main()
{
    Cents nickel{ 5 };
    Cents dime{ 10 };
    
    /// calling max() with objects of type Cents
    /// this works because operator< is overloaded for Cents class
    Cents bigger = max(nickel, dime);
    
    std::cout << bigger << " is bigger.\n";
    
    /// using average() with built in types
    /// average() works fine with built in types
    int A[] { 1, 2, 3, 4, 5};
    std::cout << average(A, 5) << '\n';
    
    double B[] { 3.12, 3.45, 9.23, 6.34 };
    std::cout << average(B, 4) << '\n';
    
    Cents cents_array[] { Cents{ 5 }, Cents{ 10 }, Cents{ 15 }, Cents{ 14 } };
    std::cout << average(cents_array, 4);
    
    return 0;
}
