//
//  main.cpp
//  4.1_intro.to.fundamental.data.types
//
//  Created by εκλεγμένοι εν Χριστώ on 9/11/22.
//

/// variable defined: piece of memory set aside for that variable
/// Bit/binary digit: smallest unit of memory, holds 0 or 1
/// memory addresses: memory organized into sequential units, these units are
/// called addresses
///
/// each memory address holds: 1byte of data
/// byte: group of bits, 8 sequential bits
/// Key insight

/// In C++, we typically work with “byte-sized” chunks of data.
///
/// Data types: to tell the compiler how to interpret the contents of memory in
/// some meaningful way
///
/// integer type: “the piece of memory that this variable uses is going to be
/// interpreted as an integer value”.
///
///
/// if you assign an integer object the value 65, that value is converted to the
/// sequence of bits 0100 0001 and stored in the memory assigned to the object.
/// when the object is evaluated to produce a value, that sequence of bits is
/// reconstituted back into the original value. Meaning that 0100 0001 is converted
/// back into the value 65.
///
/// FUNDAMENTAL DATA TYPES/BUILT IN/PRIMITIVE
/// +-----------------------------------------------------------------------------------------+
/// TYPE             CATEGORY                MEANING                                    EXAMPLE
/// float               floating point              number with fractional part             3.3232
/// double
/// long double
/// +-----------------------------------------------------------------------------------------+
/// bool               integral(boolean)        true or false                                  true
/// +-----------------------------------------------------------------------------------------+
/// char               integral(character)      a single character of text             'a'
/// wchar_t
/// char8_t
/// char16_t
/// char32_t
/// +-----------------------------------------------------------------------------------------+
/// short              integral(integer)          +ve or -ve whole numbers          22
/// int                                                     including 0
/// long
/// long long
/// +-----------------------------------------------------------------------------------------+
/// std::nullptr_t Null pointer                  a null pointer                              nullptr
/// +-----------------------------------------------------------------------------------------+
/// void               void                             no type                                       N/A
/// +-----------------------------------------------------------------------------------------+
///
/// integer: specific data type
/// integral: integer like
///
/// integral type: stored in memory as integers
///
/// boolean, characters & integers, enumerated types: all integral types
///
/// string: compound data type, not primitive, holds sequence of characters
///
///
///
///
/// _t suffix: means "type", it's a nomenclature applied to modern types, used for
/// the types defined in newer versions of C++.
