#ifndef MING_CONTAINER_LAZYVECTOR_HPP
#define MING_CONTAINER_LAZYVECTOR_HPP

#include <vector>

#include "LazyIterable.hpp"

namespace ming {
namespace container {

template <class T>
class LazyVector: 
    public std::vector<T>, 
    public LazyIterable<LazyVector<T>> {
    public:
    using value_type = T;
    using base = std::vector<T>;
    using iterable = LazyIterable<LazyVector<T>>;
    /* inherit constructor */
    using std::vector<T>::vector;

    template <class U>
    struct container {
        using type = LazyVector<U>;
    };

    private:
};

} /* end of namespace ming::container */
using container::LazyVector;
} /* end of namespace ming */
#endif
