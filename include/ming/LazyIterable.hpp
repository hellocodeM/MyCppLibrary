#ifndef MING_CONTAINER_LAZYITERABLE_HPP
#define MING_CONTAINER_LAZYITERABLE_HPP

#include <utility>
#include <list>
#include <algorithm>
#include <iterator>
#include <functional>

namespace ming {
namespace container {

template <class Derived>
class LazyIterable {
    public:

    LazyIterable() {
        derived = static_cast<Derived*>(this);
    }

    LazyIterable(const LazyIterable<Derived>& rhs) {
        derived = static_cast<Derived*>(this);
    }

    LazyIterable(LazyIterable<Derived>&& rhs) {
        derived = static_cast<Derived*>(this);
    }

    LazyIterable operator =(const LazyIterable<Derived>& rhs) {
        derived = static_cast<Derived*>(this);
        return *this;
    }

    LazyIterable operator = (LazyIterable<Derived>&& rhs) {
        derived = static_cast<Derived*>(this);
        return *this;
    }

    template <class Init, class Fn, class Pred>
    auto fold_if(Init&& init, Fn f, Pred pred) {
        for (auto&& i: *derived) {
            if (pred(i))
                init = f(init, i);
        }
        return init;
    }

    template <class Init, class Fn>
    auto fold(Init&& init, Fn f) {
        return derived->fold_if(std::forward<Init>(init), f, [](auto&& x){ return true; });
    }

    template<class Fn>
    auto map(Fn f) {
        using result_type = decltype(f(head()));
        using container_type = typename Derived::template container<result_type>::type;
        actions_.push_back([=]{
            derived->fold(container_type(), [f](auto&& init, auto&& item) {
                init += f(std::forward<decltype(item)>(item));
                return init;
            });
        });
        return *this;
    }

    template <class Fn>
    auto filter(Fn f) {
        return derived->fold_if(Derived(), [](auto&& init, auto&& item) {
            init += std::forward<decltype(item)>(item);
            return std::forward<decltype(init)>(init);
        });
    }

    /**
     * These functions will trigger the eval function, and return the result.
     */
    template <class Fn>
    void foreach(Fn f) {
        eval();
        for (auto&& i: *derived)
            f(std::forward<decltype(i)>(i));
    }

    auto take(size_t n) {
        eval();
        const size_t copy_cnt = std::min(n, derived->size());
        auto iter_end = std::next(derived->begin(), copy_cnt);
        Derived res(derived->begin(), iter_end);
        return res;
    }

    auto head() {
        eval();
        return *(derived->begin());
    }

    auto tail() {
        eval();
        auto iter_begin = std::next(derived->begin());
        Derived res(iter_begin, derived->end());
        return res;
    }

    private:
    void eval() {
        while (!actions_.empty()) {
            actions_.back()();
            actions_.pop_back();
        }
    }

    Derived* derived;
    /* store all the actions on the container */
    std::list<std::function<void(void)>> actions_;
};

} /* end of namespace ming::container */

using container::LazyIterable;
} /* end of namespace ming */
#endif
