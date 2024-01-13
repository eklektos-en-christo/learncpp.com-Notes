//
//  main.cpp
//  14.15_overloading.the.assignment.operator
//
//  Created by Εκλεκτός εν Χριστώ on 7/26/23.
//

/*
 -------------------------------------------------------------------------------------------
 COPY ASSIGNMENT OPERATOR: is used to copy values from one object to another already
 existing object
 
 COPY ASSIGNMENT VS COPY CONSTRUCTOR:
 
 The purpose of both is same, both copy one object to another except that the copy
 constructor initializes the new object but copy assignment replaces the contents of
 existing objects
 
 SUMMARY:
 
 -if a new object has to be created before the copying can occur, the copy constructor is
 used, this includes passing or returning the objects by value
 
 -if a new object doesn't have to be created before the copying can occur, the assignment
 operator is used
 
 COPY CONSTRUCTOR: creates a new object
 COPY ASSIGNMENT : modifies an existing object
 
 -------------------------------------------------------------------------------------------
 OVERLOADING THE ASSIGNMENT OPERATOR:
 
 it must be overloaded as a member function, we can chain multiple assignment together if
 the operator= returns *this
 
 -------------------------------------------------------------------------------------------
 ISSUES DUE TO SELF-ASSIGNMENT:
 
 C++ : allows self-assignment
 
        i.e.    Fraction f1{ 2, 2};
                f1 = f1;            /// self assignment
 
 Self-assignment: doesn't need to do anything at all
 
 Cases: when an assignment operator needs to dynamically assign memory, self assignment can
 actually be dangerous
 
 -------------------------------------------------------------------------------------------
 DETECTING AND HANDLING SELF-ASSIGNMENT:
 
 By checking if the address of our implicit object is the same as the address of the object being passed in as a parameter, we can have our assignment operator just return immediately without doing any other work.
 
 -------------------------------------------------------------------------------------------
 WHEN NOT TO HANDLE SELF-ASSIGNMENT:
 
 self assignment check is skipped for copy constructors, because the object being copy
 constructed is newly created, the only case where the newly created object can be equal to
 the object being copied is when you try to initialize a newly defined object with itself'
 
 like this:     some_class c{ c };      /// compiler will warn about this
 
 self assignment check maybe omitted in classes that can naturally handle self-assignment
 
 self-assignment - is a rare event
 
 BETTER PRACTICE: use self-assignment check to code defensively and then selectively
 optimize later
 
 -------------------------------------------------------------------------------------------
 COPY AND SWAP IDIOM: a better way to handle self-assignment issues
 
 The Copy and Swap idiom is a C++ programming technique used to implement a safe and efficient assignment operator (the copy assignment operator) for a class. It involves creating a temporary copy of the object to be assigned, swapping its contents with the current object, and allowing the temporary copy to be destroyed, effectively deallocating any resources that were owned by the current object before the assignment.
 
 -------------------------------------------------------------------------------------------
 DEFAULT COPY ASSIGNMENT OPERATOR:
 
 compiler will provide a default public copy assignment operator if you don't provide one,
 
 this assignment operator: does member-wise assignment
 
 To prevent the assignments being made: make the copy assignment operator private or use the
 delete keyword
 
 -------------------------------------------------------------------------------------------
 */

#include <cassert>
#include <iostream>
#include <algorithm>            /// for std::max



class Fraction
{
private:
    int m_numerator { 0 };
    int m_denominator { 1 };
    
public:
    Fraction(int num = 0, int den = 1) : m_numerator{ num }, m_denominator{ den }
    {
        assert(m_denominator != 0);
        std::cout << "DEFAULT CONSTRUCTOR CALLED!\n";
    }
    
    Fraction(const Fraction& f)
    : m_numerator{ f.m_numerator }, m_denominator{ f.m_denominator }
    {
        std::cout << "COPY CONSTRUCTOR CALLED!\n";
    }
    
    /// copy assignment
    /// delete to prevent the assignments from being made
    /// or make the copy assignment private
/*private:*/
    Fraction& operator= (const Fraction& f) /*= delete*/;
    
    friend std::ostream& operator<<(std::ostream& out, const Fraction& f);
};

/// overloaded assignment or copy assignment
Fraction& Fraction::operator=(const Fraction& f)
{
    /// self assignment guard maybe omitted because
    /// all of the operations done by the function can handle self-assignment properly
    if (this == &f)
        return *this;
    
    /// copy the contents of Fraction f to the existing object
    /// existing object is five_thirds_again in main()
    m_numerator = f.m_numerator;            /// can handle self-assignment
    m_denominator = f.m_denominator;        /// can handle self-assignment
    std::cout << "COPY ASSIGNMENT CALLED!\n";
    
    /// after copying the contents, return the modified object
    /// *this is returned, so that we can chain this operator=
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Fraction& f)
{
    out << f.m_numerator << '/' << f.m_denominator;
    return out;
}



/*----------------------------------------------------------------------------------------*/
class MyString
{
private:
    char* m_data {};
    int m_length {};
    
public:
    MyString(const char* data = nullptr, int length = 0)
    : m_length { std::max(length, 0) }
    {
        if (length)
        {
            m_data = new char[static_cast<std::size_t>(length)];
            
            for (int i{ 0 }; i < length; ++i)
                m_data[i] = data[i];
        }
    }
    
    ~MyString()
    {
        delete[] m_data;
    }
    
    MyString& operator= (const MyString& str);
    
    friend std::ostream& operator<<(std::ostream& out, const MyString& s);
};

MyString& MyString::operator= (const MyString& str)
{
    /// self assignment check
    /// if the address of our implicit object is same as the address of the object being passed in as a parameter
    /// then return immediately without doing anything
    /*if (this == &str)
        return *this;*/
    
    /// if the data exists in the current string, delete it
    /// this m_data is same as str.m_data
    /// m_data is deleted
    /// str.m_data has been deleted too
    /// m_data and str.m_data are dangling
    if (m_data)
        delete[] m_data;
    
    m_length = str.m_length;
    m_data = nullptr;
    
    /// copy the data from str to the implicit object
    /// new memory allocated to m_data (str.m_data)
    if (m_length)
        m_data = new char[static_cast<std::size_t>(str.m_length)];
    
    /// copying str.m_data to m_data
    /// str.m_data was never initialized, so garbage is copied
    for (int i{ 0 }; i < str.m_length; ++i)
        m_data[i] = str.m_data[i];
    
    /// return the existing object, so we can chain this operator
    return *this;
}

std::ostream& operator<<(std::ostream& out, const MyString& s)
{
    out << s.m_data;
    return out;
}
/*----------------------------------------------------------------------------------------*/



int main()
{
    Fraction five_thirds { 5, 3 };
    Fraction five_thirds_again {};
    
    five_thirds_again = five_thirds;
    
    std::cout << five_thirds_again << '\n';
    
    Fraction one_two { 1, 2 };
    Fraction three_four { 3, 4 };
    Fraction five_six { 5, 6 };
    
    /// chaining the operator= to change multiple objects
    /// copy assignment called 2 times
    one_two = three_four = five_six;
    
    std::cout << one_two << ' ' << three_four << ' ' << five_six << '\n';
    
    MyString alex ( "Alex", 5 );
    MyString employee;
    employee = alex;

    std::cout << employee << '\n';
    
    /// garbage is being copied from right alex to left alex, both are same
    /// right alex is deallocated in the operator=, it is dangling now
    alex = alex;
    std::cout << alex << '\n';
    
    return 0;
}
