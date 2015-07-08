#ifndef MING_EXECTIME_HPP
#define MING_EXECTIME_HPP

#include <ctime>
#include <chrono>

namespace ming { 
namespace time { 

/**
 * @desc: Compute the execution(CPU) time of a function.
 * @para: A function.
 * @ret : Execution time in milliseconds.
 */
template <class FN>
long ExecutionTime_(FN f) {
    clock_t start = clock();
    f();
    clock_t end = clock();
    return 1000 * (end - start) / CLOCKS_PER_SEC;
}

/**
 * @desc: Compute the duration of a function.
 * @para: A function.
 * @return: in milliseconds.
 */
template <class FN>
long DurationTime_(FN f) {
    using namespace std::chrono;
    auto start(steady_clock::now());
    f();
    auto end(steady_clock::now());
    return duration_cast<milliseconds>(end - start).count();
}

#define ExecutionTime(cmd) \
    ming::time::ExecutionTime_([&]{ \
        cmd; \
    })

#define DurationTime(cmd) \
    ming::time::DurationTime_([&]{ \
        cmd; \
    })

} /* end of namespace ming::time */
} /* end of namespace ming */

#endif 
