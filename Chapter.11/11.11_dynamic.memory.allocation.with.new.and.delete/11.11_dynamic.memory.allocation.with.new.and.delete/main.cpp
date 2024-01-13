//
//  main.cpp
//  11.11_dynamic.memory.allocation.with.new.and.delete
//
//  Created by Εκλεκτός εν Χριστώ on 4/3/23.
//

/*
 NEED FOR DYNAMIC MEMORY ALLOCATION:
 types of memory allocation in cpp - 3 types
 
 -static memory allocation : happens for static and global variables, memory allocated once
 for these types of variables(when program runs) and persists throughout the life of the
 program
 
 -automatic memory allocation : happens for function parameters and local variables, memory
 allocated for these types of variables when relevant block is entered and freed when block
 is exited as many times as necessary
 
 two things in common with static and automatic:
 -size of variable/array must be known at compile time
 -memory allocation and deallocation happens automatically when variable instantiated or
 destroyed
 
 four reasons when memory allocated isn't dynamic:
 -wastage of memory
 -how do we tell which bits of memory are actually used, this adds complexity
 -amount of stack memory for a program is generally quite small, exceeding the number will
 cause stack overflow
 -it can lead to artificial limitation and/or array overflows, when user tries to read in
 more records from the disk than the memory allocated for maximum records is small
 
 DYNAMIC MEMORY ALLOCATION : way for the running programs to request memory from the OS when
 needed, this memory does not come from the program's limited stack memory, it is allocated
 from a much larger pool of memory managed by OS called HEAP.
 
 HEAP - this memory can be GBs in size, managed by the OS
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Dynamically allocating single variables:
 
 TO ALLOCATE A SINGLE VARIABLE DYNAMICALLY - we use the scalar/non-array form of the new
 operator
 
 new operator - creates the object using the required memory then returns a pointer
 containing the address of the memory that has been allocated
 
 most often - we assign the return value to our own pointer variable so we can access the
 allocated memory later
 
 we can perform indirection through the pointer to access the memory
 
 Without a pointer - holding the memory address of the memory that was just allocated, we'd
 have no way to access the memory that was just allocated for us
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Working of dynamic memory allocation:
 Computer memory - available for applications to use
 
 when an application is run:
 OS - loads the application into some of that memory
 memory used by application - divided into different areas:
 one area - contains the code
 another area - for normal operations like keeping track of function calls, creating and
 destroying of global and local variables etc
 much of memory available - just sits there, waiting to be handed out to programs that
 request it
 
 when memory dynamically allocated - you're asking the OS to reserve some of that memory for
 your program's use, if it can fulfill the request, then it will return the address of that
 memory to your application
 
 when your application is done with the memory - it can return memory back to the OS to be
 given to another program
 
 dynamically allocated memory - program itself is responsible for requesting and disposing
 the dynamically allocated memory
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 How to initialize a dynamically allocated variable?
 
 TO DYNAMICALLY ALLOCATE A VARIABLE - initialization can be done via direct or uniform
 initialization
 
 int* ptr1{ new int( 2 ) };         /// direct
 int* ptr1{ new int{ 2 } };         /// uniform
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Delete a dynamically allocated variable:
 when done with the dynamically allocated variable, there is a need to explicitly tell C++
 to free the memory for reuse
 
 FOR SINGLE VARIABLES, DELETION OF DYNAMICALLY ALLOCATED VARIABLE - is done via the scalar/
 nor-array form of the delete operator
 
 // assuming the ptr has previously been allocated with operator new
 delete ptr;            /// return the memory pointer to by ptr to the OS
 ptr = nullptr;         /// or set the ptr to be a null ptr
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 What does it mean to delete the memory?
 delete operator - doesn't delete anything actually
 
 delete operator - returns the memory being pointed to back to the OS
 
 pointer variable still has the same scope as before the deletion, and can be assigned a
 new value just like any other variable
 
 deleting a pointer that isn't pointing to dynamically allocated memory - may cause bad
 things to happen
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Dangling pointers:
 C++ - does not guarantees about what will happen to the contents of the deallocated memory
 or to the value of the pointer being deleted
 
 most cases - memory returned to the OS will contain the same values it had before it was
 returned, and pointer will be left pointing to the now deallocated memory
 
 Dangling pointer - a pointer pointing to the deallocated/deleted/freed memory
 
 Indirection through or deleting a dangling pointer - will lead to undefined behavior
 
 deallocating memory - may create multiple dangling pointers
 
 few best practices:
 -avoid multiple pointers point at the same piece of dynamic memory, if not possible, be
 clear about which pointer owns the memory and is responsible for deleting it and which
 pointers are just accessing it
 -when deleting a pointer: if pointer isn't going out of scope immediately afterward, the
 set it to nullptr
 
 BEST PRACTICE:
 set deleted pointers to nullptr unless they are going out of scope immediately afterward
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Operator new can fail-
 
 if OS may not have any memory to grant with - then new fails
 
 bad_alloc exception - thrown, if new fails
 
 unhandled bad_alloc exception - termination/crash of the program with an unhandled
 exception error
 
 Alternate form  of new - can be used to tell new to return a null pointer if memory can't
 be allocated

 std::nothrow - constant, added between the keyword new and the allocation type as below-
 int* value{new(std::nothrow) int};
 
 if new fails - it will return a null pointer instead of the address of the allocated memory
 
 indirection through null pointer - undefined behavior, mostly a program crash
 
 best practice:
 check all memory requests to ensure they actually succeeded before using the allocated
 memory, may using if condition to check if pointer is null or not
 
 null check - is the most common to forget because asking the new for memory rarely fails,
 almost never fails in a dev environment
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Null pointers and dynamic memory allocation:
 
 null pointers - particularly useful when dealing with DMA
 
 in DMA context, a null pointer - basically says "no memory has been allocated to this
 pointer"
 
 this allows us to do things - like conditionally allocate memory
 
 deleting a null pointer - has no effect, no need to conditionally check the null pointer
 
 BEST PRACTICE:
 deleting a null pointer - okay, no need to conditionalize the delete statements
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Memory leaks:
 
 DMA - stays allocated until it is explicitly deallocated or until the program ends(OS clean
 it up, assuming the OS does that)
 
 pointers that hold dynamically allocated addresses - follow the normal scoping rules for
 local variables
 
 when block ends, ptr goes out of scope
 
 Memory leak - when program loses the address of some bit of dynamically allocated memory
 before giving it back to the OS, OS also can't use this memory, OS will assume that it
 is being used by the program
 
 memory leaks - eat up free memory while program is running, it may eat up the whole memory
 available, it slows down the machine, may crash,
 
 ways that memory leaks can result:
 -pointer going out of scope
 -pointer holding dynamic address when assigned another value
 -also possible to get a memory leak via double-allocation
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 CONCLUSION:
 -new and delete : allow to dynamically allocate single variable for the programs
 -DMA : has dynamic duration, will stay allocated until programmer deallocate it or program
  terminates
 -do not perform indirection through dangling or null pointers
 
 */

#include <iostream>

/// this function has a memory leak
void do_something()
{
    int* ptr{new int{}};
}   /// ptr goes out of scope here, memory allocated still present somewhere

int main()
{
    /// dynamically allocate an integer and discard the result
    /// we requesting an integer's worth of memory from the OS, new operator creates the object using that memory
    new int;
    
    /// dynamically allocate an integer and assign the address to ptr for later access, no initialization here
    int* ptr{new int};
    
    /// performing the indirection using pointer
    /// indirection - accessed the memory and assigned with 10
    *ptr = 10;
    
    /// dynamically allocating and also initializing a dynamically allocated variable
    int* ptr1{new int(2)};          /// direct initialization
    int* ptr2{new int{5}};          /// uniform initialization
    
    /// deleting the dynamically allocated memory, deleting a single variable
    /// delete - is non-array/scalar form of the delete operator
    delete ptr1;
    ptr2 = nullptr;
    
    /// dynamically allocating an integer
    int* ptr3{new int{}};
    /// putting 33 in that location
    *ptr3 = 33;
    
    /// ptr3 - now a dangling pointer
    delete ptr3;
    
    /// undefined behavior - indirection through a dangling pointer
    std::cout << *ptr3 << '\n';
    
    /// undefined behavior - trying to deallocate the memory again which was deallocated before
//    delete ptr3;
    
    /// dynamically allocating an integer
    int* ptr4{new int{}};
    /// ptr5 - points to the same memory location that ptr4 points to
    int* ptr5{ptr4};
    
    /// return memory to OS
    /// ptr4 and ptr5 - now are dangling pointers
    delete ptr4;
    /// ptr4 - now a null pointer
    ptr4 = nullptr;
    
    /// ptr5 - still a dangling pointer, undefined behavior
    std::cout << *ptr5 << '\n';
    
    /// if the allocation fails, the ptr6 will be set to a null pointer
    /// if new fails - it will return a null pointer instead of the address of the allocated memory
    int* ptr6{new(std::nothrow) int};
    
    int* ptr7{new(std::nothrow) int{}};
    
    /// handling case when pointer returned by the new is null
    if (!ptr7)
        /// print error message
        std::cout << "couldn't allocate memory" << '\n';
    
    /// if pointer isn't allocated, then only allocated memory
    if (!ptr7)
        ptr7 = new int;
    
    /// deleting a null pointer has no effect, what's the point of deleting a null pointer
    ///
    /// if pointer is not null then only delete it, otherwise do nothing
    if (ptr4)
        delete ptr4;
    
    /// instead of the above code
    /// no need to conditionalize the delete statements
    /// because if ptr is not null then memory will be deleted, otherwise nothing will happen
    delete ptr4;
    
    int value{20};
    /// allocate memory
    int* ptr8{new int{}};
    /// new address assigned, old dynamic memory leak results
    /// solution is to delete the memory before reassigning the another address
//    delete ptr8;
    ptr8 = &value;
    
    /// allocate dynamic memory
    /// first allocation - memory leak
    int* ptr9{new int{}};
    /// address changed, old memory leak results
    /// address returned from second allocation overwrote  the address of the first allocation
    /// solution - delete the old memory before assigning the new memory
//    delete ptr9;
    ptr9 = new int{};
    
    return 0;
}
