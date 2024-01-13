//
//  main.cpp
//  22.1_intro.to.smart.pointers.and.move.semantics
//
//  Created by Εκλεκτός εν Χριστώ on 12/4/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 Pointer variables: have no inherent mechanism to clean up after themselves
 
 -----------------------------------------------------------------------------------------------------------
 Classes contain destructors that automatically get executed when an object of the class goes out of scope,
 if you allocate memory in the constructor, then you can deallocate it in the destructor
 
 -----------------------------------------------------------------------------------------------------------
 Smart pointer: is a composition class that is designed to manage dynamically allocated memory and ensure
 that memory gets deleted when the smart pointer object goes out of scope
 
 Built-in pointers - sometimes called "dumb pointers", because they can't clean up after themselves
 
 Assigning or initializing a dumb pointer doesn’t copy the object being pointed to
 
 -----------------------------------------------------------------------------------------------------------
 MOVE SEMANTICS: means the class will transfer the ownership of the object rather than making a copy,
 source object is owned by the destination pointer and source pointer is set to NULL
 
 deleting a nullptr is okay, it does nothing
 
 std::auto_ptr - removed in C++17
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>

template <typename T>
class Auto_PTR
{
private:
    T* m_ptr;
    
public:
    Auto_PTR(T* ptr = nullptr) : m_ptr{ ptr }
    {
    }
    
    ~Auto_PTR()
    {
        delete m_ptr;
    }
    
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
};

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource released\n"; }
    void say_hi() { std::cout << "Hi\n"; }
};

void some_function()
{
    Auto_PTR<Resource> ptr(new Resource());
    
    int x;
    std::cout << "Enter an integer: ";
    std::cin >> x;
    
    /// if the function returns early, still the Auto_PTR will clean after itself
    if (x == 0)
        return;
    
    /// because the ptr is a local variable to this function, it will get destroyed
    /// Resource is assured to be cleaned up
    ptr->say_hi();
}

void pass_by_value(Auto_PTR<Resource> res)
{
}

/// this class implements the move semantics
template <typename T>
class Auto_PTR2
{
private:
    T* m_ptr;
    
public:
    Auto_PTR2(T* ptr=nullptr) : m_ptr(ptr)
    {
    }
    
    ~Auto_PTR2()
    {
        delete m_ptr;
    }
    
    /// copy constructor doesn't make shallow copies but
    /// transfers the ownership of the source object to the object being created
    Auto_PTR2(Auto_PTR2& a)
    {
        /// copy the address from the source pointer to the local object
        m_ptr = a.m_ptr;
        /// making sure that the source no longer owns the pointer
        a.m_ptr = nullptr;
    }
    
    /// assignment operator implements the move semantics
    Auto_PTR2& operator=(Auto_PTR2& a)
    {
        if (&a == this)
            return *this;
        
        /// deallocate any pointer the destination is already holding first
        delete m_ptr;
        
        /// transfer the address from the source pointer to the local object
        m_ptr = a.m_ptr;
        /// make sure the source no longer own the pointer
        a.m_ptr = nullptr;
        return *this;
    }
    
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    bool is_null() const { return m_ptr == nullptr; }
};

class Resource2
{
public:
    Resource2() { std::cout << "Resource2 acquired\n"; }
    ~Resource2() { std::cout << "Resource2 released\n"; }
};

int main()
{
    /// resource gets automatically deallocated when the object goes out of scope
    /// Auto_PTR handles the deallocation
    /*Auto_PTR<Resource> res(new Resource());*/
    
    some_function();
    
    Auto_PTR<Resource> res1(new Resource());
    
    /// this will crash the program
    /// Auto_PTR doesn't have custom copy constructor and assignment operator
    /// so the default copy constructor will perform shallow copy when res1 will be copied
    /// this means both res1 and res2 are pointing to the same resource
    /// when res2 goes out of scope, res1 is left dangling
    /// when res1 goes to delete itself, it will try to delete already deleted memory, crash will happen
    /*Auto_PTR<Resource> res2(res1);*/
    
    /// both res1 and res parameter will point to the same resource
    /// when res parameter is destroyed, res1 will be left dangling
    /// when res1 will be deleted, it will crash the program
    /*pass_by_value(res1);*/
    
    Auto_PTR2<Resource2> res3(new Resource2());
    Auto_PTR2<Resource2> res4;  /// null right now
    
    /// ownership transferred to res4,  source object res3 is null now
    res4 = res3;
    
    std::cout << "res3 is: " << (res3.is_null() ? "null\n" : "not null\n");
    std::cout << "res4 is: " << (res4.is_null() ? "null\n" : "not null\n");
    
    /// ownership transferred to res3, source object res4 is null now
    res3 = res4;
    
    std::cout << "res3 is: " << (res3.is_null() ? "null\n" : "not null\n");
    std::cout << "res4 is: " << (res4.is_null() ? "null\n" : "not null\n");
    
    return 0;
}
