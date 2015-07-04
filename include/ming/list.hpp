#ifndef MING_CONTAINER_LIST_HPP
#define MING_CONTAINER_LIST_HPP

#include <list>

#include "Iterable.hpp"

namespace ming {
namespace container {

template <class T>
class list: std::list<T>, Iterable<T, list<T>> {
    using std::list<T>::list;
};


} /* end of namespace ming::container */

using container::list;
} /* end of namespace ming */
#endif 
