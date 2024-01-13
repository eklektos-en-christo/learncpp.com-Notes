//
//  Date.cpp
//  13.11_class.code.and.header.files
//
//  Created by Εκλεκτός εν Χριστώ on 7/11/23.
//

/// all function definitions are inside .cpp file
/// only functions that are forward declared in the Date.hpp file
/// small access function are only one line, they are defined in .hpp file
#include "Date.hpp"

Date::Date(int day, int month, int year)
{
    set_date(day, month, year);
}

void Date::set_date(int day, int month, int year)
{
    m_day = day;
    m_month = month;
    m_year = year;
}

void Date::print()
{
    std::cout << "Day: " << m_day << '\t';
    std::cout << "Month: " << m_month << '\t';
    std::cout << "Year: " << m_year << '\n';
}
