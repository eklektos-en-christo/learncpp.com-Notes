//
//  main.cpp
//  27.6_rethrowing.exceptions
//
//  Created by Εκλεκτός εν Χριστώ on 12/4/23.
//

/*
 Case: where we may be want to catch an exception but no want to fully handle it at the point where it is
 caught, if we want to log an error but pass the issue along to the caller to handle actually
 
 Only exceptions thrown within a try block are eligible to be caught, an exception thrown within a catch
 block will not be caught by the same catch block but will be propagated up the stack to the caller,
 exception thrown from the catch block can be of any type
 
 to re-throw an exception right way as the one that was just caught: simply use the throw keyword from
 within the catch block without specifying any object/variable, this method should be preferred when
 rethrowing the same exception
 
 
 RULE:
 When rethrowing the same exception, use the throw keyword by itself
 */

#include <iostream>

class Base
{
public:
    Base() {}
    virtual void print() { std::cout << "Base\n"; }
};

class Derived : public Base
{
public:
    Derived() {}
    void print() override { std::cout << "Derived\n"; }
};

int main()
{
    try
    {
        try
        {
            throw Derived{};
        }
        catch (Base& b)
        {
            std::cout << "Caught base b, which is actually a: ";
            b.print();
            /// rethrowing the same exception, note: no object is thrown
            /// this throw actually rethrows the same exact same exception that was just caught
            /// which means no copies were made, no object slicing happened
            throw;
            
            /// if we rethrow the object, the object will be sliced and only the Base portion will remain
            /// this proves that object was sliced when copied
            /*throw b;*/
        }
    }
    catch (Base& b)
    {
        std::cout << "Caught Base b, which is actually a: ";
        b.print();
    }
    
    return 0;
}
