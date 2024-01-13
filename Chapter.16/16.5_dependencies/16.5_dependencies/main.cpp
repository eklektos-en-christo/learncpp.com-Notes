//
//  main.cpp
//  16.5_dependencies
//
//  Created by Εκλεκτός εν Χριστώ on 7/29/23.
//

/*
 -------------------------------------------------------------------------------------------
 Term "dependency" - to indicate that an object is reliant upon another object for a given
 task.
 
 Flowers are dependent upon bees to pollinate them, in order to grow fruit or propagate.
 
 DEPENDENCY: occurs when one object invokes another object's functionality in order to
 accomplish some specific task.
 
 Dependency: is a weaker relationship than an association, but still, any change to object
 being depended upon may break functionality in the dependent object(caller)
 
 Dependency: is always unidirectional relationship
 
 Example: std::ostream, classes that use std::ostream use it in order to accomplish the task
 of printing something to the console, but not otherwise
 
 -------------------------------------------------------------------------------------------
 DEPENDENCIES VS. ASSOCIATIONS IN C++:
 
 Associations: are a relationship between two classes at the class level, one class keeps a
 direct or indirect link to the associated class as a member.
 
 Dependencies: typically are not represented at the class level, the object being depended
 on is not linked as a member. Rather the object being depended on it typically instantiated
 as needed, like opening a file to write data to, or passed into a function as a parameter.
 
 -------------------------------------------------------------------------------------------
 */

#include <iostream>

class Point
{
private:
    double m_x{};
    double m_y{};
    double m_z{};
    
public:
    Point(double x=0.0, double y=0.0, double z=0.0)
    : m_x{ x }, m_y{ y }, m_z{ z }
    {
    }
    
    /// Point has a dependency on std::ostream here
    /// Point isn't directly related to the std::ostream
    friend std::ostream& operator<<(std::ostream& out, const Point& point)
    {
        out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ')';
        return out;
    }
};

int main()
{
    Point point1{ 2.1, 6.8, 4.9};
    
    /// the program has a dependency on std::out here
    std::cout << point1 << '\n';
    
    return 0;
}
