#ifndef MING_CONTAINER_PARALLEL_MAP_HPP
#define MING_CONTAINER_PARALLEL_MAP_HPP

#include <map>

#include "ParallelIterable.hpp"
#include "is_pair.hpp"
#include "ParallelVector.hpp"

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

    /**
     * Specialization for map method
     */
    template <class Fn>
    constexpr auto map(Fn f) {
        using namespace ming::placeholders;
        using result_type = decltype(f(iterable::head()));
        using container_type = std::conditional_t<
                                    ming::is_pair<result_type>::value, 
                                    ParallelMap<result_type>, 
                                    ParallelVector<result_type> 
                                >;
        return iterable::fold_if(container_type(), [f](auto&& init, auto&& elem) {
                init += f(std::forward<decltype(elem)>(elem));
                return init;
        }, [](auto&& x) { return true; }, _ + _);
    }

};
} /* end of namespace ming::container */

using container::ParallelMap;
} /* end of namespace ming */
#endif
