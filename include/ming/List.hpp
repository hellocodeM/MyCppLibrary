#ifndef MING_CONTAINER_LIST_HPP
#define MING_CONTAINER_LIST_HPP

#include <list>

#include "Iterable.hpp"
#include "ParallelList.hpp"

namespace ming {
namespace container {

template <class T>
class List: public std::list<T>, public Iterable<List<T>> {
    public:

    using std::list<T>::list;
    using base = std::list<T>;
    using iterable = Iterable<List<T>>;

    /**
     * Used for obtain another container with type U.
     */
    template <class U>
    struct container {
        using type = List<U>;
    };

    /**
     * Parallelly
     */
    ming::ParallelList<T> par() const {
        return ming::ParallelList<T>(*this);
    }

};


} /* end of namespace ming::container */

using container::List;
} /* end of namespace ming */
#endif 
