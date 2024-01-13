//
//  main.cpp
//  9.13_summary.and.quiz
//
//  Created by Εκλεκτός εν Χριστώ on 3/4/23.
//

/*
 SUMMARY:
 
 Compound/composite data types - data types that can be constructed from fundamental types
 or other compound data types
 
 Value category of an expression - indicates whether an expression resolves to a value, a
 function, or an object of some kind
 
 Lvalue - expression that evaluates to a function or an object that has an identity
 
 An object or function with an identity - has an identifier or an identifiable memory
 address
 
 Lvalue subtypes:
 -modifiable lvalues : that can be modified
 -non-modifiable lvalues : that can't be modified, typically because or their constness
 
 Rvalue - expression that is not an lvalue, includes literals(except string literals) and
 return values of functions or operators when returned by value
 
 Reference - is an alias/second name for an existing object, any operation on a defined
 reference is applied to the object being referenced
 
 Two types of references in C++:
 -lvalue references : commonly called a reference, acts as an alias for an existing lvalue
 (such as a variable)
 -rvalue references
 
 Lvalue reference variable - variable that acts as a reference to an lvalue, usually another
 variable
 
 A reference when initialized with an object - we say it is bound to that object/function
 
 Referent - the object being referenced
 
 Lvalue references - can't be bound to non-modifiable lvalues or rvalues, otherwise there
 would be a violation of their constness
 
 Lvalue references - occasionally called lvalue references to non-const, sometimes non-const
 reference
 
 A reference in C++ when once initialized - can't be reseated/changed to reference another
 object
 
 Dangling reference - when the object being referenced is destroyed before a reference to it
 the reference is left referencing an object that no longer exists
 
 Accessing a dangling reference - leads to undefined behavior
 
 const - keyword, when used to declare an lvalue reference, we tell an lvalue reference to
 treat the object it is referencing as const
 
 Lvalue reference to a const value/reference to const/const reference - when lvalue
 reference is declared with a const keyword
 
 Const references - can bind to non-modifiable lvalues, modifiable lvalues and rvalues
 
 Temporary object/unnamed object/anonymous object - an object that is created for temporary
 use and then destroyed within a single expression
 
 Pass by reference - we declare a function parameter as a reference/const reference rather
 than a normal variable, when that function is called, each reference parameter is bound to
 the appropriate argument, in this binding process, no copy of the argument is made
 
 The address-of (&) operator - returns the memory address of its operand
 
 The dereference (*) operator - returns the value at a given memory address as an lvalue
 
 Pointer - an object that holds a memory address typically of another another variable as
 its value, so we can use that address later
 
 Pointers - not initialized by default
 
 Wild pointer - pointer that has not been initialized
 
 Dangling pointer - that is holding an address of an object that in no longer valid/exists
 
 Besides a memory address - there is only one another value that a pointer can hold : null
 
 Null value/null - special value that means something has no value
 
 When a pointer holds the null value - it means pointer is not pointing at anything
 
 Null pointer - pointer that holds a null value
 
 nullptr - null pointer literal, we can use nullptr to explicitly initialize/assign a
 pointer a null value
 
 A pointer should - either hold the address of a valid object or be set to nullptr, that way
 we only need to test pointers for null and can assume any non-null pointer is valid
 
 Pointer to a const value/pointer to const - non-const pointer that points to a constant
 value
 
 const pointer - a pointer whose address can't be changed after initialization
 
 const pointer to a const value - can't have its address changed, nor can the value it is
 pointing to be changed through the pointer
 
 Pass by address - the caller provides an object's address via a pointer, the address in
 that pointer is copied into a pointer parameter of the called function, which also now
 holding the address of the object, function can dereference the parameter pointer to access
 the object whose address was passed
 
 Return by reference - returns a reference that is bound to the object being returned, this
 avoids making a copy of the return value
 
 Object being referenced - must outlive the function returning the reference
 
 Use of a dangling reference - result in undefined behavior
 
 If a parameter is passed into a function by reference - it's safe to return that parameter
 by reference
 
 If a function returns a reference and that reference is used to initialize/assign to a non
 reference variable - the return value will be copied as if it had been returned by value
 
 Type deduction for variables via the auto keyword - will drop any reference or top-level
 const qualifiers from the deduced type, these can be reapplied as part of the variable
 declaration if desired
 
 Return by address - works almost identically to return by reference except a pointer to an
 object is returned instead of a reference to an object
 */
