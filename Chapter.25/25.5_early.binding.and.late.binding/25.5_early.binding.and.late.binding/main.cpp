//
//  main.cpp
//  25.5_early.binding.and.late.binding
//
//  Created by Εκλεκτός εν Χριστώ on 11/3/23.
//

/*
 When a C++ program is executed: it executes sequentially, from the top of main, when a function call is
 encountered, the point of execution jumps to the beginning of the function being called.
 
 When a program is compiled: the compiler converts each statement into one or more lines of machine code,
 each line of machine code is given its own unique sequential address
 
 When a function is compiled: it is converted into machine code and given the next available address, thus
 each function ends up with a unique address
 
 -----------------------------------------------------------------------------------------------------------
 BINDING: the process that is used to convert the identifiers(like variable names, function names etc.) into
 addresses
 
 -----------------------------------------------------------------------------------------------------------
 Direct function call: a statement that directly calls a function, direct function call can be using a
 process known as early binding
 
 EARLY BINDING/STATIC BINDING: means the compiler or linker is able to directly associate the identifier
 name with a machine address. When compiler encounters a function call, it replaces the function call with
 a machine language instruction that tells the CPU to jump to the address of the function
 
 -----------------------------------------------------------------------------------------------------------
 LATE BINDING/DYNAMIC BINDING(in case of virtual function resolution): in some programs, the function being
 called can't be resolved until runtime
 
 In general programming: late binding means the function being called is looked up by name at runtime, C++
 does not support this mechanism.
 
 C++ late binding: typically used in cases where the actual function being called is not known by the
 compiler or linker at the point where the function call is actually being made. Instead, the function to
 be called has been determined at runtime, somewhere prior to that point
 
 One way to achieve late binding in C++ is to use function pointers, calling a function via a function
 pointer is also known as indirect function call
 
 Late binding: slightly less efficient, involves an extra level of indirection, the program has to read the
 address held in the pointer and then jump to that address. This one extra step making it slightly slower,
 but it is more flexible than early binding, decision about what function to call do not need to be made
 until runtime.
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>

void print_value(int value)
{
    std::cout << value << '\n';
}

int add(int x, int y)
{
    return x + y;
}

int subtract(int x, int y)
{
    return x - y;
}

int multiply(int x, int y)
{
    return x * y;
}

int main()
{
    /// a direct function call - statement calling the function directly - early binding
    print_value(22323);
    
    int x{};
    std::cout << "Enter 1st number: ";
    std::cin >> x;
    
    int y{};
    std::cout << "Enter 2nd number: ";
    std::cin >> y;
    
    int op{};
    do
    {
        std::cout << "Enter an operation, (0=add, 1=subtract, 2=multiply): ";
        std::cin >> op;
    } while (op < 0 || op > 2);
    
    int result{};
    switch (op)
    {
        /// call the target function directly using early binding
        /// the compiler will use early binding to resolve the add(), subtract() and multiply()
        /// compiler will replace the function call with the address of the function
        /// this will tell the CPU to jump to that address
        case 0: result = add(x, y); break;
        case 1: result = subtract(x, y); break;
        case 2: result = multiply(x, y); break;
    }
    
    std::cout << "Answer is: " << result << '\n';
    
    /// create a function pointer and make it point to the add function
    int (*p_func)(int, int){ add };
    
    /// indirect function call - calling the function add() via function pointer p_func
    /// this used the late binding - compiler can't tell which function will be called before the runtime
    std::cout << p_func(2, 2) << '\n';
    
    return 0;
}
