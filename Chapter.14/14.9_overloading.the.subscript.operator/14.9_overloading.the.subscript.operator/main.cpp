//
//  main.cpp
//  14.9_overloading.the.subscript.operator
//
//  Created by Εκλεκτός εν Χριστώ on 7/25/23.
//

/*
 -------------------------------------------------------------------------------------------
 OVERLOADING OPERATOR[] : [] must be overloaded as a member function, it will take one
 parameter which is index of the element in array
 
 WHY OPERATOR[] RETURNS A REFERENCE?
 
 example:   list[12] = 112;
 
 explanation: [] has higher precedence than = operator, so [] evaluates first
 list[12] calls operator[] which is defined to return a reference to list.m_list[12], it
 actually returns the actual array element list.m_list[12] and on right side we provided 112
 which is then assigned to the returned array element
 
 value on the left hand side of an assignment: must be an l-value which has an actual
 memory address
 
 references: are always l-values, because we can only take a reference of variables that
 have memory addresses
 
 if operator[] returned an integer by value instead of reference, then list[12] would call
 operator[] which would return the value of list.m_list[12], suppose if the value returned
 at list.m_list[12] is 11, then the expression becomes 11 = 112, that makes no sense
 
 that's why operator[] returns a reference
 
 -------------------------------------------------------------------------------------------
 DEALING WITH CONST OBJECTS:
 
 operator[] - is non-const, we can use it as an l-value to change the state of non-const
 objects
 
 What if object is const?
 
 Solution is that we can define const and non-const version of operator[] separately
 
 -------------------------------------------------------------------------------------------
 ERROR CHECKING:
 
 when we access arrays, the subscript operator doesn't check whether the index passed is
 valid or invalid
 
 if we know the size of the array, we can make overloaded subscript operator check to ensure
 if the index is within bounds
 
 we can use assert and std::size to check whether the index is valid or invalid
 
 -------------------------------------------------------------------------------------------
 POINTERS TO OBJECTS & OVERLOADED OPERATOR[]: dont' mix them
 
 if you try to call operator[] on a pointer to an object - Compiler will assume you're
 trying to index an array of objects of that type
 
 RULE:
 make sure you're not trying to call operator[] on a pointer to an object
 
 -------------------------------------------------------------------------------------------
 The parameter type of operator[]: doesn't need to be an integer
 
 We can define that the overloaded operator[] take a value of any type we desire, like it
 can take a double, std::string or whatever else required
 
 operator[] to take a std::string - can be useful when writing certain kinds of classes,
 such as those that use words as indices
 
 operator[] is often implemented in string classes to allow the user to access a single
 character of the string
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <cassert>      /// for assert()
#include <iterator>     /// for std::size()
#include <string_view>
#include <vector>
#include <algorithm>

class Intlist
{
private:
    int m_list[10] {};
    
public:
    /// using operator[] without a subscript inside is not considered a valid syntax,
    /// so default value to the function parameter shouldn't be provided
    /// int& - used so that [] return a reference and not return int by value
    /// this function is for non-const objects
    int& operator[] (int index);
    
    /// this is a const version of the operator[], can be used to call on const objects
    /// which means this can only be used for reading and not writing
    /// function can return int or const int& if returning a non-fundamental type
    const int& operator[] (int index) const;
};

/// overloading the [ ] operator, it expects an index and returns the array element at that index
int& Intlist::operator[] (int index)
{
    /// using the assert to  make sure the index is valid
    ///  if index is invalid, the assert evaluates to false, the program
    ///  terminates with an error message, better than corrupting the memory
    ///  this is the most common method of doing error checking of this sort
    assert(index >= 0 && index < std::size(m_list));
    
    return m_list[index];
}

const int& Intlist::operator[] (int index) const
{
    assert(index >= 0 && index < std::size(m_list));
    
    return m_list[index];
}



class Stupid
{
private:
    
public:
    void operator[] (std::string_view index);
};

/// function parameter can be any type and not just an integer
void Stupid::operator[](std::string_view index)
{
    std::cout << index;
}



struct StudentGrade
{
    std::string name{};
    char grade{};
};

class GradeMap
{
private:
    std::vector<StudentGrade> m_map{};
    
public:
    char& operator[] (std::string_view name);
};

/// returns a reference to a char, that will be the grade
char& GradeMap::operator[] (std::string_view name)
{
    auto found{ std::find_if(m_map.begin(), m_map.end(),
        [&](const auto& student)            /// this is a lambda function
        {
        return (student.name == name);
        })
        };
    
    /// if the student name already exists return a reference to the grade
    if (found != m_map.end())
        return found->grade;
    
    /// if name doesn't exist, then add a StudentGrade for this new student
    /// return a reference to the grade for the student we just added to the vector
    /// back() - used to access the element we just added to the vector
    m_map.push_back({ std::string{name} });
    
    return m_map.back().grade;
}


int main()
{
    Intlist list{};
    
    for (int i{ 0 }; i < 10; ++i)
        list[i] = i + 1;
    
    for (int i{ 0 }; i < 10; ++i)
        std::cout << list[i] << ' ';
    std::cout << '\n';
    
    /// 8 is passed as an argument to the overload function operator[ ]
    /// non-const version of operator[] is called
    std::cout << list[8] << '\n';
    
    const Intlist const_list{};
    
    /// const version is called
    /// cannot assign to a returned r-value by operator[]
    /*const_list[0] = 1;*/
    
    /// read only access, const version is called
    std::cout << const_list[0] << '\n';
    
    Intlist* p_list{ new Intlist{} };
    
    /// this will assume that we're trying to index 0 of an array of Intlist
    /*p_list[0] = 1;*/
    
    /// this is the valid syntax for index 0 of an array of Intlist
    /// first dereference the pointer, that will return the Intlist object, then call operator[] on the object
    /// operator[] has higher precedence than operator*, so parentheses are required
    (*p_list)[0] = 1;
    
    std::cout << p_list << '\n';
    std::cout << (*p_list)[1] << '\n';
    
    for (int i{ 0 }; i < 10; ++i)
        /// dereference the pointer then call operator[]
        std::cout << (*p_list)[i] << ' ';
    std::cout << '\n';
    
    /// string passed to operator[], allowed
    Stupid stupid{};
    stupid["HELLO WORLD!\n"];
    
    GradeMap grades{};
    
    grades["Joe"] = 'A';
    grades["Ruby"] = 'C';
    
    std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
    std::cout << "Ruby has a grade of " << grades["Ruby"] << '\n';
    
    return 0;
}
