#ifndef MING_OPERATORS_OPERATOR_HPP
#define MING_OPERATORS_OPERATOR_HPP

#include <type_traits>
#include <utility>

#include "has_iterator.hpp"
#include "underlying.hpp"
#include "HasMethod.hpp"

/**
 * Overloaded operators for containers.
 * It it used for support some universal operation on containers, such as add an element, merge another containers.
 * Without their support, the container itself will has to accomplish the functionality, which is a boring job.
 * Generally, operator += represents add an element or another container to the container which changes the container, and operator + will execute the same movement but return a new-created container.
 * To accomplish the functionality, the operator += will forward the job to push_back member function when the container has a push_back, insert when it has a insert.
 */

namespace ming {
namespace container {

/**
 * Add an element to a container with push_back member function.
 */
HAS_METHOD(push_back);
template <class Cont,
          class T,
          class Cont_ = ming::underlying_t<Cont>,
          class T_ = ming::underlying_t<T>
         >
auto operator += (Cont&& lhs, T&& rhs) 
    -> std::enable_if_t<
            has_push_back<Cont_, T_>::value,
            std::add_lvalue_reference_t<Cont>> {
    lhs.push_back(rhs);
    return lhs;
}

/**
 * Add an element to a container with push_back.
 */
template <class Cont,
          class T,
          class Cont_ = ming::underlying_t<Cont>,
          class T_ = ming::underlying_t<T>
         >
auto operator + (Cont&& lhs, T&& rhs) 
    -> std::enable_if_t<
            has_push_back<Cont_, T_>::value,
            std::remove_reference_t<Cont>> {
    return Cont_(std::forward<Cont>(lhs)) += rhs;
}

/**
 * Add an element to a container with push_back.
 */
template <class T,
          class Cont,
          class T_ = ming::underlying_t<T>,
          class Cont_ = ming::underlying_t<Cont>
         >
auto operator + (T&& lhs, Cont&& rhs) 
    -> std::enable_if_t<
            has_push_back<Cont_, T_>::value,
            std::remove_reference_t<Cont>> {
    return Cont_(std::forward<Cont>(rhs)) += lhs;
}

/**
 * Merge two containers with push_back member function.
 */
template <class LHS,
          class RHS,
          class LHS_ = ming::underlying_t<LHS>,
          class RHS_ = ming::underlying_t<RHS>,
          class LT_  = ming::underlying_t<typename LHS_::value_type>,
          class RT_  = ming::underlying_t<typename RHS_::value_type>
         >
auto operator += (LHS&& lhs, RHS&& rhs) 
    -> std::enable_if_t<
            ming::has_iterator<LHS_>::value &&
            ming::has_iterator<RHS_>::value &&
            std::is_same<LT_, RT_>::value   &&
            has_push_back<LHS_, typename RHS_::value_type>::value,
            std::add_lvalue_reference_t<LHS_>> {
    std::copy(rhs.begin(), rhs.end(), std::back_inserter(lhs));
    return lhs;
}

/**
 * Merge two containers with push_back member function.
 */
template <class LHS,
          class RHS,
          class LHS_ = ming::underlying_t<LHS>,
          class RHS_ = ming::underlying_t<RHS>,
          class LT_  = ming::underlying_t<typename LHS_::value_type>,
          class RT_  = ming::underlying_t<typename RHS_::value_type>
         >
auto operator + (LHS&& lhs, RHS&& rhs) 
    -> std::enable_if_t<
            ming::has_iterator<LHS_>::value &&
            ming::has_iterator<RHS_>::value &&
            std::is_same<LT_, RT_>::value   &&
            has_push_back<LHS_, typename RHS_::value_type>::value,
            std::remove_reference_t<LHS>> {
    return LHS_(std::forward<LHS>(lhs)) += std::forward<RHS>(rhs);
}


/**
 * Add an element to a container with insert memeber function.
 */
HAS_METHOD(insert);
template <class Cont,
          class T,
          class Cont_ = ming::underlying_t<Cont>,
          class T_ = ming::underlying_t<T>
         >
auto operator += (Cont&& lhs, T&& rhs) 
    -> std::enable_if_t<
            has_insert<Cont_, T_>::value,
            std::add_lvalue_reference_t<Cont>> {
    lhs.insert(std::forward<T>(rhs));
    return lhs;
}

/**
 * Merge two containers with insert member function.
 */
template <class LHS,
          class RHS,
          class LHS_ = ming::underlying_t<LHS>,
          class RHS_ = ming::underlying_t<RHS>,
          class LT_  = ming::underlying_t<typename LHS_::value_type>,
          class RT_  = ming::underlying_t<typename RHS_::value_type>
         >
auto operator += (LHS&& lhs, RHS&& rhs) 
    -> std::enable_if_t<
            ming::has_iterator<LHS_>::value &&
            ming::has_iterator<RHS_>::value &&
            has_insert<LHS_, RT_>::value,
            std::add_lvalue_reference_t<LHS>> {
    for (auto&& i : rhs) {
        lhs.insert(std::forward<decltype(i)>(i));
    }
    return lhs;
}

template <class Cont,
          class T,
          class Cont_ = ming::underlying_t<Cont>,
          class T_ = ming::underlying_t<T>
         >
auto operator + (Cont&& lhs, T&& rhs) 
    -> std::enable_if_t<
            has_insert<Cont_, T_>::value,
            std::remove_reference_t<Cont>> {
    return Cont_(std::forward<Cont>(lhs)) += rhs;
}

template <class Cont,
          class T,
          class Cont_ = ming::underlying_t<Cont>,
          class T_ = ming::underlying_t<T>
         >
auto operator + (T&& lhs, Cont&& rhs) 
    -> std::enable_if_t<
            has_insert<Cont_, T_>::value,
            std::remove_reference_t<Cont>> {
    return rhs + lhs;
}



/**
 * Merge two containers with insert member function.
 */
template <class LHS,
          class RHS,
          class LHS_ = ming::underlying_t<LHS>,
          class RHS_ = ming::underlying_t<RHS>,
          class LT_  = ming::underlying_t<typename LHS_::value_type>,
          class RT_  = ming::underlying_t<typename RHS_::value_type>
         >
auto operator + (LHS&& lhs, RHS&& rhs) 
    -> std::enable_if_t<
            ming::has_iterator<LHS_>::value &&
            ming::has_iterator<RHS_>::value &&
            std::is_same<LT_, RT_>::value   &&
            has_insert<LHS_, typename RHS_::value_type>::value,
            std::remove_reference_t<LHS>> {
    return LHS_(std::forward<LHS>(lhs)) += rhs;
}

} /* end of namespace ming::container */
} /* end of namespace ming */

#endif
