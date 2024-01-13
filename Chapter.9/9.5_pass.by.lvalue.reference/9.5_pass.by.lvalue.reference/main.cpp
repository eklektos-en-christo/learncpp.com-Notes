//
//  main.cpp
//  9.5_pass.by.lvalue.reference
//
//  Created by εκλεγμένοι εν Χριστώ on 2/21/23.
//

/*
 Why create an alias to a variable if you can just use the variable itself?
 
 Pass by value : where an argument passed to a function is copied into the function's
 parameter
 
 Fundamental types : are cheap to copy, so pass by value is not the problem in pass by value
 case
 
 Some objects are expensive to copy:
 most of the types provided by standard library : class types, like std::string
 class types : usually expensive to copy
 
 Whenever possible : avoid making unnecessary copies of objects that are expensive to copy,
 especially when they are destroyed immediately after their use
 
 Pass by reference :
 we declare function as a reference type/const reference type rather than as a normal type
 when function is called - each reference parameter is bound to the appropriate argument,
 reference acts as alias for the argument - no copy of the argument is made
 
 binding a reference : always inexpensive
 
 one way to avoid making expensive copy of an argument when calling a function - pass by
 reference instead of pass by value
 
 Key insight:
 pass by reference allows to pass arguments to a function without making copies of those
 arguments each time the function is called
 
 Pass by reference : allows us to change the value of an argument -
 when an object is passed by value - function parameter receives a copy of the argument,
 any changes made to the value of the parameter are made to the copy of the argument, not
 the argument itself
 when an object is passed by reference - any changes made to the reference parameter will
 affect the argument/object passed
 
 Key insight:
 values that are passed by reference to non-const allows us to write functions that modify
 the value of arguments passed in
 
 Pass by reference to non-const : can only accept modifiable lvalue arguments, because a
 reference to non-const value can only bind to a modifiable lvalue(non-const variable)
 pass by reference : only works with arguments that are modifiable lvalues
 this significantly limits the usefulness of pass by reference to non-const, it means we
 cannot pass const variables or literals
 
 pass by const reference :
 a reference to const : can bind to modifiable lvalues, non-modifiable lvalues and rvalues,
 if we make our parameter const, then it will be able to bind to any type of argument
 passing by const reference - guarantees that function can't change the value being
 referenced
 
 In most cases : we don't want our functions to modify the value of arguments
 
 best practice :
 favor passing by const reference over passing by non-const reference unless there is a
 specific reason to do so, e.g function needs to change the value of an argument
 
 that's the motivation for allowing - const lvalue references to bind to rvalues, without
 this capability, there would be no way to pass literals or other rvalues to functions
 that used pass by reference
 
 Mixing pass by value and pass by reference:
 function with multiple parameters - can determine whether each parameter is passed by value
 or passed by reference individually
 
 When to pass by reference?
 -pass fundamental types by value(cheap to copy)
 -pass class/struct types by const reference(to avoid expensive copying of the argument)
 
 Cost of pass by value and pass by reference:
 two key points to help us understand when we should pass by value vs pass by reference:
 
 first- cost of copying an object is generally proportional to two things
 -size of the object, bigger the object, bigger time to copy
 -any additional setup costs, some class types do additional setup when they are
 instantiated, e.g opening a file/database,allocating a certain amount of dynamic memory to
 hold an object of a variable size, these setup costs must be paid each time an object is
 copied
 
 binding to a reference to a object is always fast, same speed as copying a fundamental type
 
 Second-
 -accessing an object through a reference is more expensive than accessing through a normal
 variable identifier, with a variable identifier, running program can just go to the memory
 address assigned to that variable and access the value directly, with a reference, there is
 usually an extra step- the program must access first the reference to determine which
 object is being referenced, then only it can go to that memory address for that object and
 access the value
 -code generated to access objects passed by reference is typically slower than the code
 generated for objects passed by value
 
 Why we don't pass everything by reference?
 -for objects that are cheap to copy : cost of copying is similar to the cost of binding, so
 we favor pass by value so the code generated will be faster
 -for objects that are expensive to copy : cost of copy dominates, so we favor pass by const
 reference to avoid making a copy
 
 best practice:
 prefer pass by value : for objects that are cheap to copy
 prefer pass by const reference : for objects that are expensive to copy
 if not sure of either : favor pass by const reference
 
 good rule of thumb: an object is cheap to copy if it used 2 or fewer "words" of memory
 (word is approx. size of a memory address)and it has no setup costs
 
 it is best to assume that : most standard library classes have setup costs, unless you
 know otherwise that they don't
 
 An object of type T is cheap to copy : if sizeof(T) <= 2 * sizeof(void*) and has no
 additional setup costs
 
 common cheap to copy types : all fundamental types, enumerated types & std::string_view
 common expensive to copy types : std::array, std::string, std::vector and std::ostream
 */

#include <iostream>

void pass_by_value(int x)
{
    std::cout << x << '\n';
}   /// x : destroyed here, temporary object

void expensive_copy(std::string x)
{
    std::cout << x << '\n';
}   /// x : destroyed here

/// std::string& x - lvalue reference to std::string
void pass_by_reference(std::string& x)
{
    std::cout << x << '\n';
}   /// x is destroyed here

/// x : is the copy of object x in the main()
void add_one(int x)
{
    /// this modifies the copy of argument passed, not the actual object x in main()
    ++x;
}

/// x : x is bound to the actual object x in main()
void add_one_reference(int& x)
{
    /// this will modify the actual object in main()
    ++x;
}

/// y : only accepts modifiable lvalues
void print_value(int& y)
{
    std::cout << y << '\n';
}

void print_value2(const int& y)
{
    std::cout << y << '\n';
}

/// a : passed by value
/// b : passed by reference
/// s : passed by const reference
void mix_ref(int a, int& b, const std::string& s)
{
    std::cout << ++a << '\n';
    std::cout << ++b << '\n';
    std::cout << s << '\n';
}

/// preprocessor function like macro : to provide either an object or a type name as a parameter
/// normal functions disallow this
#define is_small(T) (sizeof(T) <= 2 * sizeof(void*))
 
struct S
{
    double a, b, c;
};

int main()
{
    int x{22};
    
    /// x : passed by value into the function
    /// x : copied to parameter x of the function defined outside of main()
    /// x is fundamental type, so inexpensive to copy
    pass_by_value(x);
    
    std::string str{"Hello World!"};
    
    /// str : passed by value, expensive to copy into parameter (std::string x)
    /// std::string - is a class type
    expensive_copy(str);
    
    /// str : passed by reference into reference parameter std::string& x
    /// inexpensive
    /// parameter x is bound to str
    /// no copy of str is made
    /// x is an alias for the str
    /// x is accessing actual str and not the copy of str
    pass_by_reference(str);
    
    /// x : has not been modified in the function call to add_one(x)
    std::cout << x << '\n';
    add_one(x);
    std::cout << x << '\n';
    
    /// x : has been modified
    /// x : is not a copy here
    std::cout << x << '\n';
    add_one_reference(x);
    std::cout << x << '\n';
    
    int y{20};
    /// y is modifiable lvalue
    print_value(y);
    
    const int z{400};
    /// error : z is non modifiable lvalue
//    print_value(z);
    
    /// error, 200 : is an rvalue
//    print_value(200);
    
    /// x is a modifiable lvalue
    print_value(x);
    /// y is a modifiable lvalue
    print_value2(y);
    /// z is a non-modifiable lvalue
    print_value2(z);
    /// 231 is an rvalue
    print_value2(231);
    
    int a{2222};
    int b{3333};
    std::string s{"Hello"};
    
    mix_ref(a, b, s);
    
    std::cout << std::boolalpha;
    std::cout << is_small(int) << '\n';
    std::cout << is_small(double) << '\n';
    std::cout << is_small(float) << '\n';
    std::cout << is_small(long) << '\n';
    std::cout << is_small(S) << '\n';
    
    return 0;
}
