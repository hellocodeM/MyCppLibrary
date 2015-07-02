#ifndef MING_EXECTIME_HPP
#define MING_EXECTIME_HPP

#include <ctime>
namespace ming { 
namespace time { 

/**
 * @desc: Compute the execution(CPU) time of a function.
 * @para: A function.
 * @ret : Execution time in millisecond.
 */
template <class FN>
long ExecTime_(FN f) {
    clock_t start = clock();
    f();
    clock_t end = clock();
    return 1000 * (end - start) / CLOCKS_PER_SEC;
}

#define ExecTime(cmd) \
    ming::time::ExecTime_([&]{ \
        cmd; \
    })

} /* end of namespace ming::time */
} /* end of namespace ming */

#endif 
