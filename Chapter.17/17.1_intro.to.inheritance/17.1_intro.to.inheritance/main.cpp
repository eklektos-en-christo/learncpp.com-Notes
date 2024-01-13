//
//  main.cpp
//  17.1_intro.to.inheritance
//
//  Created by Εκλεκτός εν Χριστώ on 7/30/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 Two major ways in C++ to construct complex classes:
 
 -Object Composition
 -Inheritance
 
 INHERITANCE: models an "is-a" relationship between two objects.
 
 INHERITANCE: involves creating new objects by directly acquiring the attributes and behaviors of other
 objects and then extending or specializing them.
 
 Example: C++ inherited many features from C, the language upon which it is based and C inherited many of
 its features from the programming languages that came before it
 
 Consider Apples and Bananas: they are different, but they both are fruits, all fruits have a name, color
 and a size. We can say that apples and bananas inherit these all of the properties of fruit because they're
 fruit.
 
                                FRUIT
                                /   \
                               /     \
                              /     BANANA
                            APPLE
 
 This diagram defines a hierarchy.
 
 -----------------------------------------------------------------------------------------------------------
 HIERARCHIES: a diagram that shows how various objects are related, most hierarchies either show a
 progression over time or categorize things in a way that moves from general to specific.
 
 Example:                       SHAPE
                                  |
                          |``````````````````|
                          |                  |
                      TRIANGLE          QUADRILATERAL
                          |                  |
                    RIGHT TRIANGLE       RECTANGLE
                                             |
                                          SQUARE
 
 From general(top) to specific(bottom), each item in the hierarchy inheriting the properties and behaviors
 of the item above it.
 
 -----------------------------------------------------------------------------------------------------------
 */

int main()
{
    return 0;
}
