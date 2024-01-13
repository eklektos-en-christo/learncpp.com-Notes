//
//  pair.h
//  10.10_class.templates
//
//  Created by Εκλεκτός εν Χριστώ on 3/14/23.
//

#ifndef pair_h
#define pair_h

/// class template - typically defined in header files
template <typename T>
struct my_pair
{
    T first{};
    T second{};
};

/// function template - typically defined in header files
template <typename T>
constexpr T max(my_pair<T> p)
{
    return (p.first < p.second ? p.second : p.first);
}

#endif /* pair_h */
