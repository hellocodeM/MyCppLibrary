#ifndef MING_CONTAINER_VECTOR_HPP
#define MING_CONTAINER_VECTOR_HPP

#include <vector>

#include "Iterable.hpp"
#include "HasMethod.hpp"
#include "has_iterator.hpp"
#include "underlying.hpp"
#include "ParallelVector.hpp"

namespace ming {
namespace container {

template <class T>
class Vector: public std::vector<T>, public Iterable<Vector<T>>{
    public:
    using std::vector<T>::vector;
    using base = std::vector<T>;
    using iterable = Iterable<Vector<T>>;

    /**
     * Used for obtain another container with type U.
     */
    template <class U>
    struct container {
        using type = Vector<U>;
    };

    /**
     * Parallelly
     */
    ming::ParallelVector<T> par() const {
        return ParallelVector<T>(base::begin(), base::end());
    }
};

} /* end of namespace ming::container */

using container::Vector;
} /* end of namespace ming */

#endif
