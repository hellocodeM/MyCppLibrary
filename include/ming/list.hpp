#ifndef MING_CONTAINER_LIST_HPP
#define MING_CONTAINER_LIST_HPP

#include <list>

#include "Iterable.hpp"

namespace ming {
namespace container {

template <class T>
class list: public std::list<T>, public Iterable<list<T>> {
    public:

    using std::list<T>::list;
    using base = std::list<T>;
    using iterable = Iterable<list<T>>;

    /**
     * Used for obtain another container with type U.
     */
    template <class U>
    struct container {
        using type = list<U>;
    };
};


} /* end of namespace ming::container */

using container::list;
} /* end of namespace ming */
#endif 
