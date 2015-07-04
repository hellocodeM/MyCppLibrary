#ifndef MING_CONTAINER_VECTOR_HPP
#define MING_CONTAINER_VECTOR_HPP

#include <vector>
#include <type_traits>
#include <algorithm>
#include <functional>

#include "placeholders.hpp"

namespace ming {
namespace container {

namespace ph = ming::placeholders;


template <class T>
class vector: public std::vector<T> {
    using std::vector<T>::vector;
    using base = typename std::vector<T>;

    public:
    template <class Init, class Fn, class Pred>
    auto fold_if(Init&& init, Fn f, Pred pred) {
        for (auto i = base::begin(); i != base::end(); ++i) {
            if (pred(*i))
                init = f(std::forward<Init>(init), *i);
        }
        return init;
    }

    template <class Init, class Fn>
    auto fold(Init&& init, Fn f) {
        return fold_if(std::forward<Init>(init), f, [](auto&& x){ return true;});
    }

    template <class Fn>
    void foreach(Fn f) {
        std::for_each(base::begin(), base::end(), f);
    }

    template <class Fn>
    auto map(Fn f) {
        return fold(vector<typename base::value_type>(), [f](auto&& init, auto&& item) {
            init.push_back(f(item));
            return std::forward<decltype(init)>(init);
        });
    }

    template <class Fn>
    auto filter(Fn f) {
        return fold_if(vector<typename base::value_type>(), [f](auto&& init, auto&& item) {
            init.push_back(item);
            return std::forward<decltype(init)>(init);
        }, f);
    }

    auto take(size_t n) {
        const size_t copy_cnt = std::min(n, base::size());
        vector<typename base::value_type> res(copy_cnt);
        std::copy_n(base::begin(), copy_cnt, res.begin());
        return res;
    }
};


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
} /* end of namespace ming */

#endif