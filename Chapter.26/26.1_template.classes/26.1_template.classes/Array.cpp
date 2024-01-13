//
//  Array.cpp
//  26.1_template.classes
//
//  Created by Εκλεκτός εν Χριστώ on 11/16/23.
//

#include "Array.h"

// member functions defined outside the class need their own template declaration
template <typename T>
T& Array<T>::operator[](int index) // now returns a T&
{
    assert(index >= 0 && index < m_length);
    return m_data[index];
}
