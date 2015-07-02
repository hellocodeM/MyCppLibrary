#ifndef MING_UTIL_TESTCASE_HPP
#define MING_UTIL_TESTCASE_HPP

#include "printf.hpp"

#define TestCase(body) \
    do { ming::printf("test: %\n", __func__); \
         body \
         ming::printf("pass: %\n\n", __func__); \
    } while(0)

#endif
