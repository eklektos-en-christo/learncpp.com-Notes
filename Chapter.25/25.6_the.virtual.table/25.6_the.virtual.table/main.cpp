//
//  main.cpp
//  25.6_the.virtual.table
//
//  Created by Εκλεκτός εν Χριστώ on 11/3/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 VIRTUAL TABLE: a form of late binding used by the C++ to implement virtual functions
 
 VIRTUAL TABLE: is a lookup table of functions, used to resolve functions calls in a dynamic/late binding
 manner
 
 Other names: vtable/virtual function table/virtual method table/dispatch table
 
 Every class that uses virtual functions or is derived from a class that uses virtual functions is given
 its own virtual table
 
 The table is simply a static array that the compiler sets up at compile time
 
 A virtual table contains one entry for each virtual function that can be called by object of the class
 
 Each entry in the table is simply a function pointer that points to the most-derived function accessible by
 that class
 
 The compiler also adds a hidden pointer that is a member of the base class which we call *__vptr
 
 *__vptr is set automatically when a class object is created so that it points to the virtual table for that
 class
 
 *__vptr is a real pointer member, it makes each class object allocated bigger by the size of one pointer
 
 *__vptr is inherited by the derived classes also
 
 When a class object is created, *__vptr is set to point to the virtual table for that class
 
 How the virtual tables are filled out?
 
 Suppose: there are only two virtual functions in the Base, each virtual table will have two entries, one
 for func1 and one for func2. When these virtual tables are filled out, each entry is filled out with the
 most-derived function an object of that class type can call
 
 Any class that uses virtual functions has a *__vptr and thus each object of that class will be bigger by
 one pointer
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>

/*--------------------------------------------------------------------------------------------------------*/
/// compiler will set 3 virtual table, one for each class
/// compiler also adds a hidden pointer member to the most base class that used virtual functions
class Base
{
public:
    /// this way the compiler adds a hidden pointer to the most base class that uses virtual functions
    /// __vptr is inherited by D1 and D2
    /*VirtualTable* __vptr;*/
    virtual void func1() {}
    virtual void func2() {}
};

class D1: public Base
{
public:
    void func1() override {}
};

class D2: public Base
{
public:
    void func2() override {}
};
/*--------------------------------------------------------------------------------------------------------*/

int main()
{
    /// object of Base type is created, hidden pointer *__vptr is set to point to the virtual table for Base
    /// Virtual table for Base objects is simple:
    /// Base can only access its own members, it cannot access the D1 and D2 member functions
    /// the first entry points to the func1 of Base and 2nd entry points to the func2 of Base
    Base b{};
    
    /// object of D1 type is created, hidden pointer *__vptr is set to point to the virtual table for D1
    /// D1 can access both Base and its own members, but D1 has overridden the func1 of Base
    /// so D1::func1 is more derived now than Base::func1, the first entry points to the D1::func1
    /// D1 hasn't overridden func2 of Base, so 2nd entry points to the Base::func2
    D1 d1{};
    
    /// object of D2 type is created, hidden pointer *__vptr is set to point to the virtual table for D2
    /// Similar to the D1 excepts the entry for func1 points to Base::func1 and entry for func2 points
    /// to the D2::func2
    D2 d2{};
    
    /// d_ptr is a base pointer, it only points to the base portion of D1
    /// *__vptr is in the base portion of the class
    /// so d_ptr has access to this pointer
    /// d_ptr->__vptr points to the D1 virtual table
    /// d_ptr is of type Base*, it still has access to D1's virtual table through __vptr
    Base* d_ptr{ &d1 };
    d_ptr->func1();
    
    /// b.__vptr points to the Base's virtual table, not D1's virtual table
    /// b_ptr->__vptr points to the Base's virtual table as well
    /// Base's virtual table entry for func1 points to Base::func1
    /// thus b_ptr->func1 resolves to Base::func1, which is the most derived
    /// version of func1 that a Base object should be able to call
    Base* b_ptr{ &b };
    b_ptr->func1();
    
    return 0;
}
