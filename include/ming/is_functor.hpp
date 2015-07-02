#ifndef STD_ISFUNCTOR_HPP
#define STD_ISFUNCTOR_HPP

#include <type_traits>

namespace std {
template <class T>
struct is_functor {
    private:
        template <class C> static std::true_type check(decltype(&C::operator())*);
        template <class C> static std::false_type check(...);

    public:
        const static bool value = decltype(check<T>(nullptr))::value;
        using type = std::integral_constant<bool, value>;
};

} /* end of namespace std */
#endif
