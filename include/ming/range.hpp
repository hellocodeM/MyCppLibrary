#ifndef MING_CONTAINER_RANGE_HPP
#define MING_CONTAINER_RANGE_HPP

#include "vector.hpp"

namespace ming {
namespace container {

/**
 * Helper function to create a range vector.
 */
template <class T = vector<int>>
T range(int from, int to, int step = 1) {
    T res;
    while (from < to) {
        res.add(from);
        from += step;
    }
    return res;
}

} /* end of namespace ming::container */

using container::range;
} /* end of namespace ming */
#endif
