//
//  main.cpp
//  13.18_timing.your.code
//
//  Created by Εκλεκτός εν Χριστώ on 7/18/23.
//

/*
 -------------------------------------------------------------------------------------------
 Timing the code: to see how long it takes to run, to check which method is more performant
 when using different methods to achieve the same thing
 
 <chrono> - library to timing the code
 
 FEW CAVEATS ABOUT TIMING:
 
 -make sure you're using a release build target not debug build target
 -debug builds typically turn optimization off, that can have a significant impact on result
 
 -timing results will be influenced by other things the system may be doing in background
 -for best results, make sure system isn't doing anything CPU or memory intensive tasks
 
 -measure at least 3 times, if all results are similar, then take average
 -if one or two results aren't similar, run the program few times
 
 -when doing comparison between two sets of code, be wary of what may change between runs
 -that could impact timing
 -randomization can also impact timing
 
 -results are only valid for the machine's architecture, OS, compiler on which the code is
 -run, different results might be seen on other systems that have different strengths and
 -weaknesses
 
 -------------------------------------------------------------------------------------------
 */

/// for std::chrono functions
#include <chrono>
#include <iostream>
#include <algorithm>        /// for std::sort
#include <array>
#include <cstddef>          /// for std::size_t
#include <numeric>          /// for std::iota

const int g_array_elements { 10000 };

class Timer
{
private:
    /// type aliases to make accessing nested type easier
    using Clock = std::chrono::steady_clock;
    using Second = std::chrono::duration<double, std::ratio<1>>;
    
    std::chrono::time_point<Clock> m_beg { Clock::now() };
    
public:
    void reset()
    {
        m_beg = Clock::now();
    }
    
    /// to know how long the program took to run to that point
    double elapsed() const
    {
        return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
    }
};

int main()
{
    std::array<int, g_array_elements> array;
    
    /// fill the array with value 10000 to 1
    std::iota(array.rbegin(), array.rend(), 1);
    
    /// instantiate a timer object or wherever we want to start timing
    Timer t;
    
    /*std::ranges::sort(array); // Since C++20*/
    std::sort(array.begin(), array.end());
    
    /// to know how long the program took to run to that point
    std::cout << "Time elapsed: " << t.elapsed() << " seconds.\n";
    
    return 0;
}
