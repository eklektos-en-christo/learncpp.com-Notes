//
//  main.cpp
//  27.10_std_move_if_noexcept
//
//  Created by Εκλεκτός εν Χριστώ on 12/4/23.
//

/*
 std::move - casts its lvalue argument to an rvalue, so that we can invoke move semantics
 
 -----------------------------------------------------------------------------------------------------------
 THE MOVE CONSTRUCTORS EXCEPTION PROBLEM: if we're copying some object and the copying fails, in such case,
 the object being copied is not harmed in any way, we can discard the failed copy and move on(strong
 exception guarantee is upheld)
 
 If we are moving an object, if the moving is interrupted by an exception after the transfer of ownership,
 then the source object will be left in a modified state, this isn't a problem if the source object is a
 temporary object and will be discarded after the move operation, for non-temporary objects, the source
 object will be damaged, to comply with strong exception guarantee, we need to move the resource back to the
 source object
 
 It is simple to avoid throwing exceptions in the body of a move constructor, but move constructor may
 invoke other constructor that are potentially throwing, so the strong exception guarantee will not be
 preserved
 
 -----------------------------------------------------------------------------------------------------------
 std::move_if_noexcept - noexcept functions are no-throw/no-fail, they meet the criteria for the strong
 exception guarantee, a noexcept move constructor is guaranteed to succeed
 
 std::move_if_noexcept - we can use this function to determine whether a move or a copy should be performed
 std::move_if_noexcept - is a counter part  to std::move
 
 If the compiler can tell that an object passed as an argument to std::move_if_noexcept won't throw an
 exception when it is moved(of it is moved because it is move-only and has no copy constructor), then
 std::move_if_except will perform identically to std::move and will return the object converted to an rvalue
 otherwise std::move_if_except will return a normal lvalue reference to the object
 
 std::move_if_noexcept - returns a movable rvalue if the object has a no except move constructor, otherwise
 it returns a copyable lvalue
 
 We can use the noexcept specifier in conjunction with std::move_if_noexcept to use move semantics, only
 when a strong exception guarantee exists, otherwise we use copy semantics
 
 std lib often uses move_if_noexcept to optimise for functions that are noexcept i.e moving instead of
 copying
 
 std::vector::resize will use move semantics if the element type has a noexcept move constructor, otherwise
 copy semantics will be used
 
 std::vector - generally operate faster with objects that have a noexcept move constructor
 
 -----------------------------------------------------------------------------------------------------------
 Warning

 If a type has both potentially throwing move semantics and deleted copy semantics (the copy constructor and copy assignment operator are unavailable), then std::move_if_noexcept will waive the strong guarantee and invoke move semantics. This conditional waiving of the strong guarantee is ubiquitous in the standard library container classes, since they use std::move_if_noexcept often.
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <utility>          /// for std::make_pair, pair, move and move_if_noexcept
#include <stdexcept>        /// for std::runtime_error

class MoveClass
{
private:
    int* m_resource{};
    
public:
    MoveClass() = default;
    
    MoveClass(int resource)
    : m_resource{ new int{ resource } }
    {
    }
    
    MoveClass(const MoveClass& that)
    {
        if (that.m_resource != nullptr)
        {
            m_resource = new int{ *that.m_resource };
        }
    }
    
    MoveClass(MoveClass&& that) noexcept
    : m_resource{ that.m_resource }
    {
        that.m_resource = nullptr;
    }
    
    ~MoveClass()
    {
        std::cout << "destroying " << *this << '\n';
        delete m_resource;
    }
    
    friend std::ostream& operator<<(std::ostream& out, const MoveClass& move_class)
    {
        out << "MoveClass(";
        
        if (move_class.m_resource == nullptr)
            out << "empty";
        else
            out << *move_class.m_resource;
        
        out << ')';
        return out;
    }
};

class CopyClass
{
public:
    bool m_throw{};
    
    CopyClass() = default;
    
    /// copy constructor will throw an exception when m_throw is true
    CopyClass(const CopyClass& that)
    : m_throw{ that.m_throw }
    {
        if (m_throw)
            throw std::runtime_error{ "abort!" };
    }
};

int main()
{
    /// creating a pair of MoveClass and CopyClass
    /// MoveClass{18} is temporary and destroyed after the my_pair initialization finishes
    /// MoveClass is moved to my_pair and become the subobject of my_pair
    std::pair my_pair{ MoveClass{ 18 }, CopyClass{} };
    
    std::cout << "my_pair.first: " << my_pair.first << '\n';
    
    try
    {
        /// triggering the copy constructor exception if m_throw is true
        my_pair.second.m_throw = true;
        
        /// this line throws an exception - moving the existing pair into another pair
        /// m_pair becomes an rvalue and std::move's move constructor is called
        /// the CopyClass subobject in my_pair is copied than being moved because it contains no move constructor
        /// CopyClass's copy constructor throws an exception,
        /// exception stopped the construction of moved_pair, already constructed members were destroyed
        /// already constructed member was MoveClass subobject
        /// catch block executes and prints error
        /*std::pair moved_pair{ std::move(my_pair) };*/
        
        /// this doesn't damage the source object, which is MoveClass subobject in my_pair
        /// std::move_if_noexcept returns my_pair as an lvalue reference
        /// my_pair is copied instead of being moved to moved_pair
        std::pair moved_pair{ std::move_if_noexcept(my_pair) };
        
        std::cout << "moved pair exists\n";
    }
    catch(const std::exception& ex)
    {
        std::cerr << "Error found: " << ex.what() << '\n';
    }
    
    /// on moving the MoveClass subobject to moved_pair, the source object was destroyed permanently
    /// but using the std::move_if_noexcept, the source subobject MoveClass is preserved
    std::cout << "my_pair.first: " << my_pair.first << '\n';
    
    return 0;
}   /// my_pair is destroyed here
