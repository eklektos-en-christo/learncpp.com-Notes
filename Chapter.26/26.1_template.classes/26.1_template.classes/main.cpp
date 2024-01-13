//
//  main.cpp
//  26.1_template.classes
//
//  Created by Εκλεκτός εν Χριστώ on 11/15/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 function templates: allow us to generalize functions to work with may different data types
 
 Template classes: work pretty much identically to the function templates
 
 template: is not a function or a class, it is a stencil used to create functions or classes
 
 name of the templated class is classname<T> not classname only
 
 the copy constructor and copy assignment operator used Array rather than Array<T>
 
 When the class name is used without the template arguments inside of the class, the arguments are the same
 as the ones of the current instantiation
 
 Compiler won't compile the class if it won't be used anywhere, compiler stencils out a copy when a class
 is needed for a specific type and then compiles that copy
 
 template classes: are ideal for container classes to have the containers work across a wide variety of data
 types
 
 -----------------------------------------------------------------------------------------------------------
 Splitting up template classes:
 
 With non-template classes:
 - class definition is put in a header file
 - the member function definitions in a similarly named code file
 - in this way the member function files are compiles as a separate project file
 
 this doesn't work with template classes
 
 The compiler must see both the full class template definition(not just a declaration) and the specific
 template types needed
 
 When main.cpp is compiled, the contents of Array.h are copied into main.cpp, when compiler sees that we
 need two template instances Array<int> and Array<double>, it will instantiate these and compile them as
 part of the main.cpp translation unit, operator[] member function has a declaration in the Array.h, the
 compiler will accept a call to it, assuming it will be defined elsewhere
 
 When Array.cpp is compiled separately, the contents of the Array.h are copied into the Array.cpp
 compiler won't find any code in Array.cpp that requires the Array class template or Array<int>::operator[]
 function template to be instantiated, so compiler won't instantiate anything
 
 On linking, we get a linker error, because main.cpp made a call to Array<int>:: operator[] but that
 template function was never instantiated
 
 Ways to work around this:
 
 - easy way is to put all the template class code in the header file, means put the contents of Array.cpp
 into array.h, below the class, the downside of it is that if the template class is used in many files, you
 will end up with many local instances of the template class, which can increase the compile and link times
 
 - an alternative is to put the contents of array.cpp file into the new file named Array.inl, inl stands for
 inline, then include the array.inl at the bottom of the array.h's header guard, if the compiler is giving
 an error about duplicate definitions, then it is most likely compiling the .inl file twice, once when the
 compiler compiles .inl file separately and once when the array.cpp file that includes the .inl gets
 compiled, if the .inl file contains any non-inline functions or variables, then we will run into difficulty
 of the ODR, to solve this, exclude the .inl file from the build and the linking
 
 - other solutions involve including the .cpp files, not recommended
 
 - another alternative is to use a three file approach, template class goes in the header, template class
 member functions go in the code file, then add a third file which contains all of the instantiated classes
 you need as below
 
 templates.cpp
 
 // Ensure the full Array template definition can be seen
 #include "Array.h"
 #include "Array.cpp" // we're breaking best practices here, but only in this one place

 // #include other .h and .cpp template definitions you need here

 template class Array<int>; // Explicitly instantiate template Array<int>
 template class Array<double>; // Explicitly instantiate template Array<double>

 // instantiate other templates here
 
 the "template class" command cause the compiler to explicitly instantiate the template class, in the above
 case the compiler will stencil out definitions for Array<int> and Array<double> inside of templates.cpp,
 other code files that want to use these types can include Array.h to satisfy the compiler, and the linker
 will link these explicit type definitions from template.cpp, this method requires maintaining the
 templates.cpp for each program
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include "Array.h"

int main()
{
    const int length{ 10 };
    
    /// template argument is needed outside the class
    Array<int> int_array{ length };
    Array<double> double_array{ length };
    
    for (int count{ 0 }; count < length; ++count)
    {
        int_array[count] = count;
        double_array[count] = count + 0.9;
    }
    
    for (int count{ length - 1}; count >= 0; --count)
        std::cout << int_array[count] << '\t' <<  double_array[count] << '\n';
    
    return 0;
}
