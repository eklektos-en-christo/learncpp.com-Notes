//
//  main.cpp
//  22.6_std_shared_ptr
//
//  Created by Εκλεκτός εν Χριστώ on 12/8/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 unique_ptr - manages a single owned resource
 
 shared_ptr - manages a resource that is owned by multiple smart pointers, lives in <memory>
 
 It is okay to have multiple shared_ptr pointing to the same resource
 
 std::shared_ptr - internally keeps track of how many std::shared_ptr are sharing the resource, so as long
 as at least one shared_ptr is pointing to the resource, the resource will not be deallocated, even if
 other shared_ptr's are destroyed
 
 shared_ptr - is deallocated when the last shared_ptr goes out of scope or is reassigned to point at
 something else
 
 If you need more than one std::shared_ptr to a given resource, copy an existing shared_ptr
 
 BEST PRACTICE: always make a copy of an existing shared_ptr if you need more than one shared_ptr pointing
 to the same resource
 
 -----------------------------------------------------------------------------------------------------------
 std::make_shared - make_unique can be used to create a unique_ptr, so make_shared can also be to create a
 shared_ptr
 
 make_shared is simpler and safer, there's no way to directly create two shared_ptr pointing to the same
 source when using make_shared
 
 -----------------------------------------------------------------------------------------------------------
 DIGGING INTO shared_ptr - shared_ptr uses two pointers internally as opposed to the unique_ptr which uses
 one pointer internally, one pointer in shared_ptr points at the resource being managed, the other pointer
 points at a "control block", which is a dynamically allocated object that tracks bunch of stuff, including
 how many shared_ptr are pointing at the resource
 
 When a shared_ptr is created via a shared_ptr constructor, the memory for the managed resource(passed in
 object) and memory for the control block(constructor creates this) is allocated separately, when using a
 make_shared, this separation of memory can be optimized into a single memory allocation, this leads to
 better performance
 
 When we create shared_ptr independently: in this, each shared_ptr will have one pointer pointing at the
 resource and the another will be pointing will be pointing at the separate control block, control blocks
 for both shared_ptr will be created separately, this indicates that each shared_ptr will think that they
 alone own the resource, when one shared_ptr goes out of scope, it will deallocate the resource, because
 its control block has only one pointer managing the resource, the other shared_ptr will be left dangling
 
 When a shared_ptr is cloned using copy assignment, the control block can be appropriately updated to
 indicate that there are now additional shared_ptr co-managing the resource
 
 -----------------------------------------------------------------------------------------------------------
 shared_ptr CAN BE CREATED FROM unique_ptr -
 
 a unique_ptr can be converted into a shared_ptr via a special shared_ptr constructor that accepts a
 unique_ptr rvalue, this constructor moves the contents of the unique_ptr to the shared_ptr
 
 a shared_ptr cannot be converted safely to a unique_ptr, if a function is returning a smart pointer, then
 its better be unique_ptr and assigning it to a shared_ptr, if that is appropriate
 
 -----------------------------------------------------------------------------------------------------------
 Perils of shared_ptr -
 
 if the shared_ptr is not properly disposed of, then the resource it is managing won't be deallocated either
 with unique_ptr, you only have to worry about one smart pointer being properly disposed of
 with shared_ptr, you have to worry about them all, if any of the shared_ptr who is managing a resource is
 not properly destroyed, the resource will not be deallocated properly
 
 -----------------------------------------------------------------------------------------------------------
 shared_ptr and arrays:
 
 before C++20, shared_ptr doesn't have support for managing arrays, so before the C++20, shared_ptr should
 not be used to manage c-style arrays
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <memory>

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
    Resource* res{ new Resource };
    
    /// res owned by one shared_ptr
    std::shared_ptr<Resource> ptr1{ res };
    
    {
        /// ptr0 also owns the res and goes out of scope after this block, it also deallocates the res object
        /// ptr1 is independent from ptr0, they both aren't aware of each other
        /// both thinks that they alone own the res
        /*std::shared_ptr<Resource> ptr0{ res };*/
        
        /// res owned by another shared_ptr
        /// res is not deallocated after this block, because ptr1 is still holding the res
        /// when ptr1 goes out of scope and notices that no more shared_ptr are managing the res, then the res is deallocated
        std::shared_ptr<Resource> ptr2{ ptr1 };
        std::cout << "ptr2 is killed\n";
    }
    
    /// make_shared creates a shared_ptr
    /// there’s no way to directly create two std::shared_ptr pointing to the same resource when using make_shared
    auto ptr3{ std::make_shared<Resource>() };
    
    {
        /// ptr4 uses the copy of ptr3
        auto ptr4{ ptr3 };
    }   /// ptr4 goes out of scope here, ptr3 still points to the Resource
    
    return 0;
}   /// ptr1 goes out of scope here, allocated Resource is destroyed here, ptr3 goes out fo scope here and Resource is destroyed
