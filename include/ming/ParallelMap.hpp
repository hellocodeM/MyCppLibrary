#ifndef MING_CONTAINER_PARALLEL_MAP_HPP
#define MING_CONTAINER_PARALLEL_MAP_HPP

#include <map>

#include "ParallelIterable.hpp"

namespace ming {
namespace container {

template <class T>
class ParallelMap: public std::map<typename T::first_type, typename T::second_type>, 
                   public ming::ParallelIterable<ParallelMap<T>> {
    
    public:
    using first_type = typename T::first_type;
    using second_type = typename T::second_type;
    using std::map<first_type, second_type>::map;
    using base = std::map<first_type, second_type>;
    using iterable = ming::ParallelIterable<ParallelMap<T>>;

    /**
     * Userd for creating another container with type U.
     */
    template <class U>
    struct container {
        using type = ParallelMap<U>;
    };

};
} /* end of namespace ming::container */

using container::ParallelMap;
} /* end of namespace ming */
#endif
