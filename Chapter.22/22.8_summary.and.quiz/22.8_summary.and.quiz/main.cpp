//
//  main.cpp
//  22.8_summary.and.quiz
//
//  Created by Εκλεκτός εν Χριστώ on 12/9/23.
//

/*
 Smart pointer - is a composition class designed to manage dynamically allocated memory, it ensures that
 memory gets deleted when the smart pointer object goes out of scope
 
 Copy semantics - allows our classes to be copied, copy constructor and assignment are used for this
 
 Move semantics - means a class can transfer ownership of the object rather than making a copy, move
 constructor and assignment are used for this
 
 std::auto_ptr - should be avoided, it is deprecated
 
 rvalue reference - is designed to be initialized with an rvalue, it is created using a double ampersand(&&)
 it is fine to write the functions that take an rvalue reference, but never return an rvalue reference
 
 If we construct/assign an object where the argument is an lvalue, then only copying the lvalue can be
 done, reasonably, we wouldn't expect the source lvalue to be changed in anyway
 
 If we construct/assign an object where the argument is an rvalue, we can then move the ownership of that
 rvalue to the object we're constructing/assigning, because rvalue is temporary and will go out of scope
 eventually, so instead of copying it(which is expensive), we can move it to the object that is being
 constructed/assigned to
 
 delete - keyword, can be used to disable copy semantics, this is done by deleting the copy constructor and
 assignment(= delete; at the end of function prototype)
 
 std::move - allows us to treat an lvalue as rvalue, this is useful when we want to invoke move semantics
 instead of copy semantics
 
 std::unique_ptr - a smart pointer class, manages a single non-shareable resource, it has copy semantics
 disabled
 std::make_unique - should be preferred to create new std::unique_ptr
 
 std::shared_ptr - a smart pointer class, used when multiple objects accessing the same resource are needed
 the resource is not destroyed until the last shared_ptr is destroyed, copy semantics are enabled to
 create additional shared_ptr pointing to the same object
 std::make_shared - should be preferred to create new std::shared_ptr
 
 std::weak_ptr - a smart pointer class, used when we need one or more objects with the ability to view and
 access a resource managed by a shared_ptr
 std::weak_ptr - is not considered when determining whether the resource should be destroyed(opposite of
 shared_ptr, it is determined in shared_ptr)
 */

#include <iostream>

int main()
{
    return 0;
}
