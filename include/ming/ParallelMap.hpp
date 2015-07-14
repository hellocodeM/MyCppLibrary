#ifndef MING_CONTAINER_PARALLEL_MAP_HPP
#define MING_CONTAINER_PARALLEL_MAP_HPP

#include <map>

#include "ParallelIterable.hpp"

namespace ming {
namespace container {

template <class Pair>
class ParallelMap;

template <class K, class V>
class ParallelMap<std::pair<K, V>>: public std::map<K, V>, 
      public ming::ParallelIterable<ParallelMap<std::pair<K, V>>> {
    
    public:
    using first_type = K;
    using second_type = V;
    using value_type = std::pair<K, V>;
    using base = std::map<first_type, second_type>;
    using iterable = ming::ParallelIterable<ParallelMap<value_type>>;
    /* inherit constructor */
    using std::map<first_type, second_type>::map;

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
