#ifndef MING_CONTAINER_VECTOR_HPP
#define MING_CONTAINER_VECTOR_HPP

#include <vector>
#include <type_traits>
#include <algorithm>
#include <functional>

#include "placeholders.hpp"
#include "Iterable.hpp"

namespace ming {
namespace container {

namespace ph = ming::placeholders;

template <class T>
class vector: public std::vector<T>, public Iterable<T, vector<T>>{
    public:
    using std::vector<T>::vector;
};


/**
 * Helper function to create a range vector.
 */
template <class T = vector<int>>
T range(int from, int to) {
    T res(to - from);
    std::iota(res.begin(), res.end(), from);
    return res;
}

/**
 * Overloading for operator +, which could append a item after the vector, and return the new vector.
 */
template <class T>
vector<T> operator + (const vector<T>& vec, const T& item) {
    vector<T> res = vec;
    res.push_back(item);
    return res;
}

template <class T>
vector<T> operator + (const T& item, const vector<T>& vec) {
    return std::forward<T>(vec) + item;
}

template <class T>
auto operator + (vector<T>&& vec, T&& item) {
    vector<T> res = std::forward<vector<T>>(vec);
    res.push_back(item);
    return std::forward<vector<T>>(res);
}

template <class T>
auto operator + (T&& item, vector<T>&& vec) {
    return std::forward<vector<T>>(vec) + std::forward<T>(item);
}

} /* end of namespace ming::container */

using container::vector;
using container::range;
} /* end of namespace ming */

#endif
