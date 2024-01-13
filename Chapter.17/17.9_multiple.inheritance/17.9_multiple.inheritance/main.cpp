//
//  main.cpp
//  17.9_multiple.inheritance
//
//  Created by Εκλεκτός εν Χριστώ on 10/17/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 MULTIPLE INHERITANCE: a derived class can inherit members from more than one parent
 
 To use multiple inheritance, simply specify each base class, separated by a comma
 
 -----------------------------------------------------------------------------------------------------------
 MIXINS: a small class that can be inherited from in order to add properties to a class, mixin indicates
 that the class is intended to be mixed into other classes, not instantiated on its own
 
 -----------------------------------------------------------------------------------------------------------
 CRTP(Curiously Recurring Templte Pattern): a derived class can inherit from a mixin base class using the
 derived class as a template type parameter.
 
 -----------------------------------------------------------------------------------------------------------
 PROBLEMS WITH MULTIPLE INHERITANCE: increase the complexity of programs and make them maintenance nightmare
 
 Some situations:
 
 Ambiguity - can result when multiple base classes contain a function with the same name
 
 Diamond problem - when a class multiply inherits from two classes which each inherit from a single base
 class
 
 std::cin and std::cout - are both implemented using multiple inheritance
 
 BEST PRACTICE:
 Avoid multiple inheritance unless alternative methods lead to more complexity
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <string_view>

class Person
{
private:
    std::string m_name;
    int m_age{};
    
public:
    Person(std::string_view name, int age) : m_name{ name }, m_age{ age }
    {
        
    }
    
    const std::string& get_name() const { return m_name; }
    int get_age() const { return m_age; }
};

class Employee
{
private:
    std::string m_employer;
    double m_wage{};
    
public:
    Employee(std::string_view employer, double wage) : m_employer{ employer }, m_wage{ wage }
    {
        
    }
    
    const std::string& get_employer() const { return m_employer; }
    double get_wage() const { return m_wage; }
};

/// Multiple inheritance
/// Teacher is inheriting publicly from Person and Employee
class Teacher : public Person, public Employee
{
private:
    int m_teaches_grade{};
    
public:
    Teacher(std::string_view name, int age, std::string_view employer, double wage, int teaches_grade):
    Person{ name, age }, Employee{ employer, wage }, m_teaches_grade{ teaches_grade }
    {
        
    }
};


/*--------------------------------------------------------------------------------------------------------*/
/// Mixins example
struct Point2D
{
    int x;
    int y;
};

class Box
{
private:
    Point2D m_top_left{};
    Point2D m_bottom_right{};
    
public:
    void set_top_left(Point2D point) { m_top_left = point; }
    void set_bottom_right(Point2D point) { m_bottom_right = point; }
};

class Label
{
private:
    std::string m_text{};
    int m_fontsize{};
    
public:
    void set_text(const std::string_view str) { m_text = str; }
    void set_font_size(int font_size) { m_fontsize = font_size; }
};

class Button : public Box, public Label
{
    
};


/*--------------------------------------------------------------------------------------------------------*/
/// Ambiguity problem
class USBDevice
{
private:
    long m_id {};
    
public:
    USBDevice(long id) : m_id{ id }
    {
    }
    
    long get_id() const { return m_id; }
};

class NetworkDevice
{
private:
    long m_id {};
    
public:
    NetworkDevice(long id) : m_id{ id }
    {
    }
    
    long get_id() const { return m_id; }
};

class WirelessAdapter : public USBDevice, public NetworkDevice
{
public:
    WirelessAdapter(long usb_id, long network_id)
    : USBDevice{ usb_id }, NetworkDevice{ network_id }
    {
    }
};

/*--------------------------------------------------------------------------------------------------------*/
/// Diamond problem
class PoweredDevice
{
};

class Scanner : public PoweredDevice
{
};

class Printer : public PoweredDevice
{
};

/// copier has one or two copies of PoweredDevice? - ambiguity
class Copier : public Scanner, public Printer
{
};

int main()
{
    Teacher t{ "Jasmine", 27, "Self", 20.28, 7 };
    
    /// MIxins example
    Button button{};
    button.Box::set_top_left({ 1, 1 });
    button.Box::set_bottom_right({ 10, 10 });
    button.Label::set_text("Username: ");
    button.Label::set_font_size(6);
    
    /// ambiguity problem here, get_id is contained in both base classes
    WirelessAdapter c23G { 32352, 18934 };
    /*std::cout << c23G.get_id() << '\n';*/
    
    /// way to workaround the amibiguity problem - explicit scoping
    std::cout << c23G.NetworkDevice::get_id() << '\n';
    std::cout << c23G.USBDevice::get_id() << '\n';
    
    
    
    return 0;
}
