#ifndef MING_TYPETRAITS_UNDERLYING_HPP
#define MING_TYPETRAITS_UNDERLYING_HPP

namespace ming {

namespace type_traits {
template <class T>
struct underlying: std::remove_cv<typename std::remove_reference<T>::type> {
};


} /* end of namespace ming::type_traits */

using type_traits::underlying;
} /* end of namespace ming */
#endif
