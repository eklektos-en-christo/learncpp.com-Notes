//
//  Cents.hpp
//  14.3_overloading.operators.using.normal.functions
//
//  Created by Εκλεκτός εν Χριστώ on 7/22/23.
//

#ifndef Cents_hpp
#define Cents_hpp

class Cents
{
private:
    int m_cents{};
    
public:
    Cents(int cents) : m_cents{ cents } {}
    int get_cents() const { return m_cents; }
};

/// explicit prototype declaration is necessary with normal functions
/// any files uses this header will know that this overload exists
/// because of this declaration
/// without this declaration, the use of operator+ in main() will fail
Cents operator+(const Cents& c1, const Cents& c2);

#endif /* Cents_hpp */
