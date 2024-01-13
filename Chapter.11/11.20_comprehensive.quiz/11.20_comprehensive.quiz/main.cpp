//
//  main.cpp
//  11.20_comprehensive.quiz
//
//  Created by Εκλεκτός εν Χριστώ on 6/4/23.
//

/*
 SUMMARY:
 
 Arrays allow us to store and access many variables of the same type through a single identifier.
 
 Array elements can be accessed using the subscript operator ([]).
 
 Arrays can be initialized using an initializer list or uniform initialization.
 
 Fixed arrays must have a length that is set at compile time
 
 Fixed arrays will usually decay into a pointer when evaluated or passed to a function.
 
 Loops can be used to iterate through an array.
 
 Range-based for-loops are useful when the array hasn’t decayed into a pointer.
 
 Arrays can be made multidimensional by using multiple indices.
 
 Arrays can be used to do C-style strings.
 
 You should generally avoid these and use std::string_view and std::string instead.
 
 Pointers are variables that store the memory address of (point at) another variable.
 
 The address-of operator (&) can be used to get the address of a variable.
 
 The indirection operator (*) can be used to get the value that a pointer points at.
 
 A null pointer is a pointer that is not pointing at anything.
 
 Pointers can be made null by initializing or assigning the value nullptr to them.
 
 Avoid the NULL macro.
 
 Indirection through a null pointer can cause bad things to happen.
 
 Deleting a null pointer is okay (it doesn’t do anything).
 
 A pointer to an array doesn’t know how large the array it is pointing to is.
 
 This means sizeof() and range-based for-loops won’t work.
 
 The new and delete operators can be used to dynamically allocate memory for a pointer variable or array.
 
 If you’re writing software for a memory-limited system, make sure to check if new was successful.
 
 Make sure to use the array delete (delete[]) when deleting an array.
 
 Pointers pointing to deallocated memory are called dangling pointers.
 
 Using the wrong delete, or indirection through a dangling pointer causes undefined behavior.
 
 Failing to delete dynamically allocated memory can result in memory leaks when the last pointer to that
 memory goes out of scope.
 
 Normal variables are allocated from limited memory called the stack.
 
 Dynamically allocated variables are allocated from a general pool of memory called the heap.
 
 A pointer to a const value treats the value it is pointing to as const.
 
 A const pointer is a pointer whose value can not be changed after initialization.
 
 A reference is an alias to another variable.
 
 References are declared using an ampersand (&), but this does not mean address-of in this context.
 
 References are implicitly const
 
 they must be initialized with a value, and a new value can not be assigned to them.
 
 References can be used to prevent copies from being made when passing data to or from a function.
 
 The member selection operator (->) can be used to select a member from a pointer to a struct.
 
 it combines both an indirection and normal member access (.)
 
 Void pointers are pointers that can point to any type of data.
 
 Indirection through them is not possible directly.
 
 You can use static_cast to convert them back to their original pointer type.
 
 It’s up to you to remember what type they originally were.
 
 Pointers to pointers allow us to create a pointer that points to another pointer.
 
 std::array provides all of the functionality of C++ built-in arrays (and more) in a form that won’t decay
 into a pointer.
 
 These should generally be preferred over built-in fixed arrays.
 
 std::vector provides dynamic array functionality, handles its own memory management and remembers its
 size.
 
 These should generally be favored over built-in dynamic arrays.
 
 Thanks to iterators, we don’t have to know how a container is implemented to loop through its elements.

 The algorithms library helps us to save a lot of time by providing many off-the-shelf functions.
 
 In combination with iterators (and later lambdas), the algorithms library is an important part of C++.
  
 */

/*
 std::reduce - applies a function, by default the + operator, to all elements in a list, resulting in a
 single value
 
 std::accumulate - it applies the function left-to-right.
 
 std::shuffle - takes a list and randomly re-orders its elements.
 */


#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>
#include <random>
#include <ctime>
#include <vector>

enum Item_types
{
    item_health_potion,
    item_torch,
    item_arrow,
    max_items
};

using Inventory = std::array<int, Item_types::max_items>;

int count_total_items(const Inventory& items)
{
    return std::reduce(items.begin(), items.end());
}

struct Student
{
    std::string name{};
    int grade{};
};

int get_no_of_students()
{
    int num_of_students{};
    
    do
    {
        std::cout << "How many students do you want to enter? ";
        std::cin >> num_of_students;
    } while (num_of_students <= 0);
    
    return num_of_students;
}

std::vector<Student> get_students()
{
    using Students = std::vector<Student>;
    
    int num_of_students{ get_no_of_students() };
    
    Students students(static_cast<Students::size_type>(num_of_students));
    
    int student_number{ 1 };
    
    for (auto& student : students)
    {
        std::cout << "Enter name #" << student_number << ": ";
        std::cin >> student.name;
        std::cout << "Enter grade #" << student_number << ": ";
        std::cin >> student.grade;
        
        ++student_number;
    }
    
    return students;
}

bool compare_students(const Student& a, const Student& b)
{
    return (a.grade > b.grade);
}

void swap(int& a, int& b)
{
    int temp{ a };
    
    a = b;
    
    b = temp;
}

void print_cstring(const char* str)
{
    while (*str != '\0')
    {
        std::cout << *str << '\n';
        ++str;
    }
}

int main()
{
    std::array A{ 1, 2, 3, 4 };
    
    std::cout << "Reduce: " << std::reduce(A.begin(), A.end()) << '\n';
    
    /// 0 - initial sum
    std::cout << "Accumulate: " << std::accumulate(A.begin(), A.end(), 0) << '\n';
    
    std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    
    std::shuffle(A.begin(), A.end(), mt);
    
    for (int i : A)
        std::cout << i << ' ';
    std::cout << '\n';
    
    Inventory items{ 2, 5, 10};
    
    std::cout << "The player has: " << count_total_items(items) << " items(s) in total.\n";
    
    std::cout << "The player has: " << items[Item_types::item_torch] << " torch(es).\n";
    
    auto students{ get_students() };
    
    std::sort(students.begin(), students.end(), compare_students);
    
    for (const auto& student : students)
        std::cout << student.name << " got a grade of " << student.grade << '\n';
    
    int a{ 10 };
    int b{ 20 };
    
    swap(a, b);
    
    std::cout << a << ' ' << b << '\n';
    
    print_cstring("Hello, World!");
    
    return 0;
}
