#ifndef MING_LAMBDA_HPP
#define MING_LAMBDA_HPP

#include <iosfwd>
#include <utility>

namespace ming {
namespace placeholders {
    
struct PlaceHolder {
}_, _1, _2;

#define LAMBDA1_COMMUTATIVE_OPERATOR(OP) \
    template <class T> \
    auto operator OP (PlaceHolder, T&& rhs) { \
        return [&rhs](auto&& lhs) {  \
            return std::forward<decltype(lhs)>(lhs) OP std::forward<T>(rhs); \
        }; \
    } \
    template <class T> \
    auto operator OP (T&& lhs, PlaceHolder) { \
        return [&lhs](auto&& rhs) { \
            return std::forward<T>(lhs) OP std::forward<decltype(rhs)>(rhs); \
        }; \
    }

/**
 * support for _2 
 */

#define LAMBDA2_COMMUTATIVE_OPERATOR(OP) \
    auto operator OP (PlaceHolder, PlaceHolder) { \
        return [](auto&& lhs, auto&& rhs) { \
            return std::forward<decltype(lhs)>(lhs) OP std::forward<decltype(rhs)>(rhs); \
        }; \
    }

#define LAMBDA_COMMUTATIVE_OPERATOR(OP) \
    LAMBDA1_COMMUTATIVE_OPERATOR(OP) \
    LAMBDA2_COMMUTATIVE_OPERATOR(OP)

#define LAMBDA1_UNCOMMUTATIVE_OPERATOR(OP) \
    template <class T> \
    auto operator OP (PlaceHolder, T&& rhs) { \
        return [&rhs](auto&& lhs) { \
             std::forward<decltype(lhs)>(lhs) OP std::forward<T>(rhs); \
        }; \
    }


#define LAMBDA2_UNCOMMUTATIVE_OPERATOR(OP) \
    auto operator OP (PlaceHolder, PlaceHolder) { \
        return [](auto&& lhs, auto&& rhs) { \
             std::forward<decltype(lhs)>(lhs) OP std::forward<decltype(rhs)>(rhs); \
        }; \
    }

#define LAMBDA_UNCOMMUTATIVE_OPERATOR(OP) \
        LAMBDA1_UNCOMMUTATIVE_OPERATOR(OP) \
        LAMBDA2_UNCOMMUTATIVE_OPERATOR(OP)

LAMBDA_COMMUTATIVE_OPERATOR(+)
LAMBDA_COMMUTATIVE_OPERATOR(-)
LAMBDA_COMMUTATIVE_OPERATOR(*)
LAMBDA_COMMUTATIVE_OPERATOR(/)
LAMBDA_COMMUTATIVE_OPERATOR(%)
LAMBDA_COMMUTATIVE_OPERATOR(&&)
LAMBDA_COMMUTATIVE_OPERATOR(||)
LAMBDA_COMMUTATIVE_OPERATOR(<)
LAMBDA_COMMUTATIVE_OPERATOR(>)
LAMBDA_COMMUTATIVE_OPERATOR(<=)
LAMBDA_COMMUTATIVE_OPERATOR(>=)
LAMBDA_COMMUTATIVE_OPERATOR(!=)
LAMBDA_COMMUTATIVE_OPERATOR(==)
LAMBDA_COMMUTATIVE_OPERATOR(&)
LAMBDA_COMMUTATIVE_OPERATOR(|)
LAMBDA_COMMUTATIVE_OPERATOR(<<)
LAMBDA_COMMUTATIVE_OPERATOR(>>)

LAMBDA_UNCOMMUTATIVE_OPERATOR(&=)
LAMBDA_UNCOMMUTATIVE_OPERATOR(|=)
LAMBDA_UNCOMMUTATIVE_OPERATOR(<<=)
LAMBDA_UNCOMMUTATIVE_OPERATOR(>>=)
LAMBDA_UNCOMMUTATIVE_OPERATOR(+=)
LAMBDA_UNCOMMUTATIVE_OPERATOR(-=)
LAMBDA_UNCOMMUTATIVE_OPERATOR(*=)
LAMBDA_UNCOMMUTATIVE_OPERATOR(/=)
LAMBDA_UNCOMMUTATIVE_OPERATOR(%=)


/**
 * Specialization for opeartor <<
 */
auto operator << (std::ostream& out, PlaceHolder x) {
    return [&out](auto&& x) { out << std::forward<decltype(x)>(x); };
}



/** 
 * Another kind of lambda. Could use the placeholders in arbitrary situation, including function call.
 * @exam: std::for_each(vec.begin(), vec.end(), lamdba(_1 += 1));
 * @exam: std::for_each(vec.begin(), vec.end(), lambda(ming::println(_1)));
 * 
 */

#define lambda(expr) \
    [&](auto&& _) {  \
        return expr;         \
    }

#define lambda1(expr) \
    [&](auto&& _1) { \
        return expr; \
    }

#define lambda2(expr) \
    [&](auto&& _1, auto&& _2) { \
        return expr; \
    }


}
} /* end of namespace ming::lambda */

#endif 
