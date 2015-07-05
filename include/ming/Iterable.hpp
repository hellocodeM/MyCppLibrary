#ifndef MING_CONTAINER_ITERABLE_HPP
#define MING_CONTAINER_ITERABLE_HPP

#include <utility>
#include <algorithm>

#include "printf.hpp"

namespace ming {
namespace container {

template <class Derived>
class Iterable {
    public:

    Iterable() {
        derived = static_cast<Derived*>(this);
    }

    Iterable(const Iterable<Derived>& rhs) {
        derived = static_cast<Derived*>(this);
    }

    Iterable(Iterable<Derived>&& rhs) {
        derived = static_cast<Derived*>(this);
    }

    Iterable operator =(const Iterable<Derived>& rhs) {
        derived = static_cast<Derived*>(this);
        return *this;
    }

    Iterable operator = (Iterable<Derived>&& rhs) {
        derived = static_cast<Derived*>(this);
        return *this;
    }


    template <class Init, class Fn, class Pred>
    constexpr auto fold_if(Init&& init, Fn f, Pred pred) {
        for (auto&& i: *derived) {
            if (pred(i))
                init = f(std::forward<Init>(init), i);
        }
        return std::move(init);
    }


    template <class Init, class Fn>
    constexpr auto fold(Init&& init, Fn f) {
        return fold_if(std::forward<Init>(init), f, [](auto&& x){ return true; });
    }

    template <class Fn>
    auto filter(Fn f) {
        return derived->fold_if(Derived(), [](auto&& init, auto&& item) {
                init.push_back(item);
                return std::forward<decltype(init)>(init);
        }, f);
    }

    template <class Fn>
    void foreach(Fn f) {
        for (auto&& i: *derived)
            f(std::forward<decltype(i)>(i));
    }

    private:
    Derived* derived;
};

} /* end of namespace ming::container */
using container::Iterable;
} /* end of namespace ming */

#endif
