//
//  main.cpp
//  26.4_class.template.specialization
//
//  Created by Εκλεκτός εν Χριστώ on 11/16/23.
//

/*
 CLASS TEMPLATE SPECIALIZATION:
 
 Class template specialization allows us to specialize a template class for a particular data type (or data
 types, if there are multiple template parameters). In this case, we’re going to use class template
 specialization to write a customized version of Storage8<bool> that will take precedence over the
 generic Storage8<T> class. This works analogously to how a specialized function takes precedence over
 a generic template function.

 Class template specializations are treated as completely independent classes, even though they are
 allocated in the same way as the templated class. This means that we can change anything and
 everything about our specialization class, including the way it’s implemented and even the functions it
 makes public, just as if it were an independent class. Here’s our specialized class
 
 */

#include <iostream>
#include <cstdint>

/// a templated class definition
template <class T>
class Storage8
{
private:
    T m_array[8];
    
public:
    void set(int index, const T& value)
    {
        m_array[index] = value;
    }
    
    const T& get(int index) const
    {
        return m_array[index];
    }
};

/// class above will work for any type, we want it to work differently for bool type, so specializing it for bool type
/// Storage8<bool> - to denote that we're specializing  a bool version of class Storage8
/// this class utilises a std::uint8_t(1 byte) instead of an array of 8 bytes
template <>             /// no template parameters
class Storage8<bool>
{
private:
    std::uint8_t m_data{};
    
public:
    void set(int index, bool value)
    {
        /// put a 1 in the bit we want to turn on/off
        auto mask{ 1 << index };
        
        if (value)
            m_data = m_data | mask;     /// turn the bit on if we are setting a bit
        else
            m_data = m_data & (~mask);  /// turn off the bit if we are setting off a bit
    }
    
    bool get(int index)
    {
        /// figuring out which bit we're getting
        auto mask{ 1 << index };
        /// get the value of the bit we're interested in, then implicit cast to boolean
        return (m_data & mask);
    }
};

int main()
{
    /// this uses the generic class Storage<T>, T is int here
    Storage8<int> int_storage;
    
    for (int count{ 0 }; count < 8; ++count)
        int_storage.set(count, count);
    
    for (int count{ 0 }; count < 8; ++count)
        std::cout << int_storage.get(count) << ' ';
    std::cout << '\n';
    
    /// this uses the specialized class, Storage<bool>
    Storage8<bool> bool_storage;
    
    for (int count{ 0 }; count < 8; ++count)
        bool_storage.set(count, count * 0);
    
    std::cout << std::boolalpha;
    
    for (int count{ 0 }; count < 8; ++count)
        std::cout << bool_storage.get(count) << ' ';
    std::cout << '\n';
    
    return 0;
}

