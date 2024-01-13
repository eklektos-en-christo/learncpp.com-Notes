//
//  main.cpp
//  22.7_circular.dependency.issues.with.shared_ptr.and.weak_ptr
//
//  Created by Εκλεκτός εν Χριστώ on 12/9/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 CIRCULAR REFERENCES/CYLINDRICAL REFERENCE/CYCLE: a series of references where each object references the
 next and the last object references back to first, causing a referential loop, these references can be
 anything - pointers, references, unique IDs or other means of identifying specific objects
 
 In the context of pointers, the references will be pointers
 
 When A points at B, B points to C and C points to A, in this way each object ends up in keeping the next
 object alive, thus no objects in the series can be deallocated because they all think some other object
 still needs it.
 
 -----------------------------------------------------------------------------------------------------------
 Cylindrical reference - can even happen with a single shared_ptr, in this a single shared_ptr referencing
 the object that contains it is still a cycle, just a reductive one, means shared_ptr is pointing on itself
 
 -----------------------------------------------------------------------------------------------------------
 std::weak_ptr - it is designed to solve the cylindrical ownership, lives in <memory>
 
 std::weak_ptr - is an observer, it can observe and access the same object as a shared_ptr but it is not
 considered an owner of the object
 
 When using shared_ptr, shared_ptr considers whether other shared_ptr is co-owing the same object, but
 std::weak_ptr doesn't consider it
 
 -----------------------------------------------------------------------------------------------------------
 USING std::weak_ptr - weak_ptr is not directly usable, it must first be converted to shared_ptr
 
 To convert a weak_ptr to a shared_ptr - use the lock() member function
 
 -----------------------------------------------------------------------------------------------------------
 AVOID DANGLING POINTERS WITH std::weak_ptr -
 
 weak_ptr - has access to the reference count for an object, it can determine whether if it is pointing to
 a valid object or not, if the reference count is non-zero, the resource is valid, if it is zero, then the
 resource has been destroyed
 
 expired() - member function in weak_ptr, returns true if the weak_ptr is pointing to an object that is
 invalid and false if the object is alive
 
 if weak_ptr is expired, then we shouldn't call lock on it to return a shared_ptr, if we do, we get a
 null shared_ptr
 
 -----------------------------------------------------------------------------------------------------------
 CONCLUSION:
 
 - use weak_ptr when we want a smart pointer that can see and use a shared resource but doesn't participate
   in the ownership
 - use shared_ptr when we want multiple smart pointers that can co-own a resource, the resource will be
   deallocated when the last pointing shared_ptr goes out of scope
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <memory>
#include <string>

class Resource
{
public:
    std::shared_ptr<Resource> m_ptr {};
    
    Resource() { std::cerr << "Resource acquired\n"; }
    ~Resource() { std::cerr << "Resource destroyed\n"; }
};

/*--------------------------------------------------------------------------------------------------------*/

class Person
{
    std::string m_name{};
    std::weak_ptr<Person> m_partner {};
    
public:
    Person(const std::string& name) : m_name{ name }
    {
        std::cout << m_name << " created\n";
    }
    
    ~Person()
    {
        std::cout << m_name << " destroyed\n";
    }
    
    friend bool partner_up(std::shared_ptr<Person>& p1, std::shared_ptr<Person>& p2)
    {
        if (!p1 || !p2)
            return false;
        
        p1->m_partner = p2;
        p2->m_partner = p1;
        
        std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';
        return true;
    }
                                                        /// using lock member function to convert weak_ptr to shared_ptr
    const std::shared_ptr<Person> get_partner() const { return m_partner.lock(); }
    const std::string& get_name() const { return m_name; }
};

/*--------------------------------------------------------------------------------------------------------*/
/// returns a std::weak_ptr to an invalid object
std::weak_ptr<Resource> get_weak_ptr()
{
    auto ptr{ std::make_shared<Resource>() };
    return std::weak_ptr<Resource>{ ptr };
}

/// returns a dumb pointer to an invalid object
Resource* get_dumb_ptr()
{
    auto ptr{ std::make_unique<Resource>() };
    return ptr.get();
}

/*--------------------------------------------------------------------------------------------------------*/

int main()
{
    /// circular reference with a single shared_ptr
    auto ptr1{ std::make_shared<Resource>() };
    
    /// ptr1 is pointing on itself, never deallocated
    /// ptr1 goes out of scope but Resource's m_ptr is sharing the Resource, so no deallocation happens
    /*ptr1->m_ptr = ptr1;*/
    
    auto lucy { std::make_shared<Person>("Lucy") };
    auto ricky { std::make_shared<Person>("Ricky") };
    
    /// when ricky goes out of scope it sees that there are no other shared_ptr pointing at ricky
    /// even though weak_ptr from lucy is pointing at ricky, but it doesn't count,
    /// weak_ptr from lucy is an observer, so ricky is deallocated and also the lucy in same way
    partner_up(lucy, ricky);
    
    /// get a shared_ptr to ricky's partner
    /// we don't have to worry about circular dependencies with std::shared_ptr variable "partner"
    /// partner is a local variable, will go out of scope at the end of the function
    auto partner = ricky->get_partner();
    std::cout << ricky->get_name() << "'s partner is: " << partner->get_name() << '\n';
    
    auto dumb{ get_dumb_ptr() };
    auto weak{ get_weak_ptr() };
    
    /// test whether the returned dumb pointer is null or not, dumb pointer has an address but the object itself is deallocated
    /// there is no way for main to tell whether this pointer is dangling or not, dereferencing will result in an undefined behavior
    std::cout << "dumb ptr is: " << ((dumb == nullptr) ? "nullptr\n" : "non-null\n");
    
    /// object being pointed to was already destroyed in the function, this resolves to true
    /// so main call tell that weak is pointing to an invalid object, it is because weak has access to the reference count of an object
    std::cout << "weak ptr is: " << ((weak.expired()) ? "expired\n" : "still alive\n");
    
    return 0;
}
