//
//  main.cpp
//  13.5_constructors
//
//  Created by Εκλεκτός εν Χριστώ on 7/5/23.
//

/*
 -------------------------------------------------------------------------------------------
 Aggregate initialization: can be used when all the members of a class/struct are public, we
 can use list initialization
 
 When class members become private: they can't be initialized directly because they're not
 accessible publicly
 
 -------------------------------------------------------------------------------------------
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CONSTRUCTORS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 -------------------------------------------------------------------------------------------
 
 Constructor: special kind of class member function
 
 Constructor: is automatically called when an object of that class is created
 
 Constructors: typically used to initialize member variables of the class to appropriate
 values which the user provides, or to do any setup steps that are necessary for the class
 to be used e.g. open a file or database
 
 After a constructor executes: the object should be in a well defined, usable state
 
 Special naming rules for constructors:
 -they must have the same name as the class name(capitalization included)
 -they don't have any return type, not even void
 
 -------------------------------------------------------------------------------------------
 DEFAULT COSNTRUCTORS AND DEFAULT INITIALIZATION:
 
 Default constructor: constructor that takes no parameters or have all the parameters set to
 default values
 
 Default constructor: called when the user doesn't provide initialization values
 
 -------------------------------------------------------------------------------------------
 VALUE INITIALIZATION: using empty set of braces {}, calls default constructor
 
 e.g.   Fraction frac{};
 
 
 
 Default initialization: calls default constructor
 
 e.g.   Fraction frac;
 
 BEST PRACTICE: favor value initialization {} over default initialization for class objects
 
 Many programmers favor default-initialization over value-initialization for class objects.
 This is because when using value-initialization, the compiler may zero-initialize the
 class members before calling the default constructor in certain cases, which is slightly
 inefficient (C++ programmers don’t like paying for features they’re not using).

 However, favoring default-initialization also comes with a downside: you have to know
 whether a type will initialize itself, i.e. it is a class-type and all members have an
 initializer, or there is a default-constructor that initializes all member variables. If
 you see a defined variable without an initializer, you have to think about whether that’s
 a mistake or not (depending on what type the object is).
 
 -------------------------------------------------------------------------------------------
 DIRECT AND LIST INITIALIZATION USING CONSTRUCTORS WITH PARAMETERS:
 
 Constructors: can also be declared with parameters, this is useful when we want instances
 of our class to have specific values that we provide
 
 Constructors: can coexist in the class due to function overloading as long as each has a
 unique signature(number and type of parameters)
 
 Default value: for constructors work exactly the same as with any other functions
 
 BEST PRACTICE:
 favor brace initialization to initialize class objects
 
 -------------------------------------------------------------------------------------------
 COPY INITIALIZATION USING EQUALS WITH CLASSES:
 
 It is possible: to initialize classes using copy initialization (=)
 
 Direct, list & copy initialization: work identically with fundamental types, copy
 initialization does not work the same with classes, though the end result is often the same
 
 Avoid: copy form of initialization with classes
 
 -------------------------------------------------------------------------------------------
 REDUCING THE CONSTRUCTORS:
 
 When there are multiple constructors in a class, the default constructor is actually
 somewhat redundant
 
 When implementing the constructors, consider how you might keep the number of constructors
 down through smart defaulting the values
 
 -------------------------------------------------------------------------------------------
 RULES ABOUT DEFAULT PARAMETERS:
 
 When defining a function with default parameters: all default parameters must follow any
 non-default parameters, there can't be any non-default parameters after the default
 parameters
 
 -------------------------------------------------------------------------------------------
 IMPLICITLY GENERATED DEFAULT CONSTRUCTOR:
 
 OPTION 1:
 Implicit constructor: if the class has no constructors, compiler automatically generates a
 default public constructor
 
 If the class has any other constructors: then implicit constructor will not be provided
 
 OPTION 2:
 If class has any other constructors but you want to allow the default construction: either
 add default arguments to every parameter of a constructor with parameters or explicitly
 provide a default constructor
 
 OPTION 3:
 we can use the default keyword to tell the compiler to create a default constructor for us
 anyway
 =default : expresses better what the intentions are and it's safer, this is used to create
 a default constructor, it can zero initialize the members even if they haven't been
 initialized at their declaration
 
 BEST PRACTICE:
 if you have constructors in the class and need a default constructor that does nothing,
 e.g. because all the members are initialized using non-static member initialization: then
 use =default
 
 -------------------------------------------------------------------------------------------
 CLASSES CONTAINING CLASS MEMBERS:
 
 Class: it may contain other class' objects as member variables
 
 When the outer class is constructed: the member variables will have their default
 constructor called, the happens before the body of the constructor executes
 
 Class-type members: get initialized even if we don't explicitly initialize them
 
 -------------------------------------------------------------------------------------------
 CONSTRUCTOR NOTES:
 
 -constructors don't create the objects
 -compiler sets up the memory allocation for the object prior to the construction call
 
 PURPOSE OF CONSTRUCTORS:
 
 -they determine who is allowed to create an object of the class type, object of a class can
  only be created if the matching constructor can be found
 -they can be used to initialize objects
 -its up to the programmer that if a constructor actually does the initialization or not
 -its syntactically valid to have a constructor that does no initialization at all
 -constructor still serves the purpose of allowing the object to be created
 
 BEST PRACTICE:
 -always initialize all member variables in the objects
 -its best practice to initialize all local variables
 -also a best practice to initialize all member variables on creation of the object
 
 ADVICE:
 Constructor are intended to be used for initialization when the object is created, don't
 call a constructor to re-initialize the existing object, the result may not be what was
 intended, compiler will create a temporary object and then discard it
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <cassert>
#include <string>

class Fraction
{
private:
    int m_numerator {};
    int m_denominator {};
    
public:
    /// this is the default constructor
    /// the name is same as the class'
    /// it takes not parameters or
    /// parameters can be set to default values if provided
    /// this constructor will be called when user provides no initialization values
    /// this constructor is actually redundant, constructor below does the same initialization
    /*Fraction()
    {
        m_numerator = 0;
        m_denominator = 1;
    }*/
    
    /// constructor with two parameters, one parameter has a default value
    /// this constructor is called when the user passes the
    /// arguments using list or direct initialization
    /// this constructor is defined in a way that it can accept one or two argument or even none
    Fraction(int numerator=0, int denominator=1)
    {
        assert(denominator != 0);
        m_numerator = numerator;
        m_denominator = denominator;
    }
    
    int get_numerator() { return m_numerator; }
    int get_denominator() { return m_denominator; }
    double get_value() { return static_cast<double>(m_numerator) / m_denominator; }
};

class Something
{
public:
    /// default constructor
    /// if user passed first argument as double or other type than the int
    /// then the compiler will error, if the argument were provided using list initialization
    Something(int n=0, double d=9.8)
    {
    }
    
    /// non-default constructor, only takes a double argument
    Something(double d)
    {
    }
};

class Date
{
private:
    int m_day {};
    int m_month {};
    int m_year {};
    
    /// no user provided constructors, the compile will generate a default constructor
};

class Date2
{
private:
    int m_day {};
    int m_month {};
    int m_year {};
    
public:
    /// non default constructor provided, no default constructor will be provided now
    /// if class has any other constructors, no default constructor will be provided
    Date2(int day, int month, int year)
    {
        m_day = day;
        m_month = month;
        m_year = year;
    }
    
    /// no default constructor provided and compiler won't generate it
};

class Date3
{
private:
    int m_day {};
    int m_month {};
    int m_year {};
    
public:
    /// non default constructor, also works as a default constructor
    /// class has no default constructor
    /// and to still allow the default construction
    /// we can provide default arguments to every parameter of the constructor with parameters
    Date3(int day=1, int month=1, int year=1900)
    {
        m_day = day;
        m_month = month;
        m_year = year;
    }
};

class Date4
{
private:
    int m_day {};
    int m_month {};
    int m_year {};
    
public:
    /// telling the compiler to generate a default constructor
    /// even though we have a non default constructor defined below
    /// still we can use default keyword to tell the compiler to generate a default constructor
    Date4() = default;
    
    /// non default constructor
    Date4(int day, int month, int year)
    {
        m_day = day;
        m_month = month;
        m_year = year;
    }
};

class A
{
public:
    A() { std::cout << "Constructor of A called!\n"; }
};

/// class B has an object of class A as a member variable
class B
{
private:
    /// we didn't initialized this variable of type A
    /// but still it will be initialized, because it's a class type and it is initialized even when we don't initialize it
    A m_a;
    
public:
    /// before B constructor executes, the A() constructor initializes the m_a
    /// then B executes
    B() { std::cout << "Constructor of B called!\n"; }
};

/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/
class Ball
{
private:
    std::string m_color {};
    double m_radius {};
    
public:
    Ball(double radius) { m_color = "BLACK"; m_radius = radius; };
    
    Ball(std::string_view color = "BLACK", double radius = 10.0)
    {
        m_color = color;
        m_radius = radius;
    }
    
    void print()
    {
        std::cout << "Color: " << m_color << ", ";
        std::cout << "Radius: " << m_radius << '\n';
    }
};
/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/

int main()
{
    /// because no arguments provided by the user
    /// this statement calls the default Fraction() constructor
    /// Fraction() - runs like a normal function assigning the values 0 to m_numerator
    /// and 1 to m_denominator
    /// default constructor value/default initializes the frac object
    /// empty set of braces is called value initialization
    Fraction frac {};
    std::cout << frac.get_numerator() << '/';
    std::cout << frac.get_denominator() << '\n';
    
    /// list initialization used to initialize the member variables
    /// constructor with two parameters will be called - Fraction(int, int)
    Fraction frac2 { 1, 8 };
    std::cout << frac2.get_numerator() << '/';
    std::cout << frac2.get_denominator() << '\n';
    
    /// direct initialization used to initialize the class object
    /// constructor with two parameters will be called - Fraction(int, int)
    Fraction frac3(5, 3);
    std::cout << frac3.get_numerator() << '/';
    std::cout << frac3.get_denominator() << '\n';
    
    /// second parameter isn't provided, but default value will be used
    /// constructor with two parameters will be called - Fraction(int, int)
    Fraction frac4 { 40 };
    std::cout << frac4.get_numerator() << '/';
    std::cout << frac4.get_denominator() << '\n';
    
    /// copy initialization using equals
    /// constructor with two parameters will be called - Fraction(int, int)
    Fraction frac5 = Fraction{ 22 };
    std::cout << frac5.get_numerator() << '/';
    std::cout << frac5.get_denominator() << '\n';
    
    /// copy initialization using equals
    /// constructor with two parameters will be called - Fraction(int, int)
    Fraction frac6 = 3;
    std::cout << frac6.get_numerator() << '/';
    std::cout << frac6.get_denominator() << '\n';
    
    /// Something(int, double) called
    Something s1 { 1, 1.6 };
    /// Something(int, double) called
    Something s2 { 1 };
    /// Something(int, double) called
    Something s3 {};
    
    /// error: first parameter is int
    /// we passed a double argument
    /// implicit conversion from double to int
    /// from double to int: not allowed when using list initialization
    /*Something s4 { 2.3 };*/
    
    /// Something(double) called
    Something s4 { 2.3 };
    
    /// compiles fine: implicit conversion from double to int
    /// Something(int, double) called
    /// conversion allowed when using direct initialization
    Something s5(2.5, 22.1);
    
    /// explicit cast from double to int, using list initialization in this case
    /// compiles because of static_cast
    Something s6 { static_cast<int>(2.2), 11.9 };
    
    /// Date class has no constructors
    /// compiler will generate a default constructor to create Date object  with no arguments
    /// below object has no arguments but compiler generated a default constructor that takes no parameters
    Date date{};
    
    /// Date2 has a non-default constructor
    /// compiler didn't generate a default constructor that takes no arguments
    /// the line below won't compiler because no default constructor is in the class
    /*Date2 date2{};*/
    
    /// constructor with 3 parameters called - Date2(int, int, int)
    Date2 date2{ 10, 10, 2029 };
    
    /// default constructor is not provided
    /// compiler didn't generate the default constructor
    /// but Date3(int, int, int) still called because its provided with default arguments to every parameter
    Date3 date3{};
    
    /// works because class has a default constructor provided by the compiler using the default keyword
    Date4 date4{};
    
    /// class b having the member A as a variable
    B b{};
    
    Ball def{};
    def.print();
    
    Ball blue{ "BLUE"};
    blue.print();
    
    Ball twenty{ 20.0 };
    twenty.print();
    
    Ball blue_twenty{ "BLUE", 20.0 };
    blue_twenty.print();
    
    return 0;
}
