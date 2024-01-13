//
//  main.cpp
//  9.4_lvalue.references.to.const
//
//  Created by εκλεγμένοι εν Χριστώ on 2/21/23.
//

/*
 lvalue reference : can only bind to a modifiable lvalue
 
 lvalue reference to const/reference to const/const reference : we tell an lvalue reference
 to treat the object it is referencing as const, it is done by using the const keyword when
 declaring an lvalue reference
 
 lvalue reference to const : can bind to a non-modifiable(const) lvalue
 
 lvalue references to const : treat the object they referencing as const, they can access
 the object/value but can't modify it
 
 Initializing an lvalue reference to const with a modifiable value:
 lvalue references to const - can also bind to modifiable lvalues, in this case the object
 that is being referenced is treated as const object when accessed through the reference
 even though the underlying object is non-const/modifiable
 
 best practice :
 favor lvalue references to const over lvalue references to non-const unless there is a need
 to modify the object being referenced
 
 Initializing an lvalue reference to const with an rvalue:
 lvalue references to const : can also bind to rvalues
 -when this happens : a temporary object is created an initialized with the rvalue,
 and reference to const is bound to that temporary object
 
 Temporary object/anonymous object : that is created for temporary use and then destroyed
 within a single expression
 Temporary objects : have no scope at all
 Identifier : has a scope
 Temporary objects : don't have an identifier
 Temporary objects : can only be used directly at the point where they are created, we
 can't refer to it beyond that point
 
 Const reference bound to temporary objects extend the lifetime of the temporary objects:
 temp. objects : destroyed at the end of the expression, but -
 when a const lvalue reference is bound to a temporary object, the lifetime of the temporary
 object is extended to match the lifetime of the reference, this is done to avoid dangling
 references
 
 Key insight:
 -lvalue references : can only bind to modifiable lvalues
 -lvalue references to const : can bind to modifiable lvalues, non-modifiable lvalue &
 rvalues, this makes lvalue references to const a much more flexible type of references
 */

#include <iostream>

int main()
{
    const int x{2};
    
    /// error : can't bind lvalue reference to a non-modifiable const lvalue
    /// this is a non-const reference, can modify the variable x, but x is const
//    int& ref_x{x};
    
    /// x is non modifiable/const
    /// const reference const_ref_x is an lvalue reference to the const x
    const int& const_ref_x{x};
    
    /// Okay: const reference to const object can access the value
    std::cout << const_ref_x << '\n';
    
    /// error : const reference to const object can access(read) but can't modify the object
//    ++const_ref_x;
    
    /// x2 : modifiable lvalue
    int x2{400};
    
    /// const reference const_ref_x2 : bind to a non-const/modifiable lvalue
    const int& const_ref_x2{x2};
    
    /// const reference can access the object but can't modify
//    ++const_ref_x2;
    
    /// modifiable x2 : original identifier can modify the value
    ++x2;
    
    std::cout << const_ref_x2 << ' ' << x2 << '\n';
    
    /// lvalue reference to const const_ref: can bind to rvalue 5
    /// 5 is temporary object, have no identifier, have no scope at all
    /// can't refer to 5 beyond the point of creation, it doesn't persist because it has no identifier
    ///
    /// const_ref : would be left dangling if the rvalue object 5 had been destroyed, and we'd get undefined behavior
    /// when we tried to access const_ref
    /// But –––––– lifetime of the rvalue 5 temporary object is extended to match the lifetime of the cons_ref reference
    const int& const_ref{5};
    
    /// const_ref is bound to temporary object 5
    /// lifetime of temporary object matches the lifetime of the const_ref
    /// so we can easily print the const_ref in this statement
    std::cout << const_ref << '\n';
    
    return 0;
}   /// const_ref and temp. object 5 go out of scope here
