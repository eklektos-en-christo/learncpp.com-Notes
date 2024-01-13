//
//  main.cpp
//  14.4_association
//
//  Created by Εκλεκτός εν Χριστώ on 7/28/23.
//

/*
 -------------------------------------------------------------------------------------------
 Object composition: used to model relationships where a complex object is built from one
 or more simpler objects/parts.
 
 In Association: a weaker type of relationship between two otherwise unrelated objects
 
 In Association: there is no implied whole/part relationship.
 
 -------------------------------------------------------------------------------------------
 ASSOCIATION:
 
 To qualify as an association, an object and another object must have the following
 relationship:
 
 - the associated object/member is otherwise unrelated to the object/class
 - the associated object/member can belong to more than one object/class at a time
 - the associated object/member doesn't have it's existence managed by the object/class
 - the associated object/member may or may not know about the existence of the object/class
 
 Composition or aggregation: where the part is a part of the whole object
 
 Association: the associated object is otherwise unrelated to the object
 
 Aggregation: the associated object can belong to the multiple objects simultaneously and is
 not managed by those objects
 
 Association: the relationship may be unidirectional or bidirectional, where two objects are
 aware of each other
 
 Example: Doctor and patient relationship, doctor clearly has a relationship with his
 patients, but conceptually it's not a part/whole relationship. A doctor can see many
 patients in a day, and a patient can see many doctors. Neither of the object's lifespans
 are tied to the other.
 
 Association: models a "uses-a" relationship. The doctor "uses" the patient to earn income.
 The patient uses the doctor for health benefits.
 
 -------------------------------------------------------------------------------------------
 IMPLEMENTING ASSOCIATIONS: they are broad type of relationship, can be implemented in
 different ways. Most often, they are implemented using pointers, where the object points
 at the associated object.
 
 In general: avoid bi-directional associations if a unidirectional one will do, as they add
 complexity and tend to be harder to write without making errors
 
 -------------------------------------------------------------------------------------------
 REFLEXIVE ASSOCIATION: sometimes objects may have a relationship with other objects of the
 same type. A good example of this is the relationship between a university course and its
 prerequisites which are also university courses.
 
 -------------------------------------------------------------------------------------------
 Associations can be indirect:
 
 We use pointer or references to directly link objects together, however in an association,
 this is not strictly required. Any kind of data that allows you to link two objects
 together suffices.
 
 -------------------------------------------------------------------------------------------
 COMPOSITION VS. AGGREGATION VS. ASSOCIATION SUMMARY: for remembrance
 
 +-----------------------------------------------------------------------------------------+
 |Property                               Composition     Aggregation     Association
 |------------------------------------------------------------------------------------------
 |Relationship type                     Whole/part      Whole/part      Otherwise unrelated
 |
 |Members can belong to multiple classes    No          Yes             Yes
 |
 |Member's existence managed by class       Yes         No              No
 |
 |Directionality                        Unidirectional  Unidirectional  Uni or Bidirectional
 |
 |Relationship verb                     part-of         has-a           Uses-a
 +------------------------------------------------------------------------------------------
 
 -------------------------------------------------------------------------------------------
 */

#include <functional>       /// for reference wrapper
#include <iostream>
#include <string>
#include <vector>

/// Patient is being used in Doctor as a member and as a parameter, so forward declared
class Patient;

class Doctor
{
private:
    std::string m_name{};
    
    /// reference wrapper - to treat the Patient references as assignable and copyable
    std::vector<std::reference_wrapper<const Patient>> m_patient{};
    
public:
    Doctor(const std::string& name) : m_name{ name } {}
    
    void add_patient(Patient& patient);
    
    /// function is implemented below the patient since we need Patient to be defined at that point
    friend std::ostream& operator<<(std::ostream& out, const Doctor& doctor);
    
    const std::string& get_name() const { return m_name; }
};

class Patient
{
private:
    std::string m_name{};
    std::vector<std::reference_wrapper<const Doctor>> m_doctor{};
    
    /// making it private because we don't want the public to use it
    void add_doctor(const Doctor& doctor)
    {
        m_doctor.push_back(doctor);
    }
    
public:
    Patient(const std::string& name) : m_name{ name } {}
    
    /// implemented below to parallel operator<<(std::ostream&, const Doctor&)
    friend std::ostream& operator<<(std::ostream& out, const Patient& patient);
    
    const std::string& get_name() const { return m_name; }
    
    /// Doctor::add_patient as a friend, so it can access private function Patient::add_doctor()
    friend void Doctor::add_patient(Patient& patient);
};

void Doctor::add_patient(Patient& patient)
{
    /// doctor will add this patient
    m_patient.push_back(patient);
    
    /// patient will also add this doctor
    patient.add_doctor(*this);
}

std::ostream& operator<<(std::ostream& out, const Doctor& doctor)
{
    if (doctor.m_patient.empty())
    {
        out << doctor.m_name << " has no patients right now";
        return out;
    }
    
    out << doctor.m_name << " is seeing patients: ";
    for (const auto& patient : doctor.m_patient)
        out << patient.get().get_name() << ' ';
    
    return out;
}

std::ostream& operator<<(std::ostream& out, const Patient& patient)
{
    if (patient.m_doctor.empty())
    {
        out << patient.get_name() << " has no doctors right now";
        return out;
    }
    
    out << patient.m_name << " is seeing doctors: ";
    for (const auto& doctor : patient.m_doctor)
        out << doctor.get().get_name() << ' ';
    
    return out;
}

/// Reflexive association
/// this can lead to a chain of associations
/// a course has a prerequisite, which has a prerequisite etc.
class Course
{
private:
    std::string m_name{};
    const Course* m_prerequisite{};
    
public:
    Course(const std::string& name, const Course* prerequisite=nullptr)
    : m_name{ name }, m_prerequisite{ prerequisite }
    {
    }
};

class Car
{
private:
    std::string m_name{};
    int m_id{};
    
public:
    Car(const std::string& name, int id) : m_name{ name }, m_id{ id } {}
    
    const std::string& get_name() const { return m_name; }
    int get_id() const { return m_id; }
};

/// static array of Cars and a lookup function to retrieve them
/// because it's static, we don't need to allocate an object of type Carlot to use it
class Carlot
{
private:
    static Car s_carlot[4];
    
public:
    /// ensure we don't try to create a Carlot
    Carlot() = delete;
    
    /// lookup function to retrieve the Cars
    static Car* get_car(int id)
    {
        for (int count{ 0 }; count < 4; ++count)
            if (s_carlot[count].get_id() == id)
                return &(s_carlot[count]);
        
        return nullptr;
    }
};

Car Carlot::s_carlot[4]{ { "Prius", 4 }, { "Corolla", 17 }, { "Accord", 84 }, { "Matrix", 62} };

class Driver
{
private:
    std::string m_name{};
    int m_car_id{};         /// associating with the Car by ID rather than pointer
    
public:
    Driver(const std::string& name, int car_id)
    : m_name{ name }, m_car_id{ car_id }
    {
    }
    
    const std::string& get_name() const { return m_name; }
    int get_car_id() const { return m_car_id; }
};

int main()
{
    /// create a Patient outside the scope of the Doctor
    Patient dave{ "Dave" };
    Patient frank{ "Frank" };
    Patient betsy{ "Betsy" };
    
    Doctor james{ "James" };
    Doctor scott{ "Scott" };
    
    james.add_patient(dave);
    
    scott.add_patient(dave);
    scott.add_patient(betsy);
    
    std::cout << james << '\n';
    std::cout << scott << '\n';
    std::cout << dave << '\n';
    std::cout << frank << '\n';
    std::cout << betsy << '\n';
    
    /// Franz is driving the car with ID 17
    Driver d{ "Franz", 17 };
    
    /// get that car from the Carlot
    Car* car{ Carlot::get_car(d.get_car_id()) };
    
    if (car)
        std::cout << d.get_name() << " is driving a " << car->get_name() << '\n';
    else
        std::cout << d.get_name() << " could't find his car\n";
    
    return 0;
}
