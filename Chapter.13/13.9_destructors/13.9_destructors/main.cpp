//
//  main.cpp
//  13.9_destructors
//
//  Created by Εκλεκτός εν Χριστώ on 7/10/23.
//

/*
 -------------------------------------------------------------------------------------------
 DESTRUCTORS: another special kind of class member function
 
 Destructor: it is executed when an object of that class is destroyed
 
 Constructors: for initialization
 Destructors: for clean up tasks and release of resources used by the class' object
 
 The class destructor is automatically called to do necessary cleanup before the object is
 removed from the memory, this happens when:
 -an object goes out of scope normally
 -a dynamically allocated object is explicitly deleted using delete keyword
 
 Simple classes that just initialize the values of normal member variables: doesn't need a
 destructor, C++ automatically clean up the memory
 
 If class object is holding any resource like dynamic memory, file, database etc or if you
 need to do any kind of maintenance before the object is destroyed: then the destructor is
 the perfect place to do so
 
 -------------------------------------------------------------------------------------------
 Naming rules for destructor:
 
 -should have the same name as the class, preceded by a tilde(~)
 -takes no arguments
 -has no return type
 
 A class: can only have a single destructor
 
 Don't call destructor explicitly: it is called automatically when the object is destroyed
 
 Rare cases: where you'd want to clean up an object more than once
 
 Destructors: may safely call other member functions since the object isn't destroyed until
 after the destructor executes
 
 Parentheses based initialization: should be used when initializing an array/container/list
 class with a length (as opposed to a list of elements).
 
 -------------------------------------------------------------------------------------------
 CONSTRUCTOR AND DESTRUCTOR TIMING:
 
 constructor: when object created
 destructor: when object destroyed
 
 Global variables: are constructed before main() and destroyed after main()
 
 -------------------------------------------------------------------------------------------
 RAII: Resource Acquisition Is Initialization
 
 RAII: is a programming technique in which the resource use is tied to the lifetime of
       objects with automatic duration e.g. non dynamically allocated objects.
 
 RAII: is implemented via classes with constructors and destructors
 
 Resource: is typically acquired in the object's constructor, then it can be used while the
 object is alive
 
 Resource: is released in the destructor, when the object is destroyed
 
 RAII: prevents resource leaks e.g. memory not being deallocated, all resource objects are
 cleaned up automatically
 
 std::string & std::vector - example classes that follow RAII
 
 -------------------------------------------------------------------------------------------
 std::exit() - if this is used, then program will terminate and no destructors will be
 called
 
 Be cautious: if you're relying on the destructors to do necessary cleanup
 
 -------------------------------------------------------------------------------------------
 constructors & destructors: when both used together, classes can initialize and cleanup
 after themselves without the programmer having to do any special work, this reduces the
 probability of making an error and makes classes easier to use
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <cassert>
#include <cstddef>

/// this class implements RAII
class Intarray
{
private:
    int* m_array {};
    int m_length {};
    
public:
    /// this is a constructor
    /// allocates the dynamic array for pointer member m_array
    /// allocation in the constructor
    Intarray(int length)
    {
        assert(length > 0);
        
        m_array = new int[static_cast<std::size_t>(length)]{};
        m_length = length;
    }
    
    /// this is a destructor
    /// it deletes the dynamic array
    /// deallocation in the destructor
    ~Intarray()
    {
        delete[] m_array;
    }
    
    void set_value(int index, int value) { m_array[index] = value; }
    int get_value(int index) { return m_array[index]; }
    
    int get_length() { return m_length; }
};

class Simple
{
private:
    int m_nID{};
    
public:
    Simple(int nID) : m_nID{ nID }
    {
        std::cout << "CONSTRUCTOR Simple: " << nID << '\n';
    }
    
    ~Simple()
    {
        std::cout << "DESTRUCTOR Simple: " << m_nID << '\n';
    }
    
    int get_id() { return m_nID; }
};

int main()
{
    /// integer array of 10 allocated
    /// used parentheses() based initialization for array initialization with the length specified
    Intarray A(10);
    
    /// setting the elements
    for (int count{ 0 }; count < A.get_length(); ++count)
        A.set_value(count, count+1);
    
    /// printing
    for (int count{ 0 }; count < A.get_length(); ++count)
        std::cout << A.get_value(count) << ' ';
    std::cout << '\n';
    
    /// accessing
    std::cout << "Value of element 8 is: " << A.get_value(8) << '\n';
    
    /// allocated on the stack
    Simple simple{ 1 };
    std::cout << simple.get_id() << '\n';

    /// allocated on the heap, dynamic
    Simple* p_simple{ new Simple{ 2 } };
    std::cout << p_simple->get_id() << '\n';
    
    /// delete the dynamic memory
    /// p_simple is destroyed first than the simple because it is deleted before the end of the function
    delete p_simple;
    
    return 0;
}   /// simple goes out of scope here, destructor called here
    /// Array A is destroyed here, ~Intarray destructor function is called here
