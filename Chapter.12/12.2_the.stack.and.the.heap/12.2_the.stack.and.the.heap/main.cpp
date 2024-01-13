//
//  main.cpp
//  12.2_the.stack.and.the.heap
//
//  Created by Εκλεκτός εν Χριστώ on 6/15/23.
//

/*
 _________________________________________________________________________________________
 Memory used by a program is typically divided into few different areas called segments:
 
 Code segment : text segment, where compiled program sits, typically read only
 
 BSS  segment : uninitialized data segment, where zero initialized global & static
                variables are stored
 
 Data segment : initialized data segment, where initialized global & static variables are
                stored
 
 The heap     : where dynamically allocated variables are allocated from
 
 Call stack   : where function parameters, local variables and other function related info
                are stored
 
 _________________________________________________________________________________________
 THE HEAP SEGMENT/ free store: it keeps track of memory allocated dynamically
 
 Operator new - when used, it allocated the memory in application's heap segment
 
 Operator new - passes back the address of the memory allocated and that address is then
                stored in a pointer
 
 Sequential memory requests - may not result in sequential memory addresses being
                              allocated
 
 When dynamically allocated memory is deleted - memory is returned to the heap and then
 can be reassigned for future allocation requests.
 
 Deleting a pointer - doesn't delete the variable, it just returns the memory at the
 associated address back to the OS.
 
 ADVANTAGES AND DISADVANTAGES OF HEAP MEMORY:
 
 DISADVANTAGES:
 - allocating heap memory is slow
 
 - memory stays allocated until it is specifically deallocated or when the app. ends
 
 - dynamically allocated memory must be accessed through a pointer
 
 - dereferencing a pointer is slower than accessing a variable directly
 
 ADVANTAGES:
 - heap is a big pool of memory, large arrays, structures or classes can be allocated here
 
 _________________________________________________________________________________________
 THE CALL STACK/ stack: keeps track of all the active functions from the start to the
 current of execution
 
 All function parameters and local variables are allocated in the stack
 
 Call stack: is implemented as a stack data structure
 
 _________________________________________________________________________________________
 The Stack DS: consider the stack as a stack of plates
 
 Data structure: programming mechanism for organizing data so that it can be used
                 efficiently
 
 Stack: container data structure that holds multiple variables
 
 Array: lets access and modify the elements in any order, random access
 
 But Stack is limited, below are the operations that can be performed on a stack:
 - look at the top item on the stack : top()/peek()
 - take the top item off of the stack: pop()
 - put a new item on top of the stack: push()
 
 Stack: LIFO structure
 
 LIFO mechanism: last in, first out, last item pushed onto the stack will be the first to
 popped off of the stack
 
 Pushing: stack grows
 Popping: stack shrinks/reduces
 
 A great analogy:
 
 we use a marker to keep track of the stack space, in the beginning the stack is empty,
 when we push an item onto the stack we move the marker up by one unit, when item is
 popped off we move the marker down by one unit, so now the marker is still there where
 it was in the beginning
 
 anything below the marker : considered on the stack
 anything at or above the marker : considered not on the stack
 
 _________________________________________________________________________________________
 THE CALL STACK SEGMENT: holds the memory used for the call stack
 
 OS : pushes the main() function of an app. on the call stack, from there the program
      execution starts

 Unwinding the stack: when function call is encountered, the function is pushed onto the
 stack, when the function ends, that function is popped off the call stack
 
 To get to the current point of execution: by looking at the functions that are currently
 on the call stack
 
 Stack itself - is a fixed size chunk of memory addresses
 
 Stack frames - the items we are pushing and popping on the stack
 
 Stack frame  - keeps track of all of the data associated with one function call
 
 Register(SP) - a small piece of memory in the CPU known as stack pointer
 
 Stack pointer- keeps track of where the top of the call stack currently is
 
 On the stack - when a stack frame is popped off the call stack, we only have to move the
                stack pointer down, no need to clean up the memory used by the previous
                popped off stack frame, when new stack frame to the same memory is pushed,
                the same memory will be overwritten by the new stack frame (optimization)
 
 _________________________________________________________________________________________
 THE CALL STACK IN ACTION:
 
 below are the sequence of steps that takes place when a function is called:
 
 - the program encounters a function call
 
 - a stack frame is constructed and pushed on the stack
 
 - the stack frame consists of:
                - address of the instruction beyond the function call(return address)
                - return address helps CPU to return to the next instruction which is to
                  be executed next when the current function ends
                - all function arguments
                - memory for any local variables
                - saved copies of any registers modified by the function that need to
                  be restored when the function returns
 
 - the CPU jumps to the function's start point
 - instructions inside of the function begin executing
 
 when the function terminates, following steps happen:
 
 - registers are restored from the call stack
 
 - stack frame is popped off the stack, this frees the memory for all local variables &
   arguments
 
 - the return value is handled
 
 - CPU resumes the execution at the return address
 
 On some architectures: call stack grows away from memory address 0, on others it grows
 toward memory address 0
 
 _________________________________________________________________________________________
 STACK OVERFLOW: when all the memory in the stack has been allocated, further allocations
 begin to overflow into other sections of memory
 
 Stack: has a limited size
 
 Windows: stack size is 1MB
 Unix: 8MB
 
 Stack overflow: generally the result of allocating too many variables on the stack or
 making too many nested function calls
 
 On modern OS's: stack overflow will cause the termination of the program with an access
 violation error
 
 _________________________________________________________________________________________
 ADVANTAGES AND DISADVANTAGES OF STACK:
 
 ADVANTAGES:
 
 - allocating memory on stack is faster
 
 - allocated memory on stack is known at compile time, this memory can be accessed
   directly through a variable
 
 DISADVANTAGES:
 - memory allocated on stack stays in scope as long as it is on the stack, destroyed when
   popped off the stack
 
 - stack is relatively small, not a good idea to do something that would eat up the whole
   space on the stack, this includes passing by value or creating local variables of large
   arrays or other memory intensive structures
 _________________________________________________________________________________________
 */

#include <iostream>

int global_counter{ 0 };

int foo(int x)
{
    return x;
}   /// foo is popped off the call stack here

void eat_stack()
{
    std::cout << ++global_counter << ' ';
    
    if (global_counter > 0)
        eat_stack();
    
    std::cout << "I won't execute!\n";
}

int main()
{
    /// 4 bytes allocated in the heap, ptr holds the address of that memory
    int* ptr{ new int };
    
    /// array is assigned 40 bytes in the heap
    int* array{ new int[10] };
    
    /// ptr1 & ptr2 - may not have sequential addresses
    int* ptr1{ new int };
    int* ptr2{ new int };
    
    /// foo is pushed on the call stack here
    foo(3);
    
    /// this will cause the stack overflow
//    int stack[10000000];
    
//    std::cout << "Hello " << stack[0] << '\n';
    
    /// this will cause stack overflow as the eat_stack calls itself again and again and never returns to the caller
//    eat_stack();
    
    return 0;
}
