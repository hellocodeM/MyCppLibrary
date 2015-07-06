#ifndef MING_PP_HASINNERTYPE_HPP
#define MING_PP_HASINNERTYPE_HPP

#include <type_traits>

namespace ming {
namespace PP {

#define HAS_INNERTYPE(type) \
    template <class T> \
    struct has_##type { \
        private: \
            template <class U> static std::true_type check(typename U::type*); \
            template <class U> static std::false_type check(...); \
        public: \
            const static bool value = decltype(check<T>(nullptr))::value; \
            using type = std::integral_constant<bool, value>; \
    }

} /* end of namespace ming */
} /* end of namespcae ming::PP */
#endif
