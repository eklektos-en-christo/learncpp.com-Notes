//
//  main.cpp
//  28.1_input.and.output.streams
//
//  Created by Εκλεκτός εν Χριστώ on 12/9/23.
//

/*
 IO functionality is not defined as part of the core C++ but it is rather provided through the C++ STD lib.
 
 IO functionality resides in std namespace
 
 When the iostream header is included, you gain access to a whole hierarchy of classes responsible for
 providing the IO functionality, this hierarchy used multiple inheritance
 
 -----------------------------------------------------------------------------------------------------------
 STREAMS:
 
 IO in C++ is implemented with streams
 
 Stream - is just a sequence of bytes that can be accessed sequentially, overtime a stream may consume or
 produce potentially unlimited amounts of data
 
 Types of streams:
 - Input streams
 - Output streams
 
 Input streams: are used to hold input from a data producer, like from a keyboard, file or network etc. A
 user may press a key on the keyboard while the program is currently not expecting any input, rather than
 ignoring the keypresses, the data is put into an input stream, where it will wait until the program is
 ready for it
 
 Output streams: are used to hold output for a particular data consumer, such as a monitor, file or a
 printer, when writing data to an output device, they device may not be ready to accept that data yet, the
 printer may still be warming up when the program writes data to its output stream, the data will sit in
 the output stream until the printer begins consuming it
 
 Some devices are capable of being both input and output sources, like file or network.
 
 Programmer only has to learn how to interact with the streams in order to read and write data to many
 different kinds of devices
 
 -----------------------------------------------------------------------------------------------------------
 IO in C++ -
 
 ios : a typedef for std::basic_ios<char>, it defines a bunch of stuff that is common to both input and
 output streams
 
 istream - primary class, used when dealing with input streams, extraction operator(>>) is used to remove
 values from the input streams, when the key is pressed on a keyboard, the key code is placed in an input
 stream, then program extracts the value from the stream so it can be used
 
 ostream - primary class, used when dealing with output streams, insertion operator(<<) is used to put
 values in the output streams, user insert the values into the stream and the data consumer used them, e.g.
 a monitor
 
 iostream - class can handle both input and output, bidirectional IO
 
 -----------------------------------------------------------------------------------------------------------
 STANDARD STREAMS IN C++:
 
 A standard stream is a pre-connected stream provided to a computer program by its environment, these are
 input output channels provided by the C++
 
 C++'s pre-defined standard streams:
 
 cin - an istream object, tied to the standard input, typically the keyboard
 cout - an ostream object, tied to the standard output, typically the monitor
 cerr - an ostream object, tied to the standard error, typically the monitor, provides unbuffered output
 clog - an ostream object, tied to the standard error, typically the monitor, provides buffered output
 
 Unbuffered output: typically handled immediately
 
 Buffered output: typically stored and written out as a block, clog isn't used very often
 
 -----------------------------------------------------------------------------------------------------------
 */

#include <iostream>

int main()
{
    return 0;
}
