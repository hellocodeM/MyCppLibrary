#ifndef MING_TYPETRAITS_HASITERATOR_HPP
#define MING_TYPETRAITS_HASITERATOR_HPP

#include <type_traits>
#include "HasInnerType.hpp"

namespace ming {
namespace type_traits {

HAS_INNERTYPE(iterator);

} /* end of namespace ming::type_traits */

using type_traits::has_iterator;
} /* end of namespace ming */
#endif
