//
//  main.cpp
//  26.3_function.template.specialization
//
//  Created by Εκλεκτός εν Χριστώ on 11/16/23.
//

/*
 There are cases where it is useful to implement a templated function slightly different for a specific
 data type
 
 -----------------------------------------------------------------------------------------------------------
 FUNCTION TEMPLATE SPECIALIZATION/FULL/EXPLICIT FUNCTION TEMPLATE SPECIALIZATION:
 
 to create a specialized version let say for double:
 simply define the specialized function, if the function is a member function, then do so outside the class
 replace the template type with the specific type you wish to redefine the function for
 
 template <> - tells the compiler that it is a template function but there are not template parameters
 because we're explicitly specifying all of the types
 
 Non member template functions can also be specialized
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <iomanip>

template <class T>
class Storage
{
private:
    T m_value{};
    
public:
    Storage(T value) : m_value{ value }
    {
    }
    
    void print() const { std::cout << m_value << '\n'; }
};

/// we want the output to be in scientific notation for double type
/// defining the function template specialization for type double
/// compiler won't stencil out a function for the double type,
/// compiler will use this already defined function for the double type
/// template <> - to tell the compiler that it is a template function, no parameter
/// is required, we're explicitly specifying the type we want
template <>
void Storage<double>::print() const
{
    std::cout << std::scientific << m_value << '\n';
}

template <class T>
class StorageAnother
{
private:
    T m_value{};
    
public:
    StorageAnother(T value) : m_value{ value }
    {
    }
    
    void print() const
    {
        std::cout << m_value << '\n';
    }
    
    /// destructor is needed in the StorageAnother<T>, otherwise specialized destructor outside the class won't compile
    ~StorageAnother()
    {
    }
};

/// In case of char* type, we want the constructor to make a deep copy of the input string
/// when variable of char* will be allocated, this constructor will be used instead of the
/// default constructor, m_value will have it's own copy of the input string
template <>
StorageAnother<char*>::StorageAnother(char* const value)
{
    if (!value)
        return;
    
    int length{ 0 };
    
    /// figuring out the length of the string
    while (value[length] != '\0')
        ++length;
    /// +1 for null terminator
    ++length;
    
    /// allocate new memory to hold the input string
    m_value = new char[length];
    
    /// copy the data from input string to new string
    for (int count{ 0 }; count < length; ++count)
        m_value[count] = value[count];
}

/// defining a template specialized constructor to delete the m_value, when an StorageAnother<char*> variable goes out of scope
template <>
StorageAnother<char*>::~StorageAnother()
{
    delete[] m_value;
}

int main()
{
    Storage<int> integer{ 2 };
    integer.print();
    
    /// output will be in scientific notation - function template specialization
    Storage<double> double_{ 989.232 };
    double_.print();
    
    std::string s;
    
    std::cout << "Enter your name: ";
    std::cin >> s;
    
    Storage<char*> storage(s.data());
    
    storage.print();
    
    /// delete the input string
    s.clear();
    
    /// unexpected result -
    /// string s is pointing to the input string received from the user
    /// s's data is copied to storage, internally the pointer is copied
    /// both s and storage are pointing at the same data
    /// s.clear deletes the data
    /// storage is now accessing the deleted data
    /*storage.print();*/
    
    std::string string;
    
    std::cout << "enter name: ";
    std::cin >> string;
    
    StorageAnother<char*> my_name{ string.data() };
    
    my_name.print();
    string.clear();
    
    /// my_name.print() have its own copy of the input string
    my_name.print();
    
    return 0;
}
