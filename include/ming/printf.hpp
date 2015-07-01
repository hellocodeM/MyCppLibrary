#ifndef MING_IO_PRINTF_HPP
#define MING_IO_PRINTF_HPP

#include <iostream>
#include <string>
#include <cstring>

#include "print.hpp"

namespace ming {
namespace IO {
/**
 * @desc: Print several objects to stdout, with a format string.                             
 * @para format: Format string, in which char '%' indicates a obejct.               
 * @exam: ming::printf("my name is %, my age is %, %", "Scooby Doo", "2", Dog("Scooby Doo"));
 */
void printf(const char* format) {
    std::cout << format;
}

template <class T, class ...Args>
void printf(const char* format, T x, Args... args) {
    const char* pos = strchr(format, '%');
    std::cout << std::string(format, pos);
    ming::print(x);
    printf(pos+1, args...);
}

} /* end of namespace ming::IO */

using IO::printf;
} /* end of namespace ming */

#endif 
