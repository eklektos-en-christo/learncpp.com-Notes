//
//  main.cpp
//  13.15_friend.functions.and.classes
//
//  Created by Εκλεκτός εν Χριστώ on 7/15/23.
//

/*
 -------------------------------------------------------------------------------------------
 FRIEND FUNCTIONS:
 
 friend function: a function that can access private members of a class as though it was a
 member of that class
 
 friend function: is just like a normal function
 
 friend function: maybe either a normal function or a member function of another class
 
 To declare a friend function:
 
 -simply use the friend keyword in front of the prototype of the function and it becomes a
 -friend of the class
 -it does not matter when the friend function is declared in the public or private section
 -of the class
 
 friend function: doesn't have a *this pointer
 
 -------------------------------------------------------------------------------------------
 MULTIPLE FRIENDS:
 
 A function can be a friend of more than one class at the same time.
 
 Classes: can be declared forward and defined later, they don't have return types or args
 
 Friend of multiple classes: can access the private data from all classes' objects
 
 -------------------------------------------------------------------------------------------
 FRIEND CLASSES:
 
 It is possible: to make an entire class a friend of another class, this gives all of the
 members of the friend class access to the private members of the other class
 
 Notes on friend classes:
 
 -friend class has no direct access to other class' *this pointer
 -because *this pointer is a function parameter of the other class' member functions
 -*this is not a member of other class
 
 -if one class is a friend of another class, this does not mean that the other class is also
 -a friend of the first class
 -both classes must be declared as a friend of each other in order to make them both friends
 
 -class A friend of B, B friend of C, this does not mean A is a friend of C
 
 -friend class statement also serves as a forward declaration for the class being friended
 
 ADVICE:
 limit the use of friend functions and classes to a minimum
 
 -------------------------------------------------------------------------------------------
 FRIEND MEMBER FUNCTIONS:
 
 A single member function: can also be made a friend
 
 This is same as making a normal friend function except using the name of the class member
 with classname:: prefix
 
 -------------------------------------------------------------------------------------------
 SUMMARY:
 
 friend function/class: can access the private members of another class as though it was a
 member of of that class
 
 This allows the friend function/class to work with other class intimately, with making the
 other class expose its private members e.g. via access functions
 
 Friending: commonly used when defining overloaded operators
 
 NOTE: making a specific member function a friend requires the full definition for the class
 of the member function to have been seen first
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>
#include "Point3d.hpp"
#include "Vector3d.hpp"



class Accumulator
{
private:
    int m_value{ 0 };
    
public:
    void add(int value) { m_value += value; }
    int get_value() { return m_value; }
    
    /// using keyword "friend" in front of the function prototype
    /// this function is friend of this class
    /// it can access all private members
    friend void reset(Accumulator& accumulator);
};

/// friend of the Accumulator class - defining
/// this is a normal function but can access the class's private members
/// because class has declared it as a friend
void reset(Accumulator& accumulator)
{
    /// it can access the private data of Accumulator objects
    accumulator.m_value = 0;
}
/*----------------------------------------------------------------------------------------*/



class Value
{
private:
    int m_value {};
    
public:
    Value(int value) : m_value{ value } {}
    
    /// friend of this class
    friend bool is_equal(const Value& v1, const Value& v2);
};

bool is_equal(const Value& v1, const Value& v2)
{
    return (v1.m_value == v2.m_value);
}
/*----------------------------------------------------------------------------------------*/



/// telling the compiler that there will be a class Humidity
/// declaring it to use as a parameter inside the Temperature class
class Humidity;

class Temperature
{
private:
    int m_temp {};
    
public:
    Temperature(int temp = 0) : m_temp{ temp } {}
    
    /// Humidity is being used as a parameter to friend function, so forward declaration was necessary
    /// this function is a friend of this class
    friend void print_weather(const Temperature& temp, const Humidity& humidity);
};

class Humidity
{
private:
    int m_humidity {};
    
public:
    Humidity(int humidity = 0) : m_humidity{ humidity } {}
    
    /// the same function is also a friend of the Temperature class
    friend void print_weather(const Temperature& temp, const Humidity& humidity);
};

void print_weather(const Temperature& temp, const Humidity& humidity)
{
    std::cout << "Temperature: " << temp.m_temp << '\n';
    std::cout << "Humidity:    " << humidity.m_humidity << '\n';
}
/*----------------------------------------------------------------------------------------*/



class Storage
{
private:
    int m_nvalue {};
    double m_dvalue {};
    
public:
    Storage(int nvalue, double dvalue) : m_nvalue{ nvalue }, m_dvalue{ dvalue } {}
    
    /// making the display class a friend of storage
    /// this statement also serves as a forward declaration for Display
    friend class Display;
};

class Display
{
private:
    bool m_display_int_first {};
    
public:
    Display(bool display_int_first) : m_display_int_first{ display_int_first } {}
    
    /// display members that use a storage class object can access the private members of storage directly
    void display_item(const Storage& storage)
    {
        if (m_display_int_first)
            std::cout << storage.m_nvalue << ' ' << storage.m_dvalue << '\n';
        else
            std::cout << storage.m_dvalue << ' ' << storage.m_nvalue << '\n';
    }
};
/*----------------------------------------------------------------------------------------*/



/// forward declaration for storage2, because Display2 using the Storage2 as a reference parameter
class Storage2;

class Display2
{
private:
    bool m_display_int_first {};
    
public:
    Display2(bool display_int_first) : m_display_int_first{ display_int_first } {}
    
    /// Storage2 is used here, so forward declaration provided above the Display2 class
    void display_item(const Storage2& storage);
};

class Storage2
{
private:
    int m_nvalue {};
    double m_dvalue {};
    
public:
    Storage2(int nvalue, double dvalue) : m_nvalue{ nvalue }, m_dvalue{ dvalue } {}
    
    /// making the Display2 member function as a friend of class Storage2
    friend void Display2::display_item(const Storage2& storage);
};

/// defining the member function below the storage2 class
/// because storage2 is the parameter, so member function needs to see the full definition of storage2 class
void Display2::display_item(const Storage2& storage)
{
    if (m_display_int_first)
        std::cout << storage.m_nvalue << ' ' << storage.m_dvalue << '\n';
    else
        std::cout << storage.m_dvalue << ' ' << storage.m_nvalue << '\n';
}
/*----------------------------------------------------------------------------------------*/



int main()
{
    Accumulator accu {};
    accu.add(2);
    std::cout << accu.get_value() << '\n';
    reset(accu);
    std::cout << accu.get_value() << '\n';
    
    Value v1{ 10 };
    Value v2{ 20 };
    std::cout << std::boolalpha << is_equal(v1, v2) << '\n';
    
    Humidity hum { 10 };
    Temperature temp{ 40 };
    print_weather(temp, hum);
    
    Storage storage { 21, 40.8 };
    Display display { false };
    display.display_item(storage);
    
    Storage2 storage2 { 23, 18.2 };
    Display2 display2 { false };
    display2.display_item(storage2);
    
    Point3d p{1.0, 2.0, 3.0};
    Vector3d v{2.0, 2.0, -3.0};

    p.print();
    v.print();
    p.move_by_vector(v);
    p.print();
    
    return 0;
}
