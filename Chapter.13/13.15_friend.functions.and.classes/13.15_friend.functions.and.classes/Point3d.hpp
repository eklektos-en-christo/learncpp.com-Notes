//
//  Point3d.hpp
//  13.15_friend.functions.and.classes
//
//  Created by Εκλεκτός εν Χριστώ on 7/17/23.
//

#ifndef Point3d_hpp
#define Point3d_hpp

class Vector3d;

class Point3d
{
private:
    double m_x {};
    double m_y {};
    double m_z {};
    
public:
    Point3d(double x = 0.0, double y = 0.0, double z = 0.0);
    
    void print() const;
    void move_by_vector(const Vector3d& v);
};

#endif /* Point3d_hpp */
