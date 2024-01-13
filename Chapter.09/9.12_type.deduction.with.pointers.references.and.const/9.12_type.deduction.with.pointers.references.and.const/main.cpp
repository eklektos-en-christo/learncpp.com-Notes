//
//  main.cpp
//  9.12_type.deduction.with.pointers.references.and.const
//
//  Created by Εκλεκτός εν Χριστώ on 3/4/23.
//

/*
 auto : keyword, used to have the compiler deduce the type of a variable from the
 initializer
 
 type deduction : will drop const qualifiers, const can be reapplied by adding const
 qualifier in the definition
 
 Type deduction : drops references, if you want the deduced type to be a reference, you
 an reapply the reference a the point of definition
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Top level const : const qualifier that applies to an object itself, mean the object itself
 is const
 like - a const pointer
 
 Low level const : const qualifier that applies to the object being referenced or pointed to
 means the object is const where the pointer is pointing or where reference is referencing
 like - a pointer to const
 
 a reference to a const value : is always a low level const
 
 a pointer : can have top level, low level or both kinds of const
 
 type deduction drops const qualifiers-
 it only drops top-level const, low level const is not dropped
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 TYPE DEDUCTION AND CONST REFERENCES: if the initializer is a reference to const, the
 reference is dropped first and then any top level const is dropped from the result
 
 best practice:
 if you want a const reference - reapply the const qualifier, even when it's not strictly
 necessary, this makes the intent clear and helps prevent mistakes
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 TYPE DEDUCTION AND POINTERS: type deduction doesn't drop pointers-
 we can also use an * in conjunction with pointer type deduction as below
 auto* ptr{};
 
 top level const - is only dropped during pointer type deduction
 
 auto vs auto*  ––––––––––
 -when auto used with pointer type initializer : type deduced for auto includes the pointer
 
 -when auto* used with pointer ,,    ,,  : type deduced for auto does not include the
 pointer, pointer is reapplied afterward the type is deduced
 
 differences between auto and auto*:
 auto* - must resolve to a pointer initializer, other a compiler error will result
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 TYPE DEDUCTION AND CONST POINTERS:
 with pointers - we have both const pointer and pointer to const cases, we also have auto
 and auto*

 just like the references - only top-level const is dropped during pointer type deduction
 
 When the initializer is a const pointer to const value - see in main, last 8 function calls
 
 best practice - if you want a const pointer, reapply the const qualifier even when it is
 not strictly necessary, it makes intent clear and helps prevent mistakes
 */

#include <iostream>

/// function returns a reference std::string&
std::string& get_ref()
{
    static std::string name{"Lin"};
    
    return name;
}

/// function returns a reference to const
/// returns - const std::string&
/// reference is dropped first - leaving us with const std::string
/// const std::string - const is a top level const, it is also dropped
/// which leaves the deduced type as std::string
const std::string& get_const_ref()
{
    static std::string name{"HELLO"};
    
    return name;
}

/// function returns a pointer
std::string* get_ptr()
{
    std::string* name{nullptr};
    
    return name;
}

/// function returns a pointer
std::string* get_ptr_auto()
{
    static std::string name{"LEON"};
    
    std::string* ptr_name{&name};
    
    return ptr_name;
}

/// function returns a pointer
std::string* get_ptr_const()
{
    return nullptr;
}

/// function returns a const pointer to a const value
const std::string* const get_const_ptr_const_value()
{
    return nullptr;
}

int main()
{
    /// type deduced as std::string and not std::string&
    /// & qualifier is dropped in type deduction
    auto reference{get_ref()};
    
    /// reference dropped
    auto ref1{get_ref()};
    
    /// reference reapplied at the point of definition
    auto& ref2{get_ref()};
    
    std::cout << ref2 << '\n';
    std::cout << ref1 << '\n';
    std::cout << reference << '\n';
    
    /// x : is an object
    /// const is applied to x itself, so it is top level
    const int x{44};
    /// const is applied to the pointer itself, pointer itself is a const pointer
    int* const ptr{};
    
    /// ref is a reference to const int
    /// const is applied to the object being referenced, so it is low level
    const int& ref{x};
    /// const is applied to the object being pointed to
    /// ptr2 is not const but the object itself is const
    const int* ptr2{};
    
    /// left const is : low level, value is const
    /// right const is : top level, ptr3 is const itself
    const int* const ptr3{};
    
    /// in this deduction
    /// -reference is dropped
    /// -then top level const is dropped
    auto ref3{get_const_ref()};
    
    /// const std::string reapplied
    /// but reference dropped
    /// deduced type is : const std::string
    const auto ref4{get_const_ref()};
    
    /// const std::string& - reference reapplied
    /// low level const not dropped
    /// type is still : const std::string&
    /// const std::string& - this const is a low level const, that's why not dropped
    /// type deduced is : const std::string&
    /// constness of the result is implicit and not obvious
    auto& ref5(get_const_ref());
    
    /// reference and const reapplied
    /// type is already deduced as a reference to const
    /// reapplying const here - is redundant
    /// const here - only making explicitly clear that the result will be const
    /// constness of the result is explicit and obvious
    const auto& ref6{get_const_ref()};
    
    /// deduced type is std::string*
    /// pointer is not dropped
    /// type substituted for auto - std::string*    :   pointer is included when auto used
    auto ptr_1{get_ptr()};
    
    std::cout << ((ptr_1) ? "NOT NULL" : "NULL") << '\n';
    
    /// using an * asterisk in conjunction with pointer type deduction
    /// deduced type is - std::string*
    /// pointer is not dropped
    /// type substituted for auto* - std::string    :   pointer is reapplied after the type deduction
    /// pointer is reapplied - type deduced was std::string only
    auto* ptr_2{get_ptr()};
    
    std::cout << ((ptr_2) ? "NOT NULL" : "NULL") << '\n';
    
    /// deduced to type - std::string, because we dereferenced the pointer
    /// type substituted for auto : std::string
    auto ptr_3{*get_ptr_auto()};
    
    /// ptr_3 is - std::string operand, not a pointer operand
    std::cout << ptr_3 << '\n';
    
    /// error : initializer is not a pointer
    /// auto deduced to std::string, then pointer is reapplied
    /// but std::string* can't be initialized with an initializer which is not a pointer
//    auto* ptr_4{*get_ptr_auto()};
    
    /// const auto or auto const - whatever the deduced type is, we are making it const
    /// type deduced to - std::string*, then const is applied
    /// final type is std::string* const
    const auto ptr5{get_ptr_const()};
    /// type deduced to - std::string*, then const is applied
    /// final type is std::string* const
    auto const ptr6{get_ptr_const()};
    
    /// const on the left means - deduced pointer type is a pointer to const
    /// type deduced to - const std::string*
    /// thus ptr7 - is a pointer to const
    const auto* ptr7{get_ptr_const()};
    /// const on the right means - deduced pointer type is a const pointer
    /// type deduced to - std::string* const
    /// thus ptr8 - is a const pointer
    auto* const ptr8{get_ptr_const()};
    
    
    /// type deduced to - const std::string*
    /// top level const on the pointer itself - dropped
    /// low level const on the object being pointed to- not dropped
    auto ptr_a{get_const_ptr_const_value()};
    /// type deduced to - const std::string*
    /// top level const on the pointer itself - dropped
    /// low level const on the object being pointed to- not dropped
    auto* ptr_b{get_const_ptr_const_value()};
    
    /// top level const dropped - reapplying it
    /// type deduced to - const std::string* const
    auto const ptr_c{get_const_ptr_const_value()};
    /// top level const dropped - reapplying it
    /// type deduced to - const std::string*
    const auto ptr_d{get_const_ptr_const_value()};
    
    /// top level const - dropped
    /// auto* const - reapplies the top level const
    /// so type deduced to - const std::string* const
    auto* const ptr_e{get_const_ptr_const_value()};
    /// top level const - dropped
    /// const auto* - applies the const to the type being pointed to, which was already const
    /// so type deduced to - const std::string*
    const auto* ptr_f{get_const_ptr_const_value()};
    
    /// applying the const qualifier twice - disallowed, compiler error
    const auto const ptr_g{get_const_ptr_const_value()};
    /// applying the const on both sides of the pointer - allowed, auto* must be a pointer type
    /// resulting type is - const std::string* const
    const auto* const ptr_h{get_const_ptr_const_value()};
    
    return 0;
}
