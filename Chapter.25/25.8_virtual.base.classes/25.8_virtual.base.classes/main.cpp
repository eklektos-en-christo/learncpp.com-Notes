//
//  main.cpp
//  25.8_virtual.base.classes
//
//  Created by Εκλεκτός εν Χριστώ on 11/4/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 VIRTUAL BASE CLASS:
 
 To share a base class: simply insert a "virtual" keyword in the inheritance list of the derived class
 
 Virtual Base Class: means there is only one base object, the base object is shared between all objects in
 the inheritance tree and it is only constructed once
 
 for the constructor of the most derived class, virtual base classes are always created before non-virtual
 base classes, which ensures all bases get created before their derived classes
 
 In the case below:
 Scanner and printer constructor still have calls to PoweredDevice constructor, when instance of copier is
 created, these constructor calls are simply ignored because copier is responsible for creating the
 PoweredDevice not scanner or printer. if we were to create an instance of Scanner or printer, those
 constructor calls would be used and normal inheritance rules apply
 
 if a class inherits one or more class that have virtual parents, the most derived class is responsible for
 constructing the virtual base class. copier is most derived class and scanner and printer both have a
 virtual base class parent powereddevice, so copier is responsible for creating the powereddevice. this is
 true in single inheritance also
 
 all classes inheriting a virtual base class will have a virtual table, even if they would normally not have
 one otherwise and thus instances of the class will be larger by a pointer
 
 scanner and printer derive virtually from powereddevice, copier will only be one powereddevice subobject
 scanner and printer both need to know how to find that single powereddevice subobject, so they can access
 its members because after all they're derived from it. this is typically done through some virtual table
 magic which essentially stores the offset from each subclass to the powereddevice subobject
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>

class PoweredDevice
{
public:
    PoweredDevice(int power)
    {
        std::cout << "PoweredDevice: " << power << '\n';
    }
};

/// PoweredDevice is a virtual base class now
/// this means there is only one PoweredDevice object
/// this one base object is shared between all objects in the inheritance tree
/// it is only constructed once
class Scanner: virtual public PoweredDevice
{
public:
    Scanner(int scanner, int power)
    : PoweredDevice{ power }        /// this line is required to create Scanner objects, but ignored in this case
    {
        std::cout << "Scanner: " << scanner << '\n';
    }
};

class Printer: virtual public PoweredDevice
{
public:
    Printer(int printer, int power)
    : PoweredDevice{ power }        /// this line is required to create Printer objects, but ignored in this case
    {
        std::cout << "Printer: " << printer << '\n';
    }
};

class Copier: public Scanner, public Printer
{
public:
    /// PoweredDevice is constructed by the Copier class
    /// this is one time when copier is allowed to call a non-immediate parent constructor directly
    Copier(int scanner, int printer, int power)
    : PoweredDevice{ power }, Scanner{ scanner, power }, Printer{ printer, power }
    {
    }
};

int main()
{
    /// the copier is responsible for creating the PoweredDevice
    /// PoweredDevice only gets constructed once
    Copier copier{ 1, 2, 3 };
    
    Scanner scanner{ 1, 2 };
    Printer printer{ 1, 2 };
    
    std::cout << sizeof(scanner) << '\n';
    std::cout << sizeof(printer) << '\n';
    
    return 0;
}
