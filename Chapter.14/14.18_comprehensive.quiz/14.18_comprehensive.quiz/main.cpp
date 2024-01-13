//
//  main.cpp
//  14.18_comprehensive.quiz
//
//  Created by Εκλεκτός εν Χριστώ on 7/27/23.
//

/*
 -------------------------------------------------------------------------------------------
 SUMMARY:
 
 OPERATOR OVERLOADING: a variant of function overloading that lets you overload operators
 for your classes
 
 When operators are overloaded: the intent of the operators should be kept as close to the
 original intent of the operators as possible
 
 If the meaning of an operator when applied to a custom class is not clear and intuitive,
 the use a named function instead
 
 OPERATORS: can be overloaded as a normal function, friend function or a member function
 
 Rules of thumb to determine which form is best for a given situation:
 -if overloading =,[],() or ->, do so as a member function
 -if overloading a unary operator, do so as a member function
 -if overloading a binary operator that modifies its left operand, do so as a member
 function
 -if overloading a binary operator that doesn't modify its left operand, do so as a friend
 function or normal function
 
 TYPECASTS: can be overloaded to provide the conversion functions, which can be used
 to explicitly or implicitly convert your class into another type
 
 COPY CONSTRUCTOR: special type of constructor, used to initialize an object from another
 object of the same type
 
 COPY CONSTRUCTORS: are used for direct/uniform initialization from an object of the same
 type, copy initialization and when passing or returning a parameter by value
 
 COPY CONSTRUCTOR: if not supplied, compiler will create for you
 
 MEMBERWISE INITIALIZATION: default compiler provided copy constructor does the memberwise
 initialization
 
 MEMBERWISE INITIALIZATION: each original member is copied to the new copy member
 
 COPY CONSTRUCTOR: may be elided for optimization purposes, even it has side effects, do
 rely on the copy constructor
 
 CONSTRUCTORS: are considered converting constructors by default, compiler will use them
 to implicitly convert objects of other types into objects of your class
 
 explicit keyword in front of the constructor: to avoid implicit conversion of other types
 into you own class type
 
 delete keyword: to delete copy constructor and overloaded assignment operator, this will
 cause compile error if deleted function would be called
 
 ASSIGNMENT OPERATOR: can be overloaded to allow assignment to your class
 
 Compiler: provides assignment operator, if not provided by the user
 
 OVERLOADED ASSIGNMENT OPERATORS: should always include a self-assignment check, unless its
 handled naturally or you're using a copy and swap idiom
 
 If new object had to be created before copying can occur, use copy constructor, this
 includes passing or returning by value
 
 if new object doesn't need to be created before the copying can occur, use copy assignment
 operator
 
 Compiler provided copy constructor and assignment: do a memberwise initialization or
 assignment, which is a shallow copy. below---
 
 If the class allocates memory dynamically: multiple object will end up pointing to the
 same allocated memory, in this case you'll need to explicitly define the copy constructor
 and assignment to do a deep copy
 
 Better: avoid doing own memory management if you can and use classes from the standard
 library
 -------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <cstdint>
#include <cassert>
#include <cmath>


/*----------------------------------------------------------------------------------------*/
class Average
{
private:
    std::int32_t m_total { 0 };
    std::int8_t m_numbers { 0 };
    
public:
    Average() {}
    
    /// modifies the left operand, so it should be a member function
    Average& operator+=(int num);
    
    friend std::ostream& operator<<(std::ostream& out, const Average& a);
};

Average& Average::operator+=(int num)
{
    m_total += num;     /// increment the total by our new number
    ++m_numbers;        /// increase the count by 1
    return *this;       /// for chaining the +='s together
}

std::ostream& operator<<(std::ostream& out, const Average& a)
{
    /// floating point division, not an integer division
    out << static_cast<double>(a.m_total) / a.m_numbers;
    return out;
}
/*----------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------*/
class IntArray
{
private:
    int* m_array{ nullptr };
    int m_length{ 0 };
    
public:
    /// prevent implicit conversions - explicit
    explicit IntArray(int length) : m_length{ length }
    {
        assert(length > 0 && "Length should be a +ve integer\n");
        
        m_array = new int[m_length] {};
    }
    
    /// deep copy constructor
    IntArray(const IntArray& array) : m_length{ array.m_length }
    {
        /// allocate a new array
        m_array = new int[m_length];
        
        for (int i{ 0 }; i < array.m_length; ++i)
            m_array[i] = array.m_array[i];
    }
    
    ~IntArray()
    {
        delete[] m_array;
    }
    
    friend std::ostream& operator<<(std::ostream& out, const IntArray& array);
    
    int& operator[](const int index)
    {
        assert(index >= 0);
        assert(index < m_length);
        
        return m_array[index];
    }
    
    /// deep copy assignment operator
    IntArray& operator=(const IntArray& array)
    {
        /// self-assignment guard
        if (this == &array)
            return *this;
        
        if (m_array)
            delete[] m_array;
        
        m_length = array.m_length;
        
        m_array = new int[m_length];
        
        /// copy elements from original array to new array
        for (int i{ 0 }; i < array.m_length; ++i)
            m_array[i] = array.m_array[i];
        
        return *this;
    }
};

std::ostream& operator<<(std::ostream& out, const IntArray& array)
{
    for (int count{ 0 }; count < array.m_length; ++count)
        out << array.m_array[count] << ' ';
    
    return out;
}

IntArray fillArray()
{
    IntArray a(5);
    a[0] = 5;
    a[1] = 8;
    a[2] = 2;
    a[3] = 3;
    a[4] = 6;

    return a;
}
/*----------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------*/
class FixedPoint2
{
private:
    std::int16_t m_base{};
    std::int8_t m_decimal{};
    
public:
    FixedPoint2(std::int16_t base = 0, std::int8_t decimal = 0)
    : m_base{ base }, m_decimal{ decimal }
    {
        if (m_base < 0 || m_decimal < 0)
        {
            if (m_base > 0)
                m_base = -m_base;
            
            if (m_decimal > 0)
                m_decimal = -m_decimal;
        }
    }
    
    FixedPoint2(double d) :
    m_base{ static_cast<std::int16_t>(std::trunc(d)) },
    m_decimal { static_cast<std::int8_t>(std::round(d * 100) - m_base * 100) }
    {
        
    }
    
    operator double() const
    {
        return m_base + (static_cast<double>(m_decimal) / 100);
    }
    
    friend bool operator==(const FixedPoint2& fp1, const FixedPoint2& fp2)
    {
        return (fp1.m_base == fp2.m_base && fp1.m_decimal == fp2.m_decimal);
    }
    
    FixedPoint2 operator-() const
    {
        /// We need to cast, because the negative sign (-) converts our
        /// narrow integers types to int.
        return {
            static_cast<std::int16_t>(-m_base),
            static_cast<std::int8_t>(-m_decimal)
        };
    }
};

std::ostream& operator<<(std::ostream& out, const FixedPoint2& fp)
{
    out << static_cast<double>(fp);
    return out;
}

std::istream& operator>>(std::istream& in, FixedPoint2& fp)
{
    double d{};
    in >> d;
    fp = FixedPoint2{ d };

    return in;
}

FixedPoint2 operator+(const FixedPoint2& fp1, const FixedPoint2& fp2)
{
    return { static_cast<double>(fp1) + static_cast<double>(fp2) };
}

void testAddition()
{
    std::cout << std::boolalpha;
    std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 1.98 }) << '\n'; // both positive, no decimal overflow
    std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 2.25 }) << '\n'; // both positive, with decimal overflow
    std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -1.98 }) << '\n'; // both negative, no decimal overflow
    std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -2.25 }) << '\n'; // both negative, with decimal overflow
    std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -0.48 }) << '\n'; // second negative, no decimal overflow
    std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -0.75 }) << '\n'; // second negative, possible decimal overflow
    std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 0.48 }) << '\n'; // first negative, no decimal overflow
    std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 0.75 }) << '\n'; // first negative, possible decimal overflow
}
/*----------------------------------------------------------------------------------------*/



int main()
{
    
    Average avg{};

    avg += 4;
    std::cout << avg << '\n';

    avg += 8;
    std::cout << avg << '\n';

    avg += 24;
    std::cout << avg << '\n';

    avg += -10;
    std::cout << avg << '\n';

    (avg += 6) += 10;                       /// 2 calls chained together
    std::cout << avg << '\n';

    Average copy{ avg };
    std::cout << copy << '\n';
    
    
    
    
    
    /*IntArray a{ fillArray() };

    /// If you're getting crazy values here you probably forgot to do a deep copy in your copy constructor
    std::cout << a << '\n';

    /// we're using this reference to avoid compiler self-assignment errors
    auto& ref{ a };
    a = ref;

    IntArray b(1);
    b = a;
    
    /// change a value in a, b should not change
    a[4] = 7;

    /// If you're getting crazy values here you probably forgot to do self-assignment check
    /// If b ends in 7, you probably forgot to do a deep copy in your copy assignment
    std::cout << b << '\n';*/
    
    
    

    /*FixedPoint2 a{ 34, 56 };
    std::cout << a << '\n';

    FixedPoint2 b{ -2, 8 };
    std::cout << b << '\n';

    FixedPoint2 c{ 2, -8 };
    std::cout << c << '\n';

    FixedPoint2 d{ -2, -8 };
    std::cout << d << '\n';

    FixedPoint2 e{ 0, -5 };
    std::cout << e << '\n';

    std::cout << static_cast<double>(e) << '\n';*/
    
    
    
    /*FixedPoint2 a{ 0.01 };
    std::cout << a << '\n';

    FixedPoint2 b{ -0.01 };
    std::cout << b << '\n';

    FixedPoint2 c{ 5.01 }; /// stored as 5.0099999... so we'll need to round this
    std::cout << c << '\n';

    FixedPoint2 d{ -5.01 }; /// stored as -5.0099999... so we'll need to round this
    std::cout << d << '\n';

    /// Handle case where the argument's decimal rounds to 100 (need to increase base by 1)
    FixedPoint2 e{ 106.9978 }; /// should be stored with base 107 and decimal 0
    std::cout << e << '\n';

    FixedPoint2 f{ 1.9 }; /// make sure we handle single digit decimal
    std::cout << f << '\n';*/
    
    
    
    testAddition();

    FixedPoint2 a{ -0.48 };
    std::cout << a << '\n';

    std::cout << -a << '\n';

    std::cout << "Enter a number: "; // enter 5.678
    std::cin >> a;

    std::cout << "You entered: " << a << '\n';
    
    return 0;
}
