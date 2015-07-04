#ifndef MING_CONTAINER_ITERABLE_HPP
#define MING_CONTAINER_ITERABLE_HPP

#include <utility>
#include <algorithm>

namespace ming {
namespace container {

template <class T, class Derived>
class Iterable {
    public:

    Iterable() {
        derived = static_cast<Derived*>(this);
    }

    template <class Init, class Fn, class Pred>
    auto fold_if(Init&& init, Fn f, Pred pred) {
        for (auto i : *derived) {
            if (pred(i))
                init = f(std::forward<Init>(init), i);
        }
        return init;
    }

    template <class Init, class Fn>
    auto fold(Init&& init, Fn f) {
        return derived->fold_if(std::forward<Init>(init), f, [](auto&& x){ return true; });
    }

    template <class Fn>
    auto map(Fn f) {
        return derived->fold(Derived(), [f](auto && init, auto&& item) {
                init.push_back(f(item));
                return std::forward<decltype(init)>(init);
        });
    }

    template <class Fn>
    auto filter(Fn f) {
        return derived->fold_if(Derived(), [f](auto&& init, auto&& item) {
                init.push_back(item);
                return std::forward<decltype(init)>(init);
        }, f);
    }

    auto take(size_t n) {
        const size_t copy_cnt = std::min(n, derived->size());
        Derived res(copy_cnt);
        std::copy_n(derived->begin(), copy_cnt, res.begin());
        return res;
    }

    template <class Fn>
    void foreach(Fn f) {
        std::for_each(derived->begin(), derived->end(), f);
    }

    private:
    Derived* derived;
};

} /* end of namespace ming::container */
using container::Iterable;
} /* end of namespace ming */

#endif
