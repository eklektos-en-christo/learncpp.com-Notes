//
//  main.cpp
//  13.3_public.vs.private.access.specifiers
//
//  Created by Εκλεκτός εν Χριστώ on 7/4/23.
//

/*
 -------------------------------------------------------------------------------------------
 PUBLIC MEMBERS: members of a struct/class that can be accessed directly by anyone, code
 ---------------
 outside the class/struct can directly access the public members.
 
 The public: the code outside the struct/class
 
 Class members: are private by default
 
 struct members: are public by default
 
 -------------------------------------------------------------------------------------------
 PRIVATE MEMBERS: members of a class that can't be accessed by the public
 ----------------
 
 PRIVATE MEMBERS: can only be accessed by the other members of the class or by the friends
 of the class
 
 -------------------------------------------------------------------------------------------
 ACCESS SPECIFIERS: determine who has access to the members that follow the specifier
 ------------------
 each of the members acquires the access level of the previous access specifier, if none is
 provided, then default access specifier.
 
 Types of access specifiers: public, private & protected
 
 public: make the members public
 
 private: make the members private
 
 protected: works much like private
 
 -------------------------------------------------------------------------------------------
 MIXING ACCESS SPECIFIERS: there is no limit to the number of access specifiers you can use
 -------------------------
 in a class.
 
 Member variables: usually made private
 
 Member functions: usually made public
 
 BEST PRACTICE:
 make member variables private and member functions public
 
 Public interface: group of public members of a class are often referred to, public
 interface defines how programs using the class will interact with the class.
 
 -------------------------------------------------------------------------------------------
 ACCESS CONTROLS: work on a per-class basis, not a per-object basis
 
 When a function has access to the private members of a class: it can access the private
 members of any object of that class type that it can see
 
 this is useful when we need to copy members from one object to another object of the same
 class
 
 -------------------------------------------------------------------------------------------
 Structs vs Classes
 
 Class: defaults its members to private
 
 Struct: defaults its members to public
 
 Struct inherit from other classes publicly and classes inherit privately
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <array>
#include <cassert>

class Date
{
    /// all these data members are : private by default
    int m_day {};
    int m_month {};
    int m_year {};
  
/// all member functions are public: can be accessed by anyone
/// public interface: group of public members, as set_date and print both are a group
public:
    
    /// set_date can access the private members because set_date itself is a member of this class
    void set_date(int day, int month, int year)
    {
        m_day = day;
        m_month = month;
        m_year = year;
    }
    
    void print()
    {
        std::cout << m_day << '/' << m_month << '/' << m_year;
    }
};

class Dateclass
{
    int m_day {};
    int m_month {};
    int m_year {};
    
public:
    void set_date(int day, int month, int year)
    {
        m_day = day;
        m_month = month;
        m_year = year;
    }
    
    void print()
    {
        std::cout << m_day << '/' << m_month << '/' << m_year;
    }
    
    /// NOTE: we can access the private members of object d directly
    /// which means access controls work on a per-class basis, not on a per-object basis
    /// no only this function can access the private members of the implicit object but-
    /// this function can access the private members of any object of this class that it can see
    void copy_from(const Dateclass& d)
    {
        m_day = d.m_day;
        m_month = d.m_month;
        m_year = d.m_year;
    }
};

class Point3d
{
private:
    int m_x {};
    int m_y {};
    int m_z {};
    
public:
    void set_values(int x, int y, int z)
    {
        m_x = x;
        m_y = y;
        m_z = z;
    }
    
    void print()
    {
        std::cout << '<' << m_x << ", ";
        std::cout << m_y << ", ";
        std::cout << m_z << '>';
    }
    
    bool is_equal(const Point3d& point2)
    {
        return (point2.m_x == m_x && point2.m_y == m_y && point2.m_z == m_z);
    }
};

class Stack
{
private:
    using Array = std::array<int, 10>;
    using Index = Array::size_type;
    
    Array m_array {};
    Index m_next{ 0 };
    
public:
    void reset()
    {
        m_next = 0;
    }
    
    bool push(int value)
    {
        if (m_next == m_array.size())
            return false;
        
        m_array[m_next++] = value;
        
        return true;
    }
    
    int pop()
    {
        assert(m_next > 0 && "Can't pop empty stack\n");
        
        return m_array[--m_next];
    }
    
    void print()
    {
        std::cout << "( ";
        for (Index i{ 0 }; i < m_next; ++i)
        {
            std::cout << m_array[i] << ' ';
        }
        std::cout << ")\n";
    }
};

int main()
{
    Date date;
    
    /// error: can't access the private member outside the class
    /*date.m_year = 2000;*/
    
    /// can access the private members because set_date itself is a member
    date.set_date(20, 11, 1998);
    date.print();
    
    std::cout << '\n';
    
    Dateclass d1;
    d1.set_date(22, 12, 1999);
    
    Dateclass copy {};
    copy.copy_from(d1);
    copy.print();
    
    std::cout << '\n';
    
    Point3d point;
    point.set_values(2, 3, 1);
    
    point.print();
    std::cout << '\n';
    
    Point3d point1;
    point1.set_values(1, 2, 3);
    
    Point3d point2;
    point2.set_values(1, 2, 3);
    
    if (point1.is_equal(point2))
        std::cout << "point1 and point2 are equal\n";
    else
        std::cout << "point1 and point2 are not equal\n";
    
    Point3d point3;
    point3.set_values(10, 2, 1);
    
    if (point1.is_equal(point3))
        std::cout << "point1 and point3 are equal\n";
    else
        std::cout << "point1 and point3 are not equal\n";
    
    Stack stack;
    stack.print();

    stack.push(5);
    stack.push(3);
    stack.push(8);
    stack.print();

    stack.pop();
    stack.print();

    stack.reset();
    stack.print();
    
    return 0;
}
