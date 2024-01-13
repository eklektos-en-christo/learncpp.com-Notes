//
//  main.cpp
//  12.3_std_vector.and.stack.behavior
//
//  Created by Εκλεκτός εν Χριστώ on 6/16/23.
//

/*
 std::vector - can be used as a dynamic array
 std::vector - remembers its length
 std::vector - can be resized dynamically when required
 
 _________________________________________________________________________________________
 LENGTH vs. CAPACITY:
 
 std::array - only remembers its length
 
 std::vector - has two separate attributes, length and capacity
 
 Length: how many elements are being used in the array
 
 Capacity: how many (total)elements were allocated in memory
 
 _________________________________________________________________________________________
 LENGTH vs. CAPACITY:
 
 std::vector - will reallocate its memory if needed, but it would prefer not to
 
 Resizing an array - is computationally expensive
 
 _________________________________________________________________________________________
 Array subscripts [] and at() : are based on length, not capacity
 
 std::vector - fails if we try to access the array element with index past the length
 
 std::vector - won't resize itself based on a call to [] or at() function
 
 _________________________________________________________________________________________
 Stack behavior with std::vector -
 
 std::vector - can be used as a dynamic array
 
 std::vector - can also be used as a stack
 
 std::vector - resizing a vector is expensive
 
 reserve() - function can be used to tell the vector to allocate a certain amount of
 capacity up front, this would minimize the need for resizing the vector again and again,
 if you have an idea of approx. elements that a vector would store then reserve() can be
 used
 
 VECTORS MAY ALLOCATE EXTRA CAPACITY:
 
 When a vector is resized, it may allocate some extra capacity than is needed, it is done
 to provide some breathing room for additional elements, to minimize the number of resize
 operations needed
 
 Allocation of additional capacity : is left up to the compiler implementer
 
 ___________________________________________________________________________________________
 C++ STANDARD:
 
 requires that std::vector grows the capacity exponentially, like double the capacity on
 every resize operation, some compiler results in 1.5x growth, some 2x
 
 ___________________________________________________________________________________________
 */

#include <iostream>
#include <vector>

void print_stack(const std::vector<int>& stack)
{
    for (auto element : stack)
        std::cout << element << ' ';
    
    std::cout << "\nCapacity: " << stack.capacity();
    std::cout << "\tLength: " << stack.size() << '\n';
}

int main()
{
    /// this dynamic array has length 10, even though its 5 elements are used
    int* A{ new int[10] { 1, 2, 3, 4, 5 } };
    
    /// original capacity : 3
    std::vector B { 1, 2, 3 };
    
    /// resize the vector to length 5
    B.resize(5);
    
    std::cout << "B's Length: " << B.size() << '\n';
    
    /// capacity is double the original capacity
    std::cout << "B's capacity: " << B.capacity() << '\n';
    
    for (auto element : B)
        std::cout << element << ' ';
    std::cout << '\n';
    
    std::vector<int> stack{};
    
    /// to avoid the resizing of vector again and again
    /// reserve() - will preallocate the enough capacity for the vector
    stack.reserve(5);
    
    /// capacity is preset to 5
    print_stack(stack);
    
    /// capacity is preset to 5
    /// push_back - function pushes an element on the stack
    stack.push_back(1);
    print_stack(stack);
    
    /// capacity is preset to 5
    stack.push_back(2);
    print_stack(stack);
    
    /// capacity is preset to 5
    stack.push_back(3);
    print_stack(stack);
    
    /// back - function returns the top element on the stack
    std::cout << "Top: " << stack.back() << '\n';
    
    /// pop_back - function pops off the top element on the stack
    stack.pop_back();
    stack.pop_back();
    stack.pop_back();
    
    /// capacity is preset to 5
    print_stack(stack);
    
    std::vector<int> extra_capacity{ 1, 2, 3, 4, 5};
    
    /// capacity is 5
    std::cout << extra_capacity.capacity() << '\n';
    
    extra_capacity.push_back(6);
    
    /// capacity is 10, more than the capacity needed, this happened to minimize the number of resize operations
    std::cout << extra_capacity.capacity() << '\n';
    
    return 0;
}
