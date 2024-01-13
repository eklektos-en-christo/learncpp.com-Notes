//
//  Vector3d.hpp
//  13.15_friend.functions.and.classes
//
//  Created by Εκλεκτός εν Χριστώ on 7/17/23.
//

#ifndef Vector3d_hpp
#define Vector3d_hpp

#include "Point3d.hpp"

class Vector3d
{
private:
    double m_x{};
    double m_y{};
    double m_z{};
    
public:
    Vector3d(double x = 0.0, double y = 0.0, double z = 0.0);
    
    void print() const;
    friend void Point3d::move_by_vector(const Vector3d& v);
};

#endif /* Vector3d_hpp */
