#ifndef MING_UTIL_TESTCASE_HPP
#define MING_UTIL_TESTCASE_HPP

#include "printf.hpp"

namespace ming {
namespace PP {

#define Test \
    ming::printf("test: %\n", __func__); 

#define TestBlock
        
}
} /* end of namespace ming::PP */
#endif
