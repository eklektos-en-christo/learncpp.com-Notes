//
//  main.cpp
//  10.5_intro.to.structs.members.and.member.selection
//
//  Created by Εκλεκτός εν Χριστώ on 3/6/23.
//

/*
 Two compound types designed to group all of the related pieces of data together:
 -structs
 -classes
 
 struct(short for structure) - program-defined data type, allows us to bundle multiple
 variables together into a single type, this makes management of related sets of
 variables much simpler
 
 struct - program-defined data type, so definition is required first for the compiler to
 tell what our struct type looks like before we can begin using it
 
 struct - keyword, used to tell the compiler that we're defining a struct, then followed by
 the name, name typically starts with a capital letter, then inside the pair of curly
 braces we define the variables that each object will contain
 
 data members/data variables - the variables that are part of the struct are called
 data members
 
 In common language - member is a individual who belongs to a group
 
 In CPP - a member is a variable, function or type that belongs to a struct or class
 
 All members : must be declared within the struct or class definition
 
 term member : is used a lot
 
 empty set of curly braces used - to value initialize normal variables
 
 empty set of curly braces after each member variable - ensures that the member variables
 inside our struct/class are value initialized when object or struct/class is created
 
 semicolon : type definition must end up with a semicolon, common error
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Defining struct objects:
 to use the struct type - we simply define a variable of type struct
 at the definition of variable - object is created
 in the object - data members are created in sequential order
 after the creation of all data members - they all are value initialized, if {} was used
 
 like any other type - it is possible to define multiple variables of the same struct type
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Accessing members:
 member selection operator - in an entire object that contains member variables, if we want
 to access a specific member variable, we use operator. in between the struct variable name
 and the member name
 
 . - operator, member selection operator
 
 example - if we want to access nick's age, we'd use : nick.age
 
 struct member variables - works just like normal variables, it is possible to do normal
 operations on them, including assignment, arithmetic, comparison etc..
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Biggest advantages of structs:
 -we only need to create one new name per struct variable, the member names are fixed as
 part of the struct type definition
 */

#include <iostream>

/// defining a structure
struct Employee
{
    /// 3 data members/variables
    /// all are value initialized using {}
    int id{};
    int age{};
    double wage{};
};

int main()
{
    /// defined a variable nick of type Employee
    /// at the definition of variable - object is created
    /// in the object - 3 data members are created in sequential order
    /// after the creation of all data members - they all are value initialized
    /// it is possible - to define multiple variables of the same struct type
    Employee nick;
    
    /// . - member selection operator used to select the age member of variable nick
    nick.age = 40;
    
    /// printing the age member of variable nick using operator.
    std::cout << nick.age << '\n';
    
    /// Employee object : joe
    Employee joe;
    joe.id = 11;
    joe.age = 33;
    joe.wage = 80000.0;
    
    /// Employee object : frank
    Employee frank;
    frank.id = 113;
    frank.age = 48;
    frank.wage = 52000.0;
    
    /// arithmetic operation on member variables
    int total_age{joe.age + frank.age};
    std::cout << "joe's + frank's age: " << total_age << '\n';
    
    /// comparison operation
    if (joe.wage > frank.wage)
        std::cout << "Joe is richer than frank\n";
    else if (joe.wage < frank.wage)
        std::cout << "Joe makes less than frank\n";
    else
        std::cout << "Joe and frank make the same amount\n";
    
    /// frank got a promotion
    /// assignment operation
    frank.wage += 20000.0;
    std::cout << frank.wage << '\n';
    
    /// assignment operation
    /// today is joe's birthday
    ++joe.age;
    std::cout << joe.age << '\n';
    
    return 0;
}
