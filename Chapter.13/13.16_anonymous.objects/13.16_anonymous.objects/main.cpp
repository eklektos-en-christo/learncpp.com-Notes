//
//  main.cpp
//  13.16_anonymous.objects
//
//  Created by Εκλεκτός εν Χριστώ on 7/17/23.
//

/*
 -------------------------------------------------------------------------------------------
 ANONYMOUS OBJECT: essentially a value that has no name
 
 Because anonymous objects have no name - there's no way to refer to them beyond the point
 where they are created
 
 Anonymous objects: have expression scope, they are created, evaluated & destroyed within
 a single expression
 
 -------------------------------------------------------------------------------------------
 ANONYMOUS CLASS OBJECTS:
 
 It is possible: to construct our own anonymous objects of class types as well
 
 To create anonymous class object:
 -simply omit the variable name as below
 
        Cents cents{ 10 };         /// this object has a name, not anonymous
        Cents{ 10 };               /// this object doesn't have a name, anonymous object
 
 code above creates an anonymous object, initialize it with value 10 then object destroyed
 
 -------------------------------------------------------------------------------------------
 SUMMARY:
 
 Use of anonymous objects: primarily used to pass or return values without having to create
 lots of temporary variables to do so
 
 Memory allocated dynamically: is also done so anonymously, the memory address should be
 stored in a pointer, otherwise there would be no way to refer to it.
 
 Anonymous objects: have expression scope, can only be used once unless they're bound to a
 constant l-value reference, which will extend the lifetime of the temporary object to match
 the lifetime of the reference
 
 If you need to reference a value in multiple expressions: a named variable should be used
 instead of an anonymous object
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>

int add(int x, int y)
{
    /// this is an anonymous object
    /// the result of x+y is placed in an anonymous object
    /// anonymous object holds and returns the result of x+y
    /// a copy of the anonymous object then returned to the caller by value
    /// then the object is destroyed
    return x + y;
}

void print_value(int value)
{
    std::cout << value << '\n';
}

class Cents
{
private:
    int m_cents {};
    
public:
    Cents(int cents) : m_cents{ cents } {}
    
    int get_cents() const { return m_cents; }
};

void print(const Cents& cents)
{
    std::cout << cents.get_cents() << " cents\n";
}

Cents add(const Cents& c1, const Cents& c2)
{
    /// the list initialization looks at function's return type and
    /// creates the correct object accordingly
    /// function return an anonymous Cents value
    /// no named variable sum is used
    return { c1.get_cents() + c2.get_cents() };
}

int main()
{
    std::cout << add(2, 2) << '\n';
    
    /// expression evaluated, placed in anonymous object
    /// copy of the object is then passed to the function
    /// then object is destroyed
    print_value(20 + 36);
    
    /// we are passing a named cents object to the function print()
    Cents cents{ 40 };
    print(cents);
    
    /// Now we are passing an anonymous Cents value to print()
    /// the object passed isn't a named object, it is anonymous
    /// the name of the object is omitted
    print(Cents{ 40 });
    
    Cents cents1{ 40 };
    Cents cents2{ 60 };
    Cents sum{ add(cents1, cents2) };
    /// used the named variable sum to print the value
    std::cout << "I've " << sum.get_cents() << " cents.\n";
    
    /// no longer used a named variable sum to print the value
    /// we are using the return value of the add function anonymously
    /// and calling the get_cents member function on the anonymous object returned by the add
    std::cout << "I've " << add(cents1, cents2).get_cents() << " cents.\n";
    
    /// anonymizing the cout statement further
    /// cents1 and cents2 are not used now, two anonymous objects are passed to the add function
    /// add function returns the anonymous object, then member function is called on the anonymous object
    /// returned by the add function
    std::cout << "I've " << add(Cents{ 40 }, Cents{ 60 }).get_cents() << " cents.\n";
    
    return 0;
}
