#ifndef MING_TYPETRAITS_HASITERATOR_HPP
#define MING_TYPETRAITS_HASITERATOR_HPP

#include <type_traits>
#include "HasInnerType.hpp"

namespace ming {
namespace type_traits {

HAS_INNERTYPE(iterator);

template <class T>
using has_iterator_t = typename has_iterator<T>::type;
} /* end of namespace ming::type_traits */

using type_traits::has_iterator;
using type_traits::has_iterator_t;
} /* end of namespace ming */
#endif
