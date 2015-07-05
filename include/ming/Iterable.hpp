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
        return derived->fold_if(std::forward<Init>(init), f, [](auto&& x){ return true; });
    }


    template<class Fn>
    constexpr auto map(Fn f) {
        using item_type = decltype(f(head()));
        using container_type = typename Derived::template container<item_type>::type;
        return derived->fold(container_type(), [f](auto&& init, auto&& item) {
            init.push_back(f(std::forward<decltype(item)>(item)));
            return std::forward<decltype(init)>(init);
            });
    }

    template <class Fn>
    constexpr auto filter(Fn f) {
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

    constexpr auto take(size_t n) const {
        const size_t copy_cnt = std::min(n, derived->size());
        Derived res(copy_cnt);
        std::copy_n(derived->begin(), copy_cnt, res.begin());
        return std::move(res);
    }

    constexpr auto head() const {
        return derived->front();
    }

    constexpr auto tail() const {
        Derived res(derived->size() - 1);
        std::copy(std::next(derived->begin()), derived->end(), res.begin());
        return std::move(res);
    }

    private:
    Derived* derived;
};

} /* end of namespace ming::container */
using container::Iterable;
} /* end of namespace ming */

#endif