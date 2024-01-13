//
//  Array.h
//  26.1_template.classes
//
//  Created by Εκλεκτός εν Χριστώ on 11/16/23.
//

#ifndef Array_h
#define Array_h

#include <cassert>

/// template declaration
template <class T>
class Array
{
private:
    int m_length{};
    T* m_data{};
    
public:
    Array(int length)
    {
        assert(length > 0);
        m_data = new T[length] {};
        m_length = length;
    }
    
    /// we don't want to allow copies of Array to be created
    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;
    
    ~Array()
    {
        delete[] m_data;
    }
    
    void erase()
    {
        delete[] m_data;
        m_data = nullptr;
        m_length = 0;
    }
    
    T& operator[](int index);
    
    int get_length() const { return m_length; }
};

/// solution 2: including the inline code file in the header
/// so the definition for operator[] is included in the array.h file and template instantiation code works in the main
#include "Array.inl"

#endif /* Array_h */
