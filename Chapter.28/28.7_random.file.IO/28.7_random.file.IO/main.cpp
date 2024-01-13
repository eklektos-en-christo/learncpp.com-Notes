//
//  main.cpp
//  28.7_random.file.IO
//
//  Created by Εκλεκτός εν Χριστώ on 12/14/23.
//

/*
 -----------------------------------------------------------------------------------------------------------
 The file pointer: each file stream class contains a file pointer, used to keep track of the current R/W
 position within the file, R/W happens at the pointer's current location, if file is opened in append mode,
 then the pointer moves to the end of the file to avoid the overwriting of previous contents of the file
 
 -----------------------------------------------------------------------------------------------------------
 RANDOM FILE ACCESS WITH seekg() AND seekp():
 
 it is done by manipulating the file pointer using either seekg(for input) and seekp(for output), g for get
 and p for put, seekg and seekp operate independently for some types of streams, the R/W positions are
 always identical for file streams, so seekg and seekp can be used interchangeably
 
 seekg, seekp - take two parameters
 first param - is an offset, it determines how many bytes to move the file pointer
 second param - is an ios flag, it specifies what the offset parameter should be offset from
 
 ios seek flags:
 beg - the offset is relative to the beginning of the file(default)
 cur - the offset is relative to the current location of the file pointer
 end - the offset is relative to the end of the file
 
 positive offset - means move the file pointer towards the end of the file
 negative offset - means move the file pointer towards the beginning of the file
 
 examples:
 inf.seekg(14, std::ios::cur)   - means to move file pointer forward 14 bytes from current position
 inf.seekg(-22, std::ios::cur) - move backwards 22 bytes from current position
 inf.seekg(22, std::ios::beg) - move to 22nd byte from the beginning
 inf.seekg(20) - move to 20th byte from the beginning, beginning is default ios seek flag here
 inf.seekg(-30, std::ios::end) - move to 30th byte from the end, backward moving
 inf.seekg(0, std::ios::beg) - move to the beginning of the file
 inf.seekg(0, std::ios::end) - move to the end of the file
 
 tellg & tellp - they return the absolute position of the pointer, it is helpful in calculating the size of
 the file
 
 On windows - a newline is represented as sequential carriage return and line feed, thus taking 2 bytes of
 storage
 
 On unix - newline is represented as line feed, so taking 1 byte
 
 -----------------------------------------------------------------------------------------------------------
 Reading and writing a file at the same time using fstream:
 
 fstream - is almost capable of both reading and writing a file at the same time, it is not possible to
 switch between reading and writing arbitrarily, once a read or write has taken place, then the only way to
 switch between the two is to perform an operation that modifies the file position e.g. a seek
 
 iofile.seekg(iofile.tellg(), std::ios::beg); // seek to current file position, if you don't do this, any
 number of bizarre things may occur
 
 to delete a file, use the remove() function
 
 Warning:
 Do not write memory addresses to file, the variables that were originally at those addresses may be at
 different addresses when you read their values back in from disk and the addresses will be invalid
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ofstream output_file{ "output_file.txt" };
    output_file << "This is line 1\n";
    output_file << "This is line 2\n";
    output_file << "This is line 3\n";
    output_file << "This is line 4\n";
    output_file.close();                /// needed here, because data is still in buffer, so flush it to the file
    
    std::ifstream input_file{ "output_file.txt" };
    
    if (!input_file)
        std::cerr << "input file couldn't not be opened\n";
    
    std::string str_data;
    
    /// go to the 8th character, then read the whole line and print it
    input_file.seekg(8);
    std::getline(input_file, str_data);
    std::cout << str_data << '\n';
    
    /// skip from current position to 23rd character, then print the line
    input_file.seekg(23, std::ios::cur);
    std::getline(input_file, str_data);
    std::cout << str_data << '\n';
    
    /// read from 15th character before the  end of the file
    input_file.seekg(-15, std::ios::end);
    std::getline(input_file, str_data);
    std::cout << str_data << '\n';
    
    /// starting from the beginning of the file
    input_file.seekg(0, std::ios::beg);
    std::getline(input_file, str_data);
    std::cout << input_file.tellg() << '\n';    /// tellg returning the absolute position of the pointer
    std::getline(input_file, str_data);
    std::cout << input_file.tellg() << '\n';
    std::getline(input_file, str_data);
    std::cout << input_file.tellg() << '\n';
    std::getline(input_file, str_data);
    std::cout << input_file.tellg() << '\n';    /// total size of the file is 60 bytes
    
    /// in case of fstream , we need to specify both in and out file modes
    std::fstream iofile{ "output_file.txt", std::ios::in | std::ios::out };
    
    /// if we couldn't open the file
    if (!iofile)
    {
        std::cout << "output_file.txt couldn't be opened\n";
        return 1;
    }
        
    char ch{};
    
    /// change any vowels found in the file to a '*' symbol
    /// get returns the current character which is boolean true when evaluated
    /// when EOF is returned, condition becomes false and loop stops
    while (iofile.get(ch))
    {
        switch (ch)
        {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
            case 'A':
            case 'E':
            case 'I':
            case 'O':
            case 'U':
                
                /// temporarily move the pointer to back up one character
                /// when iofile.get was executed, the file pointer moved forward one character, so move back to update the char with '*'
                iofile.seekg(-1, std::ios::cur);
                iofile << '*';
                /// seek to the current location of file pointer, don't move the file pointer
                /// move to the current byte from the beginning
                /// tellg - get the current position, seekg - set the position to tellg
                iofile.seekg(iofile.tellg(), std::ios::beg);
                break;
        }
    }
    
    /// delete the specified file
    /*std::remove("output_file.txt");*/
    
    return 0;
}
