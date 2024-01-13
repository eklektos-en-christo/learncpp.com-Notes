//
//  main.cpp
//  12.1_function.pointers
//
//  Created by Εκλεκτός εν Χριστώ on 6/4/23.
//

/*
 Pointer - holds the address of another variable
 
 Function pointer - it points to functions rather than pointing to variables
 
 Functions : have their own l-value function type
 Functions : live at an assigned address is memory
 
 When a function is called via the operator() - execution jumps to the address of the function being called
 
 Possible - to declare a non-constant pointer to a normal variable
 Possible - to declare a non-constant pointer to a function
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Pointers to functions:
 
 syntax for creating a non-const function pointer -
 
        int (*function_pointer)();
 
 function_pointer - is a pointer to a function that has no parameters and returns an integer
 function_pointer - can point to any function that matches this type
 
 (*function_pointer) - parentheses around *function_pointer are for precedence reasons
 
        int* function_pointer();
 this would be interpreted as forward declaration for a function named function_pointer that takes no
 parameters and returns a pointer to an integer
 
 syntax for creating a const function pointer - const goes after the asterisk
 
        int (*const function_pointer)();
 
 
        const int (*function_pointer)();    - this indicates the function being pointed to would return a
                                              const int
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ASSIGNING A FUNCTION TO A FUNCTION POINTER:
 
 Function pointers - can be initialized with a function
 
 Non-const function pointers - can be assigned a function because they are not const hence can be
 reassigned
 
 Return type and parameters of function pointer - must match the type of the function being assigned
 
 Address of operator(&) - no need to use to get the function's address, C++ will implicitly convert a
 function into a function pointer if needed
 
 Function pointers - will not convert to void pointers
 Void pointer - will not convert to function pointers
 
 Function pointers - can also be initialized or assigned the value nullptr
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 CALLING A FUNCTION USING A FUNCTION POINTER:
 
 Using a function pointer to actually call the function- two ways to do this.
 WAY 1 : Explicit dereference
 WAY 2 : Implicit dereference
 
 Normal function names - are pointers to function internally
 
 Default parameters : won't work for functions called through function pointers
 
 Default parameters : are resolved at compile time
 
 Function pointers  : are resolved at run time
 
 Default parameters : cannot be resolved at runtime when making a function call with a function pointer
 
 Default parameters : must be passed in explicitly when making a function call with a function pointer
 
 Function pointers  : can be set to nullptr, they should be conditionally checked before calling them
 
 Dereferencing a null function pointer : leads to undefined behavior
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 PASSING FUNCTION AS ARGUMENTS TO ANOTHER FUNCTIONS:
 
 Callback functions : functions used as arguments to another function
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Note : if a function parameter is of a function type then parameter will be converted to a pointer to the
 function type
 
 void selectionSort(int* array, int size, bool (*comparisonFcn)(int, int))
 
        ----------------same as-----------------------
 
 void selectionSort(int* array, int size, bool comparisonFcn(int, int))
 
 this only works for function parameters
 
 On non-function parameter -
 
 bool (*ptr)(int, int);             - this is a function pointer
 -------not same as ------
 bool ptr(int, int);                - this is interpreted as a forward declaration
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 PROVIDING DEFAULT FUNCTIONS:
 
 Like in selection sort - we can provide a default argument to the function pointer parameter, if the user
 calls selection sort normally, the parameter will default to the ascending(if ascending is the default
 argument given in the definition),
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 MAKING THE FUNCTION POINTERS PRETTIER USING TYPE ALIASES:
 
 The syntax for function pointers - is ugly
 
 Type aliases - can be used to make function pointers look more like regular variables
 
 instead of using this:
 bool validate(int x, int y, bool (*fcnPtr)(int, int));        -    ugly
 
 this can be used:
 bool validate(int x, int y, compare fcn)                      -    clean
 
 Note: fcn in above statement is the declaration of a function pointer variable
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Using std::function - alternate method for defining and storing function pointers
 
 std::function : part of the std lib header <functional>
 
 declaration of std::function object-
 bool validate(int x, int y, std::function<bool(int, int)> fcn);
 
 from above prototype:
 return type and parameters - go inside angled brackets, parameters inside parentheses
 
 if there are not parameters - parentheses can be left empty as below:
 bool validate(int x, int y, std::function<bool()> fcn);
 
 TYPE ALIASING THE std::function - can be helpful for readability
 
 std::function : allows only calling the function via implicit dereference not explicit dereference
 
 When defining a type alias - we must explicitly specify any template arguments
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 TYPE INFERENCE FOR FUNCTION POINTERS:
 
 auto keyword - can also infer the type of a function pointer but downside is that all the function's
 parameter types and return type are hidden, it's easier to make mistake when making call with the function
 or using it's return value
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 CONCLUSION:
 Function pointers - useful when we want to store functions in an array or other structure
 function pointers - useful when you need to pass a function to another function
 
 use - std::function, as native syntax to declare function pointers is ugly and error
       prone
 
 Where function pointer is only used once(a single parameter or return value) -
 std::function can be used directly
 
 Where function pointer is used multiple times - a type alias to a std::function is a
 better choice to prevent repetition
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */


#include <iostream>
#include <cassert>
#include <utility>
#include <functional>
using arithmetic_function = std::function<int(int, int)>;

/// foo - an identifier, function's name
///
int foo()
{
    return 10;
}

int goo()
{
    return 4;
}

void hoo();

int loo()
{
    return 1;
}

int poo(int x)
{
    return x;
}

int fn_default_params(int x, int y = 2)
{
    return (x * y);
}

/// comparison function - sorts in ascending order
bool ascending(int x, int y)
{
    return (x > y);
}

/// comparison function - sorts in descending order
bool descending(int x, int y)
{
    return (x < y);
}

void print_array(int* A, int size)
{
    for (int i{ 0 }; i < size; ++i)
    {
        std::cout << A[i] << ' ';
    }
    
    std::cout << '\n';
}

/// comp_func - a comparison function pointer parameter, to which the caller can pass a comparison function to specify the order of sorting
/// defaulted the sort to ascending, if user doesn't pass the comparison function to the selection sort
/// In this case - ascending is the default order of sorting provided to the function pointer parameter
///
/// commented out prototype also works - works only if the function parameter is of function type
/// commented out prototype, comp_func function parameter- is a function pointer to the function type
/// If a function parameter is of a function type, it will be converted to a pointer to the function type
//void selection_sort(int* A, int size, bool comp_func(int, int) = ascending)
///
///
void selection_sort(int* A, int size, bool (*comp_func)(int, int) = ascending)
{
    for (int start{ 0 }; start < (size - 1); ++start)
    {
        int smallest{ start };
        
        for (int current{ start + 1 }; current < size; ++current)
        {
            if (comp_func(A[smallest], A[current]))
            {
                smallest = current;
            }
        }
        
        std::swap(A[start], A[smallest]);
    }
}

/// sorts even numbers first in the array
bool evens_first(int x, int y)
{
    if ((x % 2 == 0) && !(y % 2 == 0))
        return false;
    
    if (!(x % 2 == 0) && (y % 2 == 0))
        return true;
    
    return ascending(x, y);
}

///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int get_integer()
{
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;
    
    return x;
}

char get_operation()
{
    char c{};
    
    do
    {
        std::cout << "Enter the one operation from +, -, *, / : ";
        std::cin >> c;
    }
    while (c != '+' && c != '-' && c != '*' && c != '/');
    
    return c;
}

int add(int a, int b)
{
    return (a + b);
}

int subtract(int a, int b)
{
    return (a - b);
}

int multiply(int a, int b)
{
    return (a * b);
}

int divide(int a, int b)
{
    return (a / b);
}

arithmetic_function get_arithmetic_function(char c)
{
    switch (c)
    {
        case '+' : return &add;
        case '-' : return &subtract;
        case '*' : return &multiply;
        case '/' : return &divide;
            
    }
    
    return nullptr;
}

int main()
{
    /// printing the foo itself, this is not a call to foo()
    /// machine is not printing the actual address of the foo
    /// so using reinterpret_cast - converting the function to a void pointer
    /// C++ will interpret function foo as a void pointer
    std::cout << reinterpret_cast<void*>(foo) << '\n';
    
    /// Note: we can use & to get a function pointer to foo in the below case
    /// fn_pointer initialized with foo function
    /// fn_pointer points to the function foo now
    int (*fn_pointer)(){ &foo };
 
    /// fn_pointer now points to the function goo, assignment  used here
    /// fn_pointer is non-const, so reassigning to it the goo won't produce an error
    fn_pointer = &goo;
    
    /// error : () will call the foo and int return value will be provided to fn_pointer which is what fn_pointer expecting
    /// fn_pointer expecting : int (*)()
    /// solution : remove parentheses
//    fn_pointer = foo();
    
    /// no need to use & operator to get the foo's address
    /// implicit conversion from function into a function pointer
    /// foo converted to a function pointer even though we didn't use & operator
    fn_pointer = foo;
    
    /// foo will not convert to a void pointer
//    void* vptr{ foo };
    
    /// function pointer can also be initialized with a nullptr value
    int (*null_fcn_ptr)(){ nullptr };
    
    /// function pointer can also be assigned a nullptr value
    null_fcn_ptr = nullptr;
    
    int (*explicit_dereference_ptr)(){ &loo };
    
    /// calling the function loo using a function pointer
    /// this is explicit dereference to loo
    (*explicit_dereference_ptr)();
    
    int (*implicit_dereference_ptr)(int){ &poo };
    
    /// this is implicit dereference to poo
    /// implicit dereference - just looks like the normal function call
    std::cout << implicit_dereference_ptr(40) << '\n';
    
    int (*default_param_ptr)(int, int){ fn_default_params };
    
    /// default argument not provided, call to function fn_default_params fails
//    default_param_ptr(2);
    
    /// explicit passing in the value for default parameter
    std::cout << default_param_ptr(2, 10) << '\n';
    
    default_param_ptr = nullptr;
    
    /// dereferencing the null function pointer - undefined behavior
//    (*null_fcn_ptr)();
//    null_fcn_ptr();
    
    /// checking whether the function pointer is null or not
    /// if null then don't make a call to the function
    if (null_fcn_ptr)
        null_fcn_ptr();
    
    null_fcn_ptr = &foo;
    
    /// works - null function pointer assigned the function foo in previous statement
    if (null_fcn_ptr)
        std::cout << null_fcn_ptr() << '\n';
    
    null_fcn_ptr = nullptr;
    
    int A[]{ 2, 0, 1, 30, 16, 9, 10, 3 };
    
    /// sort function taking the comparison function as an argument
    /// function passed as an argument to other function
    selection_sort(A, 8, ascending);
    print_array(A, 8);
    
    /// function passed as an argument to other function
    selection_sort(A, 8, descending);
    print_array(A, 8);
    
    selection_sort(A, 8, evens_first);
    print_array(A, 8);
    
    /// the function argument is optional now
    /// if user doesn't pass the function argument then the default parameter is used
    selection_sort(A, 8);
    print_array(A, 8);
    
    /// using type alias to make the function pointer name simple and readable and easier to use
    /// func_pointer - is a pointer to a function that takes two integers and returns the integer sum
    using func_pointer = int (*)(int, int);
    
    /// declaring a function pointer using std::function
    /// return type is - int, inside the <> brackets
    /// parameters are empty - <int()>
    /// fcn_ptr - name of the function pointer, pointer to foo
    std::function<int()> fcn_ptr{ &foo };
    fcn_ptr = &goo;
    
    /// implicit dereference
    /// calling the function just like the normal function call
    std::cout << fcn_ptr() << '\n';
    
    /// explicit dereference - not allowed when using std::function
//    std::cout << (*fcn_ptr)() << '\n';
    
    /// type alias to a raw function pointer
    using validate_func_raw = bool(*)(int, int);
    
    /// type alias to std::function
    using validate_func = std::function<bool(int, int)>;
    
    /// When defining a type alias, we must explicitly specify any template arguments
    /// We can’t use CTAD in this case since there is no initializer to deduce the template arguments from.
    using template_func_alias = int(*)();
    
    /// auto - can be used to infer the type of a function pointer
    /// downside - function's parameter type and return type are hidden
    auto infer_ptr{ &loo };
    
    /// easy to make mistake when using type inference
    /// function accepts no arguments but here is provided one
//    std::cout << infer_ptr(2) << '\n';
    
    std::cout << infer_ptr() << '\n';
    std::cout << (*infer_ptr)() << '\n';
    
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int x{ get_integer() };
    int y{ get_integer() };
    
    char op{ get_operation() };
    
    arithmetic_function arith_fcn{ get_arithmetic_function(op) };
    
    if (arith_fcn)
    {
        std::cout << x << ' ' << op << ' ' << y << " : ";
        std::cout << arith_fcn(x, y) << '\n';
    }
    
    return 0;
}
