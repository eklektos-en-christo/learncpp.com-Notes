//
//  main.cpp
//  26.6_partial.template.specialization.for.pointers
//
//  Created by Εκλεκτός εν Χριστώ on 11/23/23.
//

/*
 Full template specialization: forces us to fully resolve template types
 */

#include <iostream>

/// template class that works with any types
template <class T>
class Storage
{
private:
    T m_value{};
    
public:
    Storage(T value) : m_value{ value }
    {
        std::cout << "template class used!\n";
    }
    
    ~Storage()
    {
    }
    
    void print() const { std::cout << m_value << '\n'; }
};

/// partial specialization of Storage class that works with pointer types specially
template <class T>
class Storage<T*>
{
private:
    T* m_value{};
    
public:
    Storage(T* value) : m_value{ new T { *value } }
    {
        std::cout << "partially specialized template class used!\n";
    }
    
    ~Storage()
    {
        delete m_value;
    }
    
    void print() const { std::cout << *m_value << '\n'; }
};

/*--------------------------------------------------------------------------------------------------------*/

/// fully specializing the Storage class for char* type
template <>
class Storage<char*>
{
private:
    char* m_value{};
    
public:
    /// fully specialising the constructor for char*
    Storage(char* value)
    {
        int length{ 0 };
        while (value[length] != '\0')
            ++length;
        ++length;
        
        m_value = new char[length];
        
        for (int count{ 0 }; count < length; ++count)
            m_value[count] = value[count];
    }
    
    /// fully specialising the constructor for char*
    ~Storage() { delete[] m_value; }
    
    
    /// fully specialising the print function for char*
    void print() const
    {
        std::cout << m_value;
    }
};

/*--------------------------------------------------------------------------------------------------------*/
/// full specialization for the individual functions will look like this
///
/// constructor
/*template <>
Storage<char*>::Storage(char* value)
{
    int length{ 0 };
    while (value[length] != '\0')
        ++length;
    ++length;
    
    m_value = new char[length];
    
    for (int count{ 0 }; count < length; ++count)
        m_value[count] = value[count];
}

/// destructor full specialization
template <>
Storage<char*>::~Storage()
{
    delete[] m_value;
}

/// print() function's full specialization
template <>
void Storage<char*>::print() const
{
    std::cout << m_value;
}*/

/*--------------------------------------------------------------------------------------------------------*/

int main()
{
    Storage<int> my_int{ 2 };
    my_int.print();
    
    int x{ 9 };
    
    /// template parameter int* is passed, compiler will see that there is
    /// a partially specialized template class defined that works with any
    /// pointer type, so compiler will instantiate a version of Storage using that partial template
    Storage<int*> my_int_ptr{ &x };
    
    /// changing the value of x won't affect the my_int_ptr
    /// deep copy is performed by the constructor of class Storage<T*>
    /// my_int_ptr will be affected if there was not partial specialization of the pointer types
    /// the constructor of the normal template class would do a shallow copy pointer assignment
    /// which means m_int_ptr.m_value and x would be referencing the same address
    x = 10;
    my_int_ptr.print();
    
    Storage<int> my_int5{ 5 };
    my_int5.print();
    
    int y{ 22 };
    Storage<int*> my_int_ptr_2{ &y };
    
    y = 28;
    my_int_ptr_2.print();
    
    char* name{ new char[40] { "Leon\n" } };
    
    Storage<char*> my_name{ name };
    
    delete[] name;
    
    my_name.print();
    
    return 0;
}
