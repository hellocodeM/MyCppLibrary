#ifndef MING_TYPETRAITS_UNDERLYING_HPP
#define MING_TYPETRAITS_UNDERLYING_HPP

#include <type_traits>

namespace ming {
namespace type_traits {

template <class T>
struct underlying: std::remove_cv<std::remove_reference_t<T>> {
};

template <class T>
using underlying_t = typename underlying<T>::type;
} /* end of namespace ming::type_traits */

using type_traits::underlying;
using type_traits::underlying_t;
} /* end of namespace ming */
#endif
