//
//  IntArray.h
//  16.6_container.classes
//
//  Created by Εκλεκτός εν Χριστώ on 7/29/23.
//

#ifndef IntArray_h
#define IntArray_h

#include <cassert>

/// container class
class IntArray
{
private:
    int m_length{};
    int* m_data{};
    
public:
    /// constructs an empty array
    IntArray() = default;
    
    /// constructs an array of a predetermined size
    IntArray(int length) : m_length{ length }
    {
        assert(length >= 0);
        
        if (length > 0)
            m_data = new int[length]{};
    }
    
    /// destructor to clean up the IntArrays
    ~IntArray()
    {
        delete[] m_data;
    }
    
    /// erase the object
    void erase()
    {
        delete[] m_data;
        
        m_data = nullptr;
        m_length = 0;
    }
    
    int& operator[](int index)
    {
        /// passed index validation
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }
    
    int get_length() const { return m_length; }
    
    /// resize the array, existing elements will be destroyed but operation will be fast
    void reallocate(int new_length)
    {
        /// delete any existing elements in the array
        erase();
        
        /// if the new array is going to be empty, just return simply
        if(new_length <= 0)
            return;
        
        /// then reallocate new elements
        m_data = new int[new_length];
        m_length = new_length;
    }
    
    /// resizes the array, existing elements are kept but operation is slow
    void resize(int new_length)
    {
        /// if the new array length is same as the old array then do nothing
        if (m_length == new_length)
            return;
        
        /// if we're resizing to an empty array, do that and return
        if (new_length <= 0)
            erase();
        
        /// allocate a new array
        int* temp_array{ new int[new_length] };
        
        /// figure out how many elements are there in the existing array
        if (m_length > 0)
        {
            int element_to_copy{ (new_length > m_length) ? new_length : m_length };
            
            /// copy the elements one by one
            for (int index{ 0 }; index < element_to_copy; ++index)
                temp_array[index] = m_data[index];
            
            /// delete the old array
            delete[] m_data;
            
            /// point the m_data to new array
            m_data = temp_array;
            m_length = new_length;
        }
    }
    
    /// copy constructor
    IntArray(const IntArray& array)
    {
        /// set the size of the new array
        reallocate(array.get_length());
        
        /// then copy the elements
        for (int index{ 0 }; index < m_length; ++index)
            m_data[index] = array.m_data[index];
    }
    
    /// copy assignment
    IntArray& operator=(const IntArray& array)
    {
        /// self assignment check
        if (&array == this)
            return *this;
        
        /// set the size of the new array
        reallocate(array.get_length());
        
        /// then copy the elements
        for (int index{ 0 }; index < m_length; ++index)
            m_data[index] = array.m_data[index];
        
        return *this;
    }
    
    void insert_before(int value, int index)
    {
        /// sanity check the index value
        assert(index >= 0 && index <= m_length);
        
        /// create a new array one element larger than the old array
        int* new_array{ new int[m_length + 1] };
        
        /// copy all the elements up to the index
        for (int before{ 0 }; before < index; ++before)
            new_array[before] = m_data[before];
        
        /// inset the new element into the new array
        new_array[index] = value;
        
        /// copy all the values after the inserted element
        for (int after{ index }; after < m_length; ++after)
            new_array[after + 1] = m_data[after];
        
        /// delete the old array and use the new array
        delete[] m_data;
        m_data = new_array;
        ++m_length;
    }
    
    void remove(int index)
    {
        /// validate the index
        assert(index >= 0 && index < m_length);
        
        /// if this is the last remaining element in the array, set the array to empty
        if (m_length == 1)
        {
            erase();
            return;
        }
        
        /// create a new array one element smaller than the old array
        int* new_array{ new int[m_length - 1] };
        
        /// copy all the elements up to the index
        for (int before{ 0 }; before < index; ++before)
            new_array[before] = m_data[before];
        
        /// copy all the values after the removed element
        for (int after{ index + 1 }; after < m_length; ++after)
            new_array[after - 1] = m_data[after];
        
        /// delete the old array and use the new one
        delete[] m_data;
        m_data = new_array;
        --m_length;
    }
    
    void insert_at_beginning(int value) { insert_before(value, 0); }
    void insert_at_end(int value) { insert_before(value, m_length); }
};

#endif /* IntArray_h */
