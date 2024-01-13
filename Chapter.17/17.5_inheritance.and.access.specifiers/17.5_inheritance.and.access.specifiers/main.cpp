//
//  main.cpp
//  17.5_inheritance.and.access.specifiers
//
//  Created by Εκλεκτός εν Χριστώ on 7/31/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 Derived classes: cannot access private members of base class directly
 
 Access specifiers: determine who can access the members of a class
 
 -----------------------------------------------------------------------------------------------------------
 THE PROTECTED ACCESS SPECIFIER:
 
 Protected: access specifier is only useful in inheritance context
 
 PROTECTED: allows the class the member belongs to, friends, and derived classes to access the member.
 
 Protected members: are not accessible from outside the class but they are accessible by the derived classes
 
 -----------------------------------------------------------------------------------------------------------
 When should use protected access specifier?
 
 When you or your team are going to be ones deriving from your own classes & the number of derived classes
 is reasonable. That way if you make a change to the implementation of base class and updates to the
 derived classes are necessary as a result, you can make the update yourself
 
 Making the members private means public and derived classes can't directly make changes to the class, it
 also means your class may need a larger public/protected interface to support all of the functions that
 the public or derived classes need for operation, which has its own cost to build, test and maintain
 
 In general - it's better to make the members private if you can, use protected only when derived classes
 are planned and the cost to build and maintain an interface to those private member is too high
 
 BEST PRACTICE:
 Favor private members over protected members
 
 -----------------------------------------------------------------------------------------------------------
 DIFFERENT KINDS OF INHERITANCE AND THEIR IMPACT ON ACCESS:
 
 Three different ways for classes to inherit from other classes:
 - public
 - protected
 - private
 
 When specifying the type of access for the derived classes - if you don't choose an inheritance type, then
 C++ defaults to private inheritance, just like the members are default to private if you don't specify the
 access specifier
 
 9 combinations:
 - public members inherited publicly
 - public members inherited privately
 - public members inherited protectedly
 - private members inherited publicly
 - private members inherited privately
 - private members inherited protectedly
 - protected members inherited publicly
 - protected members inherited privately
 - protected members inherited protectedly
 
 When members are inherited, the access specifier for an inherited member may be changed in the derived
 class(only) depending upon the type of inheritance used.
 
 Members that are public or protected in the base class many change access specifiers in the derived class
 
 RULES:
 - a class can always access it own members that are non-inherited
 - the public access the members of a class based on the access specifiers of the class it is accessing
 - a derived class accesses inherited members based on the access specifier inherited from the parent class
   this varies depending on the access specifier and type of inheritance used
 
 -----------------------------------------------------------------------------------------------------------
 PUBLIC INHERITANCE: most commonly used type of inheritance, easiest to understand.
 
 When we inherit a base class publicly: inherited base class members stay public, inherited protected
 members stay protected, inherited private members stay inaccessible because they were private in the base
 class
 
 +---------------------------------------------------------------------------------+
 | ACCESS SPECIFIER IN THE BASE CLASS  |  ACCESS SPECIFIER WHEN INHERITED PUBLICLY |
 +-------------------------------------+-------------------------------------------+
 |      public                         |    public                                 |
 +-------------------------------------+-------------------------------------------+
 |      protected                      |    protected                              |
 +-------------------------------------+-------------------------------------------+
 |      private                        |    inaccessible                           |
 +-------------------------------------+-------------------------------------------+
 
 In public inheritance: things work identically in the base and derived class
 
 BEST PRACTICE:
 Use public inheritance unless you have a specific reason to do otherwise
 
 -----------------------------------------------------------------------------------------------------------
 PROTECTED INHERITANCE: least common method of inheritance, it is almost never used, except in particular
 cases.
 
 With protected inheritance, the public and protected members become protected and  private stays
 inaccessible
 
 +------------------------------------------------------------------------------------+
 | ACCESS SPECIFIER IN THE BASE CLASS  |  ACCESS SPECIFIER WHEN INHERITED PROTECTEDLY |
 +-------------------------------------+----------------------------------------------+
 |      public                         |    protected                                 |
 +-------------------------------------+----------------------------------------------+
 |      protected                      |    protected                                 |
 +-------------------------------------+----------------------------------------------+
 |      private                        |    inaccessible                              |
 +-------------------------------------+----------------------------------------------+
 
 -----------------------------------------------------------------------------------------------------------
 PRIVATE INHERITANCE: this inheritance is rarely used
 
 With private inheritance, all the members from the base are inherited as private, so private members are
 inaccessible, public and protected members become private
 
 +------------------------------------------------------------------------------------+
 | ACCESS SPECIFIER IN THE BASE CLASS  |  ACCESS SPECIFIER WHEN INHERITED PRIVATELY   |
 +-------------------------------------+----------------------------------------------+
 |      public                         |    private                                   |
 +-------------------------------------+----------------------------------------------+
 |      protected                      |    private                                   |
 +-------------------------------------+----------------------------------------------+
 |      private                        |    inaccessible                              |
 +-------------------------------------+----------------------------------------------+
 
 Private inheritance can be useful when the derived class has no obvious relationship to the base class but
 used the base class for implementation internally. In such as case we probably don't want the public
 interface of the base class to be exposed through objects of the derived class as it would be inherited
 publicly
 
 -----------------------------------------------------------------------------------------------------------
 Access rules: hold true for all members e.g. member functions and types declared inside the class
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>

class Base
{
public:
    int m_public {};            /// can be accessed by anybody
    
protected:
    int m_protected {};         /// can be accessed by base members, friends and derived classes
    
private:
    int m_private {};           /// can only be accessed by base members and friends but not derived classes
};

class Derived : public Base
{
public:
    Derived()
    {
        m_public = 1;           /// allowed, public base members are accessible outside the class
        m_protected = 2;        /// allowed, protected base members are accessible to derived classes
        /*m_private = 3;*/      /// not allowed, private base members are not accessible to derived classes
    }
};



/*--------------------------------------------------------------------------------------------------------*/
/// inherit from base publicly
/*class Pub : public Base
{
};

/// inherit from Base protectedly
class Pro : protected Base
{
};

/// inherit from Base privately
class Pri : private Base
{
};

/// inherit from base privately
class Def : Base
{
};*/
/*--------------------------------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------------------------------*/
class Public : public Base         /// this is public inheritance, Pub is inheriting the base members publicly
{
public:
    Public()
    {
        m_public = 1;           /// public inherited members stay public, so m_public is treated as public
        m_protected = 2;        /// protected inherited members stay protected, so m_protected is treated as protected
        /*m_private = 3;*/      /// private inherited members stay inaccessible, so m_private is inaccessible
    }
};
/*--------------------------------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------------------------------*/
class Protected : protected Base        /// this is a protected inheritance, Protected is inheriting the Base class protectedly
{
public:
    Protected()
    {
        m_public = 1;                   /// public inherited members become protected, so m_public is treated as protected
        m_protected = 2;                /// protected inherited members stay protected, so m_protected is treated as protected
        /*m_private = 3;*/              /// private inherited members stay private, so m_private is inaccessible
    }
};
/*--------------------------------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------------------------------*/
class Private : private Base            /// this is a private inheritance, Private is inheriting the Base class privately
{
public:
    Private()
    {
        m_public = 1;                   /// public inherited members become private, so m_public is treated as private
        m_protected = 2;                /// protected inherited members become private, so m_protected is treated as private
        /*m_private = 3;*/              /// private inherited members say inaccessible, so m_private is inaccessible
    }
};
/*--------------------------------------------------------------------------------------------------------*/



int main()
{
    /*
    /// outside class access uses the access specifiers of the class being accessed
    Base base;
    base.m_public = 1;          /// okay, m_public is public in Base class
    base.m_protected = 2;       /// not okay, m_protected is protected in Base class
    base.m_private = 3;         /// not okay, m_private is private in Base class
    
    Public pub;
    pub.m_public = 1;           /// okay, m_public is public in Public
    pub.m_protected = 2;        /// not okay, m_protected is protected in Public
    pub.m_private = 3;          /// not okay, m_private is inaccessible in Public
    */
    
    /*
    Protected pro;
    pro.m_public = 1;           /// not okay, m_public is protected in Protected
    pro.m_protected = 2;        /// not okay, m_protected is protected in Protected
    pro.m_private = 3;          /// not okay, m_private is inaccessible in Protected
    */
    
    /*
    Private pri;
    pri.m_public = 1;           /// not okay, m_public is private in Private
    pri.m_protected = 2;        /// not okay, m_protected is private in Private
    pri.m_private = 3;          /// not okay, m_private is inaccessible in Private
    */
    
    return 0;
}
