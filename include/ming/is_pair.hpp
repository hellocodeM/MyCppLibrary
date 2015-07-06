#ifndef MING_TYPETRAITS_ISPAIR_HPP
#define MING_TYPETRAITS_ISPAIR_HPP

#include <type_traits>
#include <utility>

namespace ming{
namespace type_traits {

template <class >
struct is_pair: std::false_type {
};

template <class T, class U>
struct is_pair<std::pair<T, U>>: std::true_type {
};

template <class T>
using is_pair_t = typename is_pair<T>::type;

} /* end of namespace ming::type_traits */

using type_traits::is_pair;
using type_traits::is_pair_t;
} /* end of namespace ming */
#endif
