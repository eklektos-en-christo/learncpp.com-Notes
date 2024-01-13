//
//  my_types.h
//  8.6_typedefs.and.type.aliases
//
//  Created by εκλεγμένοι εν Χριστώ on 2/12/23.
//

#ifndef my_types_h
#define my_types_h

/// type aliases for int and float
using Test_int = int;
using Test_float = float;

/// machines where ints are only 2 bytes, INT_2_BYTES can be #defined
/// program will be compiled with the top set of type aliases
///
/// machines where ints are of 4 bytes, INT_2_BYTES undefined will cause the
/// program to be compiled with the bottom set of type aliases to be used
#ifdef INT_2_BYTES
using int8_type = char;
using int16_type = int;
using int32_type = long;
#else
using int8_type = char;
using int16_type = short;
using int32_type = int;
#endif

#endif /* my_types_h */
