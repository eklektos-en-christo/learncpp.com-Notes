//
//  main.cpp
//  14.7_overloading.the.comparison.operators
//
//  Created by Εκλεκτός εν Χριστώ on 7/24/23.
//

/*
 -------------------------------------------------------------------------------------------
 Comparison operators: are all binary operators, they don't modify their operands, it better
 to overload them as friend functions
 
 BEST PRACTICE:
 only define overloaded operators that make sense intuitively for the class
 
 Many of the comparison operators: can be implemented using other comparison operators i.e.
 using the overloaded operators to implement other overloaded operators
 
 operator!= : can also be implemented as !(operator==)
 operator>  : can also be implemented as operators< with the order of parameters flipped
 operator>= : can also be implemented as !(operator<)
 operator<= : can also be implemented as !(operator>)
 
 so we only need to implement logic for operators == and <, other four comparison operators
 can be defined in terms of these two
 
 -------------------------------------------------------------------------------------------
 THE SPACESHIP OPERATOR: <=>, allows to reduce the number of comparison functions we need
 to write down to 2 at most, and sometimes just 1
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <string_view>
#include <numeric>
#include <vector>
#include <algorithm>

/*----------------------------------------------------------------------------------------*/
class Car
{
private:
    std::string m_make {};
    std::string m_model{};
    
public:
    Car(std::string_view make, std::string_view model)
    : m_make{ make }, m_model{ model }
    {
    }
    
    /// overloaded operator== & operator!= using member functions
    friend bool operator==(const Car& c1, const Car& c2);
    friend bool operator!=(const Car& c1, const Car& c2);
    
    friend bool operator<(const Car& c1, const Car& c2);
    
    friend std::ostream& operator<<(std::ostream& out, const Car& c);
};

bool operator==(const Car& c1, const Car& c2)
{
    return (c1.m_make == c2.m_make && c1.m_model == c2.m_model);
}

bool operator!=(const Car& c1, const Car& c2)
{
    return (c1.m_make != c2.m_make || c1.m_model != c2.m_model);
}

bool operator<(const Car& c1, const Car& c2)
{
    /// if the car is not the same make
    if (c1.m_make != c2.m_make)
        /// then compare the make
        return c1.m_make < c2.m_make;
    else
        /// otherwise compare the model
        return c1.m_model < c2.m_model;
}

std::ostream& operator<<(std::ostream& out, const Car& c)
{
    out << '(' << c.m_make << ", " << c.m_model << ')';
    return out;
}
/*----------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------*/
class Cents
{
private:
    int m_cents{};
    
public:
    Cents(int cents) : m_cents{ cents } {}
    
    /// overloading all 6 logical comparison operators
    /// reducing the comparative redundancy by using one comparison overload for implementing other comparison overload
    friend bool operator==(const Cents& c1, const Cents& c2) { return c1.m_cents == c2.m_cents;}
    friend bool operator!=(const Cents& c1, const Cents& c2) { return !(operator==(c1, c2)); }
    
    friend bool operator<(const Cents& c1, const Cents& c2) { return c1.m_cents < c2.m_cents; }
    /// order of the parameters flipped
    friend bool operator>(const Cents& c1, const Cents& c2) { return operator<(c2, c1); }
    
    friend bool operator<=(const Cents& c1, const Cents& c2) { return !(operator>(c1, c2)); }
    friend bool operator>=(const Cents& c1, const Cents& c2) { return !(operator<(c1, c2)); }
};

/// redundancy when comparison operators implemented
/*
bool operator==(const Cents& c1, const Cents& c2)
{
    return c1.m_cents == c2.m_cents;
}

bool operator!=(const Cents& c1, const Cents& c2)
{
    return c1.m_cents != c2.m_cents;
}

bool operator<(const Cents& c1, const Cents& c2)
{
    return c1.m_cents < c2.m_cents;
}

bool operator>(const Cents& c1, const Cents& c2)
{
    return c1.m_cents > c2.m_cents;
}

bool operator<=(const Cents& c1, const Cents& c2)
{
    return c1.m_cents <= c2.m_cents;
}

bool operator>=(const Cents& c1, const Cents& c2)
{
    return c1.m_cents >= c2.m_cents;
}*/
/*----------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------*/
class Fraction
{
private:
    int m_numerator{};
    int m_denominator{};

public:
    Fraction(int numerator = 0, int denominator = 1) :
        m_numerator{ numerator }, m_denominator{ denominator }
    {
        /// We put reduce() in the constructor to ensure any new fractions we make get reduced!
        /// Any fractions that are overwritten will need to be re-reduced
        reduce();
    }

    void reduce()
    {
        int gcd{ std::gcd(m_numerator, m_denominator) };
        if (gcd)
        {
            m_numerator /= gcd;
            m_denominator /= gcd;
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const Fraction& f1);
    
    friend bool operator==(const Fraction& f1, const Fraction& f2);
    friend bool operator!=(const Fraction& f1, const Fraction& f2);
    
    friend bool operator<(const Fraction& f1, const Fraction& f2);
    friend bool operator>(const Fraction& f1, const Fraction& f2);
    
    friend bool operator<=(const Fraction& f1, const Fraction& f2);
    friend bool operator>=(const Fraction& f1, const Fraction& f2);
};

std::ostream& operator<<(std::ostream& out, const Fraction& f1)
{
    out << f1.m_numerator << '/' << f1.m_denominator;
    return out;
}

bool operator==(const Fraction& f1, const Fraction& f2)
{
    return (f1.m_numerator == f2.m_numerator) && (f1.m_denominator == f2.m_denominator);
}

bool operator!=(const Fraction& f1, const Fraction& f2)
{
    return !(operator==(f1, f2));
}

bool operator<(const Fraction& f1, const Fraction& f2)
{
    return (f1.m_numerator * f2.m_denominator < f2.m_numerator * f1.m_denominator);
}

bool operator>(const Fraction& f1, const Fraction& f2)
{
    return operator<(f2, f1);
}

bool operator<=(const Fraction& f1, const Fraction& f2)
{
    return !(operator>(f1, f2));
}

bool operator>=(const Fraction& f1, const Fraction& f2)
{
    return !(operator<(f1, f2));
}
/*----------------------------------------------------------------------------------------*/



int main()
{
    Car corolla{ "Toyota", "Corolla" };
    Car camry{ "Toyota", "Camry" };
    
    if (corolla == camry)
        std::cout << "Corolla and Camry are the same\n";
    else
        std::cout << "Corolla and Camry aren't the same\n";
    
    Cents dime{ 10 };
    Cents nickel{ 5 };
    
    if (nickel > dime)
        std::cout << "A nickel is greater than a dime.\n";
    if (nickel >= dime)
        std::cout << "A nickel is greater than or equal to a dime.\n";
    if (nickel < dime)
        std::cout << "A dime is greater than a nickel.\n";
    if (nickel <= dime)
        std::cout << "A dime is greater than or equal to a nickel.\n";
    if (nickel == dime)
        std::cout << "A dime is equal to a nickel.\n";
    if (nickel != dime)
        std::cout << "A dime is not equal to a nickel.\n";
    
    Fraction f1{ 3, 2 };
    Fraction f2{ 5, 8 };

    std::cout << f1 << ((f1 == f2) ? " == " : " not == ") << '\t' << f2 << '\n';
    std::cout << f1 << ((f1 != f2) ? " != " : " not != ") << '\t' << '\t' << f2 << '\n';
    std::cout << f1 << ((f1 < f2) ? " < " : " not < ") << '\t' << f2 << '\n';
    std::cout << f1 << ((f1 > f2) ? " > " : " not > ") << '\t' << '\t' << f2 << '\n';
    std::cout << f1 << ((f1 <= f2) ? " <= " : " not <= ") << '\t' << '\t' << f2 << '\n';
    std::cout << f1 << ((f1 >= f2) ? " >= " : " not >= ") << '\t' << f2 << '\n';
    
    std::vector<Car> cars
    {
        { "Toyota", "Corolla" },
        { "Honda", "Accord" },
        { "Toyota", "Camry" },
        { "Honda", "Civic" }
    };

    std::sort(cars.begin(), cars.end());

    for (const auto& car : cars)
        std::cout << car << '\n';
    
    return 0;
}
