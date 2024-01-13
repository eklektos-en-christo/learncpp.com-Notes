//
//  main.cpp
//  16.2_composition
//
//  Created by Εκλεκτός εν Χριστώ on 7/27/23.
//

/*
 -------------------------------------------------------------------------------------------
 OBJECT COMPOSITION:
 
 Complex objects in real life: are often built from smaller, simpler objects
 
 A car: is built using a metal frame, an engine, some tires, a transmission, a steering
 wheel and a large number of other parts
 
 A PC: is built from a CPU, a motherboard, some memory etc...
 
 OBJECT COMPOSITION: is the process of building complex object from simpler objects
 
 OBJECT COMPOSITION: models a "has-a" relationship between two objects
 
 Complex object: sometimes called the whole or the parent
 
 Simpler object: often called part, child or component
 
 When we build classes with data members, we're essentially constructing a complex object
 from simpler parts, which is object composition
 
 Composite types: structs and classes are sometimes referred to as composite types
 
 OBJECT COMPOSITION: allows us to create complex classes by combining simpler, more
 easily manageable parts, this reduces complexity, allows us to write code faster and with
 less errors because we can reuse code that has already been written, tested and verified as
 working.
 
 -------------------------------------------------------------------------------------------
 TYPES OF OBJECT COMPOSITION:
 
 There are two subtypes of object composition:
 
 -composition
 -aggregation
 
 -------------------------------------------------------------------------------------------
 COMPOSITION:
 
 To qualify as a composition, an object and a part must have the following relationship:
 
 - the part/member is part of the object/class
 - the part/member can only belong to one object/class at a time
 - the part/member has its existence managed by the object/class
 - the part/member does not know about the existence of the object/class
 
 A good real life example of a composition is: relationship between a person's body and a
 heart.
 
 Composition relationships: are part-whole relationships where the part must constitute the
 part of the whole object. A heart is part of a person's body. The part of a composition can
 only be part of one object at a time. A heart that is part of one person's body can not be
 part of someone else' body at the same time.
 
 In a composition relationship:
 
 - the object is responsible for the existence of the parts
 - part is created when object is created and destroyed when object is destroyed
 - the object manages the part's lifetime
 - because of this, composition is sometimes called a "death relationship"
 - a part doesn't know about the existence of the whole
 
 Unidirectional relationship: the body knows about the heart, but heart doesn't know about
 the whole body.
 
 Composition: has nothing to say about the transferability of parts. A heart can be
 transplanted from one body to another. Even after being transplanted, it still meets the
 requirements for a composition, the heart is now owned by the recipient, and can only be
 part of the recipient object unless transferred again.
 
 OBJECT COMPOSITION: models has-a type relationships
 
 COMPOSITION: models "part-of" relationships
 
 COMPOSITION: is often used to model physical relationships, where one object is physically
 contained inside another.
 
 Parts of an object composition: can be singular or multiplicative
 
 Example: a heart is a singular part of the body, but a body contains 10 fingers.

 -------------------------------------------------------------------------------------------
 IMPLEMENTING COMPOSITIONS:
 
 They are typically created as structs or classes with normal data members. Because these
 data members exist directly as part of the struct/class, the lifetime of the data members
 is bound to the class instance itself.
 
 Compositions that need to do dynamic allocation or deallocation may be implemented using
 pointer data members, in this case the composition class should be responsible for doing
 all the necessary memory management itself, not the user of the class
 
 In general, if you can design a class using composition, you should design it using
 composition
 
 -------------------------------------------------------------------------------------------
 VARIANTS ON THE COMPOSITION THEME:
 
 - a composition may defer creation of some parts until they are needed
 - a composition may opt to use a part that has been given to it as input rather than create
   the part itself
 - a composition may delegate destruction of its parts to some other object
 
 Composition: should manage its parts without the user of the composition needing to manage
 anything
 
 -------------------------------------------------------------------------------------------
 COMPOSITION AND CLASS MEMBERS:
 
 A good rule of thumb is that each class should be built to accomplish a single task, the
 task should either be the storage and manipulation of some kind of data (e.g. Point2D,
 std::string) or the coordination of its members (e.g. Creature). Ideally not both.
 
 - each individual class can be kept relatively simple and straightforward, focused on
   performing one task well, this makes those classes easier to write and much easier to
   understand, as they are more focused, e.g. Point2D only worries about point-related stuff
   which keeps it simple
 
 - each class can be self contained, which makes them reusable, e.g. we can use Point2D
   class in a completely different application
 
 - the outer class can have the class members do most of the hard work and instead focus
   on coordinating the data flow between the members, this lowers the complexity of the
   outer class, because it can delegate the task to its members, who already know how to do
   these tasks. e.g. we can move our creature, it delegates that task to the Point2D class,
   which already understands how to set a point. Thus the Creature class don't have to worry
   about how such things would be implemented
 
 TIP:
 A good rule of thumb is that each class should be built to accomplish a single task, the
 task should either be the storage and manipulation of some kind of data or the coordination
 of its members e.g Creature, ideally not both.
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include "Creature.h"
#include "Point2D.h"

class Fraction
{
private:
    
    /// these two data members are part of the Fraction, contained within the fraction
    /// they can't belong to more than one Fraction at a time
    /// they both don't know they are part of a Fraction
    /// when Fraction instance is created, they both are created
    /// when Fraction instance is destroyed, they both are destroyed
    /// fraction "has-a" numerator, fraction "has-a" denominator
    /// numerator is a "part-of" Fraction, denominator is a "part-of" fraction
    int m_numerator;
    int m_denominator;
    
public:
    Fraction(int num =  0, int den = 1) : m_numerator{ num }, m_denominator{ den }
    {
    }
};

int main()
{
    std::cout << "Enter a name for your creature: ";
    std::string name;
    std::cin >> name;
    Creature creature{ name, { 4, 7 } };
    
    while (true)
    {
        std::cout << creature << '\n';
        
        std::cout << "Enter new X location for creature (-1 to quit): ";
        int x{ 0 };
        std::cin >> x;
        if (x == -1)
            break;
        
        std::cout << "Enter new Y location for creature (-1 to quit): ";
        int y{ 0 };
        std::cin >> y;
        if (y == -1)
            break;
        
        creature.move_to(x, y);
    }
    
    return 0;
}
