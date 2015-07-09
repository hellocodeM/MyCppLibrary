#ifndef MING_CONTAINER_PARALLEL_LIST_HPP
#define MING_CONTAINER_PARALLEL_LIST_HPP

#include <list>

#include "List.hpp"
#include "ParallelIterable.hpp"

namespace ming {
namespace container {

template <class T>
class ParallelList: public std::list<T>, public ming::ParallelIterable<ParallelList<T>> {
    public:
    using std::list<T>::list;
    using base = std::list<T>;
    using iterable = ming::ParallelIterable<ParallelList<T>>;

    /**
     * User for creating another container with type U.
     */
    template <class U>
    struct container {
        using type = ParallelVector<U>;
    };
};


} /* end of namespace ming::container */

using container::ParalleList;
} /* end of namespace ming */
#endif 
