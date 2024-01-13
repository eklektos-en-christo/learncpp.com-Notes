//
//  main.cpp
//  14.10_overloading.the.parentheses.operator
//
//  Created by Εκλεκτός εν Χριστώ on 7/25/23.
//

/*
 -------------------------------------------------------------------------------------------
 operator() - it allows you to vary both the type & number of parameter it takes
 
 other operator - dont' allow you to vary the number of parameters they take but only type
 
 FIRST: operator() must be implemented as a member function
 
 SECOND: operator() is used to call functions in non-object oriented C++
 
 CLASSES CASE: operator() is just a normal operator that calls a function named operator()
 like any other overloaded operators
 
 operator() - can take as many parameters as we want, we can use it to access the 2D array
 
 -------------------------------------------------------------------------------------------
 FUNCTORS: function object, they are classes that operate like functions, operator() can
 be used to implement the functors
 
 Functors: can store data in member variables, since they are classes
 
 Functors: we can instantiate as many separate functor objects as we want, then use them all
 simultaneously, they can also have member function like reset() etc. for convenient things
 
 Functors: are used in more advanced programming topics
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <cassert>
#include <string>
#include <string_view>


/*----------------------------------------------------------------------------------------*/
class Matrix
{
private:
    double m_data[4][4]{};
    
public:
    double& operator()(int row, int col);       /// for non-const objects
    double operator()(int row, int col) const;  /// for const objects
    
    void operator()();
};

double& Matrix::operator()(int row, int col)
{
    /// validating the indexes passed
    assert(col >= 0 && col < 4);
    assert(row >= 0 && row < 4);
    
    return m_data[row][col];
}

double Matrix::operator()(int row, int col) const
{
    /// validating the indexes passed
    assert(col >= 0 && col < 4);
    assert(row >= 0 && row < 4);
    
    return m_data[row][col];
}

/// reset the matrix to 0.0
/// this is not recommended, because it doesn't indicate what the operator is doing
void Matrix::operator()()
{
    for (int row{ 0 }; row < 4; ++row)
    {
        for (int col{ 0 }; col < 4; ++col)
        {
            m_data[row][col] = 0.0;
        }
    }
}
/*----------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------*/
class Accumulator
{
private:
    int m_counter{ 0 };
    
public:
    int operator() (int i) { return (m_counter+= i); }
    
    void reset() { m_counter = 0; }
};
/*----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------*/
class MyString
{
private:
    std::string m_string{};
    
public:
    MyString(const std::string& string = {}) : m_string{ string } {}
    
    friend std::ostream& operator<<(std::ostream& out, const MyString& s);
    MyString operator()(int start, int length);
    
    std::string_view substr(int start, int length);
};

MyString MyString::operator()(int start, int length)
{
    assert(start >= 0);
    assert(start + length <= static_cast<int>(m_string.length()) &&
           "MyString::operator(int, int): Substring is out of range\n");
    
    /// substr returns the std::string, copy of a part of the source string is made
    /// overloaded operator() uses this to construct a new MyString which contains a std::string, another copy
    /// MyString returned to the caller, another copy
    return m_string.substr(
            static_cast<std::string::size_type>(start),
            static_cast<std::string::size_type>(length)
            );
}

std::ostream& operator<<(std::ostream& out, const MyString& s)
{
    out << s.m_string;
    return out;
}

std::string_view MyString::substr(int start, int length)
{
    assert(start >= 0);
    assert(start + length <= static_cast<int>(m_string.length()) &&
           "MyString::operator(int, int): Substring is out of range\n");
    
    /// create a temporary std::string_view of m_string, inexpensive
    /// call member function substr on string_view to get the substring, non-null terminated view of m_string
    /// return that view to the caller, view is not dangling here because it is a view of m_string
    /// 3 std::string_view created, more efficient than creating 3 std::string
    return std::string_view{ m_string }.substr(
            static_cast<std::string_view::size_type>(start),
            static_cast<std::string_view::size_type>(length)
            );
}
/*----------------------------------------------------------------------------------------*/



int main()
{
    Matrix matrix{};
    matrix(1, 2) = 4.1;                         /// using operator() to work with 2D array
    std::cout << matrix(1, 2) << '\n';          /// operator() returning a reference, so printing is possible
    
    /// print the matrix
    for (int i{ 0 }; i < 4; ++i)
    {
        for (int j{ 0 }; j < 4; ++j)
        {
            std::cout << matrix(i, j) << '\t';
        }
        std::cout << '\n';
    }
    
    /// reset the matrix, void operator() called
    matrix();
    
    /// print the matrix again to check if reset is working
    /*for (int i{ 0 }; i < 4; ++i)
    {
        for (int j{ 0 }; j < 4; ++j)
        {
            std::cout << matrix(i, j) << '\t';
        }
        std::cout << '\n';
    }*/
    
    Accumulator accu1{};
    /// looks like a normal function call, but it stores an accumulated value, functor
    std::cout << accu1(2) << '\n';
    std::cout << accu1(3) << '\n';
    
    Accumulator accu2{};
    /// looks like a normal function call, but it stores an accumulated value functor
    std::cout << accu2(40) << '\n';
    std::cout << accu2(60) << '\n';
    
    MyString s{ "HELLO WORLD!" };
    /// starting at index 6 and return five chars
    std::cout << s(6, 5) << '\n';
    
    return 0;
}
