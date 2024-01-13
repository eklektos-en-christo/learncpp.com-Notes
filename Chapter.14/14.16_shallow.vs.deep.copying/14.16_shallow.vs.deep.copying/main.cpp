//
//  main.cpp
//  14.16_shallow.vs.deep.copying
//
//  Created by Εκλεκτός εν Χριστώ on 7/26/23.
//

/*
 -------------------------------------------------------------------------------------------
 SHALLOW COPYING:
 
 Default copy constructor and default assignment operator provided by the C++: use a copying
 method called member-wise copy, this is shallow copy
 
 This mean C++ copies each member of the class individually, when classes are simple, e.g.
 they don't contain any dynamically allocated memory, this works well
 
 like in the fraction class, the members don't use dynamic memory, so default copy
 constructor and assignment operator work fine with the fraction class, all members are
 copied individually, there is no need to write our own version of copy constructor and
 assignment in this case
 
 When designing classes that handle dynamic memory, memberwise/shallow copying can get us in
 a lot of trouble, because shallow copies of a pointer just copy the address of the pointer,
 it doesn't allocate memory or copy the contents being pointed to
 
 -------------------------------------------------------------------------------------------
 DEEP COPYING:
 
 answer to the shallow copying is to do the deep copy on any non-null pointers being copied
 
 Deep copy: allocates memory for the copy(MyString class below) and then copies the actual
 value, so that the copy lives in the distinct memory from the source
 
 Deep copies: requires that we write our own copy constructors and copy assignment operators
 
 -------------------------------------------------------------------------------------------
 BETTER SOLUTION:
 
 std::string and std::vector etc - should be used, they handle all their memory management,
 they do proper deep copying
 
 -------------------------------------------------------------------------------------------
 SUMMARY:
 
 Default copy constructor & default copy assignment operators: do shallow copies, which is
 fine for classes that contain no dynamically allocated variables
 
 Classes with dynamically allocated variables: need to have a copy constructor and
 assignment operator that do a deep copy
 
 Favor using classes in the STD library over doing your own memory management
 
 -------------------------------------------------------------------------------------------
 */

#include <cstring>
#include <cassert>
#include <iostream>

class MyString
{
private:
    char* m_data{};
    int m_length{};
    
public:
    MyString(const char* source="")
    {
        /// make sure the source is not a null string
        assert(source);
        
        /// find the length of the source
        /// +1 is for the null terminator
        m_length = static_cast<int>(std::strlen(source)) + 1;
        
        /// allocate a buffer equal to this length
        m_data = new char[m_length];
        
        /// copy the source into our internal buffer
        for (int i{ 0 }; i < m_length; ++i)
            m_data[i] = source[i];
    }
    
    ~MyString()
    {
        /// deallocate the string m_data
        delete[] m_data;
    }
    
    /// class contains no default copy constructor and copy assignment operator
    /// C++ will provide them for us
    /// m_data is just a shallow pointer copy of source.m_data,
    /// this means they now point to the same thing
    /*
    MyString(const MyString& source)
        : m_length { source.m_length }
        , m_data { source.m_data }
    {
    }*/
    
    MyString(const MyString& source);
    MyString& operator=(const MyString& source);
    
    void deepcopy(const MyString& source);
    
    char* get_string() { return m_data; }
    int get_length() { return m_length; }
};

void MyString::deepcopy(const MyString& source)
{
    /// deallocate any value that this string is holding
    delete[] m_data;
    
    /// m_length isn't a pointer, so shallow copy it
    m_length = source.m_length;
    
    /// m_data is a pointer, so deep copy it if it is non-null
    if (source.m_data)
    {
        /// this is new string allocated, it is distinct from the source.m_data
        m_data = new char[m_length];
        
        /// do the copy
        for (int i{ 0 }; i < m_length; ++i)
            m_data[i] = source.m_data[i];
    }
    else
        /// if the pointer is null then set the m_data to nullptr too
        /// it is same as shallow copy
        m_data = nullptr;
}

MyString::MyString(const MyString& source)
{
    deepcopy(source);
}

MyString& MyString::operator=(const MyString& source)
{
    /// check the self-assignment, if passes then do deep copy
    if (&source != this)
        /// reallocation and deallocation is handled inside deepcopy()
        deepcopy(source);
    
    /// for chaining the assignment operator
    return *this;
}

int main()
{
    /// this calls MyString constructor,
    /// constructor allocates some memory
    /// sets hello.m_data to point to the allocated memory
    /// copies the parameter string into hello.m_data
    MyString hello{ "hello, world!" };
    
    {
        /// default copy constructor is called
        /// copy.m_data is initialized to the same address of hello.m_data
        /// it copies the pointer
        /// at the end of the block, the copy is destroyed,
        /// the destructor deallocates the copy's string,
        /// hello is left with a dangling pointer, because it was pointing to the same string
        /// hello is now pointing to the invalid memory
        /*MyString copy{ hello };*/
    }   /// copy gets destroyed here, destructor called on copy
    
    /// undefined behavior
    std::cout << hello.get_string() << '\n';
    
    {
        /// this is destroyed at the end of the block
        /// but it's a new string allocated from hello
        /// it's destruction won't affect the hello
        MyString copy_hello{ hello };
    }
    
    /// working now, because of the deep copy
    std::cout << hello.get_string() << '\n';
    
    return 0;
}
