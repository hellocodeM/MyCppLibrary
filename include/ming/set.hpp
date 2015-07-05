#ifndef MING_CONTAINER_SET_HPP
#define MING_CONTAINER_SET_HPP

#include <set>

#include "Iterable.hpp"
#include "range.hpp"

namespace ming {
namespace container {

template <class T>
class set: public std::set<T>, public Iterable<set<T>> {
    public:
    using std::set<T>::set;
    using base = std::set<T>;
    using iterable = Iterable<set<T>>;

    /**
     * Used for obtain another container with type U.
     */
    template <class U>
    struct container {
        using type = set<U>;
    };

    /**
     * Add element.
     */
    
    void add(const T& elem) {
        base::insert(elem);
    }
};
} /* end of namespace ming::container */

using container::set;
} /* end of namespace ming */
#endif
