//
//  main.cpp
//  16.3_aggregation
//
//  Created by Εκλεκτός εν Χριστώ on 7/28/23.
//

/*
 -------------------------------------------------------------------------------------------
 Aggregation: 2nd subtype of object composition
 
 To qualify as an aggregation, a whole object and its parts must have the following
 relationship:
 
 - the part/member is part of the object/class
 - the part/member can belong to more than one object/class at a time
 - the part/member does not have its existence managed by the object/class
 - the part/member does not know about the existence of the object/class
 
 Aggregation: is a part-whole relationship like a composition, the parts are contained
 within the whole, and it is a unidirectional relationship. However, the parts can belong to
 more than one object at a time, and the whole object is not responsible for the existence
 and lifespan of the parts.
 
 When an aggregation is created, the aggregation is not responsible for creating the parts,
 when an aggregation is destroyed, the aggregation is not responsible for destroying the
 parts
 
 Aggregation: models "has-a" relationships
 
 The parts of an aggregation can be singular or multiplicative
 
 -------------------------------------------------------------------------------------------
 IMPLEMENTING AGGREGATIONS:
 
 The difference between implementing the composition and aggregation is mostly semantic.
 
 Aggregation: the members variables are typically either references or pointers that are
 used to point at objects that have created outside the scope of the class, an aggregation
 usually either takes the object it is going to point to as constructor parameters or it
 begins empty and the sub-objects are added later via access functions or operators
 
 Because these parts exist outside of the scope of the class, when the class is destroyed,
 the pointer or reference member variable will be destroyed but not deleted. The parts
 themselves will still exist
 
 BEST PRACTICE:
 Implement the simplest relationship type that meets the needs of a program, not what seems
 right in real-life.
 
 -------------------------------------------------------------------------------------------
 SUMMARY OF COMPOSITION AND AGGREGATION:
 
 Compositions:
 
 - typically use normal member variables
 - can use pointer members if the class handles object allocation/deallocation itself
 - responsible for creation and destruction of parts
 
 Aggregations:
 
 - typically use pointer or reference members that point to reference object that live
   outside the scope of the aggregate class
 - not responsible for creating/destroying parts
 
 Favor compositions over aggregations.
 
 -------------------------------------------------------------------------------------------
 CORRIGENDUM:
 
 Aggregate data types: class and structs, they group multiple variables together
 
 Aggregate class: struct or class that has no provided constructors, destructors or overload
 assignment, has all public members, and does not use inheritance. Essentially a plain-old-
 data struct.
 
 Aggregates & aggregation: are different and should not be confused
 
 -------------------------------------------------------------------------------------------
 std::reference_wrapper
 
 In the Department class below, we used a reference in the Department to store the Teacher,
 this works fine if there is only one teacher, but what if a Department has multiple
 teachers. We'd like to store those Teachers in a list of some kind. But fixed arrays and
 the various standard library lists can't hold references, because list elements must be
 assignable, and references can't be reassigned.
 
 std::reference_wrapper - a class that acts like a reference, but also allows assignment &
 copying, so it's compatible with lists like std::vector
 
 std::reference_wrapper - lives in <functional>
 
 std::reference_wrapper - the wrapped object created of this class can't be anonymous
 because anonymous objects have expression scope, and this would leave the reference
 dangling.
 
 std::reference_wrapper - use get() member function to get the object back out of reference_
 wrapper
 
 -------------------------------------------------------------------------------------------
 */

#include <functional>       /// for std::reference_wrapper
#include <iostream>
#include <string>
#include <vector>

class Teacher
{
private:
    std::string m_name{};
    
public:
    Teacher(const std::string& name) : m_name{ name }
    {
    }
    
    const std::string& get_name() const { return m_name; }
};



class Department
{
private:
    const Teacher& m_teacher;
    
public:
    /// Department points to the object outside of the Department class
    Department(const Teacher& teacher) : m_teacher{ teacher }
    {
    }
};



int main()
{
    /// create a teacher outside the scope of the department
    /// bob is created independently of department
    Teacher bob{ "Bob" };
    
    {   /// create a department and use the constructor to pass the teacher to it
        Department dept{ bob };
    }   /// department goes out of scope here and is destroyed
    
    /// but bob still exists here, but the department doesn't
    std::cout << bob.get_name() << " still exists." << '\n';
    
    std::string tom{ "Tom" };
    std::string berta{ "Berta" };
    
    /// these string are stored by reference
    /// use const std::string inside < > for const references
    std::vector<std::reference_wrapper<std::string>> names{ tom, berta };
    
    std::string jim{ "Jim" };
    
    names.push_back(jim);
    
    for (auto name : names)
    {
        /// get member function to get the referenced string
        name.get() += " Beam";
    }
    
    std::cout << jim << '\n';
    
    return 0;
}
