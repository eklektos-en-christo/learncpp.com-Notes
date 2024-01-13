//
//  main.cpp
//  10.9_member.selection.with.pointers.and.references
//
//  Created by Εκλεκτός εν Χριστώ on 3/11/23.
//

/*
 member selection operator (.) - to select a member from a struct object
 
 references to an object - act like the object itself, we can also use the member selection
 operator (.) to select a member from a reference to a struct
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 member selection for pointers to structs -
 member selection operator (.) - doesn't work if you have a pointer to a struct,
 
 pointers hold addresses - we first need to dereference the pointer to get the object before
 we can do anything with it, this is a bit ugly
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 member selection from pointer operator(->)/arrow operator - can be used to select members
 from a pointer to an object
 
 -> operator - works identically to the (.) but does an implicit dereference to the pointer
 object before selecting the member
 
 arrow operator -> : must less prone to error and easier to type, indirection is simply done
 implicitly, so there are no precedence issues to worry about
 
 best practice : when using a pointer to access the value of a member, use the member
 selection from pointer operator(->) instead of member selection operator (.)
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Mixing pointer and non-pointers to members:
 
 member selection operator - always applied to the currently selected variable
 
 mix of pointers and normal variables - you can see member selections where . and -> are
 both used in sequence, see the out statement at the end in main()
 */

#include <iostream>

struct Employee
{
    int id{};
    int age{};
    double wage{};
};

/// in this function:
/// e - reference to struct object emp1 in main
/// e - acts as the emp1 object itself
/// member selection operator - used to select member from reference to struct
void print_employee(const Employee& e)
{
    std::cout << "Age: " << e.age << '\n';
    std::cout << "ID: " << e.id << '\n';
    std::cout << "Wage: $" << e.wage << '\n';
}

struct Paw
{
    int claws{};
};

struct Animal
{
    std::string name{};
    Paw paw{};
};

int main()
{
    Employee emp1{1, 44, 20000.0};
    
    print_employee(emp1);
    
    Employee* ptr{&emp1};
    
    /// error : member selection operator (.) doesn't work with pointers
//    std::cout << ptr.id << '\n';
    
    /// first dereference the pointer, then use member selection operator(.) to select the members
    /// this is a bit ugly
    /// parenthesized the *ptr - so it will take precedence over the member selection operator
    std::cout << (*ptr).id << '\n';
    
    /// better than the previous one
    /// member selection from pointer operator (->) used to select the members
    std::cout << ptr->id << '\n';
    
    Animal lion{"Lion", {5}};
    
    Animal* ptr1{&lion};
    
    /// ptr1 - pointer to Animal
    /// ->  used - to access the paw
    /// . used - to access the claws, paw in not a pointer that's why (.) used
    /// parentheses - not necessary, used for readability
    /// -> and . : evaluated in left to right order
    std::cout << (ptr1->paw).claws << '\n';
    
    std::cout << ptr1->name << '\n';
    
    return 0;
}
