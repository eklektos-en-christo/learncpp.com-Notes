//
//  main.cpp
//  13.4_access.functions.and.encapsulation
//
//  Created by Εκλεκτός εν Χριστώ on 7/5/23.
//

/*
 -------------------------------------------------------------------------------------------
 ENCAPSULATION/information hiding: keeping the details about how an object is implemented
 hidden away from the users of the object
 
 Users: access the object through a public interface
 
 Encapsulation in C++: is implemented via access specifiers
 
 Encapsulation: also used to refer to the packaging of data and functions that work on that
 data together
 
 Benefits of encapsulated classes:
 -easier to use and reduce the complexity of the programs
 -help protect the data and prevent misuse
 -easier to change
 -easier to debug
 
 -------------------------------------------------------------------------------------------
 EASIER TO USE AND REDUCE THE COMPLEXITY OF THE PROGRAMS:
 
 * only need to know what members functions are publicly available to use the class, what
   arguments they take, what values they return
 * this reduces complexity and also the mistakes
 * this is the key advantage of encapsulation
 * all C++ standard library classes are encapsulated
 
 -------------------------------------------------------------------------------------------
 HELP PROTECT THE DATA AND PREVENT MISUSE:
 
 * we can put validation checks in the public member functions that would check the user
   arguments before doing any modification to the private member variables
 * this protects the integrity of the program
 
 -------------------------------------------------------------------------------------------
 EASIER TO CHANGE:
 
 * gives us the ability to change how classes are implemented without breaking all of the
   programs that use them.
 * users won't even notice the changes that were made to the implementation
 
 -------------------------------------------------------------------------------------------
 EASIER TO DEBUG:
 
 * if everybody has to call the same public function to modify a value, then we can simply
   breakpoint that function and watch as each caller changes the value until we see where
   it goes wrong
 * if everyone is able to access the member variables directly, then it would be difficult
   to track down which piece of code modified the variable
 
 -------------------------------------------------------------------------------------------
 ACCESS FUNCTIONS: a short public function whose job is to retrieve or change the value of
 a private member variable
 
 Two flavors of access functions:
 - Getters/accessors : return the value of a private member variable
 - Setters/mutators  : that set the value of a private member variable
 
 Getters: should provide read-only access to the data, they should return by value or by
 const reference, not by non-const reference
 
 If getter return by non-const reference: this violates encapsulation and read-only nature
 of getters
 
 BEST PRACTICE:
 getters should return by value or by const reference
 
 - if nobody outside the class needs to access a member, don't provide access function
 - if someone outside the class needs to access a member, think about whether you can expose
   a behavior or action instead, if you can't, consider whether you can provide only a
   getter
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <iterator>

class Intarray
{
private:
    int m_array[10];
    
public:
    void set_value(int index, int value)
    {
        /// this validation check will ensure that users don't modify the data if index is invalid
        if (index < 0 || index >= std::size(m_array))
            return;
        
        m_array[index] = value;
    }
};

class Mystring
{
private:
    char* m_string;
    int m_length;
    
public:
    /// this is an access function, it returns the length of the string
    int get_length() { return m_length; }
};

class Date
{
private:
    int m_day {};
    int m_month {};
    int m_year {};
    
public:
    
    /// getter for the day
    int get_day() { return m_day; }
    /// setter for the day
    void set_day(int day) { m_day = day; }
    
    /// getter for the month
    int get_month() { return m_month; }
    /// setter for the month
    void set_month(int month) { m_month = month; }
    
    /// getter for the year
    int get_year() { return m_year; }
    /// setter for the year
    void set_year(int year) { m_year = year; }
};

class Foo
{
private:
    int m_value {};
    
public:
    /// this getter function returns by non-const reference
    /// the actual m_value can be modified by the caller
    /// violation of encapsulation
    int& get_value() { return m_value; };
};

int main()
{
    Foo f;
    /// caller modifying the actual private member variable
    /// violation of encapsulation
    f.get_value() = 5;
    
    std::cout << f.get_value() << '\n';
    
    return 0;
}
