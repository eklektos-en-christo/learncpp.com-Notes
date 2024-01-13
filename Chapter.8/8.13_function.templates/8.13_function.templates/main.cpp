//
//  main.cpp
//  8.13_function.templates
//
//  Created by εκλεγμένοι εν Χριστώ on 2/19/23.
//

/*
 Template system was designed to simplify the process of creating functions/classes that
 are able to work with different data types
 
 instead of manually creating a bunch of identical functions/classes, we instead create a
 single template
 
 template: describes what a function/class looks like,
 
 in a template : we can use one or more placeholder types
 
 placeholder type : represents some type that is not known at the time the template is
 written, but that will be provided later.
 
 once template is defined : compiler can use that template to generate as many overloaded
 functions/classes as needed, each using different actual types
 
 end result : is same, we end up with bunch of identical functions/classes, but we only have
 to create and maintain a single template, compiler does the hard work for us
 
 key insight:
 compiler can use a single template to generate a family of related functions/classes, each
 using a different set of types
 
 template : is essentially a stencil for creating functions and classes
 
 templates : can work with types that didn't even exist when template was written, this make
 template code both flexible and future proof
 
 Function templates : function like definition, used to generate one or more overloaded
 functions, each with a different set of actual types, this allows us to create functions
 that can work with many different types
 
 type template parameters/template types : at the creation of function template, we use
 placeholder types for any parameter types, return types or types used in the function body
 
 CPP supports: 3 different types of template parameters
 -type template parameters : where the template parameter represents a type - MOST COMMON
 -non-type template parameters : where the template parameter represents a constexpr value
 -template template parameters : where the template parameter represents a  template
 
 common convention : to use single capital letters, starting with T, to represent type
 template parameters
 
 best practice
 use a capital T to name the type template parameters, like T, U, V etc.
 
 template parameter declaration : when we tell the compiler that it is a function template
 and T is a type template parameter
 
 first:
 we start with a keyword : template, tells the compiler that we are creating a template
 second:
 we specify all of the type template parameters that our template will use inside angled
 brackets <>
 -for each type template parameter : we use the keyword typename or class, followed by the
 name of the type template parameter e.g. T, U etc.
 
 each function or class template : needs its own template parameter declaration
 
 typename vs class : no difference, class keyword was introduced earlier in the language
 -typename is more clearer which specifies that type template parameter can be replaced by
 any type and not just class types
 */

#include <iostream>

/// int version of max
//int max(int x, int y)
//{
//    return (x > y) ? x : y;
//}

/// new version of max that uses a single template type
///
/// this function template has one template type named T, refer to it as max<T>
template <typename T>               /// template parameter declaration
T max(T x, T y)                     /// function template definition for max<T>
{
    return (x > y) ? x : y;
}

int main()
{
    std::cout << max(2, 3) << '\n';
    
    return 0;
}
