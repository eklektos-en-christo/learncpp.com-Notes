//
//  main.cpp
//  9.3_lvalue.references
//
//  Created by εκλεγμένοι εν Χριστώ on 2/20/23.
//

/*
 Reference in CPP : an alias/another name for an existing object
 
 Once reference is defined : any operation on it is applied to the object being referenced
 
 Reference = identical to the object being referenced
 
 We can use a reference : to read or modify the object being referenced
 
 references : are used everywhere in CPP
 
 we can also create references : to functions
 
 Two types of references in modern CPP : lvalue reference & rvalue references
 
 ___________________________
 lvalue reference types:
 lvalue reference/reference : acts as an alias for an existing lvalue, such as a variable
 
 to declare an lvalue reference type : we use & ampersand in the type declaration-
 int        >   a normal int type
 int&       >   an lvalue reference to an int object/variable
 double&    >   an lvalue reference to a double object
 
 ___________________________
 lvalue reference variables:
 variable that acts as a reference to an lvalue(another variable)
 -to create an lvalue reference variable : simply define a variable with an lvalue reference
 type
 
 best practice:
 when defining a reference, place the & next to the type, not the reference variable's name
 reference : is part of the type information, not the identifier
 
 Modifying values through an lvalue reference:
 we can also use the reference to modify the object being referenced
 
 Initialization of lvalue references:
 as with the constants, all references must be initialized
 
 bound : when reference is initialized with an object/function, we say it is bound to that
 object/function
 
 reference binding : the process of binding a reference to an object/function
 
 referent : the object/function being referenced
 
 lvalue references : must be bound to modifiable lvalues, can't be bound to non-modifiable
 lvalues or rvalues, otherwise through the reference, their const-ness would be changed
 
 lvalue references to non-const : lvalue references are occasionally called
 non-const reference : lvalue references are occasionally called
 
 type of the reference : must match the type of the referent(some exceptions are there)
 
 lvalue references to void : disallowed
 
 References : can't be reseated/changed to refer to another object
 
 when a reference is evaluated in an expression : it resolves to the object it is
 referencing
 
 lvalue reference's scope and duration : reference variables follow the same scoping and
 duration rules that normal variables do
 
 References and referents : have independent lifetimes
 -a reference can be destroyed before the object it is referencing
 -object being referenced can be destroyed before the reference
 
 when a reference is destroyed before the referent : referent/object is not impacted
 
 Dangling references : when object being referenced is destroyed before the reference to it
 is destroyed, the reference is left referencing an object that no longer exists
 
 Accessing a dangling reference : leads to undefined behavior
 
 ___________________________
 References : are not objects
 Reference : not required to exist or occupy storage
 References : can't be used anywhere an object is required
 reference to reference : can't have that, lvalue reference must reference an identifiable
 object
 
 cases : where reference is needed that is an object, a reference that can be reseated -
 std::reference_wrapper provides a solution there
 
 int&& : reference to a reference, doesn't supported in cpp, but repurposed in cpp11 to
 indicate an rvalue reference
 */

#include <iostream>

int main()
{
    /// normal integer variable
    int x1{2};
    
    /// ref_to_x1 : lvalue reference variable
    /// ref_to_x1 : can be used an an alias for variable x
    /// & in this context : doesn't mean "address of", it means "lvalue reference to"
    /// ref_to_x1 is bound to x1
    /// referent : x1
    int& ref_to_x1{x1};
    
    std::cout << x1 << '\n';
    std::cout << ref_to_x1 << '\n';
    
    /// using reference to x to change the value of x
    ++ref_to_x1;
    std::cout << x1 << ref_to_x1 << '\n';
    
    ++x1;
    std::cout << x1 << ref_to_x1 << '\n';
    
    /// error : reference declaration requires an initializer
//    int& invalid_ref;
    
    int x2{70};
    
    /// lvalue reference modif_ref : bound to a modifiable lvalue - x2
    int& modif_ref{x2};
    
    const int y2{22};
    
    /// can't bind to a non-modifiable lvalue : y2
//    int& invalid_ref2{y2};
    
    /// can't bind to an rvalue, 2 is temporary
//    int& invalid_ref3{2};
    
    int x3{21};
    
    /// reference to float cannot bind to int variable
//    float& float_ref_to_int{x3};
    
    /// reference to double cannot bind to int variable
//    double& double_ref_to_int{x3};
    
    int x4{99};
    int y4{40};
    
    int& ref_x4{x4};
    
    /// this won't change ref_x4 into a reference to y4
    /// this will assign the y4 to x4
    /// ref_x4 refers to x4 and not y4
    ref_x4 = y4;
    
    std::cout << x4 << ' ' << y4 << '\n';
    
    int x5{33};
    
    {
        int& ref_x5{x5};
        std::cout << ref_x5 << '\n';
    }   /// ref_x5 : destroyed here, x5 doesn't know this
    
    /// x5 is not impacted
    std::cout << x5 << '\n';
    
    int var1{2222};
    
    /// ref1 : reference to var1
    int& ref1{var1};
    
    /// ref2 : not a reference to ref1
    /// ref1 : evaluates to var1 - remember
    /// ref2 : normal lvalue reference bound to var1
    int& ref2{ref1};
    
    std::cout << ref1 << ' ' << ref2 << '\n';
    
    /// rvalue reference - interesting
    int&& reff{2200};
    std::cout << reff << '\n';
    
    return 0;
}   /// x4 and ref_x4 die here : same scope and duration
