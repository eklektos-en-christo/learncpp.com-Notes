//
//  main.cpp
//  22.4_std_move
//
//  Created by Εκλεκτός εν Χριστώ on 12/7/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 Making copies can be inefficient and slow, to avoid copies we can use move semantics. What if the objects
 we're working with are l-value and not r-values, then we don't have a way to invoke the move constructor
 or assignment instead of copy constructor/assignment
 
 -----------------------------------------------------------------------------------------------------------
 std::move - standard lib function, it uses static_cast to cast its argument into an r-value reference, so
 that move semantics can be invoked, we can use std::move to cast an l-value into a type that will prefer
 being moved over being copied, std::move lives in utility header
 
 -----------------------------------------------------------------------------------------------------------
 MOVED FROM OBJECTS WILL BE IN A VALID BUT POSSIBLY INDETERMINATE STATE:
 
 When we move the value of a temporary object(rvalue), it doesn't matter what the object is left with,
 because the temporary object will be destroyed immediately anyway
 
 if the moved from object is an lvalue, we can continue to access that lvalue object, even if their values
 have been moved
 
 Two thoughts:
 - objects that have been moved from should be reset back to some default/zero state, where the object does
   not own a resource anymore
 - we should do whatever is most convenient and not constrain ourselves to having to clear the moved from
   object if its not convenient to do so
 
 C++ standard: "unless otherwise specified, moved from objects(of types defined in the std lib) shall be
 placed in a valid but unspecified state
 
 with a moved from object: it is safe to call any function that does not depend on the current value of the
 object, we can set or reset the value of the moved from object, we can also test the state of the
 moved-from object to see if it is empty or have a value, avoid the functions like operator[] or front()
 which returns the first element in a container, because moved-from container may or may not have elements
 
 std::move - gives a hint to the compiler that the programmer doesn't need the value of an object any more,
 only use std::move on the persistent objects and do not make assumptions about the value of the object
 beyond that point, it is okay to give a moved-from object a new value using operator= after the current
 value has been moved
 
 std::move - is useful when sorting an array of elements, move semantics can be used instead of copy
 semantics when sorting, which is more efficient, we can also move the contents managed by one smart pointer
 to another
 
 std::move_if_noexcept - a variant of std::move, it returns a movable r-value if the object has a noexcept
 move constructor, otherwise it returns a copyable l-value
 
 -----------------------------------------------------------------------------------------------------------
 std::move can be used whenever we want to treat an l-value like an r-value for the purpose of invoking
 move semantics instead of copy semantics.
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <utility>          /// std::move lives here
#include <string>
#include <vector>

/// use of std::move, this casts the lvalue argument to an rvalue
template <class T>
void my_swap_move(T& a, T& b)
{
    T temp{ std::move(a) };     /// move constructor invoked here, data moved to temp
    a = std::move(b);           /// move assignment invoked here, a is reused to be filled with value of b
    b = std::move(temp);        /// move assignment invoked here, b is reused to be filled with value of temp
}

int main()
{
    std::string x{ "jkl" };     /// x is moved to temp, y is moved to x and temp is moved to x
    std::string y{ "mno" };
    
    std::cout << x << '\n';
    std::cout << y << '\n';
    
    my_swap_move(x, y);
    
    std::cout << x << '\n';
    std::cout << y << '\n';
    
    std::vector<std::string> v;
    
    std::string string{ "Knock" };
    
    std::cout << "Copying string\n";
    v.push_back(string);                /// lvalue passed, so copy semantics are used
    
    /// string is copied to vector v, both statements below show this
    std::cout << "string: " << string << '\n';
    std::cout << "vector: " << v[0] << '\n';
    
    std::cout << "Moving string\n";
    v.push_back(std::move(string));     /// string is lvalue but std::move converted it to an rvalue, so move semantics are used
    
    /// string is move to vector v, v[1] proves that
    std::cout << "string: " << string << '\n';
    std::cout << "vector: " << v[0] << '\n';
    std::cout << "vector: " << v[1] << '\n';
    
    return 0;
}
