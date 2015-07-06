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


} /* end of namespace type_traits */

using type_traits::is_functor;
} /* end of namespace ming */
#endif
