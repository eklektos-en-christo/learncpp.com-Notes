//
//  main.cpp
//  22.3_move.constructors.and.move.assignment
//
//  Created by Εκλεκτός εν Χριστώ on 12/6/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 Copy Constructors: used to initialize a class by making a copy of an object of the same class
 Copy Assignment: used to copy one class object to another existing class object
 
 Compiler provided copy constructor and copy assignment: do shallow copies, which may cause problems for
 classes that allocate dynamic memory
 
 The goal of the copy constructor and assignment is to make a copy of one object to another
 
 The goal of the move constructor and assignment is to move the ownership of the resources from one object
 to another, this is much less expensive than making a copy
 
 Move constructors and assignment: use non-const rvalue reference parameters which only bind to rvalues
 
 Move constructor and assignment: are called when both are defined in the class and the argument for
 construction or assignment is an rvalue, typically this value will be a literal or temporary value
 
 When the argument is an lvalue or when the argument is an rvalue and the move semantics are not defined,
 then the copy constructor and assignment are called
 
 Conditions for the implicit move constructor and assignment, when the compiler will create them:
 - there are no user-defined copy constructor or copy assignment operators
 - there are no user-defined move constructor or move assignment operators
 - there is no user-defined destructor
 
 With the help of move-semantics, we can avoid the unnecessary copying of objects when the source object is
 an rvalue, temporary, we can simply transfer the resource to the object we're constructing or assigning
 
 C++11, through r-value references, gives us the ability to provide different behaviors when the argument
 is an r-value vs an l-value, enabling us to make smarter and more efficient decisions about how our
 objects should behave.
 
 -----------------------------------------------------------------------------------------------------------
 MOVE SEMANTICS: should always leave both objects(source & destination) in valid state
 
 setting the source pointer/object to null is necessary, even thought it is a temporary object, if it is
 still pointing to the destination object, then when source pointer is deleted, it will also delete the
 destination object, destination pointer will be left as a dangling pointer and when the destination pointer
 is destroyed, it will try to delete the already deleted resource and we'll get undefined behavior
 
 -----------------------------------------------------------------------------------------------------------
 Automatic lvalues returned by value: may be moved instead of copied
 
 C++ RULE: AUTOMATIC OBJECTS RETURNED FROM A FUNCTION BY VALUE CAN BE MOVED EVEN IF THEY ARE LVALUES
 
 Although the compiler can move l-value return values, in some cases it may be able to do even better by
 simply eliding the copy altogether (which avoids the need to make a copy or do a move at all). In such
 a case, neither the copy constructor nor move constructor would be called.
 
 -----------------------------------------------------------------------------------------------------------
 DISABLE COPYING: it is sometimes desirable to delete the copy constructor and assignment functions to
 ensure copies aren't made
 
 Do not implement move semantics using std::swap
 
 Since the goal of move semantics is to move a resource from a source object to a destination object, you
 might think about implementing the move constructor and move assignment operator using std::swap().
 However, this is a bad idea, as std::swap() calls both the move constructor and move assignment on
 move-capable objects, which would result in an infinite recursion.
 
 You can implement the move constructor and move assignment using your own swap function, as long as your
 swap member function does not call the move constructor or move assignment. We avoid recursive calls by
 invoking std::swap on class's members rather than on class's variable name
 
 -----------------------------------------------------------------------------------------------------------
 DELETING THE MOVE CONSTRUCTOR AND ASSIGNMENT:
 
 If the copy constructor is deleted, the compiler won't generate an implicit move constructor. Therefore
 when deleting the copy constructor, it is useful to explicitly tell about what behavior you want from the
 move constructors, either delete them or making them default(move only class)
 
 RULE OF FIVE: if the copy constructor/assignment, move constructor/assignment or destructor are defined or
 deleted, then each of the function should be defined or deleted
 
 deleting only the move constructor and assignment may seem like a good idea if we need a copyable but not
 a movable object, but this has the consequence of making the class not returnable by value in cases where
 mandatory copy elision is not required, this happens because a deleted move constructor is still declared
 and thus is eligible for overload resolution, return by value will favor a deleted move constructor over a
 non-deleted copy constructor
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <algorithm>
#include <chrono>
#include <string>
#include <string_view>

/// move constructor & assignment
template <typename T>
class Auto_PTR
{
private:
    T* m_ptr{};
    
public:
    Auto_PTR(T* ptr=nullptr) : m_ptr{ ptr }
    {
    }
    
    ~Auto_PTR()
    {
        delete m_ptr;
    }
    
    /// copy constructor - performs a deep copy
    Auto_PTR(const Auto_PTR& a)
    {
        m_ptr = new T;
        *m_ptr = *a.m_ptr;
    }
    
    /// copy assignment - performs a deep copy
    Auto_PTR& operator=(const Auto_PTR& a)
    {
        if (&a == this)
            return *this;
        
        delete m_ptr;
        
        m_ptr = new T;
        *m_ptr = *a.m_ptr;
        return *this;
    }
    
    /// move constructor - transfer the ownership of source object to destination object
    Auto_PTR(Auto_PTR&& a) noexcept
    : m_ptr{ a.m_ptr }
    {
        /// shallow copy the source pointer to implicit object(destination) and set the source pointer to null
        a.m_ptr = nullptr;
    }
    
    /// move assignment - transfer the ownership of source object to destination object
    Auto_PTR& operator=(Auto_PTR&& a) noexcept
    {
        if (&a == this)
            return *this;
        
        delete m_ptr;
        
        m_ptr = a.m_ptr;
        a.m_ptr = nullptr;
        return *this;
    }
    
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    bool is_null() const { return m_ptr == nullptr; }
};

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

Auto_PTR<Resource> generate_resource()
{
    Auto_PTR<Resource> res{ new Resource };
    /// on returning time, the res is moved, instead of copied
    /// even though res is an lvalue
    /// C++ rule: automatic objects returned from a function by value
    /// can be moved even if they are lvalues
    return res;     /// this evokes the move constructor
}

/*--------------------------------------------------------------------------------------------------------*/
/// disabling the copying
template <typename T>
class DynamicArray
{
private:
    T* m_array {};
    int m_length {};
    
public:
    DynamicArray(int length)
    : m_array{ new T[length] }, m_length{ length }
    {
    }
    
    ~DynamicArray()
    {
        delete[] m_array;
    }
    
    DynamicArray(const DynamicArray& array) = delete;
    /*: m_length{ array.m_length }
    {
        m_array = new T[array.m_length];
        std::copy_n(array.m_array, m_length, m_array);
    }*/
    
    DynamicArray& operator=(const DynamicArray& array) = delete;
    /*{
        if (&array == this)
            return *this;
        
        delete[] m_array;
        
        m_length = array.m_length;
        m_array = new T[m_length];
        
        std::copy_n(array.m_array, m_length, m_array);
        return *this;
    }*/
    
    DynamicArray(DynamicArray&& array) noexcept
    : m_array(array.m_array), m_length(array.m_length)
    {
        array.m_length = 0;
        array.m_array = nullptr;
    }
    
    DynamicArray& operator=(DynamicArray&& array) noexcept
    {
        if (&array == this)
            return *this;
        
        delete[] m_array;
        
        m_length = array.m_length;
        m_array = array.m_array;
        array.m_length = 0;
        array.m_array = nullptr;
        
        return *this;
    }
    
    int get_length() const { return m_length; }
    T& operator[](int index) { return m_array[index]; }
    const T& operator[](int index) const { return m_array[index]; }
};

class Timer
{
private:
    using clock = std::chrono::high_resolution_clock;
    using second = std::chrono::duration<double, std::ratio<1>>;
    
    std::chrono::time_point<clock> m_beg{ clock::now() };
    
public:
    void reset() { m_beg = clock::now(); }
    double elapsed() const
    {
        return std::chrono::duration_cast<second>(clock::now() - m_beg).count();
    }
};

DynamicArray<int> clone_array_and_double(const DynamicArray<int>& array)
{
    DynamicArray<int> dbl(array.get_length());
    
    for (int i{ 0 }; i < array.get_length(); ++i)
        dbl[i] = array[i] * 2;
    
    return dbl;
}

/*--------------------------------------------------------------------------------------------------------*/
/// Do not implement move semantics using std::swap
class Name
{
private:
    std::string m_name{};
    
public:
    Name(std::string_view name) : m_name{ name }
    {
    }
    
    Name(const Name& name) = delete;
    Name& operator=(const Name& name) = delete;
    
    friend void swap(Name& a, Name& b) noexcept
    {
        std::swap(a.m_name, b.m_name);
    }
    
    Name(Name&& name)
    {
        std::cout << "Move ctor\n";
        swap(*this, name);             /// calling the member swap, not std::swap
    }
    
    Name& operator=(Name&& name)
    {
        std::cout << "Move assign\n";
        /*std::swap(*this, name);*/         /// infinite recursion
        swap(*this, name);                  /// calling the member swap, not std::swap
        return *this;
    }
    
    const std::string& get() const { return m_name; }
};

/*--------------------------------------------------------------------------------------------------------*/

int main()
{
    Auto_PTR<Resource> main_res;
    
    /// res is constructed in generate_resource()  then returned to the main() by value
    /// on returning res from the function, resources are moved into a temporary object
    /// res goes out of scope, it no longer manages a pointer, because pointer is copied to the temporary object
    /// res has a null pointer now
    /// temporary object is moved to main_res when assigned to main_res
    /// when the assignment expression ends, the temporary object goes out of expression scope and is destroyed
    /// temporary object is null now, main_res got the ownership of temporary object's data
    main_res = generate_resource();         /// this evokes the move assignment
    
    Timer t;
    
    DynamicArray<int> array(1000000);
    
    for (int i{ 0 }; i < array.get_length(); ++i)
        array[i] = i;
    
    array = clone_array_and_double(array);
    
    std::cout << t.elapsed() << '\n';
    
    Name n1{ "Leon" };
    /*n1 = Name{ "NaN" };*/         /// infinite recursion
    n1 = Name{ "Keon" };            /// works, own swap function used with the move semantics
    
    std::cout << n1.get() << '\n';
    
    return 0;
}   /// main_res goes out of scope here and object is destroyed
