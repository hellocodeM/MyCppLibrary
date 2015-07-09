#ifndef MING_CONTAINER_PARALLEL_VECTOR_HPP
#define MING_CONTAINER_PARALLEL_VECTOR_HPP

#include <vector>

#include "Vector.hpp"
#include "ParallelIterable.hpp"

namespace ming {
namespace container {

template <class T>
class ParallelVector: public std::vector<T>, public ming::ParallelIterable<ParallelVector<T>> {
    
    public:
    using std::vector<T>::vector;
    using base = std::vector<T>;
    using iterable = ming::ParallelIterable<ParallelVector<T>>;

    /**
     * Userd for creating another container with type U.
     */
    template <class U>
    struct container {
        using type = ParallelVector<U>;
    };

};
} /* end of namespace ming::container */

using container::ParallelVector;
} /* end of namespace ming */
#endif
