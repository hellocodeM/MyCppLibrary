#ifndef STD_HASITERATOR_HPP
#define STD_HASITERATOR_HPP

#include <type_traits>

namespace std {
    template <class T>
    struct has_iterator {
        private:
        template <class C> static std::true_type test(typename C::iterator*);
        template <class C> static std::false_type test(...);

        public:
        const static bool value = std::is_same<decltype(test<T>(0)), std::true_type>::value;
        using type = std::integral_constant<bool, value>;
    };
}

#endif
