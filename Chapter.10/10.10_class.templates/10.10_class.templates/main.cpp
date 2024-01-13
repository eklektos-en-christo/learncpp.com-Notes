//
//  main.cpp
//  10.10_class.templates
//
//  Created by Εκλεκτός εν Χριστώ on 3/14/23.
//

/*
 type definitions - can't be overloaded
 
 class template - template definition for instantiating class types
 
 class type - is a struct, class or union type
 
 class template definition: start with a template parameter declaration
 
 begin with the template keyword, next specify all of the template types that the class
 template will use inside angled brackets(<>), for each template type we need, we use the
 keyword typename(preferred) or class(not preferred), followed by the name of the template
 type e.g. T
 next we define our struct like usual, except we can use our template type T wherever we
 want a templated type that will be replaced with a real type later
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Using class templates in a function:
 a function that can take a pair of any type
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 class templates with template type and non-template type parameters:
 class templates can have some members using a template type and other members using a
 normal type
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 class templates with multiple template types:
 class templates can also have multiple template types
 example - if we wanted the two members of our Pair class to be able to have different types
 we can define our Pair class template with two template types
 
 to define multiple template types in template parameter declaration - separate each of
 desired template types with a comma
 
 actual template type arguments can be different or the same
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::pair - a class template, in the utility header
 favor std::pair over writing your own pair
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Using class templates in multiple files:
 class templates - typically defined in header files, so they can be included into any code
 file that needs them,
 
 template definitions and type definitions - both are exempt from one-definition rule
 */

#include "pair.h"
#include <iostream>
#include <utility>

/// Pair class/struct - as a class template
/// T - we only need one template type
/// both members will be the same type
template <typename T>
struct Pair
{
    T first{};
    T second{};
};

template <typename T>
constexpr T max(Pair<T> p)
{
    return (p.first < p.second ? p.second : p.first);
}

/// template class specialization
/// explicit definition
/// that's what Pair<int> looks like
/// that's what compiler actually compiles -
/// after all the template instantiations are done
/// template <> - tells the compiler that this is a template -
/// type with no template parameters
template <>
struct Pair<int>
{
    int first{};
    int second{};
};

/// following snippet shows what the compiler actually instantiates
template <>
constexpr int max(Pair<int> p)
{
    return (p.first < p.second ? p.second : p.first);
}

/// class template with template type and non-template type members
template <typename T>
struct Foo
{
    /// this will have whatever the type T is replaced with
    T first{};
    /// this will always have type int, regardless of what type T is
    int second{};
};

/// class template with multiple template types
template <typename T, typename U>
struct Pair2
{
    T first{};
    U second{};
};

template <typename T, typename U>
void print(Pair2<T, U> p)
{
    std::cout << p.first << ' ' << p.second << '\n';
}

/// inbuilt std::pair, a class template
template <typename T, typename U>
void print_std_pair(std::pair<T, U> p)
{
    std::cout << p.first << ' ' << p.second << '\n';
}

/// forward declaration for foo(), defined in pair.cpp
void foo();

int main()
{
    /// instantiates Pair<int>
    /// creates object p1
    Pair<int> p1{1, 22};
    std::cout << p1.first << ' ' << p1.second << '\n';
    
    /// instantiates Pair<double>
    /// creates object p2
    Pair<double> p2{11.11, 33.1};
    std::cout << p2.first << ' ' << p2.second << '\n';
    
    /// creates object p3
    /// no new Pair instantiated - prior Pair<double> definition used
    Pair<double> p3{1.0, 2.0};
    std::cout << p3.first << ' ' << p3.second << '\n';
    
    Pair<int> p4{1, 5};
    /// explicit call to max<int>
    /// instantiate the the function - max<int>(Pair<int>)
    std::cout << max<int>(p4) << '\n';
    
    Pair<double> p5{2.2, 1.1};
    /// call to max<double> using template argument deduction(preferred)
    /// instantiate the the function - max<double>(Pair<double>)
    std::cout << max<double>(p5) << '\n';
    
    Foo<char> f1{'A', 1};
    std::cout << static_cast<int>(f1.first) << ' ' << f1.second << '\n';
    
    /// Pair - holding a double and an int
    Pair2<double, int> p6{3.14, 200};
    print(p6);
    
    /// std library std::pair,
    std::pair<int, double> p7{22, 4.101};
    print_std_pair(p7);
    
    
    foo();
    
    return 0;
}
