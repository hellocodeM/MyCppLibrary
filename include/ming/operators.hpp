#ifndef MING_OPERATORS_OPERATOR_HPP
#define MING_OPERATORS_OPERATOR_HPP

#include <type_traits>
#include <utility>

#include "has_iterator.hpp"
#include "underlying.hpp"
#include "HasMethod.hpp"

namespace ming {
namespace operators {

HAS_METHOD(push_back);
template <class Cont,
          class T,
          class Cont_ = typename ming::underlying<Cont>::type,
          class T_ = typename ming::underlying<T>::type
         >
auto operator + (Cont&& lhs, T&& rhs) 
    -> typename std::enable_if<
            ming::has_iterator<Cont_>::value &&
            has_push_back<Cont_, T_>::value &&
            std::is_same<T_, typename Cont_::value_type>::value,
            Cont>::type {
    Cont res = std::forward<Cont>(lhs);
    res.push_back(rhs);
    return res;
}

HAS_METHOD(insert);
template <class Cont,
          class T,
          class Cont_ = typename ming::underlying<Cont>::type,
          class T_ = typename ming::underlying<T>::type
         >
auto operator + (Cont&& lhs, T&& rhs) 
    -> typename std::enable_if<
            ming::has_iterator<Cont_>::value &&
            has_insert<Cont_, T_>::value &&
            std::is_same<T_, typename Cont_::value_type>::value,
            Cont>::type {
    Cont res = std::forward<Cont>(lhs);
    res.insert(rhs);
    return (res);
}

} /* end of namespace ming::operators */
} /* end of namespace ming */

#endif
