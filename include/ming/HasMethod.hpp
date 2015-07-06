#ifndef MING_PP_HASMETHOD_HPP
#define MING_PP_HASMETHOD_HPP


#include <type_traits>

namespace ming {
namespace PP {

/**
 * Check is a class has a specified method, including static function, overloaded function.
 * example: HAS_METHOD(push_back); has_push_back<std::vector<int>, int>::value;
 */
#define HAS_METHOD(M) \
    template <class T, class... Args> \
    struct has_##M { \
        private: \
            template <class C, \
                      class = decltype(std::declval<C>().M(std::declval<Args>()...) )\
                     >  \
                          static std::true_type check(int); \
            template <class C> static std::false_type check(...); \
        public: \
            const static bool value = decltype(check<T>(0))::value; \
            using type = std::integral_constant<bool, value>; \
    }

}

} /* end of namespace ming::PP */
#endif 
