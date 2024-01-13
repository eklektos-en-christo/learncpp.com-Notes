//
//  Date.hpp
//  13.11_class.code.and.header.files
//
//  Created by Εκλεκτός εν Χριστώ on 7/11/23.
//

#ifndef Date_hpp
#define Date_hpp

#include <iostream>

class Date
{
private:
    int m_day {};
    int m_month {};
    int m_year {};
    
public:
    /// forward declarations for member functions
    Date(int day, int month, int year);
    
    void set_date(int day, int month, int year);
    void print();
    
    /// access functions are defined here, they are small enough to be defined inside the class
    int get_day() { return m_day; }
    int get_month() { return m_month; }
    int get_year() { return m_year; }
};

#endif /* Date_hpp */
