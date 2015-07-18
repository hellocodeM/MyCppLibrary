#ifndef MING_CONTAINER_PARALLEL_ITERABLE_HPP
#define MING_CONTAINER_PARALLEL_ITERABLE_HPP

#include <future>

#include "operators.hpp"


namespace ming {
namespace container {

template <class Derived>
class ParallelIterable {
    public:

    ParallelIterable() {
        derived = static_cast<Derived*>(this);
    }

    ParallelIterable(const ParallelIterable& pi) :ParallelIterable() { }
    ParallelIterable(ParallelIterable&& pi): ParallelIterable() {}

    ParallelIterable operator = (const ParallelIterable<Derived>& rhs) {
        derived = static_cast<Derived*>(this);
        return *this;
    }

    ParallelIterable operator = (ParallelIterable<Derived>& rhs) {
        derived = static_cast<Derived*>(this);
        return *this;
    }

    
    template <class Init, class Fn, class Pred>
    constexpr auto fold_if(Init&& init, Fn f, Pred pred) {
        constexpr int thread_num = 4;
        auto first = derived->begin();
        auto last = derived->end();
        int interval = std::distance(first, last) / thread_num;
        std::future<Init> fs[thread_num];

        for (int i = 0; i < thread_num; i++) {
            auto start = std::next(first, interval*i);
            auto end = (i == thread_num - 1) ? last : std::next(start, interval);
            fs[i] = std::async(std::launch::async, [=, init=std::forward<Init>(init)]{
                Init res = init;
                for (auto i = start; i != end; ++i) {
                    if (pred(*i))
                        res = f(std::forward<Init>(res), *i);
                }
                return res;
            });
        }
        Init res = init;
        for (auto&& i : fs)
            res += i.get();
        return res;
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
            init += f(std::forward<decltype(item)>(item));
            return std::move(init);
        });
    }

    template <class Pred>
    constexpr auto filter(Pred pred) {
        return derived->fold_if(Derived(), [](auto&& init, auto&& item) {
            init += std::forward<decltype(item)>(item);
            return std::move(init);
        }, pred);
    }

    template <class Fn>
    void foreach(Fn f) {
        constexpr int thread_num = 4;
        auto first = derived->begin();
        auto last = derived->end();
        int interval = std::distance(first, last) / thread_num;
        std::future<void> fs[4];

        for (int i = 0; i < thread_num; i++) {
            auto start = std::next(first, interval * i);
            auto end = (i == thread_num - 1) ? last : std::next(start, interval);
            fs[i] = std::async(std::launch::async, [=] {
                for (auto i = start; i != end; ++i)
                    f(*i);
            });
        }
        for (auto&& i: fs)
            i.wait();
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

using container::ParallelIterable;
} /* end of namespace ming */
#endif
