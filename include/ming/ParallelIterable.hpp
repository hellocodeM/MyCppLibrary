#ifndef MING_CONTAINER_PARALLEL_ITERABLE_HPP
#define MING_CONTAINER_PARALLEL_ITERABLE_HPP

#include <future>
#include <vector>
#include <unistd.h>     /* for sysconf */

#include "operators.hpp"
#include "placeholders.hpp"


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

    
    template <class Init, class Fn, class Pred, class Combine>
    auto fold_if(Init&& init, Fn f, Pred pred, Combine comb) const {
        /* the thread_num depends on the number of CPU cores */
        const size_t thread_num = std::thread::hardware_concurrency();
        auto first = derived->begin();
        auto last = derived->end();
        int interval = std::distance(first, last) / thread_num;
        std::vector<std::future<Init>> fs(thread_num);

        for (int i = 0; i < thread_num; i++) {
            auto start = std::next(first, interval*i);
            auto end = (i == thread_num - 1) ? last : std::next(start, interval);
            fs[i] = std::async(std::launch::async, [=, init=std::forward<Init>(init)]{
                Init res = init;
                for (auto i = start; i != end; ++i) {
                    if (pred(*i))
                        res = std::move(f(std::forward<Init>(res), *i));
                }
                return res;
            });
        }
        Init res = init;
        for (auto&& i : fs)
            res = std::move(comb(res, i.get()));
        return res;
    }

    template <class Init, class Fn>
    constexpr auto fold(Init&& init, Fn f) {
        return derived->fold_if(std::forward<Init>(init), f, [](auto&& x){ return true; }, f);
    }


    template<class Fn>
    constexpr auto map(Fn f) {
        using namespace ming::placeholders;
        using item_type = decltype(f(head()));
        using container_type = typename Derived::template container<item_type>::type;
        return derived->fold_if(container_type(), [f](auto&& init, auto&& item) {
            init += f(std::forward<decltype(item)>(item));
            return std::move(init);
        }, [](auto&& x) {
            return true;
        }, [](auto&& lhs, auto&& rhs) {
            return lhs += rhs;
        });
    }

    template <class Pred>
    constexpr auto filter(Pred pred) {
        using namespace ming::placeholders;
        return derived->fold_if(Derived(), [](auto&& init, auto&& item) {
            init += std::forward<decltype(item)>(item);
            return std::move(init);
        }, pred, [](auto&& lhs, auto&& rhs) {
            lhs += rhs;
            return std::move(lhs);
        });
    }

    template <class Fn>
    void foreach(Fn f) {
        const size_t thread_num = std::thread::hardware_concurrency();
        auto first = derived->begin();
        auto last = derived->end();
        int interval = std::distance(first, last) / thread_num;
        std::vector<std::future<void>> fs(thread_num);

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
