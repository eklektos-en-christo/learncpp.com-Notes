//
//  main.cpp
//  6.15_unnamed.and.inline.namespaces
//
//  Created by εκλεγμένοι εν Χριστώ on 12/12/22.
//

/*
 Variants of namespaces supported by CPP:
 
 Unnamed(anonymous) namespaces: namespace that is defined without a name
 
 Unnamed namespace: all content declared inside it is treated as a part of the
 parent namespace(in this case below the parent namespace is global namespace).
 
 Unnamed namespace: all identifiers inside the unnamed namespace are treated as if
 they has internal linkage
 
 Unnamed namespace: the content of unnamed namespace can't be seen outside of the file
 in which the unnamed namespace is defined
 
 Functions in unnamed namespace: this is effectively same as defining all functions
 in the unnamed namespace as static functions
 
 Unnamed namespace: typically used when you have a lot of content that you want to
 ensure stays local to a the file
 
 Unnamed namespace: makes possible to cluster such content in an unnamed namespace
 than individually mark all declaration as static
 
 Unnamed namespace: also keep user-defined types local to the file, something for
 which there is not alternative equivalent mechanism to do.
 
 Inline namespaces: namespace that is typically used to version the content
 
 Inline namespace: anything declared inside is considered as a part of the parent
 namespace
 
 Inline namespace: don't give everything internal linkage
 
 inline : keyword to declare the inline namespace
 */

#include <iostream>

/// unnamed namespace below - namespace defined without a name
namespace
{
    /// this is only accessible in this file
    /// the function itself is accessible from the parent namespace, which is global namespace in this case
    void do_smthng()
    {
        std::cout << "FROM UNNAMED NAMESPACE!" << '\n';
    }
}

/// this is the inline namespace named version_1
/// also the default version
inline namespace version_1
{
    void do_smthng_inline()
    {
        std::cout << "FROM INLINE V1 NAMESPACE!" << '\n';
    }
}

/// normal namespace named version_2
/// this can be made inline, then the do_smthng_inline will be called from version_2 namespace
/// we can say that inline makes the namespace as default namespace
/// the other versions of the same namespace can be used using namespace_name::
namespace version_2
{
    void do_smthng_inline()
    {
        std::cout << "FROM INLINE V2 NAMESPACE!" << '\n';
    }
}

namespace version_3
{
    void do_smthng_inline()
    {
        std::cout << "FROM INLINE V3 NAMESPACE!" << '\n';
    }
}

int main()
{
    /// calling the function without namespace prefix or ::
    /// the function call works because this function is accessible from the parent(global) namespace
    do_smthng();
    
    /// calling the version_1 namespace's function do_smthng_inline
    version_1::do_smthng_inline();
    /// calling the version_2 namespace's function do_smthng_inline
    version_2::do_smthng_inline();
    /// calling the version_3 namespace's function do_smthng_inline
    version_3::do_smthng_inline();
    
    /// this will call the inline version of do_smthng_inline which is version_1
    /// if the existing programs who want the version_2, they will need to globally replace do_smthng_inline
    /// with version_2::do_smthng_inline
    /// this is called because currently the version_1 is inline namespace, do it is the default version
    do_smthng_inline();
    do_smthng_inline();
    
    /// calling explicitly the version_2 of do_smthng_inline function
    /// this allows newer programs to take advantage of newer/better variations
    version_2::do_smthng_inline();
    
    return 0;
}
