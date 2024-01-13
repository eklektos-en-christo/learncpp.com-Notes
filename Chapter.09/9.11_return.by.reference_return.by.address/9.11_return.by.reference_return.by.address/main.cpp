//
//  main.cpp
//  9.11_return.by.reference_return.by.address
//
//  Created by Εκλεκτός εν Χριστώ on 3/3/23.
//

/*
 When returning a value : a copy of the return value is passed back to the caller, if the
 return type of the function is class type then copying can be expensive, like std::string
 copying back to the caller
 
 Return by reference: cases where we pass a class type back to the caller
 return by reference - returns a reference that is bound to the object being returned, this
 avoids making the copy of the return value
 
 to return by reference - simply define the return value of the function to be a reference
 type:
 example - const std::string&   - returns a const reference to an existing std::string
           std::string&         - returns a reference to an existing std::string
 
 Object being returned by reference : must exist after the function returns
 one major caveat - object being referenced must live longer than the function returning the
 reference, otherwise the reference being returned will be a dangling reference, use of
 that dangling reference  will result in undefined behavior
 
 Warning:
 objects returned by reference - must live beyond the scope of the function that returns the
 reference
 never return : a local variable by reference
 
 Don't return - non-const static local variables by reference: fairly non-idiomatic, should
 generally be avoided, programs that run static local by const reference is that there is no
 standardized way to reset s_x back to the default state, such programs must use a non-
 idiomatic solution, like a reset parameter or can only be reset by quitting or restarting
 the program
 
 best practice : avoid returning references to non-const local static variables
 
 returning a const reference to a const local static variable : sometimes done if the local
 variable being returned by reference is expensive to create, so we don't have to recreate
 the variable every function call
 
 returning a const reference to a const const global variable : sometimes done as a way to
 encapsulate access to a global variable
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Assigning/initializing a normal variable with a returned reference makes a copy:
 if a function - returns a reference, and that reference is used to initialize or assign to
 a non-reference(normal) variable, the return value will be copied, as if it had been
 returned by value
 
 this also defeats the purpose of returning a value by reference, because copies are made
 
 if program returns a dangling reference - the reference is left dangling before the copy is
 made which will lead to undefined behavior
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ITS OKAY : to return by reference the reference parameters-
 returning objects by reference : makes sense when a parameter is passed into a function by
 reference, it's safe to return that parameter by reference
 
 this makes sense : in order to pass an argument to a function, the argument must exist in
 the scope of  the caller, when the called function returns, that object must still exist
 in the scope of the caller
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Caller - can modify the values through the reference-
 when an argument is passed to a function by non-const reference, the function can use the
 reference to modify the value of the arguments
 when a non-const reference is returned from a function, the caller can use that reference
 to modify the value being returned
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 RETURN BY ADDRESS: works almost identically to return by reference,
 except - a pointer to an object is returned instead of a reference to an object
 
 return by address - the object being returned by address must live longer than the scope of
 the function returning the address of the object, otherwise the caller will receive a
 dangling pointer
 
 return by address over return by reference advantage - we can have the function return
 nullptr if there is no valid object to return
 
 example-
 we have a list of students that we want to search, if we find the student we are looking
 for, we can return a pointer to the object representing the matching student, if we don't
 find any students matching, we can return nullptr to indicate a matching student object
 was not found
 
 return by address disadvantage - caller has to remember to do a nullptr check before
 dereferencing the return value, otherwise dereferencing a returned null pointer will
 produce undefined behavior
 
 best practice:
 return by reference - should be preferred over return by address unless the ability to
 return "no object" is needed
 
 to return by address-
 specify the * operator after the return type of the function as below
 int* get_integer();
 
 before closing the bracket of the function, remember to return a pointer to the return
 value
 */

#include <iostream>

/// this function returns a const reference
/// no copy will be made on return, a const reference to s_program_name is returned
const std::string& get_program_name()
{
    /// s_program_name - has static duration, it will exist until end of the program
    /// main() will access the s_program_name, which won't be destroyed until later : fine
    static const std::string s_program_name{"CALCULATOR"};
    
    return s_program_name;
}

/// function returning a dangling reference
const std::string& get_program_name_dangling()
{
    /// program_name : local variable, destroys at the end of the function
    const std::string program_name{"CALCULATOR"};
    
    /// undefined behavior
    /// never return a local variable by reference
    return program_name;
}

/// returning non-const local static variable by reference
const int& get_next_id()
{
    /// s_x : is non const
    static int s_x{0};
    /// generating the next ID
    ++s_x;
    /// return a reference to the s_x
    return s_x;
}

/// function returns a reference
const int& get_next_id_assign()
{
    static int s_x{0};
    ++s_x;
    return s_x;
}

/// function returns a dangling reference
const std::string& get_prog_name()
{
    const std::string prog_name{"CALCUALTOR"};
    
    return prog_name;
}

/// no copied are made
/// by using pass by reference/return by reference -  we can avoid the copies that are expensive
const std::string& first_alpha(const std::string& a, const std::string& b)
{
    /// < can be used with std::string to determine which comes first alphabetically
    return (a < b) ? a : b;
}

/// x and y : non-const reference parameters
/// return :  by non-const reference also
/// x binds to a and y binds to b
int& max(int& x, int& y)
{
    return (x > y) ? x : y;
}

/// return by address
/// this example is not totally correct
int* get_integer()
{
    int my_int{30};
    
    int* ptr_my_int{&my_int};
    
//    std::cout << "value: " << my_int << '\n';
    std::cout << ptr_my_int << '\n';

    /// returns the address of my_int
    return ptr_my_int;
}

int main()
{
    /// caller used the const reference returned by the function to access the value of s_program_name
    std::cout << "Program name is: " << get_program_name() << '\n';
    
    /// using a dangling reference to access a destroyed object : undefined behavior
//    std::cout << "Program name is: " << get_program_name_dangling() << '\n';
    
    /// id_1 and id_2 : referencing the same object s_x in the function
    const int& id_1{get_next_id()};
    const int& id_2{get_next_id()};
    
    /// both references id_1 and id_2 : are accessing the modified value
    std::cout << id_1 << id_2 << '\n';
    
    /// id_3 and id_4 : are normal non-reference variables
    /// return value from the returned reference s_x is copied into the id_3 and id_4
    const int id_3{get_next_id_assign()};
    const int id_4{get_next_id_assign()};
    
    std::cout << id_3 << id_4 << '\n';
    
    /// function call returns a copy of a dangling reference
    /// dangling reference is copied to prog_name
    /// undefined behavior
    std::string prog_name{get_prog_name()};
    std::cout << "Program name is: " << prog_name << '\n';
    
    /// no copied made
    /// function returns by reference the reference parameters
    std::cout << first_alpha("hello", "world") << '\n';
    
    int a{20};
    int b{400};
    
    /// max : returns reference to b, because b is greater than a
    /// b : is assigned with value 100
    /// max(a, b) = 100; is equivalent of/resolves to b = 100;
    /// y is still bound to b
    max(a, b) = 100;
    
    std::cout << a << ' ' << b << '\n';
    
    /// dereferencing the returned address to access the value
    std::cout << ++*get_integer() << '\n';
    std::cout << ++*get_integer() << '\n';
    std::cout << ++*get_integer() << '\n';
    
    std::cout << "address: " << get_integer() << '\n';
    
    int x{*get_integer()};
    
    std::cout << x << '\n';
    
    return 0;
}
