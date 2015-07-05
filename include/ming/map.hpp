#ifndef MING_CONTAINER_MAP_HPP
#define MING_CONTAINER_MAP_HPP

#include <map>
#include <utility>

#include "Iterable.hpp"
#include "is_pair.hpp"
#include "vector.hpp"

namespace ming {
namespace container {

template <class Pair>
class Map;

template <class K, class V>
class Map<std::pair<K, V>>: public std::map<K, V>, public Iterable<Map<std::pair<K, V>>> {
    public:
    using base = std::map<K, V>;
    using std::map<K, V>::map;
    using pair_type = std::pair<K, V>;
    using iterable = Iterable<Map<pair_type>>;
    
    /**
     * Use for create another container with type T, U.
     */
    template <class T, class U>
    struct container {
        using type = Map<std::pair<T, U>>;
    };

    void add(const pair_type& elem) {
        base::insert(elem);
    }

    /**
     * Sepcialization for map method.
     */
    template <class Fn>
    auto map(Fn f) {
        using result_type = decltype(f(iterable::head()));
        using container_type = typename std::conditional<
                                            std::is_pair<result_type>::value, 
                                            Map<result_type>, 
                                            vector<result_type>>::type;
        return iterable::fold(container_type(), [f](auto&& init, auto&& elem) {
                init.add(f(std::forward<decltype(elem)>(elem)));
                return std::forward<decltype(init)>(init);
                });
    }
};

} /* end of namespace ming::container */

using container::Map;
} /* end of namespace ming */
#endif
