//
//  constants.h
//  6.9_sharing.global.constants.across.multiple.files.using.inline.variables
//
//  Created by εκλεγμένοι εν Χριστώ on 11/21/22.
//

#ifndef constants_h
#define constants_h

namespace constants
{
    /// global constants as internal variables
    constexpr double cx_pi{3.14159};
    constexpr double cx_my_gravity{9.2};

    /// global constants as external variables
    extern const double pi;
    extern const double my_gravity;

    /// inline variables
    inline constexpr double in_pi{3.14159};
    inline constexpr double in_my_gravity{7.2};
}

#endif /* constants_h */
