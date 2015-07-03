#ifndef MING_UTIL_TESTCASE_HPP
#define MING_UTIL_TESTCASE_HPP

#include "printf.hpp"

#define Test \
    ming::printf("test: %\n", __func__); 
        
#endif
