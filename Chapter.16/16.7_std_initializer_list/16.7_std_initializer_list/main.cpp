//
//  main.cpp
//  16.7_std_initializer_list
//
//  Created by Εκλεκτός εν Χριστώ on 7/29/23.
//

/*
 -------------------------------------------------------------------------------------------
 CLASS INITIALIZATION USING std::initializer_list -
 
 When a compiler sees an initializer list, it automatically converts it into an object of
 type std::initializer_list.
 
 If we create a constructor that take a std::initializer_list parameter, we can create
 objects using the initializer list as an input
 
 <initializer_list> - header
 
 std::initializer_list - type of data it will store should be specified in <> brackets,
 unless it is initialized right away
 
 std::initializer_list - has a misnamed size() function that returns the number of elements
 in the list, it is useful when we need to know the length of the list passed in
 
 std::initializer_list - is ofter passed by value, it is a view, copying the
 initializer_list doesn't copy the elements in the list
 
 -------------------------------------------------------------------------------------------
 LIST INITIALIZATION PREFERS LIST CONSTRUCTORS OVER NON-LIST CONSTRUCTORS:
 
 Non-empty initializer lists: always favor a matching initializer_list constructor over
 other potentially matching constructors
 
        // uses IntArray(int) constructor, allocates array of 5 integers
        IntArray a1(5);
 
        // used IntArray(std::initializer_list<int>), array of 1 with element 5
        IntArray a2{5};
 
 a1: direct initialization doesn't consider list constructors
 
 a2: used list initialization which favors list constructors
 
 KEY INSIGHT: list initialization favors matching list-constructors over matching non-list
 constructors
 
 BEST PRACTICE:
 
 When initializing a container that has a list constructor-
 
 -use brace initialization when intending to call the list constructor, e.g. because the
 initializers are element values
 
 -use direct initialization when intending to call the non-list constructor, e.g. because
 the initializers are not element values
 
 // Calls std::vector::vector(std::vector::size_type), 5 value-initialized elements: 0 0 0 0 0
 // initializer 5 is not an element value here
 std::vector<int> array(5);
 
 // Calls std::vector::vector(std::initializer_list<int>), 1 element: 5, initializer 5 is an element value
 std::vector<int> array{ 5 };
 
 -------------------------------------------------------------------------------------------
 ADDING LIST CONSTRUCTORS TO AN EXISTING CLASS IS DANGEROUS:
 
 List initialization: favors list constructors, adding list constructor to an existing class
 that didn't previously have any list constructor can cause existing programs to silently
 change behavior
 
 WARNING:
 Adding a list constructor to an existing class that did not have one may break existing programs.
 
 -------------------------------------------------------------------------------------------
 CLASS ASSIGNMENT USING std::initializer_list -
 
 You can also use std::initializer_list to assign new values to the class by overloading the
 assignment operator to take std::initializer_list parameter
 
 If you implement a constructor that takes a std::initializer_list, you should ensure you do
 at least one of the following:
 
 - provide an overloaded list assignment operator
 - provide a proper deep-copying copy assignment operator
 - delete the copy assignment operator
 
 BEST PRACTICE:
 if you provide list construction, it's a good to provide list assignment as well
 
 -------------------------------------------------------------------------------------------
 SUMMARY:
 
 Implementing a constructor that takes a std::initializer_list parameter allows us to use
 list initialization with out custom classes, we can also use initializer_list to implement
 other functions that need to use an initializer list such as an assignment operator
 
 -------------------------------------------------------------------------------------------
 */

#include <initializer_list>
#include <cassert>
#include <iostream>

class IntArray
{
private:
    int m_length {};
    int* m_data {};

public:
    IntArray() = default;

    IntArray(int length)
        : m_length{ length }
        , m_data{ new int[length]{} }
    {

    }

    IntArray(std::initializer_list<int> list) /// allow IntArray to be initialized via list initialization
        : IntArray(static_cast<int>(list.size())) /// use delegating constructor to set up initial array
    {
        /// Now initialize our array from the list
        int count{ 0 };
        for (auto element : list)
        {
            m_data[count] = element;
            ++count;
        }
    }

    ~IntArray()
    {
        delete[] m_data;
        /// we don't need to set m_data to null or m_length to 0 here, since the object will be destroyed immediately after this function anyway
    }

    IntArray(const IntArray&) = delete; /// to avoid shallow copies
    IntArray& operator=(const IntArray& list) = delete; /// to avoid shallow copies
    
    IntArray& operator=(std::initializer_list<int> list)
    {
        int length{ static_cast<int>(list.size()) };
     
        /// if the new list is a different size, reallocate the existing array
        if (length != m_length)
        {
            delete[] m_data;
            m_length = length;
            m_data = new int[length]{};
        }
        
        /// now initialize the array from the list passed
        int count{ 0 };
        for (auto element : list)
        {
            m_data[count] = element;
            ++count;
        }
        
        return *this;
    }

    int& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    int getLength() const { return m_length; }
};

class Foo
{
public:
    Foo(int, int)
    {
        std::cout << "Foo(int, int) called\n";
    }
    
    /// added a list constructor to an existing class Foo
    Foo(std::initializer_list<int>)
    {
        std::cout << "Foo(std::initializer_list<int>) called\n";
    }
};

int main()
{
    Foo f1(1, 2);
    Foo f2{ 1, 2 };
    
    IntArray array { 5, 4, 3, 2, 1 }; /// initializer list
    for (int count{ 0 }; count < array.getLength(); ++count)
    std::cout << array[count] << ' ';

    std::cout << '\n';

    array = { 1, 3, 5, 7, 9, 11 };

    for (int count{ 0 }; count < array.getLength(); ++count)
        std::cout << array[count] << ' ';

    std::cout << '\n';
    
    return 0;
}
