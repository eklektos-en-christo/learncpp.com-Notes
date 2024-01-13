//
//  main.cpp
//  13.12_const.class.objects.and.member.functions
//
//  Created by Εκλεκτός εν Χριστώ on 7/12/23.
//

/*
 Fundamental data types: can be made const via the const keyword
 
 All const variables: must be initialized at the time of creation
 
 In case of const fundamental types: initialization can be done through copy, direct and
 uniform initialization
 
 -------------------------------------------------------------------------------------------
 CONST CLASSES:
 
 Instantiated class objects: can also me made const by using the const keyword
 
 Initialization of const class objects: is done via class constructor
 
 Once the const class object has been initialized via constructor: any attempt to modify
 the member variables is disallowed, this includes both changing the member variables
 directly if they are public and calling member functions that set the value of member
 variables
 
 Const class objects: use them when there is a need to ensure that objects aren't modified
 after creation
 
 -------------------------------------------------------------------------------------------
 CONST MEMBER FUNCTIONS:
 
 const member function: member function that guarantees it will not modify the object or
 call any non-const member function(because they may modify the object)
 
 Const class objects: can only explicitly call const member functions
 
 To make a member function const: simply append the const keyword to the function prototype,
 after the parameter list and before the function body as shown below:
 
                                    _____
                    int get_value() const { return m_value; }
 
 Member functions defined outside of the class definition: must use const keyword on both
 the function prototype in the class definition and on the function definition
 
 Const member function: that attempts to change a member variable or call a non-const
 member function will cause compiler error to occur
 
 Constructors: cannot be marked as const, because const constructor won't be able to
 initialize the member variables
 
 Const member functions: can also be called by non-const objects
 
 BEST PRACTICE:
 
 Any member function that doesn't modify the state of the class object const: mark it as
 const, so that it can be called by the const objects
 
 -------------------------------------------------------------------------------------------
 CONST OBJECTS VIA PASS BY CONST REFERENCE:
 
 One way to create const objects: by instantiating them
 
 A more common way to get a const object: by passing an object to a function by const
 reference
 
 Passing a class argument by value: causes a copy of the class to be made(slower)
 
 Passing a class argument by reference: avoids the needless copy
 
 const reference: to ensure the function doesn't inadvertently change the argument
 
 const reference: to allow the function to work with R-values
 
 R-values: can't be passed as non-const references, but can be passed as const references
 
 -------------------------------------------------------------------------------------------
 CONST MEMBERS CAN NOT RETURN NON-CONST REFERENCES TO MEMBERS:
 
 When a member function is const: the hidden *this pointer is a const pointer to const
 
 When a member function const: all the members are treated as const within that function
 
 Const member function: cannot return a non-const reference to a member because that would
 allow the caller to have non-const access to that const member
 
 Const member functions: can return const references to members
 
 -------------------------------------------------------------------------------------------
 OVERLOADING CONST AND NON-CONST FUNCTION: typically done when return value needs to differ
 in constness
 
 It is possible: to overload a function in such a way to have a const and non-const version
 of the same function
 
 Const qualifier: is considered part of the function's signature, two functions differ in
 their const-ness are considered distinct
 
 non const version: only work with non-const objects
 it is more flexible : we can use it to both read and write
 
 const version: works with const and non-const objects, but returns a const reference to
 prevent the modification of const object
 
 -------------------------------------------------------------------------------------------
 SUMMARY:
 
 Passing objects by const reference: is common
 
 Classes should be: const friendly
 
 Make member functions const: those don't modify the state of the class object
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>

class Something
{
public:
    int m_value {};
    
    Something() : m_value{ 0 } {}
    
    void set_value(int value) { m_value = value; }
    
    /// get_value is a const member function
    /// it can only be called on const class objects
    int get_value() const { return m_value; }
    
    /// error: const member function cannot change the member variable
    /// also it cannot call a non-const member function
    /*void increment() const {test(); ++m_value; }
    void test(){return;}*/
};

class Date
{
private:
    int m_day {};
    int m_month {};
    int m_year {};
    
public:
    Date(int day, int month, int year)
    {
        set_date(day, month, year);
    }
    
    void set_date(int day, int month, int year)
    {
        m_day = day;
        m_month = month;
        m_year = year;
    }
    
    /// all these getters are const, to make them callable via const class object
    /// because non-const members functions can't be called on const objects
    int get_day() const { return m_day; }
    int get_month() const { return m_month; }
    int get_year() const { return m_year; }
};

/// passing the object via const reference
/// no copy is made of the object
/// const prevents the object to be modified
void print_date(const Date& date)
{
    std::cout << date.get_day() << '/';
    std::cout << date.get_month() << '/';
    std::cout << date.get_year() << '\n';
}

/// overloading a const and non-const member functions
class Overload_Const
{
private:
    std::string m_value {};
    
public:
    Overload_Const(const std::string& value = "") : m_value{ value } {}
    
    /// overloaded access function for const objects
    /// it returns the const reference
    const std::string& get_value() const
    {
        std::cout << "Const version called!\n";
        return m_value;
    }
    
    /// overloaded access function for non-const objects
    /// it returns non-const reference
    std::string& get_value()
    {
        std::cout << "Non-const version called!\n";
        return m_value;
    }
};

int main()
{
    /// create a const class object
    const Something s1 {};
    
    /// attempt to change the public member variable directly : error, const object
    /*s1.m_value = 1;*/
    
    /// attempt to change the public member via member function : error, const object
    /*s1.set_value(2);*/
    
    /// working: const class object can call a const member function
    std::cout << s1.get_value() << '\n';
    
    Something s2 {};
    
    /// const member function get_value : can also be called by the non-const s2 object
    std::cout << s2.get_value() << '\n';
    
    Overload_Const over1 { "YELLO" };
    /// non const version only work with non-const objects
    /// it is more flexible : we can use it to both read and write
    over1.get_value() = "LELLO";
    
    /// non-const version of the function is called
    std::cout << over1.get_value() << '\n';
    
    /// const version of the function is called
    const Overload_Const over2 { "KELLO" };
    std::cout << over2.get_value() << '\n';
    
    return 0;
}
