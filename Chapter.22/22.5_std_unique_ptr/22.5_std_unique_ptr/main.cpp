//
//  main.cpp
//  22.5_std_unique_ptr
//
//  Created by Εκλεκτός εν Χριστώ on 12/7/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 Smart pointer: should never be dynamically allocated themselves, by allocating it on stack, we're
 guaranteed that the smart pointer will properly go out of scope when the function or object it is contained
 within ends, ensuring the object the smart pointers owns is properly deallocated
 
 C++ has four smart pointer classes:
 - std::auto_ptr(removed)
 - std::unique_ptr
 - std::shared_ptr
 - std::weak_ptr
 
 -----------------------------------------------------------------------------------------------------------
 std::unique_ptr - should be used to manage any dynamically allocated object that is not shared by multiple
 objects, unique_ptr should completely own the object it manages, not share the ownership with other classes
 
 <memory> - std::unique_ptr lives here
 
 std::unique_ptr - properly implements the move semantics, copy initialization and assignment are disabled
 
 -----------------------------------------------------------------------------------------------------------
 Accessing the managed object: 
 
 std::unique_ptr - has an overloaded operator* and operator->, this can be used to return the resource being
 managed, operator* returns a reference to the managed resource and operator-> returns a pointer,  before we
 either of these operators, we should check whether the std::unique_ptr actually has a resource,
 
 std::unique_ptr has a cast to bool that returns true if the std::unique_ptr is managing a resource
 
 -----------------------------------------------------------------------------------------------------------
 std::unique_ptr and arrays - unique_ptr knows whether to use scalar delete or array delete, we can use
 unique_ptr with both scalar objects and arrays
 
 std::array or std::vector or std::string - are always a better choice than using std::unique_ptr with a
 fixed array, dynamic array or c-style string
 
 -----------------------------------------------------------------------------------------------------------
 std::make_unique - a templated function, it constructs an object of the template type and initializes it
 with the arguments passed into the function, lives in <memory> header, it also resolves an exception safety
 issue that can result from C++ leaving the order of evaluation for function arguments unspecified
 
 best practice:
 use std::make_unique function instead of creating std::unique_ptr and using new operator by yourself
 
 -----------------------------------------------------------------------------------------------------------
 some_function(std::unique_ptr<T>(new T), function_that_can_throw_exception());

 The compiler is given a lot of flexibility in terms of how it handles this call. It could create a new T,
 then call function_that_can_throw_exception(), then create the std::unique_ptr that manages the
 dynamically allocated T. If function_that_can_throw_exception() throws an exception, then the T that
 was allocated will not be deallocated, because the smart pointer to do the deallocation hasn’t been
 created yet. This leads to T being leaked.
 
 std::make_unique() doesn’t suffer from this problem because the creation of the object T and the creation
 of the std::unique_ptr happen inside the std::make_unique() function, where there’s no ambiguity about
 order of execution.
 
 This issue was fixed in C++17, as evaluation of function arguments can no longer be interleaved.
 
 -----------------------------------------------------------------------------------------------------------
 RETURNING A std::unique_ptr from a function - it can be safely returned from a function by value
 
 In general, you should not return std::unique_ptr by pointer (ever) or reference (unless you have a
 specific compelling reason to).
 
 -----------------------------------------------------------------------------------------------------------
 PASSING std::unique_ptr TO A FUNCTION - unique_ptr is only movable ant not copyable
 
 if you want the function to take the ownership of the contents of unique_ptr, pass it by value,
 unique_ptr's copy semantics have been disabled, so you'll need to use std::move to actually pass a variable
 in
 
 pass a unique_ptr by reference only when function wants to modify the object
 
 It is better to just pass the resource itself, this allows the function to remain agnostic of how the
 caller is managing its resources, to get a raw resource pointer from a unique_ptr, use the get() member
 function
 
 -----------------------------------------------------------------------------------------------------------
 unique_ptr and classes -
 
 we can use std::unique_ptr as a composition member of a class and when the class object is destroyed, the
 unique_ptr will be destroyed automatically
 
 if the class object is not destroyed properly, then the unique_ptr will not be
 destroyed either and the object being managed by the std::unique_ptr will not be deallocated
 
 -----------------------------------------------------------------------------------------------------------
 Misusing the unique_ptr:
 
 - don't let multiple classes manage the same resource
 - don't manually delete the resource out from underneath the std::unique_ptr
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <memory>       /// for std::unique_ptr
#include <utility>

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
    
    friend std::ostream& operator<<(std::ostream& out, const Resource& res)
    {
        out << "I am a resource";
        return out;
    }
};

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };
    
public:
    Fraction(int num=0, int den=1)
    : m_numerator{ num }, m_denominator{ den }
    {
    }
    
    friend std::ostream& operator<<(std::ostream& out, const Fraction& f1)
    {
        out << f1.m_numerator << '/' << f1.m_denominator;
        return out;
    }
};

/// if the return value is not assigned to anything:
/// the temporary value will go out of scope and Resource will be cleaned up
/// if assigned to anything, move semantics will be used to transfer the Resource from
/// the return value to the object assigned to - C++14
/// or return will be elided if using C++17
std::unique_ptr<Resource> create_resource()
{
    return std::make_unique<Resource>();
}

/// this function takes the ownership of the of the Resource passed in
/// Resource will be destroyed at the end of this function, because function has the ownership of Resource
void take_ownership(std::unique_ptr<Resource> res)
{
    if (res)
        std::cout << *res << '\n';
}

/// function only uses the Resource and is agnostic of how the caller manages its resources
/// its accepts a pointer to the resource, not a reference to the whole std::unique_ptr<Resource>
void use_resource(const Resource* res)
{
    if (res)
        std::cout << *res << '\n';
    else
        std::cout << "No resource\n";
}

void print_fraction(const Fraction* ptr)
{
    if (ptr)
        std::cout << *ptr << '\n';
    else
        std::cout << "NO FRACTION\n";
}

int main()
{
    /// unique_ptr owns the Resource type object, dynamically allocated
    /// unique_ptr is allocated on the stack itself, it is guaranteed to go out of scope
    std::unique_ptr<Resource> res{ new Resource() };
    
    std::unique_ptr<Resource> res1{ new Resource{} };
    std::unique_ptr<Resource> res2{};
    
    std::cout << (res1 ? "not null\n" : "null\n");
    std::cout << (res2 ? "not null\n" : "null\n");
    
    /// copy assignment is deleted
    /*res2 = res1;*/
    
    /// this proves that unique_ptr implements the move semantics properly
    /// res2 has the ownership and res1 is null now
    /// std::move converts the res1 into an rvalue, this triggers the move assignment
    res2 = std::move(res1);
    
    std::cout << (res1 ? "not null\n" : "null\n");
    std::cout << (res2 ? "not null\n" : "null\n");
    
    /// using the implicit cast to bool ensure res1 contains a Resource
    /// res1 is moved, so this condition will evaluate to false and won't execute
    /// * returns the reference to res1 and operator<< prints the object to cout
    if (res1)
        std::cout << *res1 << '\n';
    
    /// using std::make_unique to create an object of the Fraction type and initializing it with the arguments(2, 3) passed
    /// object is dynamically allocated
    /// auto type deduction also used
    auto fraction1{ std::make_unique<Fraction>(2, 3) };
    std::cout << *fraction1 << '\n';
    
    /// auto type deduction also used
    /// dynamically allocated array of type Fraction of length 5
    auto fraction2{ std::make_unique<Fraction[]>(5) };
    std::cout << fraction2[3] << ' ' << fraction2[0] << '\n';
    
    auto ptr{ create_resource() };
    
    /// unique_ptr doesn't have copy semantics, so move semantics have to be invoked
    take_ownership(std::move(ptr));
    
    /// get a pointer to the Resource* parameter, not a reference to the whole std::unique_ptr<Resource>
    auto ptr2{ create_resource() };
    use_resource(ptr2.get());
    
    /// misusing the unique_ptr
    /// both r1 and r2 will try to delete the same Resource - undefined behavior
    Resource* r{ new Resource() };
    /*std::unique_ptr<Resource> r1{ r };
    std::unique_ptr<Resource> r2{ r };*/
    
    /// don't manually delete the resource out from underneath the std::unique_ptr
    Resource* r3{ new Resource() };
    /// unique_ptr will delete the r3 and r3 will be left dangling
    std::unique_ptr<Resource> r4{ r3 };
    /*delete r3;*/
    
    auto ptr3{ std::make_unique<Fraction>(3, 5) };
    print_fraction(ptr3.get());
    
    return 0;
}   /// res goes out of scope here and allocated Resource is destroyed
