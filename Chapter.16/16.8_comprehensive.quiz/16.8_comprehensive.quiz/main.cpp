//
//  main.cpp
//  16.8_comprehensive.quiz
//
//  Created by Εκλεκτός εν Χριστώ on 7/30/23.
//

/*
 SUMMARY:
 
 Object composition: process of building complex object from the simpler ones
 
 Type of object composition: composition and aggregation
 
 Composition: exists when a member of a class has a part-of relationship with the class, in this relation
 the class manages the existence of the members
 
 To qualify as a composition, an object and a part must have the following relationship:
 
 - the part/member is part of the object/class
 - the part/member can only belong to the object/class at a time
 - the part/member has its existence managed by the object/class
 - the part/member doesn't know about the existence of the object/class
 
 Compositions: are typically implemented via normal member variables or by pointers where the class manages
 all the memory allocation and deallocation. if you can implement a class as a composition, you should
 implement a class as a composition
 
 Aggregations: exists when a class has a has-a relationship with the member, in this relation, the class
 doesn't manage the existence of the members, to qualify as an aggregation, object and its parts must have
 the following relationship:
 
 - the part/member is part of the object/class
 - the part/member can belong to more than one object/class at a time
 - the part/member does not have its existence managed by the class/object
 - the part/member does not know about the existence of the object/class
 
 Aggregations: are typically implemented via pointer or reference
 
 Associations: are a looser type of relationship, where the class uses-an otherwise unrelated object, to
 qualify as an association, and object and an associated object must have the following relationship:
 
 - the associated object/member is otherwise unrelated to the object/class
 - the associated object/member can belong to more than one object/class at a time
 - the associated object/member does not have its existence managed by the object/class
 - the associated object/member may or may not know about the existence of the object/class
 
 Associations: may be implemented via pointer or reference, or by a more indirect means, such as holding
 the index or key of the associated object
 
 Dependency: one class uses another class to perform a task, dependent class is typically not a member of
 the class using it, but rather is temporarily created, used and then destroyed or passed into a member
 function from an external source
 
 Container class: that provides a container to hold multiple objects of another type
 
 Value container: composition that stores copies of the objects it is holding
 
 Reference container: an aggregation that stores pointers or references to objects that live outside the
 container
 
 std::initializer_list - can be used to implement constructors, assignment operators, and other functions
 that accept a list initialization parameter, std::initializer_list lives in <initializer_list> header
 
 Property\Type                          Composition     Aggregation    Association          Dependency
 Relationship type                      Whole/part      Whole/part     Otherwise unrelated  Otherwise unrelated
 Members can belong to multiple classes No              Yes            Yes                  Yes
 Members existence managed by class     Yes             No             No                   No
 Directionality                         Unidirectional  Unidirectional Uni or bi            Unidirectional
 Relationship verb                      Part-of         Has-a          Uses-a               Depends-on
 */

#include <iostream>

int main()
{
    return 0;
}
