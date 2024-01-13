//
//  main.cpp
//  14.11_overloading.typecasts
//
//  Created by Εκλεκτός εν Χριστώ on 7/26/23.
//

/*
 -------------------------------------------------------------------------------------------
 USER-DEFINED CONVERSIONS: allow us to convert the class type into another data type
 
 THREE THINGS TO NOTE:
 
 -to overload a function that casts our class to an int, we write a new function in our
 class called operator int(), note the space between the operator and the int(),  such
 functions must be non-static members
 
 -user-defined conversion don't have parameters, no way to pass arguments explicitly to them
 they do have a hidden *this pointer, pointing to the implicit object(which is the object to
 be converted)
 
 -user-defined conversions don't declare a return type, the name of the conversion is used
 as a return type as it is the only return type allowed, conversion functions don't have
 return type, this prevents redundancy
 
 You can provide user-defined conversions for any data type, including your own program-
 defined data types
 
 -------------------------------------------------------------------------------------------
 CONVERTING CONSTRUCTORS vs. OVERLOADED TYPECASTS:
 
 They both perform similar roles-
 
 Overloaded typecast: allows us to define a function that converts some program-defined type
 A into other type B
 
 Converting constructor: allows us to define a function that creates some program-defined
 type A from some other type B
 
 Converting constructor should be preferred to an overloaded typecast, as it allows the
 type being constructed to own the construction
 
 FEW CASES WHERE AN OVERLOADED TYPECAST SHOULD BE USED INSTEAD OF CONVERTING CONSTRUCTORS:
 
 -when providing a conversion to a fundamental type because we can't define constructors for
 fundamental types, these are used to provide a conversion to bool where it makes sense to
 be able to use an object in a conditional statement, so object is converted to bool there
 
 -when providing a conversion to a type you can't add members to, like a conversion to
 std::vector, because we can't provide constructors for these types either
 
 -when you dont want the type being constructed to be aware of the type being converted to,
 this can be helpful avoiding circular dependencies, example std::string provides an
 overloaded typecast to std::string_view so that std::string_view doesn't have to #include
 <string> header
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>

class Cents
{
private:
    int m_cents{};
    
public:
    Cents(int cents=0) : m_cents{ cents } {}
    
    int get_cents() const { return m_cents; }
    void set_cents(int cents) { m_cents = cents; }
    
    /// conversion operator
    /// overloading the int cast
    operator int() const { return m_cents; }
};



class Dollars
{
private:
    int m_dollars{};
    
public:
    Dollars(int dollars=0) : m_dollars{ dollars } {}
    
    /// convert the dollars into cents
    /// convert the dollars into program-defined data type Cents
    operator Cents() const { return Cents{m_dollars * 100}; }
};



void print_int(int value)
{
    std::cout << value << '\n';
}

void print_cents(Cents cents)
{
    /// cents will be implicitly converted to an int here
    std::cout << cents;
}

int main()
{
    Cents cents1{ 10 };
    print_int(cents1.get_cents());
    
    /// print_int take an int, we provided cents1
    /// compiler will look for a way to convert a Cents into an int
    /// it will call operator int() function which will return an int
    /// that int will be passed to the print_int function
    print_int(cents1);
    
    /// works because of operator int()
    /// explicitly casting our Cents into an int
    Cents cents2{ 11 };
    int c{ static_cast<int>(cents2) };
    
    Dollars dollars{ 10 };
    /// dollars will be implicitly casted to a Cents here
    /// dollars to Cents and Cents to an int
    print_cents(dollars);
    
    std::cout << " cents\n";
    
    return 0;
}
