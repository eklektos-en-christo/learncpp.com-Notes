//
//  0.12_configuring.compiler.choosing.language.standard.cpp
//  Chapter.0
//
//  Created by Judah's Leon on 7/14/22.
//

/*
 Code names for in-progress language standards

 Finalized language standards are named after the years in which they are finalized (e.g. C++17 was finalized in 2017).

 However, when a new language standard is being agreed upon, it’s not clear in what year the finalization will take place. Consequently, in-progress language standards are given code names, which are then replaced by the actual names upon finalization of the standard. For example, C++11 was called c++1x while it was being worked on. You may still see the code names used in places (especially for upcoming version of the language standard, which won’t have a final name yet).
 
 Which language standard should you choose?

 In professional environments, it’s common to choose a language standard that is one or two versions back from the latest standard (e.g. now that C++20 is out, that means C++14 or C++17). This is typically done to ensure the compiler makers have had a chance to resolve defects, and so that best practices for new features are well understood. Where relevant, this also helps ensure better cross-platform compatibility, as compilers on some platforms may not provide full support for newer language standards immediately.

 For personal projects and while learning, there is little downside to choosing the latest finalized standard (as of the time of writing, currently C++20).

 Author’s note

 This website currently targets the C++17 standard, meaning our lessons and examples assume your compiler is C++17 capable. Some C++20 content is optionally available for those with C++20 compatible compilers.

 To take full advantage of all the lesson content, we recommend using the C++20 language standard if your compiler supports it. Using the C++17 language standard will also provide a good experience.

 If your compiler doesn’t support C++17, we recommend upgrading to one that does. If this is not possible for some reason, you will need to skip some newer content, and alter some examples so that they will compile. This should not impact your overall experience too heavily (especially in the early lessons).

 C++14 is the minimum language standard for a decent experience on this site.

 There’s an example at the end of this lesson which you can use to test if you set up your compiler to use C++17 correctly.
 
 https://isocpp.org/std/the-standard
 https://www.open-std.org/jtc1/sc22/wg21/docs/standards
 
 */

#include <array>
#include <iostream>
#include <string_view>
#include <tuple>
#include <type_traits>

namespace a::b::c
{
    inline constexpr std::string_view str{ "hello" };
}

template <class... T>
std::tuple<std::size_t, std::common_type_t<T...>> sum(T... args)
{
    return { sizeof...(T), (args + ...) };
}

int main()
{
    auto [iNumbers, iSum]{ sum(1, 2, 3) };
    std::cout << a::b::c::str << ' ' << iNumbers << ' ' << iSum << '\n';

    std::array arr{ 1, 2, 3 };

    std::cout << std::size(arr) << '\n';

    return 0;
}
