#ifndef MING_CONTAINER_ITERABLE_HPP
#define MING_CONTAINER_ITERABLE_HPP

#include <utility>
#include <algorithm>
#include <iterator>

#include "printf.hpp"
#include "ParallelIterable.hpp"

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
                init = std::move(f(std::forward<Init>(init), i));
        }
        return std::forward<Init>(init);
    }


    template <class Init, class Fn>
    constexpr auto fold(Init&& init, Fn f) {
        return derived->fold_if(std::forward<Init>(init), f, [](auto&& x){ return true; });
    }


    template<class Fn>
    constexpr auto map(Fn f) {
        using result_type = decltype(f(head()));
        using container_type = typename Derived::template container<result_type>::type;
        return derived->fold(container_type(), [f](auto&& init, auto&& item) {
            init += f(std::forward<decltype(item)>(item));
            return std::forward<decltype(init)>(init);
        });
    }

    template <class Fn>
    constexpr auto filter(Fn f) {
        return derived->fold_if(Derived(), [](auto&& init, auto&& item) {
            init += std::forward<decltype(item)>(item);
            return std::forward<decltype(init)>(init);
        }, f);
    }

    template <class Fn>
    void foreach(Fn f) {
        for (auto&& i: *derived)
            f(std::forward<decltype(i)>(i));
    }

    constexpr auto take(size_t n) const {
        const size_t copy_cnt = std::min(n, derived->size());
        auto iter_end = std::next(derived->begin(), copy_cnt);
        Derived res(derived->begin(), iter_end);
        return res;
    }

    constexpr auto head() const {
        return *(derived->begin());
    }

    constexpr auto tail() const {
        auto iter_begin = std::next(derived->begin());
        Derived res(iter_begin, derived->end());
        return res;
    }

    private:
    Derived* derived;
};
} /* end of namespace ming::container */

using container::Iterable;
} /* end of namespace ming */
#endif
