#ifndef MING_TYPETRAITS_ISFUNCTOR_HPP
#define MING_TYPETRAITS_ISFUNCTOR_HPP

#include <type_traits>

namespace ming{
namespace type_traits {

template <class T>
struct is_functor {
    private:
        template <class C> static std::true_type check(decltype(&C::operator()));
        template <class C> static std::false_type check(...);

    public:
        const static bool value = decltype(check<T>(nullptr))::value;
        using type = std::integral_constant<bool, value>;
};

/**
 * Helper function
 */
template <class T>
using is_functor_t = typename is_functor<T>::type;

} /* end of namespace type_traits */

using type_traits::is_functor;
using type_traits::is_functor_t;
} /* end of namespace ming */
#endif
