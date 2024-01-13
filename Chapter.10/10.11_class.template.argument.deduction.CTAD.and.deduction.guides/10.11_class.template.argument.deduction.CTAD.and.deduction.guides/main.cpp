//
//  main.cpp
//  10.11_class.template.argument.deduction.CTAD.and.deduction.guides
//
//  Created by Εκλεκτός εν Χριστώ on 3/14/23.
//

/*
 CTAD: class template argument deduction, C++17
 
 CTAD - when instantiating an object from a class template, the compiler can deduce the
 template template types from the type of the object's initializer
 
 CTAD - only performed when no template argument list is present
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Template argument deduction guides: C++17
 in certain cases - compiler may need a little extra help understanding how to deduce the
 template arguments properly
 
 in cpp17, CTAD - doesn't know how to deduce the template arguments for aggregate class
 templates
 
 deduction guide - tells the compiler how to deduce the template arguments for a given class
 template
 
 how deduction guide works - example from the Pair class
 -we use the same template type definition as in our Pair class
 -if our deduction is going to tell the compiler how to deduce the types for a Pair<T, U>
  we have to define what T and U are(template types)
 -on right hand side of the arrow, we have the type that we're helping the compiler to
  deduce, in this case, we want the compiler to be able to deduce template arguments for
  objects of type Pair<T, U>, so that's exactly what we put here
 -on the left hand side of the arrow, we tell the compiler what kind of declaration to look
  for, in this case, we are telling it to look for a declaration of some object named Pair
  with two arguments, we could also use this as Pair(T t, U u), where t and u are the names
  of the parameters, but since we don't use t and u, we won't need to give them names
 finally - we're telling the compiler that if it sees a declaration of a Pair with two
 arguments of types T and U respectively then it should deduce the type to be a Pair<T, U>
 
 In the case of Pair2 - deduction guide maps a Pair(T, T)(two arguments of type T) to a
 Pair<T>
 
 
 std::pair and other std lib template types - come with pre-defined deduction guides, that's
 why the std::pair example in main compiles fine with us having to provide the deduction
 guide ourselves
 
 C++20 - added the ability for the compiler to automatically generate deduction guides for
 aggregate class types
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Type template parameters with default values:
 function parameters - can have default arguments
 template parameters - can be given default values, these will be used when the template
 parameter isn't explicitly specified and can't be deduced
 */

#include <iostream>
#include <utility>

template <typename T, typename U>
struct Pair
{
    T first{};
    U second{};
};

/// deduction guide for Pair - needed in C++17
/// Pair objects initialized with arguments of type T and u - should deduce to Pair<T, U>
template <typename T, typename U>
Pair(T, U) -> Pair<T, U>;

/// example for a Pair that takes a single template type
template <typename T>
struct Pair2
{
    T first{};
    T second{};
};

/// deduction guide for Pair2
/// Pair2 objects initialized with arguments of type T and T should deduce to Pair<T>
template <typename T>
Pair2(T, T) -> Pair2<T>;

/// template type parameters T and U defaulted to type int
template <typename T=int, typename U=int>
struct Pair3
{
    T first{};
    U second{};
};

template <typename T, typename U>
Pair3(T, U) -> Pair3<T, U>;

int main()
{
    /// explicitly specify class template std::pair<int, int>
    /// std library pair
    std::pair<int, int> p1{2, 3};
    
    /// not explicit specifying
    /// CTAD - used to deduce std::pair<int, double>
    /// template types are deduced from the types of the object's initializer which are 40 and 2.2
    /// no template argument list present - CTAD PERFORMED in this case
    std::pair p2{40, 2.2};
    
    /// too few template arguments - error
    /// no argument deduced
    /// CTAD - NOT PERFORMED
//    std::pair<> p3{2, 2};
    
    /// second argument not deduced
    /// few arguments passed - error
    /// CTAD - NOT PERFORMED
//    std::pair<int> p4{2, 2};
    
    /// explicitly specify class template Pair<int, int>
    Pair<int, int> pair1{2, 2};
    /// error - no viable constructor or deduction guide
//    Pair pair2{2, 1};
    
    /// CTAD used to deduce Pair<int, int> from the initializers 3 and 3
    /// when compiler sees this definition,
    /// it will say that this is a declaration of a Pair with two arguments of type int and int
    /// so using the deduction guide, it should deduce this to be a Pair<int, int>
    Pair pair3{3, 3};
    
    /// explicitly specifying class template Pair2<int>
    Pair2<int> pair4{22, 22};
    /// CTAD used to deduce Pair2<int, int> from the initializers 1 and 1
    Pair2 pair5{1, 1};
    
    /// explicitly specifying class template Pair3<int, int>
    Pair3<int, int> pair6{33, 30};
    /// CTAD used to deduce Pair3<int, int> from the initializers 44 and 41
    Pair3 pair7{44, 41};
    /// default Pair3<int, int> used
    /// no explicit specification for the type template parameters
    /// no initializer for these types to be deduced from
    /// compiler will use the types specified in the defaults
    /// pair8 will be of type Pair3<int, int>
    Pair3 pair8;
    
    return 0;
}
