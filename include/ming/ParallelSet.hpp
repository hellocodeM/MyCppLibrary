#ifndef MING_CONTAINER_PARALLEL_SET_HPP
#define MING_CONTAINER_PARALLEL_SET_HPP

#include <set>

#include "ParallelIterable.hpp"

namespace ming {
namespace container {

template <class T>
class ParallelSet: public std::set<T>, public ming::ParallelIterable<ParallelSet<T>> {
    
    public:
    using std::set<T>::set;
    using base = std::set<T>;
    using iterable = ming::ParallelIterable<ParallelSet<T>>;

    /**
     * Userd for creating another container with type U.
     */
    template <class U>
    struct container {
        using type = ParallelSet<U>;
    };
};
} /* end of namespace ming::container */

using container::ParallelSet;
} /* end of namespace ming */
#endif
