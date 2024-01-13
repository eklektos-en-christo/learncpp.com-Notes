//
//  main.cpp
//  13.11_class.code.and.header.files
//
//  Created by Εκλεκτός εν Χριστώ on 7/10/23.
//

/*
 -------------------------------------------------------------------------------------------
 DEFINING THE MEMBER FUNCTIONS OUTSIDE THE CLASS DEFINITION:
 
 When classes get longer and more complicated: then having all the member function
 definitions inside the class can make class harder to manage and work with
 
 To separate the "declaration" portion of the class from "implementation" portion:
 
 -define the class member functions outside the class definition
 -define the member functions as if they were normal functions
 -but prefix the class name to the function name using the :: operator, like with namespaces
 
 Access functions: are often only one line, they are typically left in the class definition
 
 -------------------------------------------------------------------------------------------
 PUTTING CLASS DEFINITIONS IN A HEADER FILE:
 
 Function declarations: can be put into header files to use in multiple files or projects
 
 Class definitions: can also be put in header files to use in multiple files or projects
 
 METHOD:
 
 Class definitions: are put in a header file, name of the header file is same as the class'
 Member functions: which are to be defined outside of the class are put in a .cpp file which
 also has same name as the class'
 
 .cpp also needs to be compiled into any project that uses .hpp/.h file, so the linker knows
 how the class is implemented
 
 -------------------------------------------------------------------------------------------
 Doesn't defining a class in a header file violate the One definition rule?
 
 If the header files has proper guards: then it's impossible to include the class definition
 more than once into the same file
 
 Types(which include classes) - are exempt from the part of the ODR which says you can only
 have one definition per program
 
 #including multiple class definitions into multiple code files: isn't an issue
 
 -------------------------------------------------------------------------------------------
 Doesn’t defining member functions in the header violate the one-definition rule?
 
 Member functions defined inside the class definition: are considered implicitly inline
 
 Inline functions: are exempt from the one definition per program part of the ODR
 
 Trivial member functions: are okay when defined in the class definition itself
 
 Member functions defined outside the class definition: are treated like normal functions
 
 Normal functions: are subject to the one definition per program of the ODR
 
 Normal member functions: should be defined in a code file, not inside the header
 
 Template functions: are implicitly inline also, they can be define inside or outside the
 class
 
 -------------------------------------------------------------------------------------------
 HEADER FILE VS. THE .CPP FILE & IN CLASS DEFINITIONS VS DEFINITIONS OUTSIDE THE CLASS:
 
 Downsides, If put all member function definitions into the header file inside the class:
 -this clutter up the class definition
 -any change to the header will require the recompilation of every file that includes header
 
 Upsides, if put function definitions in .cpp file, If you change the code in a .cpp file:
 -then only that .cpp file needs to be recompiled
 
 RECOMMENDATIONS:
 
 *classes used in only one file that aren't generally reusable: define them directly in the
  single .cpp file they're used in
 
 *classes used in multiple files, that are intended for general use: define them in a .h
  file, the name of .h file should be same as the class' name
 
 *Trivial member functions,constructors/destructors,access function etc: can be defined
  inside the class definition
 
 *Non Trivial member functions: should be defined in .cpp file, the name of the file should
  be same as the class' name
 
 -------------------------------------------------------------------------------------------
 DEFAULT PARAMETERS:
 
 Member functions that have default parameters: should be declared in the class definition
 i.e. in the header file, where they can be seen by whomever includes the header
 
 -------------------------------------------------------------------------------------------
 LIBRARIES:
 
 Separation of class definition(.h) and implementation(.cpp) : very common for libraries
 
 iostream, string, vector, array etc: are all headers from the STD library, implementations
 for the classes that belong to the STD library are contained in a precompiled file that is
 linked in at the link stage, the code is never visible
 
 Precompile library file: can be shared by many applications
 
 -------------------------------------------------------------------------------------------
 */

//#include <iostream>

/// using Date class in the main()
#include "Date.hpp"

class Calculate
{
private:
    int m_value{ 0 };
    
public:
    /// prototypes still exist inside the class definition
    Calculate(int value=0);
    
    Calculate& add(int value);
    Calculate& sub(int value);
    Calculate& mul(int value);
    
    /// this access function is only one line, so it is left defined inside the class
    int get_value() { return m_value; }
};

/// defining member function outside the class
/// :: operator is important to specify which class' member function we are defining outside
Calculate::Calculate(int value) : m_value { value }
{
}

Calculate& Calculate::add(int value)
{
    m_value += value;
    return *this;
}

Calculate& Calculate::sub(int value)
{
    m_value -= value;
    return *this;
}

Calculate& Calculate::mul(int value)
{
    m_value *= value;
    return *this;
}

int main()
{
    Date d1{ 10, 10, 2020 };
    d1.print();
    
    return 0;
}
