namespace ming { 
namespace time { 
namespace detail {


template <class FN>
long ExecTime(FN f) {
    clock_t start = clock();
    f();
    clock_t end = clock();
    return 1000 * (end - start) / CLOCKS_PER_SEC;
}

} /* end of namespace ming::time::detail */
} /* end of namespace ming::time */
} /* end of namespace ming */

