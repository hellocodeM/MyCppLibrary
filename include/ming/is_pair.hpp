#ifndef STD_ISPAIR_HPP
#define STD_ISPAIR_HPP

#include <utility>

namespace std {

template <class >
struct is_pair: std::false_type {
};

template <class T, class U>
struct is_pair<std::pair<T, U>>: std::true_type {
};

}
#endif
